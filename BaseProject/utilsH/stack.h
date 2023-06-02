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

void stack_symbols_table_push(struct stack_symbols_table *s, struct symbol *num);

void stack_int_push(struct stack_int *s, const int num);

int stack_int_head(struct stack_int *s);

struct symbol *stack_symbols_table_head(struct stack_symbols_table *s);

int stack_int_empty(struct stack_int *s);

int stack_symbols_table_empty(struct stack_symbols_table *s);

void stack_int_pop(struct stack_int *s);

void stack_symbols_table_pop(struct stack_symbols_table *s);

void stack_int_destruct(struct stack_int *s);

void stack_symbols_table_destruct(struct stack_symbols_table *s);

#endif