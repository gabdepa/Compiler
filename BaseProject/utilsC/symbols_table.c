#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utilsH/symbols_table.h"

void *new_simple_var(unsigned short int type, unsigned int off_set)
{
    simple_var_av_t *ret;
    ret = malloc(sizeof(simple_var_av_t));

    ret->type = type;
    ret->off_set = off_set;

    return (void *)ret;
}

void destruct_simple_var(void *var_simples)
{
    if (var_simples)
        free(var_simples);
}

void *new_formal_parameter(unsigned short int type, unsigned int off_set, unsigned short int passage)
{
    formal_parameter_av_t *ret;
    ret = malloc(sizeof(formal_parameter_av_t));

    ret->type = type;
    ret->off_set = off_set;
    ret->passage = passage;

    return (void *)ret;
}

void destruct_formal_parameter(void *parametro_formal)
{
    if (parametro_formal)
        free(parametro_formal);
}

void *new_procedure(const char *label, unsigned short int num_params)
{
    procedure_av_t *ret;
    ret = malloc(sizeof(procedure_av_t));

    ret->label = malloc(strlen(label) + 1);
    strcpy(ret->label, label);
    ret->num_params = num_params;

    return (void *)ret;
}

void destruct_procedure(void *procedimento)
{
    procedure_av_t *proc = (procedure_av_t *)procedimento;
    if (proc)
    {
        if (proc->label)
            free(proc->label);
        proc->params = NULL;
        free(proc);
    }
}

/*
    Passar ponteiro já alocado para atributos variáveis da category
    A variável de category informa qual o type do atributo variável
*/
void set_symbol(symbols_t *simb, const char *ident, unsigned short int cat, unsigned short int niv, void *av)
{

    simb->id = malloc(strlen(ident) + 1);
    strcpy(simb->id, ident);
    simb->category = cat;
    simb->level = niv;
    simb->var_attributes = av;
}

void init_symbols_table(symbols_table_t *tab)
{
    tab->stack = NULL;
    tab->size = 0;
    tab->alloc_size = 0;
}

void simbolo_destroi_atributos(symbols_t *simb)
{
    if (simb->id)
        free(simb->id);
    if (simb->var_attributes)
    {
        if (simb->category == SIMPLE_VAR)
            destruct_simple_var(simb->var_attributes);
        else if (simb->category == FORMAL_PARAMETER)
            destruct_formal_parameter(simb->var_attributes);
        else
            destruct_procedure(simb->var_attributes);
    }
}

void destruct_symbols_table(symbols_table_t *tab)
{
    for (unsigned int i = 0; i < tab->size; ++i)
        simbolo_destroi_atributos(&(tab->stack[i]));

    free(tab->stack);
    tab->size = 0;
    tab->alloc_size = 0;
}

// Faz procedimento apontar para posição acima na stack caso tenha parametros
void atribuir_inicio_params(symbols_t *simb)
{
    procedure_av_t *av = (procedure_av_t *)simb->var_attributes;

    if (av->num_params)
        av->params = simb + 1; // Posição na stack logo após
    else
        av->params = NULL;
}

void symbols_table_append(symbols_table_t *tab, symbols_t *simb)
{
    if (tab->alloc_size == tab->size)
        tab->stack = realloc(tab->stack, (tab->alloc_size + ALLOC_STEP) * sizeof(symbols_t));

    if (simb->category == PROCEDURE)
        atribuir_inicio_params(simb);

    memcpy(&(tab->stack[tab->size]), simb, sizeof(symbols_t));
    tab->size++;
}

/* Se tabela não tem o símbolo, retorna -1 */
int symbols_table_search(symbols_table_t *tab, char *ident)
{
    int it = tab->size - 1;
    while (it >= 0)
    {
        if (!strcmp(tab->stack[it].id, ident))
            return it; // falta testar o level
        it--;
    }
    return it;
}

void symbols_table_remove(symbols_table_t *tab, unsigned int n)
{
    if (n > tab->size)
    {
        fprintf(stderr, "Tentaste remover elementos demais da tabela!\n");
        exit(1);
    }

    // Desemstack e libera elemento por elemento
    while (n)
    {
        tab->size--;
        simbolo_destroi_atributos(&(tab->stack[tab->size]));
        n--;
    }

    // Fase de realocação
    unsigned int exceeding_blocks = (tab->alloc_size - tab->size) / ALLOC_STEP;
    if (exceeding_blocks)
    {
        unsigned int novo_size = tab->alloc_size - exceeding_blocks * ALLOC_STEP;
        tab->stack = realloc(tab->stack, novo_size * sizeof(symbols_t));
        tab->alloc_size = novo_size;
    }
}