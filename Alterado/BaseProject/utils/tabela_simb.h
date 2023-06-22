#ifndef __TABELA_SIMB__
#define __TABELA_SIMB__

#include <stdbool.h>


typedef enum tipo_simbolo{
    VARIAVEL_S,
    PARAMETRO_S,
    PROCEDIMENTO_S,
    FUNCAO_S,
    LABEL_S
} tipo_simbolo;

typedef enum tipo_variavel{
    INTEGER_S,
    BOOLEAN_S,
    UNDEFINED_S
} tipo_variavel;

typedef enum tipo_passagem{
    PARAMETRO_COPIA_S,
    PARAMETRO_REF_S
} tipo_passagem;


/* Três tipos de símbolos */
typedef struct variavel{
    int tipo;
    int deslocamento;
} variavel;

typedef struct parametro{
    int tipo;
    int deslocamento;
    int passagem;
} parametro;

typedef struct procedimento{
    int rotulo;
    int qtd_parametros;
    parametro lista[128];
} procedimento;

typedef struct label {
    int rotulo;
}label;

/*------------------------*/
typedef struct tipo_conteudo{
    variavel var;
    parametro param;
    procedimento proc;
} tipo_conteudo;

typedef struct simbolo_t{
    char *identificador;
    int categoria;
    int nivel;
    tipo_conteudo conteudo; // conteudo do simbolo contem variavel | parametro | procedimento
} simbolo_t;


typedef struct tabela_de_simbolos_t{
    simbolo_t *simbolos;
    unsigned int qtd;
    unsigned int tam;
}tabela_de_simbolos_t;

simbolo_t cria_simbolo(char *ident, int cat, int niv, tipo_conteudo tipo);
void inicializa(tabela_de_simbolos_t **ts);
void insere_tabela(tabela_de_simbolos_t **ts, simbolo_t);
simbolo_t pop(tabela_de_simbolos_t **ts) ;
void remove_n_tabela(tabela_de_simbolos_t **ts, int n);
simbolo_t *busca_simbolo(tabela_de_simbolos_t **ts, const char *nome);
void atribui_tipo(tabela_de_simbolos_t **ts, int categoria, int tipo, int qtd);

#endif
