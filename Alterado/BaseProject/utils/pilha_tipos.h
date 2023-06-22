#ifndef __PILHA_SIMB_PTR__
#define __PILHA_SIMB_PTR__

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32
#include "tabela_simb.h"

struct pilha_tipos {
    unsigned int tam;
    unsigned int topo;
    simbolo_t **p;
};

void pilha_tipos_inicializar(struct pilha_tipos *p);
void pilha_tipos_empilhar(struct pilha_tipos *p, simbolo_t* num);
simbolo_t* pilha_tipos_topo(struct pilha_tipos *p);
int pilha_tipos_vazia(struct pilha_tipos *p);
void pilha_tipos_desempilhar(struct pilha_tipos *p);
void pilha_tipos_destruir(struct pilha_tipos *p);

#endif