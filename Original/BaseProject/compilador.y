
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.

// Ainda precisa de suporte para booleanos


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "utils/tabela_simb.h"
#include "utils/pilha_rotulos.h"
#include "utils/pilha_tipos.h"

int num_vars;
int num_params; // número de parâmetros do procedimento atual
int num_params_secao; // número de parâmetros da seção atual => seção é aquela separada por ';'
int num_params_chamada;
int nivel_lex;
int pos_var;
int qt_tipo_atual;
int referencia; // indica se a seção atual é por referência, se não for, é por cópia, auxilia nas verificacoes se eh ARMI e CRVI
int dentro_chamada_proc; // indica se está dentro de uma chamada de procedimento
int num_subprocs_proc_atual; // numero de sub processo contidos no processo atual
int atribui;

char buffer_mepa[128], proc_name[128], idents[128][128];
tabela_de_simbolos_t *ts, *pilha_atribuicao;
simbolo_t s, *sptr, *sptr_var_proc, *sptr_chamada_proc, *sptr_atribuicao, proc_atual, lista_simbolos[128];

struct pilha_rotulos pilha_rotulos, pilha_amem, pilha_procs; // pilha para o rotulo, calculo dos amem e para os procedimentos
struct pilha_tipos pilha_ident_esquerdo;
struct parametro lista_parametros[128]; 
struct cat_conteudo ti;

int str2token(const char *str){
   if (!strcmp(str, "integer")) return INTEGER_S;
   if (!strcmp(str, "boolean")) return BOOLEAN_S;
   return UNDEFINED_S;
}
short int proc_subnivel; // para o desvio de sub procedures dentro das procedures
char rot_str[4];
int rot_w;

%}

%token PROGRAM LABEL TYPE ARRAY OF VAR 
%token PROCEDURE FUNCTION T_BEGIN T_END GOTO IF
%token THEN ELSE WHILE DO OR AND NOT
%token DIV ATRIBUICAO PONTO_E_VIRGULA
%token DOIS_PONTOS VIRGULA PONTO
%token ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_COLCHETES FECHA_COLCHETES
%token ABRE_CHAVES FECHA_CHAVES
%token IDENT MAIOR MENOR IGUAL MAIS MENOS
%token VEZES NUMERO DIFERENTE MENOR_IGUAL
%token MAIOR_IGUAL VALOR_BOOL TIPO READ WRITE

// Obs: Para declarar mais tipos de retorno se necessario adicionar aqui e colocar no type o retorno necessario
%union{
   char * str_value;  // define o tipo str
   int int_value; // define o tipo int_val
   struct simbolo_t *simb;
}

%type <int_value> expressao;
%type <int_value> expressao_simples;
%type <str_value> mais_menos_or; // numa expressão
%type <str_value> mais_menos_vazio; // antes de um fator
%type <int_value> numero; 
%type <int_value> fator;
%type <str_value> relacao;
%type <int_value> termo;
%type <int_value> tipo;
%type <int_value> variavel; // atribui o tipo str a regra variavel
%type <str_value> vezes_div_and;

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

/* 
   REGRA 01
   <programa> ::=
   program <identificador> (<lista de identificadores>);      
      <bloco>. 
*/
programa    :
            PROGRAM IDENT
            {
             geraCodigo (NULL, "INPP");
             nivel_lex = 0;
             proc_subnivel = 0;
             dentro_chamada_proc = 0;
             }
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             geraCodigo (NULL, "PARA");
             }
;

/* 
   REGRA 02  
   <bloco> ::=
      [<parte de declarações de rótulos>] 
      [<parte de definições de tipos>]
      [<parte de declarações de variáveis>]
      [<parte de declarações de sub-rotinas>] 
      <comando composto> 
*/
bloco       :
              parte_declara_vars
              {
               sprintf(buffer_mepa, "DSVS R%02d", proc_subnivel);
               geraCodigo(NULL, buffer_mepa);
               pilha_rotulos_empilhar(&pilha_rotulos, proc_subnivel);
               proc_subnivel++;
               nivel_lex++;
               num_subprocs_proc_atual = 0;
              }
              parte_declara_subrotinas
              {
               pilha_rotulos_empilhar(&pilha_procs, num_subprocs_proc_atual);
               nivel_lex--;

               sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos));
               geraCodigo(rot_str, "NADA");
               pilha_rotulos_desempilhar(&pilha_rotulos);
              }
              comando_composto
              {
               sprintf(buffer_mepa, "DMEM %d", pilha_rotulos_topo(&pilha_amem)); 
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_amem)); // Removo os pilha_rotulos_topo(&pilha_amem) elemento da tabela
               geraCodigo(NULL, buffer_mepa);
               pilha_rotulos_desempilhar(&pilha_amem);   // desempilho os rotulos removido s
              }
