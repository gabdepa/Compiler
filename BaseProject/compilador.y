%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./utilsH/compilador.h"
#include "./utilsH/symbols_table.h"
#include "./utilsH/stack.h"

int num_vars;
int num_params; // número de parâmetros do procedure atual
int curr_section_params; // número de parâmetros da seção atual => seção é aquela separada por ';'
int curr_call_params;
int level_lex;
int pos_var;
int qt_type_atual;
int referencia; // indica se a seção atual é por referência, se não for, é por cópia
//int dentro_proc; /* indica se estamos dentro de um procedure, mas acho que não precisa por conta da forma das structs
//                     usada na linha ~470 */
int dentro_chamada_proc; // indica se está dentro de uma chamada de procedure
int nr_procs_for_curr_proc;
int atribui;

char mepa_buf[128], proc_name[128], idents[128][128];
struct symbol_table *ts, *pilha_atribuicao;
struct symbol s, *sptr, *sptr_var_proc, *sptr_chamada_proc, *sptr_atribuicao, curr_proc, list_symbols[128];
struct stack_int pilha_labels, pilha_amem, pilha_procs;
struct stack_symbols_table pilha_ident_esquerdo;
struct parameter list_parameters[128];
struct content ti;


int str2type(const char *str)
{
   if ( !strcmp(str, "integer") ) return pas_integer;
   if ( !strcmp(str, "boolean") ) return pas_boolean;
   return undefined_type;
}

short int rot_num;
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

%union{
   char * str;  // Define the type str
   int int_val; // Define the type int_val
   struct symbol *symb;
}

%type <str> plus_minus_or; // In a expression
%type <str> plus_minus_empty; // Before a factor
%type <str> times_div_and;
%type <str> relation;
%type <int_val> expression;
%type <int_val> simple_expression;
%type <int_val> factor;
%type <int_val> term;
%type <int_val> type;

%nonassoc "lower_then_else"
%nonassoc ELSE

%%

// ========== REGRA 01 ========== //
programa    :{
             geraCodigo (NULL, "INPP");
             level_lex = 0;
             rot_num = 0;
             dentro_chamada_proc = 0;
             }
             PROGRAM IDENT
             ABRE_PARENTESES id_list FECHA_PARENTESES PONTO_E_VIRGULA
             block PONTO {
             geraCodigo (NULL, "PARA");
             }
;

// ========== REGRA 02 ========== //
block       :
              parte_declara_vars

              {
               sprintf(mepa_buf, "DSVS R%02d", rot_num);
               geraCodigo(NULL, mepa_buf);
               stack_push(&pilha_labels, rot_num, NULL, NULL); // stack_int_push
               rot_num++;
               level_lex++;
               nr_procs_for_curr_proc = 0;
              }
            
              parte_declara_subrotinas

              {
               stack_push(&pilha_procs, nr_procs_for_curr_proc, NULL, NULL); // stack_int_push
               level_lex--;

               sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels));
               geraCodigo(rot_str, "NADA");
               stack_pop(&pilha_labels, NULL);// stack_int_pop
              }
              comando_composto

              {
               sprintf(mepa_buf, "DMEM %d", stack_int_head(&pilha_amem));
               remove_n(&ts, stack_int_head(&pilha_amem));
               geraCodigo(NULL, mepa_buf);
               stack_pop(&pilha_amem, NULL);// stack_int_pop
              }

              ;

// ========== REGRA 08 ========== //
parte_declara_vars: { num_vars = 0; } VAR declara_vars { 
               sprintf(mepa_buf, "AMEM %d", num_vars);
               geraCodigo(NULL, mepa_buf);
               stack_push(&pilha_amem, num_vars, NULL, NULL); // stack_int_push
               }
            | {stack_push(&pilha_amem, 0, NULL, NULL);} // stack_int_push
;

// ========== REGRA 09 ========== //
declara_vars: declara_vars declara_var
            | declara_var
;

declara_var : { qt_type_atual = 0; }
              list_id_var DOIS_PONTOS
              type
              { set_type(&ts, variable, $4, qt_type_atual); }
              PONTO_E_VIRGULA
;

type        : TIPO { $$ = str2type(token); }
;

