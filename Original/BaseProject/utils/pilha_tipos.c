#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha_tipos.h"

void pilha_tipos_inicializar(struct pilha_tipos *p){
    p->p = NULL;
    p->tam = 0;
    p->topo = 0;
}

void pilha_tipos_empilhar(struct pilha_tipos *p, simbolo_t * simb){

    if (p->topo == p->tam){
        simbolo_t **auxptr = NULL;
        p->tam += PILHA_TAM_INCREMENTO;
        auxptr = realloc(p->p, p->tam*sizeof(simbolo_t *));
        if (auxptr == NULL){
            fprintf(stderr, "Erro alocando pilha de inteiros! Abortando programa...\n");
            exit(0);
        }
        p->p = auxptr;
    }
    p->p[p->topo++] = simb;
}

simbolo_t *pilha_tipos_topo(struct pilha_tipos *p){
    if (p->tam > 0)
        return p->p[p->topo-1];
    else {
        fprintf(stderr, "Pilha de inteiros vazia não tem topo!\n");
        exit(1);
    }
    return NULL;
}

int pilha_tipos_vazia(struct pilha_tipos *p){
    return p->topo == 0;
}

void pilha_tipos_desempilhar(struct pilha_tipos *p){
    p->topo--;
}

void pilha_tipos_destruir(struct pilha_tipos *p){
    p->topo = 0;
    p->tam = 0;
    free(p->p);
}