;

/* 
   REGRA 6
   <tipo> ::=
    <identificador>|
    array [<índice> {, <índice>}] of <tipo> 
*/
tipo        : TIPO { $$ = str2token(token); } // converte o token de tipo recebido e retorna
;

/* 
   REGRA 08
   <parte de declarações de variáveis> ::= 
    var <declaração de variáveis>
        {; <declaração de variáveis>}; 
*/
parte_declara_vars: { num_vars = 0; } // inicializacao do num_vars como 0
            VAR declara_vars { 
               sprintf(buffer_mepa, "AMEM %d", num_vars);
               geraCodigo(NULL, buffer_mepa);

               pilha_rotulos_empilhar(&pilha_amem, num_vars);
            }
            | {pilha_rotulos_empilhar(&pilha_amem, 0);}
;


declara_vars: declara_vars declara_var
            | declara_var
;

/*
   REGRA 09
   <declaracao de variaveis> ::=
      <lista de identificadores>: <tipo> 
*/
declara_var : { qt_tipo_atual = 0; }
              lista_id_var DOIS_PONTOS tipo
              { atribui_tipo(&ts, VARIAVEL_S, $4, qt_tipo_atual); } // atribue a variavel da tabela de simbolos a categoria VARIAVEL e o tipo dela conforme definido
              PONTO_E_VIRGULA
;

lista_id_var: lista_id_var VIRGULA IDENT {
               ti.var.deslocamento = num_vars;
               s = cria_simbolo(token, VARIAVEL_S, nivel_lex, ti); 
               insere_tabela(&ts, s);
               num_vars++; qt_tipo_atual++;
            }
            | IDENT { 
               ti.var.deslocamento = num_vars;
               s = cria_simbolo(token, VARIAVEL_S, nivel_lex, ti); 
               insere_tabela(&ts, s);
               num_vars++; 
               qt_tipo_atual++;
            }
;

/* 
   REGRA 10
   <lista de identificadores> ::= 
      <identificador> {, <identificador>} 
*/
lista_idents: 
              lista_idents 
              VIRGULA  // mais que um identificador separados por virgula
              ident_params 
            | ident_params // apenas um identificador
;

ident_params: 
              IDENT 
              {
               strcpy(idents[num_params], token);
               lista_parametros[num_params].passagem = referencia ? PARAMETRO_REF_S : PARAMETRO_COPIA_S;
               num_params++;  // incrementa numero de parametros conforme a lista de identificadores
               num_params_secao++;    
              }
;


/* 
   REGRA 11
   <parte de declarações de sub-rotinas> ::=
    {<declaração de procedimento>; |
    <declaração de função> ;} 
*/
parte_declara_subrotinas: 
                           parte_declara_subrotinas declara_proc {num_subprocs_proc_atual++;} PONTO_E_VIRGULA
                          | parte_declara_subrotinas declara_func PONTO_E_VIRGULA
                          | comando_vazio
;

/*
   REGRA 12
   declaração de procedimento> ::=
      procedure <identificador>
         [<parâmetros formais>]: <bloco> */