// ========== REGRA 10 ========== //
id_list: id_list 
              VIRGULA 
              ident_params
            | ident_params
;
ident_params: IDENT 
              {
               strcpy(idents[num_params], token);
               list_parameters[num_params].passage = referencia? reference_parameter : copy_parameter;
               num_params++;
               curr_section_params++;
              }
;
list_id_var: list_id_var VIRGULA IDENT {
               ti.var.offset = num_vars;
               s = symbol_init(token, variable, level_lex, ti); 
               push(&ts, s);
               num_vars++; qt_type_atual++;
            }
            | IDENT { 
               ti.var.offset = num_vars;
               s = symbol_init(token, variable, level_lex, ti); 
               push(&ts, s);
               num_vars++; qt_type_atual++;
            }
;

// ========== REGRA 11 ========== //
parte_declara_subrotinas: parte_declara_subrotinas declara_proc {nr_procs_for_curr_proc++;} 
                          | parte_declara_subrotinas declara_func 
                          |
;

// ========== REGRA 12 ========== //
declara_proc: PROCEDURE 
              IDENT
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
              parameters_formais_ou_nada
              {
               sprintf(rot_str, "R%02d", rot_num);
               sprintf(mepa_buf, "ENPR %d", level_lex);
               geraCodigo(rot_str, mepa_buf);
               
               ti.proc.label = rot_num;
               ti.proc.parameters_quantity = num_params;

               memcpy(ti.proc.list, list_parameters, sizeof(struct parameter)*num_params);
               
               // for(int i = 0; i < num_params; ++i){
               //    printf("proc.list[%d] tem type %d e passado por %d \n", i, ti.proc.list[i].type, ti.proc.list[i].passage);
               // }
               printf("nome: %s level: %d desloca: %d\n",proc_name, level_lex, ti.var.offset);

               s = symbol_init(proc_name, procedure, level_lex, ti);
               push(&ts, s);

               // atribui o offset correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  list_symbols[i].content.param.offset = -4 + (i - (num_params-1)); 
                  printf(">>>>>>>>> Parametro %s tem offset %d\n", list_symbols[i].id, list_symbols[i].content.param.offset);
                  push(&ts, list_symbols[i]);
               }
               rot_num++; // para o desvio de procedures dentro dessa procedure
               stack_push(&pilha_amem, num_params, NULL, NULL); // stack_int_push

               // dentro_proc = 1;
              }

              PONTO_E_VIRGULA 
              block 
              {
               remove_n(&ts, stack_int_head(&pilha_amem));
               sprintf(mepa_buf, "RTPR %d, %d", level_lex, stack_int_head(&pilha_amem));
               stack_pop(&pilha_amem, NULL);// stack_int_pop
               remove_n(&ts, stack_int_head(&pilha_procs));
               stack_pop(&pilha_procs, NULL);// stack_int_pop
               geraCodigo(NULL, mepa_buf);
              }
              PONTO_E_VIRGULA
;

// ========== REGRA 13 ========== //

declara_func: FUNCTION
              IDENT
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
              parameters_formais_ou_nada
              
              DOIS_PONTOS
              type
              {
               sprintf(rot_str, "R%02d", rot_num);
               sprintf(mepa_buf, "ENPR %d", level_lex);
               geraCodigo(rot_str, mepa_buf);
               
               ti.proc.label = rot_num;
               ti.proc.parameters_quantity = num_params;

               memcpy(ti.proc.list, list_parameters, sizeof(struct parameter)*num_params);
               
               // for(int i = 0; i < num_params; ++i){
               //    printf("proc.list[%d] tem type %d e passado por %d \n", i, ti.proc.list[i].type, ti.proc.list[i].passage);
               // }
               ti.var.type = $6;
               ti.var.offset = -4 - num_params;
               s = symbol_init(proc_name, function, level_lex, ti);
               push(&ts, s);

               // atribui o offset correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  list_symbols[i].content.param.offset = -4 + (i - (num_params-1)); 
                  push(&ts, list_symbols[i]);
               }
               rot_num++; // para o desvio de procedures dentro dessa procedure
               stack_push(&pilha_amem, num_params, NULL, NULL); // stack_int_push

               // dentro_proc = 1;
              }
              PONTO_E_VIRGULA

              block
              {
               remove_n(&ts, stack_int_head(&pilha_amem));
               sprintf(mepa_buf, "RTPR %d, %d", level_lex, stack_int_head(&pilha_amem));
               stack_pop(&pilha_amem, NULL);// stack_int_pop

               remove_n(&ts, stack_int_head(&pilha_procs));
               stack_pop(&pilha_procs, NULL);// stack_int_pop
               geraCodigo(NULL, mepa_buf);
              }
              PONTO_E_VIRGULA
