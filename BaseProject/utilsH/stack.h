#ifndef __STACK__
#define __STACK__

#define STACK_INCREMENT 1024
#define STACK_SIZE_STRING 32

struct stack_symbols_table
{
    struct symbol **stack;
    unsigned int size;
    unsigned int head;
};

struct stack_int
{
    int *stack;
    unsigned int size;
    unsigned int head;
};

void stack_init(struct stack_int *si, struct stack_symbols_table *sst);

void stack_push(struct stack_int *si, const int num, struct stack_symbols_table *sst, struct symbol *symbol);

int stack_int_head(struct stack_int *s);

struct symbol *stack_symbols_table_head(struct stack_symbols_table *s);

int stack_empty(struct stack_int *si, struct stack_symbols_table *sst);

void stack_pop(struct stack_int *si, struct stack_symbols_table *sst);

void stack_destruct(struct stack_int *si, struct stack_symbols_table *sst);

#endif