declara_proc: PROCEDURE 
              IDENT
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
              parametros_formais_ou_vazio
              {
               sprintf(rot_str, "R%02d", proc_subnivel);
               sprintf(buffer_mepa, "ENPR %d", nivel_lex);
               geraCodigo(rot_str, buffer_mepa);
               
               ti.proc.rotulo = proc_subnivel;
               ti.proc.qtd_parametros = num_params;
               memcpy(ti.proc.lista, lista_parametros, sizeof(struct parametro)*num_params);
               s = cria_simbolo(proc_name, PROCEDIMENTO_S, nivel_lex, ti);
               insere_tabela(&ts, s);

               // atribui o deslocamento correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  lista_simbolos[i].conteudo.param.deslocamento = -TAM_INT + (i - (num_params-1)); 
                  insere_tabela(&ts, lista_simbolos[i]);
               }
               proc_subnivel++;
		         // Adiciona rotulos na pilha
               pilha_rotulos_empilhar(&pilha_amem, num_params);
              }

              PONTO_E_VIRGULA 
              bloco 
              {
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_amem)); // remove da pilha de amem os n rotulos ja empilhados
               sprintf(buffer_mepa, "RTPR %d, %d", nivel_lex, pilha_rotulos_topo(&pilha_amem));
               pilha_rotulos_desempilhar(&pilha_amem);
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_procs));
               pilha_rotulos_desempilhar(&pilha_procs);
               geraCodigo(NULL, buffer_mepa);
              }
;

 /* 
   REGRA 13
   <declaração de função> ::=
    function <identificador>
        [<parâmetros formais>]: <identificador> ;
         <bloco> 
*/

declara_func: FUNCTION
              IDENT
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
              parametros_formais_ou_vazio
              
              DOIS_PONTOS
              tipo
              {
               sprintf(rot_str, "R%02d", proc_subnivel);
               sprintf(buffer_mepa, "ENPR %d", nivel_lex);
               geraCodigo(rot_str, buffer_mepa);
               ti.proc.rotulo = proc_subnivel;
               ti.proc.qtd_parametros = num_params;
               memcpy(ti.proc.lista, lista_parametros, sizeof(struct parametro)*num_params);
               ti.var.tipo = $6;
               ti.var.deslocamento = -TAM_INT - num_params;
               s = cria_simbolo(proc_name, FUNCAO_S, nivel_lex, ti);
               insere_tabela(&ts, s);

               // atribui o deslocamento correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  lista_simbolos[i].conteudo.param.deslocamento = -TAM_INT + (i - (num_params-1)); 
                  insere_tabela(&ts, lista_simbolos[i]);
               }
               proc_subnivel++; 
               pilha_rotulos_empilhar(&pilha_amem, num_params);
              }
              PONTO_E_VIRGULA

              bloco
              {
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_amem));
               sprintf(buffer_mepa, "RTPR %d, %d", nivel_lex, pilha_rotulos_topo(&pilha_amem));
               pilha_rotulos_desempilhar(&pilha_amem);
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_procs));
               pilha_rotulos_desempilhar(&pilha_procs);
               geraCodigo(NULL, buffer_mepa);
              }
;

/* 
   REGRA 14
   <parâmetros formais> ::=
    (<seção de parâmetros formais> 
    {: <seção de parâmetros formais>}) */
parametros_formais_ou_vazio: parametros_formais | comando_vazio;


parametros_formais: ABRE_PARENTESES
                     parametros
                    FECHA_PARENTESES
;

parametros: parametros PONTO_E_VIRGULA secao_parametros_formais | secao_parametros_formais
;

/* 
   REGRA 15
   <seção de parâmetros formais> ::=
      [var] <lista de identificadores>:<identificador> | 
      function <lista de identificadores>:<identificador | 
      procedure <lista de identificadores> 
*/

secao_parametros_formais : var_ou_vazio
                   {num_params_secao = 0;}
                   lista_idents 
                   DOIS_PONTOS 
                   tipo
                   {
                     // atribui tipo para os parâmetros dessa seção e coloca numa lista de símbolos a serem empilhados
                     for(int i = num_params-num_params_secao; i < num_params; ++i){
                        ti.param = lista_parametros[i];
                        ti.param.tipo = $5;
                        lista_simbolos[i] = cria_simbolo(idents[i], PARAMETRO_S, nivel_lex, ti);
                     }
                   }                   
;

/* lembrando que no pascal, caso seja VAR nome_variavel eh por referencia, senao copia */
var_ou_vazio: VAR {referencia = 1;} | {referencia = 0;} ;

/* 
   REGRA 16
   <comando composto> ::=
      begin <comando>{;<comando>} end  
*/
comando_composto: T_BEGIN comandos T_END 
;

