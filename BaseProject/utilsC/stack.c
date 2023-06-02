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

// void stack_int_init(struct stack_int *s)
// {
//     s->stack = NULL;
//     s->size = 0;
//     s->head = 0;
// }

void stack_symbols_table_push(struct stack_symbols_table *s, struct symbol *simb)
{

    if (s->head == s->size)
    {
        struct symbol **auxstr = NULL;
        s->size += STACK_INCREMENT;
        auxstr = realloc(s->stack, s->size * sizeof(struct symbol *));
        if (auxstr == NULL)
        {
            fprintf(stderr, "Erro alocando stack de inteiros! Abortando srograma...\n");
            exit(0);
        }
        s->stack = auxstr;
    }
    s->stack[s->head++] = simb;
}

void stack_int_push(struct stack_int *s, const int num)
{

    if (s->head == s->size)
    {
        int *auxstr = NULL;
        s->size += STACK_INCREMENT;
        auxstr = realloc(s->stack, s->size * sizeof(int));
        if (auxstr == NULL)
        {
            fprintf(stderr, "Erro alocando stack de inteiros! Abortando srograma...\n");
            exit(0);
        }
        s->stack = auxstr;
    }
    s->stack[s->head++] = num;
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

int stack_int_empty(struct stack_int *s)
{
    return s->head == 0;
}

int stack_symbols_table_empty(struct stack_symbols_table *s)
{
    return s->head == 0;
}

void stack_int_pop(struct stack_int *s)
{
    s->head--;
}

void stack_symbols_table_pop(struct stack_symbols_table *s)
{
    s->head--;
}

void stack_int_destruct(struct stack_int *s)
{
    s->head = 0;
    s->size = 0;
    free(s->stack);
}

void stack_symbols_table_destruct(struct stack_symbols_table *s)
{
    s->head = 0;
    s->size = 0;
    free(s->stack);
}