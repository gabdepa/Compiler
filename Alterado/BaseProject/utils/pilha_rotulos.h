#ifndef __PILHA__
#define __PILHA__

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32

struct pilha_rotulos {
    unsigned int tam;
    unsigned int topo;
    int *p;
};

void pilha_rotulos_inicializar(struct pilha_rotulos *p);
void pilha_rotulos_empilhar(struct pilha_rotulos *p, const int num);
int pilha_rotulos_topo(struct pilha_rotulos *p);
int pilha_rotulos_vazia(struct pilha_rotulos *p);
void pilha_rotulos_desempilhar(struct pilha_rotulos *p);
void pilha_rotulos_destruir(struct pilha_rotulos *p);

#endif