/* 
   REGRA 17
   <comando> ::=
    [<número>:]<comando sem rótulo> */
comandos: comando_sem_rotulo | comandos PONTO_E_VIRGULA comando_sem_rotulo;

comando_vazio:;

/* 
   REGRA 18
   <comando sem rótulo> ::=
    <atribuição>
    |<chamada de procedimento>
    |<desvio>
    |<comando composto>
    |<comando condicional>
    |<comando repetitivo>
*/
comando_sem_rotulo: 
                  atribuicao_proc
                  | comando_composto
                  | comando_condicional
                  | comando_repetitivo 
                  | escrita
                  | leitura
;


/*
   REGRA 19
    <atribuição> ::=
    <variável>:= <expressão> 
*/
atribuicao_proc:  
                  IDENT 
                  { 
                     sptr_var_proc = busca_simbolo(&ts, token); 
                     pilha_tipos_empilhar(&pilha_ident_esquerdo, sptr_var_proc); // empilho nos tipos o simbolo buscado
                  } 
                  a_continua
                  { 
                     pilha_tipos_desempilhar(&pilha_ident_esquerdo);
                  };

a_continua: ATRIBUICAO {atribui = 1;} atribuicao {atribui = 0;} |
            procedimento_sem_parametro |
            chama_procedimento;

atribuicao: 
   expressao {
   sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);
   // verifica se o tipo da variavel eh compativel com a expressao
   if(sptr_var_proc->conteudo.var.tipo != $1){ 
      fprintf(stderr, "ERRO:\n Tipo da variável é incompatível com o tipo da expressão. \n" ); 
      exit(1);
   }

   // conforme a categoria do tipo corrente 
   if (sptr_var_proc->categoria == VARIAVEL_S)
      sprintf(buffer_mepa, "ARMZ %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.var.deslocamento); // se variavel ARMZ nivel, deslocamento_variaveis
   else if (sptr_var_proc->categoria == PARAMETRO_S){ // caso seja por parametro pode ser por copia 
      if (sptr_var_proc->conteudo.param.passagem == PARAMETRO_COPIA_S)
         sprintf(buffer_mepa, "ARMZ %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.param.deslocamento); // se parametro copia ARMZ nivel, deslocamento_parametros
      else   // ou pode ser por referencia
         sprintf(buffer_mepa, "ARMI %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.param.deslocamento); // como eh por referencia aqui devemos armazenar indiretamente usando ARMI
   } else if (sptr_var_proc->categoria == FUNCAO_S){
         sprintf(buffer_mepa, "ARMZ %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.var.deslocamento); // ARMZ nivel, deslocamento_vars
   } else {
      fprintf(stderr, "ERRO:\n Procedimento atribuido a uma variável!\n"); // procedimento sendo atribuido a variavel 
      exit(1);
   }
   geraCodigo(NULL, buffer_mepa);
}
;


/* 
   REGRA 20
   <chamada de procedimento> ::= 
    <identificador> [(<lista de expressões>)] 
*/
chama_procedimento:
             {
               sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);

              if(!sptr_var_proc){
                  fprintf(stderr, "ERRO:\n Procedimento não encontrado.\n"); 
                  exit(1);
              }
              sptr_atribuicao = sptr_var_proc;
              memcpy(&proc_atual, sptr_var_proc, sizeof(simbolo_t));

              if(proc_atual.categoria == FUNCAO_S ){
                  geraCodigo(NULL, "AMEM 1");
              }
              sprintf(proc_name, "CHPR R%02d, %d", sptr_var_proc->conteudo.proc.rotulo, nivel_lex);
             } 
             ABRE_PARENTESES 
             {
               num_params_chamada = 0;
               dentro_chamada_proc++;
             }
             lista_expressoes
             FECHA_PARENTESES
             {
               dentro_chamada_proc--;
               if(num_params_chamada != proc_atual.conteudo.proc.qtd_parametros){
                   fprintf(stderr, "ERRO:\n Quantidade incorreta de parametros esperado %d recebido %d.\n",proc_atual.conteudo.proc.qtd_parametros,num_params_chamada); 
                   exit(1);
               }
               geraCodigo(NULL, proc_name);
             }
;

procedimento_sem_parametro:
              {
               sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);
               if(!sptr_var_proc){
                  fprintf(stderr, "ERRO:\n Procedimento não encontrado.\n"); 
                  exit(1);
               }
               sprintf(buffer_mepa, "CHPR R%02d, %d", sptr_var_proc->conteudo.proc.rotulo, nivel_lex);
               geraCodigo(NULL, buffer_mepa);
              }


/*
   REGRA 22
   <comando condicional> ::=
    if <expressão> then <comando sem rótulo>
        [else <comando sem rótulo>] 
*/

comando_condicional: IF expressao {
                        if ($2 != BOOLEAN_S){
                           fprintf(stderr, "ERRO:\n Expressão do If não é booleana!\n");
                           exit(1);
                        }

                        sprintf(buffer_mepa, "DSVF R%02d", proc_subnivel+1);
                        geraCodigo(NULL, buffer_mepa);

                        pilha_rotulos_empilhar(&pilha_rotulos, proc_subnivel);
                        proc_subnivel += 2;
                     }  
                     THEN
                     comando_sem_rotulo {
                        sprintf(buffer_mepa, "DSVS R%02d", pilha_rotulos_topo(&pilha_rotulos));
                        geraCodigo(NULL, buffer_mepa);

                        sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos)+1);
                        geraCodigo(rot_str, "NADA");

                     } 
                      else_ou_vazio {
                        sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos));
                        geraCodigo(rot_str, "NADA");
                        pilha_rotulos_desempilhar(&pilha_rotulos);
                     }
