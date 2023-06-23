#ifndef __PILHA_SIMB_PTR__
#define __PILHA_SIMB_PTR__

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32
#include "tabela_simb.h"

typedef struct pilha_tipos {
    unsigned int tam;
    unsigned int topo;
    simbolo_t **p;
} pilha_tipos;

void pilha_tipos_inicializar( pilha_tipos *p);
void pilha_tipos_empilhar( pilha_tipos *p, simbolo_t* num);
simbolo_t* pilha_tipos_topo( pilha_tipos *p);
int pilha_tipos_vazia( pilha_tipos *p);
void pilha_tipos_desempilhar( pilha_tipos *p);
void pilha_tipos_destruir( pilha_tipos *p);

#endif