;

// ========== REGRA 14 ========== //
parameters_formais_ou_nada: parameters_formais | ;

parameters_formais: ABRE_PARENTESES
                     parameters
                    FECHA_PARENTESES
;

parameters: parameters PONTO_E_VIRGULA secao_parameters | secao_parameters
;

secao_parameters : var_ou_nada
                   {curr_section_params = 0;}
                   id_list 
                   DOIS_PONTOS 
                   type
                   {
                     // atribui type para os parâmetros dessa seção e coloca numa list de símbolos a serem empilhados
                     for(int i = num_params-curr_section_params; i < num_params; ++i){
                        ti.param = list_parameters[i];
                        ti.param.type = $5;
                        list_symbols[i] = symbol_init(idents[i], parameter, level_lex, ti);
                     }
                   }                   
;

var_ou_nada: VAR {referencia = 1;} | {referencia = 0;} ;

// ========== REGRA 16 ========== //
comando_composto: T_BEGIN comandos T_END 
;

// ========== REGRA 17 ========== //
comandos: comando_sem_label | comandos PONTO_E_VIRGULA comando_sem_label;

// ========== REGRA 18 ========== //
comando_sem_label: atribuicao_proc
                  | comando_repetitivo 
                  | comando_condicional
                  | escrita
                  | leitura
                  |
;

leitura : READ ABRE_PARENTESES leitura_itens FECHA_PARENTESES;

leitura_itens: leitura_itens VIRGULA item_leitura | item_leitura
;

item_leitura: IDENT
               {
                  geraCodigo(NULL, "LEIT");
                  sptr = search(&ts, token);
                  if(!sptr || sptr->category == procedure){
                     fprintf(stderr, "COMPILATION ERROR!!!\n Wrong use of read()\n"); 
                     exit(1);
                  }
                  sprintf(mepa_buf, "ARMZ %d, %d", sptr->level, sptr->content.var.offset);
                  geraCodigo(NULL, mepa_buf);
               }

;

escrita : WRITE ABRE_PARENTESES escreve_itens FECHA_PARENTESES;

escreve_itens: escreve_itens VIRGULA expression {geraCodigo(NULL, "IMPR");}| expression {geraCodigo(NULL, "IMPR");};
;

atribuicao_proc:  IDENT 
                  { 
                     // printf("Buscando o token %s\n", token);
                     sptr_var_proc = search(&ts, token); 
                     stack_push(NULL, 0, &pilha_ident_esquerdo, sptr_var_proc); // symbols_table_push
                  } 
                  a_continua
                  { 
                     stack_pop(NULL, &pilha_ident_esquerdo);// stack_symbols_table_pop
                  };

a_continua: ATRIBUICAO {atribui = 1;}atribuicao {atribui = 0;}|
            procedure_sem_parameter |
            procedure;

// ========== REGRA 19 ========== //
atribuicao: expression {
   sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);
   if(sptr_var_proc->content.var.type != $1){
      fprintf(stderr, "COMPILATION ERROR!!!\n Variable type differs from expression type.\n"); 
      exit(1);
   }
   /* search posição da variable */
   
   // pode ser indireto
   // printf("%s: %d", sptr_var_proc->id, sptr_var_proc->category);
   if (sptr_var_proc->category == variable)
      sprintf(mepa_buf, "ARMZ %d, %d", sptr_var_proc->level, sptr_var_proc->content.var.offset);
   else if (sptr_var_proc->category == parameter){
      if (sptr_var_proc->content.param.passage == copy_parameter)
         sprintf(mepa_buf, "ARMZ %d, %d", sptr_var_proc->level, sptr_var_proc->content.param.offset);
      else
         sprintf(mepa_buf, "ARMI %d, %d", sptr_var_proc->level, sptr_var_proc->content.param.offset);
   } else if (sptr_var_proc->category == function){
         sprintf(mepa_buf, "ARMZ %d, %d", sptr_var_proc->level, sptr_var_proc->content.var.offset);
   } else {
      fprintf(stderr, "Procedimento tratado como variável!\n");
      exit(1);
   }
   geraCodigo(NULL, mepa_buf);
}
;

