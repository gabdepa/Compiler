#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "tabela_simb.h"

void inicializa(tabela_de_simbolos_t **ts){
    *ts = malloc(sizeof(tabela_de_simbolos_t));
    (*ts)->simbolos = malloc(sizeof(simbolo_t));
    (*ts)->qtd = 0;
    (*ts)->tam = 1;
}

simbolo_t cria_simbolo(char *ident, int cat, int niv, struct cat_conteudo conteudo){
    simbolo_t s;
    s.identificador = malloc(strlen(ident)+1); 
    strcpy(s.identificador, ident);

    s.categoria = cat;
    s.nivel = niv;
    s.conteudo = conteudo;
    return s;
}

// insere o simbolo s na tabela de simbolos ts
void insere_tabela(tabela_de_simbolos_t **ts, simbolo_t s){
    int indice;
    (*ts)->qtd++;

    // se a quantidade de elementos ultrapassa o tamanho alocado
    if((*ts)->qtd > (*ts)->tam){
        (*ts)->tam <<= 1;
        (*ts)->simbolos = realloc((*ts)->simbolos, (*ts)->tam*(sizeof(simbolo_t)));
    }
    indice = (*ts)->qtd-1;
    (*ts)->simbolos[indice] = s; 
    
}

simbolo_t pop(tabela_de_simbolos_t **ts){
    simbolo_t ret;
    int indice = (*ts)->qtd-1;

    ret = (*ts)->simbolos[indice];

    (*ts)->qtd--;
    return ret;
}

void remove_n_tabela(tabela_de_simbolos_t **ts, int n){
    (*ts)->qtd -= n;
}

simbolo_t *busca_simbolo(tabela_de_simbolos_t **ts, const char *nome){
    int indice = (*ts)->qtd-1;
    
    while(indice >= 0){
        simbolo_t *atual = &( (*ts)->simbolos[indice--] );
        if (!strcmp( atual->identificador, nome )) return atual;
    }
    return NULL;
}

void atribui_tipo(tabela_de_simbolos_t **ts, int categoria, int tipo, int qtd){
    int indice = (*ts)->qtd-1;
    for(int i = 0; i < qtd; ++i){
        (*ts)->simbolos[indice - i].conteudo.var.tipo = tipo;
    }
}