;

else_ou_vazio: ELSE comando_sem_rotulo  | %prec LOWER_THEN_ELSE;

/* 
   REGRA 23
   <comando repetitivo> ::=
      while <expressão> do <comando sem rótulo> 
*/
comando_repetitivo:  WHILE {
                        pilha_rotulos_empilhar(&pilha_rotulos, proc_subnivel);
                         
                        sprintf(rot_str, "R%02d", proc_subnivel);
                        geraCodigo(rot_str, "NADA");
                        proc_subnivel += 2;
                     }
                     expressao {
                        sprintf(buffer_mepa, "DSVF R%02d", pilha_rotulos_topo(&pilha_rotulos)+1);
                        geraCodigo(NULL, buffer_mepa); 
                     }
                     DO 
                     comando_sem_rotulo {
                        sprintf(buffer_mepa, "DSVS R%02d", pilha_rotulos_topo(&pilha_rotulos));
                        geraCodigo(NULL, buffer_mepa);
                        sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos)+1);
                        geraCodigo(rot_str, "NADA");
                        pilha_rotulos_desempilhar(&pilha_rotulos);
                     }
;


/* 
   Regra 24
   <lista de expressões> ::= 
    <expressão> {, <expressão>} 
*/
lista_expressoes:  expressao
                  {  
                     num_params_chamada++;   // conforme a lista de expressoes incrementados a quantidade de parametros da expressao
                  } 
                  VIRGULA 
                  lista_expressoes 
                  | expressao 
                  {
                     num_params_chamada++;
                  };

/*
   REGRA 25
   <expressão> ::=
      <expressão simples>[<relação><expressão simples>] 
*/
expressao   : expressao_simples { $$ = $1; } 
            | expressao_simples relacao expressao_simples{
               // verifica se o tipos das variaveis a serem comparadas sao compativeis
               if ($1 != $3){
                  fprintf(stderr, "ERRO:\n Comparação entre expressões de tipos diferentes!\n");
                  exit(1);
               }
               geraCodigo(NULL, $2);
               $$ = BOOLEAN_S;
            }
;

/* 
   REGRA 26
   <relação> ::= =|<>|<|<=|>=|> 
*/
relacao  : IGUAL        { $$ = "CMIG"; }  // Retornar o tipo para que quem chamou a regra verifique se pode ser usada essa relacao
         | DIFERENTE    { $$ = "CMDG"; }
         | MENOR        { $$ = "CMME"; }
         | MENOR_IGUAL  { $$ = "CMEG"; }
         | MAIOR_IGUAL  { $$ = "CMAG"; }
         | MAIOR        { $$ = "CMMA"; }