// ========== REGRA 19 ========== //
procedure:
             {
               sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);

              if(!sptr_var_proc){
                  fprintf(stderr, "COMPILATION ERROR!!!\n Procedure not found.\n"); 
                  exit(1);
              }
              sptr_atribuicao = sptr_var_proc;
              memcpy(&curr_proc, sptr_var_proc, sizeof(struct symbol));
            //   printf("curr_proc.category = %d\n", curr_proc.category);
            //   printf("fun: %d\n", function);
            //   printf("proc: %d\n", procedure);
              if(curr_proc.category == function ){
                  geraCodigo(NULL, "AMEM 1");
              }
              sprintf(proc_name, "CHPR R%02d, %d", sptr_var_proc->content.proc.label, level_lex);
             } 
             ABRE_PARENTESES 
             {
               curr_call_params = 0;
               dentro_chamada_proc++;
             }
             list_expressoes
             FECHA_PARENTESES
             {
               dentro_chamada_proc--;
               if(curr_call_params != curr_proc.content.proc.parameters_quantity){
                   fprintf(stderr, "COMPILATION ERROR!!!\n Wrong number of parameters.\n"); 
                   exit(1);
               }
               geraCodigo(NULL, proc_name);
             }
;

procedure_sem_parameter:
              {
               sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);
               if(!sptr_var_proc){
                  fprintf(stderr, "COMPILATION ERROR!!!\n Procedure not found.\n"); 
                  exit(1);
               }
               sprintf(mepa_buf, "CHPR R%02d, %d", sptr_var_proc->content.proc.label, level_lex);
               geraCodigo(NULL, mepa_buf);
              }

// ========== REGRA 23 ========== //
comando_repetitivo:  WHILE {
                        stack_push(&pilha_labels, rot_num, NULL, NULL); // stack_int_push
                         
                        sprintf(rot_str, "R%02d", rot_num);
                        geraCodigo(rot_str, "NADA");
                        rot_num += 2;
                     }
                     expression {
                        sprintf(mepa_buf, "DSVF R%02d", stack_int_head(&pilha_labels)+1);
                        geraCodigo(NULL, mepa_buf); // falta testar expressão
                     }
                     DO 
                     comando_sem_label_ou_composto {
                        sprintf(mepa_buf, "DSVS R%02d", stack_int_head(&pilha_labels));
                        geraCodigo(NULL, mepa_buf);

                        sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels)+1);
                        geraCodigo(rot_str, "NADA");

                        stack_pop(&pilha_labels, NULL);// stack_int_pop
                     }
;

comando_sem_label_ou_composto: comando_sem_label | comando_composto;

// ========== REGRA 22 ========== //

comando_condicional: IF expression {
                        if ($2 != pas_boolean){
                           fprintf(stderr, "COMPILATION ERROR!!!\n If expression is not boolean!\n");
                           exit(1);
                        }

                        sprintf(mepa_buf, "DSVF R%02d", rot_num+1);
                        geraCodigo(NULL, mepa_buf); // falta testar expressão
                        
                        stack_push(&pilha_labels, rot_num, NULL, NULL);// stack_int_push
                        rot_num += 2;
                     }  
                     THEN
                     comando_sem_label_ou_composto {
                        sprintf(mepa_buf, "DSVS R%02d", stack_int_head(&pilha_labels));
                        geraCodigo(NULL, mepa_buf);

                        sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels)+1);
                        geraCodigo(rot_str, "NADA");

                     } 
                     else_ou_nada{
                        sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels));
                        geraCodigo(rot_str, "NADA");

                        stack_pop(&pilha_labels, NULL);// stack_int_pop
                     }
;

else_ou_nada: ELSE comando_sem_label_ou_composto 
            | %prec "lower_then_else"
;

// ========== REGRA 25 ========== //

