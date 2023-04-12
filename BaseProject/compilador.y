%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./utilsH/compilador.h"
#include "./utilsH/symbols_table.h"

int num_vars;
symbols s;
symbols_table tab;
int nivel = 0;
char buffer[100];
int num_vars;

%}

%token PROGRAM VAR T_BEGIN T_END LABEL
%token TYPE ARRAY OF PROCEDURE
%token FUNCTION GOTO IF THEN 
%token ELSE FOR DO WHILE 
%token OR AND NOT DIV
%token ASTERISCO ATRIBUICAO PONTO_E_VIRGULA DOIS_PONTOS
%token VIRGULA PONTO ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_COLCHETES FECHA_COLCHETES ABRE_CHAVES FECHA_CHAVES
%token MAIOR MENOR NUMERO IDENT

%%

programa    :{
             geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             geraCodigo (NULL, "PARA");
             }
;

bloco       :
              parte_declara_vars
              {
              }

              comando_composto
              ;

parte_declara_vars:  var
;


var         : { num_vars = 0; } VAR declara_vars {
               sprintf(buffer, "AMEM %d", num_vars);
               geraCodigo(NULL, buffer);
             }
            |
;

declara_vars: declara_vars declara_var
            | declara_var
;

declara_var : { }
              lista_id_var DOIS_PONTOS
              tipo
              {
              }
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA IDENT {
   /* insere �ltima vars na tabela de s�mbolos */
   num_vars++;
}
            | IDENT { num_vars++; /* insere vars na tabela de s�mbolos */ }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;


comando_composto: T_BEGIN comandos T_END

comandos:
;

%%

int main (int argc, char** argv) 
{
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2)
   {
      printf("usage compilador <arq>a %d\n", argc);
      return(-1);
   }

   fp=fopen (argv[1], "r");
   if (fp == NULL) 
   {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de Símbolos
 * ------------------------------------------------------------------- */

   yyin=fp;
   yyparse();

   return 0;
}