;

 /*
   REGRA 27
   <expressão simples> ::=
    [+|-] <termo>{(+|-|or) <termo>} 
*/
expressao_simples : expressao_simples mais_menos_or termo {
                     if (strcmp($2, "DISJ") == 0){
                        // caso seja uma disjuncao verifica se ambos os tipos sao booleanos
                        if ($1 != BOOLEAN_S || $3 != BOOLEAN_S){
                           fprintf(stderr, "ERRO:\n Operação booleana entre operandos não booleanos!\n");
                           exit(1);
                        }
                        $$ = BOOLEAN_S;
                     }
                     else {
                        if ($1 != INTEGER_S || $3 != INTEGER_S){
                           fprintf(stderr, "ERRO:\n Operação de inteiros com operandos não inteiros!\n");
                           exit(1);
                        }
                        $$ = INTEGER_S;
                     }
                     
                     geraCodigo(NULL, $2); // gera codigo DISJ
                  }
                  | mais_menos_vazio termo{
                     if ( strcmp($1, "VAZIO") != 0){
                        if ($2 != INTEGER_S){
                           fprintf(stderr, "ERRO:\n Operação inválida, esperado inteiros.\n");
                           exit(1);
                        }else{
                           $$ = INTEGER_S;
                        }
                     } else {
                        $$ = $2;
                     }
                     
                     if ( strcmp($1, "MENOS") == 0 )
                        geraCodigo(NULL, "INVR");
                  } 
;

mais_menos_vazio  : MAIS  { $$ = "MAIS"; }
                  | MENOS { $$ = "MENOS"; }
                  |       { $$ = "VAZIO"; }
;

mais_menos_or  : MAIS { $$ = strdup("SOMA"); }
               | MENOS { $$ = strdup("SUBT"); } 
               | OR { $$ = strdup("DISJ"); }
; 

/*
REGRA 28
   <termo> ::=
      <fator> {(*|div|and) <fator>} */
termo : termo vezes_div_and fator { 
         if (strcmp($2, "CONJ") == 0){
            // caso seja uma conjuncao verificamos se ambos os tipos sao booleanos
            if ($1 != BOOLEAN_S || $3 != BOOLEAN_S){
               fprintf(stderr, "ERRO:\n Operação booleana entre operandos não booleanos!\n");
               exit(1);
            }
            $$ = BOOLEAN_S;
         }
         else {
            if ($1 != INTEGER_S || $3 != INTEGER_S){
               fprintf(stderr, "ERRO:\n Operação de inteiros com operandos não inteiros!\n");
               exit(1);
            }
            $$ = INTEGER_S;
         }
         geraCodigo(NULL, $2);
      }
      | fator
;

vezes_div_and  : VEZES { $$ = strdup("MULT"); }
               | DIV { $$ = strdup("DIVI"); }
               | AND { $$ = strdup("CONJ"); }
;

procedimento_ou_vazio: chama_procedimento {
                        sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);
                        pilha_tipos_desempilhar(&pilha_ident_esquerdo);
                     }
                     | comando_vazio {

                        sptr = pilha_tipos_topo(&pilha_ident_esquerdo); 
                        pilha_tipos_desempilhar(&pilha_ident_esquerdo); 
                     };