list_expressoes:  expression
                  {  
                     // curr_section_params++;
                     curr_call_params++;
                  } 
                  VIRGULA 
                  list_expressoes 
                  | expression 
                  {
                     // curr_section_params++;
                     curr_call_params++;
                  };

expression   : simple_expression { $$ = $1; } 
            | simple_expression relation simple_expression{
               if ($1 != $3){
                  fprintf(stderr, "COMPILATION ERROR!!!\nCannot compare expressions with different types!\n");
                  exit(1);
               }
               geraCodigo(NULL, $2);
               $$ = pas_boolean;
            }
;

// ========== REGRA 26 ========== //
relation  : IGUAL        { $$ = "CMIG"; }
         | DIFERENTE    { $$ = "CMDG"; }
         | MENOR        { $$ = "CMME"; }
         | MENOR_IGUAL  { $$ = "CMEG"; }
         | MAIOR_IGUAL  { $$ = "CMAG"; }
         | MAIOR        { $$ = "CMMA"; }
;

// ========== REGRA 27 ========== //
simple_expression : simple_expression plus_minus_or term {
                     if (strcmp($2, "DISJ") == 0){
                        if ($1 != pas_boolean || $3 != pas_boolean){
                           fprintf(stderr, "COMPILATION ERROR!!!\n Boolean operation with non-boolean operands!\n");
                           exit(1);
                        }
                        $$ = pas_boolean;
                     }
                     else {
                        if ($1 != pas_integer || $3 != pas_integer){
                           fprintf(stderr, "COMPILATION ERROR!!!\n Integer operation with non-integer operands!\n");
                           exit(1);
                        }
                        $$ = pas_integer;
                     }
                     
                     geraCodigo(NULL, $2);
                  }
                  | plus_minus_empty term{
                     if ( strcmp($1, "VAZIO") != 0){
                        if ($2 != pas_integer){
                           fprintf(stderr, "COMPILATION ERROR!!!\n Sign on non integer type!\n");
                           exit(1);
                        }
                        $$ = pas_integer;
                     } else {
                        $$ = $2;
                     }
                     
                     if ( strcmp($1, "MENOS") == 0 )
                        geraCodigo(NULL, "INVR");
                  } 
;

plus_minus_empty  : MAIS  { $$ = "MAIS"; }
                  | MENOS { $$ = "MENOS"; }
                  |       { $$ = "VAZIO"; }
;

plus_minus_or  : MAIS { $$ = strdup("SOMA"); }
               | MENOS { $$ = strdup("SUBT"); } 
               | OR { $$ = strdup("DISJ"); }
; 

// ========== REGRA 28 ========== //
term : term times_div_and factor { 
         if (strcmp($2, "CONJ") == 0){
            if ($1 != pas_boolean || $3 != pas_boolean){
               fprintf(stderr, "COMPILATION ERROR!!!\n Boolean operation with non-boolean operands!\n");
               exit(1);
            }
            $$ = pas_boolean;
         }
         else {
            if ($1 != pas_integer || $3 != pas_integer){
               fprintf(stderr, "COMPILATION ERROR!!!\n Integer operation with non-integer operands!\n");
               exit(1);
            }
            $$ = pas_integer;
         }
         geraCodigo(NULL, $2);
      }
      | factor
;

times_div_and  : VEZES { $$ = strdup("MULT"); }
               | DIV { $$ = strdup("DIVI"); }
               | AND { $$ = strdup("CONJ"); }
;

// ========== REGRA 29 ========== //
procedure_ou_nada: procedure {
                        sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);
                        stack_pop(NULL, &pilha_ident_esquerdo);// stack_symbols_table_pop
                     }
                     | {
                        sptr = stack_symbols_table_head(&pilha_ident_esquerdo); 
                        stack_pop(NULL, &pilha_ident_esquerdo);// stack_symbols_table_pop
                     };

