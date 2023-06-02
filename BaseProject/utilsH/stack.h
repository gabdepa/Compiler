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

// Initialize the integer stack and\or symbol stack structures.
void stack_init(struct stack_int *si, struct stack_symbols_table *sst);

// Push an integer to the integer stack or a symbol to the symbol stack.
void stack_push(struct stack_int *si, const int num, struct stack_symbols_table *sst, struct symbol *symbol);

// Check if integer stack or symbol stack are empty. Returns 0.
int stack_empty(struct stack_int *si, struct stack_symbols_table *sst);

// Remove the top element from the integer stack or the symbol stack.
void stack_pop(struct stack_int *si, struct stack_symbols_table *sst);

// Clean up resources used by the integer stack or the symbol stack.
void stack_destruct(struct stack_int *si, struct stack_symbols_table *sst);

// Returns the top element of the integer stack without removing it.
int stack_int_head(struct stack_int *s);

// Returns the top element of the symbol stack without removing it.
struct symbol *stack_symbols_table_head(struct stack_symbols_table *s);

#endif