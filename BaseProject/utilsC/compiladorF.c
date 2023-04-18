#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utilsH/compilador.h"

/*********************GLOBAL VARIABLES*********************/
simbolos simbolo, relacao;
char token[TAM_TOKEN];
FILE* fp=NULL;
typedef enum {
  T_NULL,
  T_IGUAL,
  T_DIFERENTE,
  T_MENOR,
  T_MENOR_OU_IGUAL,
  T_MAIOR,
  T_MAIOR_OU_IGUAL,
  T_SOMA,
  T_SUBTR,
  T_MULT,
  T_DIVI,
  T_CONJ,
  T_DISJ,
  T_NEGA
} operationsTypes;

operationsTypes operacao = T_NULL; // variavel de operacao inicializada como nula
/*********************GLOBAL VARIABLES*********************/


void geraCodigo (char* rot, char* comando) {

  if (fp == NULL) {
    fp = fopen ("MEPA", "w");
  }

  if ( rot == NULL ) {
    fprintf(fp, "     %s\n", comando); fflush(fp);
  } else {
    fprintf(fp, "%s: %s \n", rot, comando); fflush(fp);
  }
}

/**
 * @brief Funcao para geracao da operacao, recebe a operacao e converte para o comando MEPA referente
 * 
 * @param op - Enum com os tipos de operacoes previstas
 */
void geraOperacao(operationsTypes op) {
	switch (op) {
		case T_IGUAL: //=
			geraCodigo(NULL, "CMIG \0");
			break;
		case T_DIFERENTE: //<>
			geraCodigo(NULL, "CMDG \0");
			break;
		case T_MENOR: //<
			geraCodigo(NULL, "CMME \0");
			break;
		case T_MENOR_OU_IGUAL: //<=
			geraCodigo(NULL, "CMEG \0");
			break;
		case T_MAIOR: //>
			geraCodigo(NULL, "CMMA \0");
			break;
		case T_MAIOR_OU_IGUAL: //>=
			geraCodigo(NULL, "CMAG \0");
			break;
		case T_SOMA: //+
			geraCodigo(NULL, "SOMA \0");
			break;
		case T_SUBTR: //-
			geraCodigo(NULL, "SUBT \0");
			break;
		case T_MULT: //*
			geraCodigo(NULL, "MULT \0");
			break;
		case T_DIVI: ///
			geraCodigo(NULL, "DIVI \0");
			break;
		case T_CONJ: //&&
			geraCodigo(NULL, "CONJ \0");
			break;
		case T_DISJ: //||
			geraCodigo(NULL, "DISJ \0");
			break;
		case T_NEGA: //!
			geraCodigo(NULL, "NEGA \0");
			break;
		default:
			break;
	}
	operacao = T_NULL;
}

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}