factor : IDENT 
         {
            sptr = search(&ts, token);
            stack_push(NULL, 0, &pilha_ident_esquerdo, search(&ts, token));//symbols_table_push

         } procedure_ou_nada { 

         if(!sptr){
            printf("Variável não encontrada\n");
            exit(1);
         }
         
         // printf("Variavel %s level %d, offset %d\n", sptr->id, sptr->level, sptr->content.var.offset);
         $$ = sptr->content.var.type;
         // pode ser indireto
         int flag = 0;
         if (sptr->category == variable){
            
            if (dentro_chamada_proc){
               int qtd_params = sptr_var_proc->content.proc.parameters_quantity;
               // printf("curr: %d actual: %d\n", curr_call_params, qtd_params);
               if (curr_call_params >= qtd_params){
                  fprintf(stderr, "COMPILATION ERROR! Excesso de parâmetros em função!!\n");
                  exit(1);
               }
               if (sptr_var_proc->content.proc.list[curr_call_params].passage == reference_parameter){
                  sprintf(mepa_buf, "CREN %d, %d", sptr->level, sptr->content.var.offset);
               }
               else if (sptr_var_proc->content.proc.list[curr_call_params].passage == copy_parameter){
                  sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.var.offset);
               }else {
                  fprintf(stderr, "INTERNAL ERROR: parameter não é nem copia nem referencia\n");
                  exit(1);
               }
            } else if (sptr_var_proc && sptr_var_proc->category != function){
               sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.var.offset);
            } else if (atribui && (sptr_var_proc && sptr_var_proc->category == function) && sptr_atribuicao->category != function){
               sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.var.offset);

            } else {
               flag = 1;
            }

         }
         else if (sptr->category == parameter){
            if (sptr->content.param.passage == copy_parameter)
               sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.param.offset);
            else {
               if(sptr_var_proc->content.proc.list[curr_call_params].passage == reference_parameter){
                  sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.param.offset);
               } else {
                  sprintf(mepa_buf, "CRVI %d, %d", sptr->level, sptr->content.param.offset);
               }
            }
         } else if (sptr->category != function){
            fprintf(stderr, "Procedimento tratado como variável!!\n");
            exit(1);
         } else {
            flag = 1;
         }
         if(!flag)
            geraCodigo(NULL, mepa_buf);
      } 
      | NUMERO {
         $$ = pas_integer;
         sprintf (mepa_buf, "CRCT %d", atoi(token));
         geraCodigo(NULL, mepa_buf);
      }
      | VALOR_BOOL {
         $$ = pas_boolean;
         if(strcmp(token, "True") == 0)
            sprintf (mepa_buf, "CRCT %d", 1);
         else
            sprintf (mepa_buf, "CRCT %d", 0);
         geraCodigo(NULL, mepa_buf);
      }
      | ABRE_PARENTESES expression FECHA_PARENTESES { $$ = $2; }
      | NOT factor {
         if ($2 != pas_boolean){
            fprintf(stderr, "COMPILATION ERROR!!! Boolean operation with non-boolean value!\n");
            exit(1);
         }
         $$ = pas_boolean;
         geraCodigo(NULL, "NEGA");
       }
         /* falta chamada de função */
      /* | IDENT procedure {$$ = sptr_var_proc->content.var.type;} */
;

// ========== REGRA 30 ========== //
/* variable:   IDENT { sptr = search(&ts, token);} 
                  | IDENT { sptr = search(&ts, token);}procedure ; */

%%

int main (int argc, char** argv) 
{
   FILE* fp;
   extern FILE* yyin;

   if ( argc<2 || argc>2 )
   {
         printf("ERROR: Compiler usage: ./compilador <testFile>.pas, you've passed %d argument, but we need one test file\n", argc);
         return(-1);
   }

   fp=fopen (argv[1], "r");
   if ( fp == NULL ) 
   {
      printf("ERROR: File %s passed is NULL.\n", argv[1]);
      return(-1);
   }

   /* Initialize Tables */
   table_init(&ts);
   table_init(&pilha_atribuicao);
   stack_init(&pilha_labels, NULL);
   stack_init(&pilha_amem, NULL);
   stack_init(&pilha_procs, &pilha_ident_esquerdo);

   yyin=fp;
   yyparse();

   /* Destruct Tables */
   stack_destruct(&pilha_labels, NULL);
   stack_destruct(&pilha_amem, NULL);
   stack_destruct(&pilha_procs, NULL);
   stack_destruct(NULL, &pilha_ident_esquerdo);

   return 0;
}