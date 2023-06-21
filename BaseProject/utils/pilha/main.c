#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha_rotulos.h"

int main(){

    struct pilha_rotulos pilha;

    pilha_rotulos_inicializar(&pilha);

    pilha_rotulos_empilhar(&pilha, 1);

    pilha_rotulos_empilhar(&pilha, 2);

    printf("A string: %02d\n", pilha_rotulos_topo(&pilha));

    pilha_rotulos_desempilhar(&pilha);
    printf("A string: %02d\n", pilha_rotulos_topo(&pilha));

    pilha_rotulos_desempilhar(&pilha);
    if (pilha_rotulos_vazia(&pilha))
        printf("Pilha vazia\n");
    else 
        printf("A string: %2d\n", pilha_rotulos_topo(&pilha));

    pilha_rotulos_destruir(&pilha);

    return 0;
}