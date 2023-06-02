#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utilsH/symbols_table.h"
#include "../utilsH/stack.h"

void stack_init(struct stack_int *si, struct stack_symbols_table *sst)
{
    if (si && sst)
    {
        si->stack = NULL;
        si->size = 0;
        si->head = 0;
        sst->stack = NULL;
        sst->size = 0;
        sst->head = 0;
    }
    else if (si && !sst)
    {
        si->stack = NULL;
        si->size = 0;
        si->head = 0;
    }
    else if (!si && sst)
    {
        sst->stack = NULL;
        sst->size = 0;
        sst->head = 0;
    }
    else
    {
        fprintf(stderr, "Both pointers are NULL, exiting...\n");
        exit(0);
    }
}

void stack_push(struct stack_int *si, const int num, struct stack_symbols_table *sst, struct symbol *symbol)
{
    if (sst && !si)
    {
        if (!symbol)
        {
            fprintf(stderr, "Pointer symbol is NULL, exiting...\n");
            exit(0);
        }
        if (sst->head == sst->size)
        {
            struct symbol **auxstr = NULL;
            sst->size += STACK_INCREMENT;
            auxstr = realloc(sst->stack, sst->size * sizeof(struct symbol *));
            if (auxstr == NULL)
            {
                fprintf(stderr, "Erro alocando stack de inteiros! Abortando srograma...\n");
                exit(0);
            }
            sst->stack = auxstr;
        }
        sst->stack[sst->head++] = symbol;
    }
    else if (!sst && si)
    {
        if (si->head == si->size)
        {
            int *auxstr = NULL;
            si->size += STACK_INCREMENT;
            auxstr = realloc(si->stack, si->size * sizeof(int));
            if (auxstr == NULL)
            {
                fprintf(stderr, "Erro alocando stack de inteiros! Abortando srograma...\n");
                exit(0);
            }
            si->stack = auxstr;
        }
        si->stack[si->head++] = num;
    }
    else
    {
        fprintf(stderr, "Both Pointers passed are valid, exiting...\n");
        exit(0);
    }
}

int stack_int_head(struct stack_int *s)
{
    if (s->head > 0)
        return s->stack[s->head - 1];
    else
    {
        fprintf(stderr, "stack de inteiros empty não tem head!\n");
        exit(1);
    }
    return 0;
}

struct symbol *stack_symbols_table_head(struct stack_symbols_table *s)
{
    if (s->size > 0)
        return s->stack[s->head - 1];
    else
    {
        fprintf(stderr, "stack de inteiros empty não tem head!\n");
        exit(1);
    }
    return NULL;
}

int stack_empty(struct stack_int *si, struct stack_symbols_table *sst)
{
    if (si && !sst)
    {
        return si->head == 0;
    }
    else if (!si && sst)
    {
        return sst->head == 0;
    }
}

void stack_pop(struct stack_int *si, struct stack_symbols_table *sst)
{
    if (si && !sst)
    {
        si->head--;
    }
    else if (!si && sst)
    {
        sst->head--;
    }
}

void stack_destruct(struct stack_int *si, struct stack_symbols_table *sst)
{
    if (si && !sst)
    {
        si->head = 0;
        si->size = 0;
        free(si->stack);
    }
    else if (!si && sst)
    {
        sst->head = 0;
        sst->size = 0;
        free(sst->stack);
    }
}