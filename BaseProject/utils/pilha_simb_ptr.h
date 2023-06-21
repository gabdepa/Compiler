#ifndef __PILHA_SIMB_PTR__
#define __PILHA_SIMB_PTR__

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32
#include "tabela_simb.h"

struct pilha_simb_ptr {
    unsigned int tam;
    unsigned int topo;
    simbolo_t **p;
};

void pilha_simb_ptr_inicializar(struct pilha_simb_ptr *p);

void pilha_simb_ptr_empilhar(struct pilha_simb_ptr *p, simbolo_t* num);

simbolo_t* pilha_simb_ptr_topo(struct pilha_simb_ptr *p);

int pilha_simb_ptr_vazia(struct pilha_simb_ptr *p);

void pilha_simb_ptr_desempilhar(struct pilha_simb_ptr *p);

void pilha_simb_ptr_destruir(struct pilha_simb_ptr *p);

#endif