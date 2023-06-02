#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utilsH/compilador.h"

symbols simbolo, relacao;
char token[TAM_TOKEN];
FILE *fp = NULL;

void geraCodigo(char *rot, char *comando)
{

  if (fp == NULL)
  {
    fp = fopen("MEPA", "w");
  }

  if (rot == NULL)
  {
    fprintf(fp, "     %s\n", comando);
    fflush(fp);
  }
  else
  {
    fprintf(fp, "%s: %s \n", rot, comando);
    fflush(fp);
  }
}

int imprimeErro(char *erro)
{
  fprintf(stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}
