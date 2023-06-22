#ifndef __PILHA__
#define __PILHA__

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32

typedef struct pilha_rotulos {
    unsigned int tam;
    unsigned int topo;
    int *p;
} pilha_rotulos;

void pilha_rotulos_inicializar( pilha_rotulos *p);
void pilha_rotulos_empilhar( pilha_rotulos *p, const int num);
int pilha_rotulos_topo( pilha_rotulos *p);
int pilha_rotulos_vazia( pilha_rotulos *p);
void pilha_rotulos_desempilhar( pilha_rotulos *p);
void pilha_rotulos_destruir( pilha_rotulos *p);

#endif