/* 
   REGRA 29 -- TODO VERIFICAR
   <fator>::=
    <variável>
    |<número>
    |<chamada de função>
    |(<expressão>)
    |not <fator> 
*/
fator : 
         variavel
         procedimento_ou_vazio { 

         if(!sptr){
            fprintf(stderr, "ERRO: Variável não encontrada!\n");
            exit(1);
         }
         
         $$ = sptr->conteudo.var.tipo;

         int proximo = 0;
         if (sptr->categoria == VARIAVEL_S){
            if (dentro_chamada_proc){
               if (num_params_chamada >= sptr_var_proc->conteudo.proc.qtd_parametros){ // se a localizacao desse parametro no procedimento excede a quantidade declarada
                  fprintf(stderr, "ERRO: Excesso de parâmetros em chamada de procedimento!\n");
                  exit(1);
               }
               if (sptr_var_proc->conteudo.proc.lista[num_params_chamada].passagem == PARAMETRO_REF_S){
                  sprintf(buffer_mepa, "CREN %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);   // se o tipo desse paramtro for por referencia entao CREN
               }
               else if (sptr_var_proc->conteudo.proc.lista[num_params_chamada].passagem == PARAMETRO_COPIA_S){
                  sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
               } 

            } else if (sptr_var_proc && sptr_var_proc->categoria != FUNCAO_S){
               sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
            } else if (atribui && (sptr_var_proc && sptr_var_proc->categoria == FUNCAO_S) && sptr_atribuicao->categoria != FUNCAO_S){
               sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
            } else {
               proximo = 1;
            }

         }
         else if (sptr->categoria == PARAMETRO_S){
            if (sptr->conteudo.param.passagem == PARAMETRO_COPIA_S)
               sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.param.deslocamento);
            else {
               if(sptr_var_proc->conteudo.proc.lista[num_params_chamada].passagem == PARAMETRO_REF_S){
                  sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.param.deslocamento);
               } else {
                  sprintf(buffer_mepa, "CRVI %d, %d", sptr->nivel, sptr->conteudo.param.deslocamento); 
               }
            }
         } else if (sptr->categoria != FUNCAO_S){
            fprintf(stderr, "ERRO: Procedimento tratado como variável!!\n");
            exit(1);
         } else {
            proximo = 1;
         }
         if(!proximo)
            geraCodigo(NULL, buffer_mepa);
      }; 
      | numero
      | VALOR_BOOL {
         $$ = BOOLEAN_S;
         if(strcmp(token, "True") == 0)
            sprintf (buffer_mepa, "CRCT %d", 1);
         else
            sprintf (buffer_mepa, "CRCT %d", 0);
         geraCodigo(NULL, buffer_mepa);
      }
      | ABRE_PARENTESES expressao FECHA_PARENTESES { $$ = $2; }
      | NOT fator {
         if ($2 != BOOLEAN_S){
            fprintf(stderr, "ERRO: Operação booleana entre operandos não booleanos!\n");
            exit(1);
         }
         $$ = BOOLEAN_S;
         geraCodigo(NULL, "NEGA");
       }
;

/* 
   REGRA 30
   <variável> ::=
      <identificador>
      |<identificador> [<lista de expressões>] */
variavel:   
         IDENT
         {
            sptr = busca_simbolo(&ts, token);
            pilha_tipos_empilhar(&pilha_ident_esquerdo, busca_simbolo(&ts, token));
         }; 


/* 
32. <número> ::=
    <dígito>{<dígito>} 
*/
numero: NUMERO {
         $$ = INTEGER_S;
         sprintf (buffer_mepa, "CRCT %d", atoi(token));
         geraCodigo(NULL, buffer_mepa);
      }


/////// Regras sem regras
leitura : READ ABRE_PARENTESES leitura_itens FECHA_PARENTESES;

leitura_itens: leitura_itens VIRGULA item_leitura | item_leitura;

item_leitura: IDENT
               {
                  geraCodigo(NULL, "LEIT");
                  sptr = busca_simbolo(&ts, token);
                  if(!sptr || sptr->categoria == PROCEDIMENTO_S){
                     fprintf(stderr, "ERRO:\n Uso incorreto da leitura no procedimento\n"); 
                     exit(1);
                  }
                  sprintf(buffer_mepa, "ARMZ %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
                  geraCodigo(NULL, buffer_mepa);
               }

;

escrita : WRITE ABRE_PARENTESES escreve_itens FECHA_PARENTESES;

escreve_itens: escreve_itens VIRGULA expressao {geraCodigo(NULL, "IMPR");}| expressao {geraCodigo(NULL, "IMPR");};
;

%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
   inicializa(&ts);
   inicializa(&pilha_atribuicao);
   pilha_rotulos_inicializar(&pilha_rotulos);
   pilha_rotulos_inicializar(&pilha_amem);
   pilha_rotulos_inicializar(&pilha_procs);
   pilha_tipos_inicializar(&pilha_ident_esquerdo);

   yyin=fp;
   yyparse();

   pilha_rotulos_destruir(&pilha_rotulos);
   pilha_rotulos_destruir(&pilha_amem);
   pilha_rotulos_destruir(&pilha_procs);
   pilha_tipos_destruir(&pilha_ident_esquerdo);

   return 0;
}
