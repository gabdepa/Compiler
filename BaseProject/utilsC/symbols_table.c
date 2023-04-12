#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utilsH/symbols_table.h"

// Function declaration: setSimpleVar takes two arguments, an unsigned short int 'type', and an unsigned int 'off_set', and returns a void pointer.
void *setSimpleVar(unsigned short int type, unsigned int off_set)
{
    // Declare a pointer 'ret' of type simple_var_av .
    simple_var_av *ret;
    // Allocate memory for 'ret' with the size of simple_var_av using malloc, and assign the memory address to 'ret'.
    ret = malloc(sizeof(simple_var_av));
    // Set the 'type' field of the simple_var_av struct pointed to by 'ret' to the provided 'type' argument.
    ret->type = type;
    // Set the 'off_set' field of the simple_var_av struct pointed to by 'ret' to the provided 'off_set' argument.
    ret->off_set = off_set;
    // Cast 'ret' to a void pointer and return it.
    return (void *)ret;
}

// Function declaration: deleteSimpleVar takes a void pointer 'simple_var' as an argument and returns nothing (void).
void deleteSimpleVar(void *simple_var)
{
    // Check if 'simple_var' is not a null pointer (i.e., it points to a valid memory address).
    if (simple_var)
    {
        // If 'simple_var' is valid, free the memory it points to using the 'free' function.
        free(simple_var);
    }
    else
    {
        // If 'simple_var' is a null pointer (i.e., not valid), print an error message using the 'perror' function.
        perror("Var passed does not exist!");
        // Terminate the program with a non-zero exit status (1) to indicate that an error has occurred.
        exit(1);
    }
}

// Function declaration: setFormalParameter takes three arguments - an unsigned short int 'type', an unsigned int 'off_set', and an unsigned short int 'passage'. It returns a void pointer.
void *setFormalParameter(unsigned short int type, unsigned int off_set, unsigned short int passage)
{
    // Declare a pointer 'ret' of type formal_parameter_av .
    formal_parameter_av *ret;
    // Allocate memory for 'ret' with the size of formal_parameter_av using malloc, and assign the memory address to 'ret'.
    ret = malloc(sizeof(formal_parameter_av));
    // Set the 'type' field of the formal_parameter_av struct pointed to by 'ret' to the provided 'type' argument.
    ret->type = type;
    // Set the 'off_set' field of the formal_parameter_av struct pointed to by 'ret' to the provided 'off_set' argument.
    ret->off_set = off_set;
    // Set the 'passage' field of the formal_parameter_av struct pointed to by 'ret' to the provided 'passage' argument.
    ret->passage = passage;
    // Cast 'ret' to a void pointer and return it.
    return (void *)ret;
}

// Function declaration: deleteFormalParameter takes a void pointer 'formal_parameter' as an argument and returns nothing (void).
void deleteFormalParameter(void *formal_parameter)
{
    // Check if 'formal_parameter' is not a null pointer (i.e., it points to a valid memory address).
    if (formal_parameter)
    {
        // If 'formal_parameter' is valid, free the memory it points to using the 'free' function.
        free(formal_parameter);
    }
    else
    {
        // If 'formal_parameter' is a null pointer (i.e., not valid), print an error message using the 'perror' function.
        perror("Formal parameter passed does not exist!");
        // Terminate the program with a non-zero exit status (1) to indicate that an error has occurred.
        exit(1);
    }
}

// Function declaration: setProcedure takes two arguments - a constant character pointer 'label' and an unsigned short int 'num_params'. It returns a void pointer.
void *setProcedure(const char *label, unsigned short int num_params)
{
    // Declare a pointer 'ret' of type procedure_av .
    procedure_av *ret;
    // Allocate memory for 'ret' with the size of procedure_av using malloc, and assign the memory address to 'ret'.
    ret = malloc(sizeof(procedure_av));
    // Allocate memory for 'ret->label' with the size equal to the length of the input 'label' string plus 1 (to account for the null-terminator), and assign the memory address to 'ret->label'.
    ret->label = malloc(strlen(label) + 1);
    // Copy the input 'label' string to the memory pointed to by 'ret->label' using the strcpy function.
    strcpy(ret->label, label);
    // Set the 'num_params' field of the procedure_av struct pointed to by 'ret' to the provided 'num_params' argument.
    ret->num_params = num_params;
    // Cast 'ret' to a void pointer and return it.
    return (void *)ret;
}

// Function declaration: deleteProcedure takes a void pointer 'procedure' as an argument and returns nothing (void).
void deleteProcedure(void *procedure)
{
    // Cast the input 'procedure' void pointer to a procedure_av pointer and assign it to a new pointer 'proc'.
    procedure_av *proc = (procedure_av *)procedure;
    // Check if 'proc' is not a null pointer (i.e., it points to a valid memory address).
    if (proc)
    {
        // Check if the 'label' field of the procedure_av struct pointed to by 'proc' is not a null pointer.
        if (proc->label)
        {
            // If 'proc->label' is valid, free the memory it points to using the 'free' function.
            free(proc->label);
        }
        // Set the 'params' field of the procedure_av struct pointed to by 'proc' to NULL.
        proc->params = NULL;
        // Free the memory pointed to by 'proc' using the 'free' function.
        free(proc);
    }
}

// Function declaration: setSymbol takes five arguments - a pointer to a symbols 'symbol' , a constant character pointer 'ident', two unsigned short ints 'cat' and 'niv', and a void pointer 'av'. The function returns nothing (void).
void setSymbol(symbols *symbol, const char *ident, unsigned short int cat, unsigned short int niv, void *av)
{
    // Allocate memory for 'symbol->id' with the size equal to the length of the input 'ident' string plus 1 (to account for the null-terminator), and assign the memory address to 'symbol->id'.
    symbol->id = malloc(strlen(ident) + 1);
    // Copy the input 'ident' string to the memory pointed to by 'symbol->id' using the strcpy function.
    strcpy(symbol->id, ident);
    // Set the 'category' field of the symbols struct pointed to by 'symbol' to the provided 'cat' argument.
    symbol->category = cat;
    // Set the 'level' field of the symbols struct pointed to by 'symbol' to the provided 'niv' argument.
    symbol->level = niv;
    // Set the 'var_attributes' field of the symbols struct pointed to by 'symbol' to the provided 'av' argument (void pointer).
    symbol->var_attributes = av;
}

// Function declaration: initializeSymbolsTable takes a pointer to a symbols_table 'table'  as an argument and returns nothing (void).
void initializeSymbolsTable(symbols_table *table)
{
    // Set the 'stack' field of the symbols_table struct pointed to by 'table' to NULL. This initializes the stack as empty.
    table->stack = NULL;
    // Set the 'size' field of the symbols_table struct pointed to by 'table' to 0. This indicates that there are currently no elements in the table.
    table->size = 0;
    // Set the 'allocated_size' field of the symbols_table struct pointed to by 'table' to 0. This indicates that no memory has been allocated yet for the table.
    table->allocated_size = 0;
}

// Function declaration: deleteAttributes takes a pointer to a symbols 'symbol'  as an argument and returns nothing (void).
void deleteAttributes(symbols *symbol)
{
    // Check if the 'id' field of the symbols struct pointed to by 'symbol' is not a null pointer.
    if (symbol->id)
    {
        // If 'symbol->id' is valid, free the memory it points to using the 'free' function.
        free(symbol->id);
    }
    // Check if the 'var_attributes' field of the symbols struct pointed to by 'symbol' is not a null pointer.
    if (symbol->var_attributes)
    {
        // If the 'category' field of the symbols struct pointed to by 'symbol' is equal to SIMPLE_VAR.
        if (symbol->category == SIMPLE_VAR)
        {
            // Call the deleteSimpleVar function to free the memory associated with the simple variable's attributes.
            deleteSimpleVar(symbol->var_attributes);
        }
        // Else if the 'category' field of the symbols struct pointed to by 'symbol' is equal to FORMAL_PARAMETER.
        else if (symbol->category == FORMAL_PARAMETER)
        {
            // Call the deleteFormalParameter function to free the memory associated with the formal parameter's attributes.
            deleteFormalParameter(symbol->var_attributes);
        }

        else // Else, it is assumed that the 'category' field is associated with a procedure.
        {
            // Call the deleteProcedure function to free the memory associated with the procedure's attributes.
            deleteProcedure(symbol->var_attributes);
        }
    }
}

// Function declaration: deleteSymbolsTable takes a pointer to a symbols_table 'table'  as an argument and returns nothing (void).
void deleteSymbolsTable(symbols_table *table)
{
    // Iterate through each element in the symbols table using a for loop with an unsigned int index 'i'.
    for (unsigned int i = 0; i < table->size; ++i)
    {
        // Call the deleteAttributes function on each element in the symbols table to free the memory associated with its attributes.
        deleteAttributes(&(table->stack[i]));
    }
    // Free the memory pointed to by the 'stack' field of the symbols_table struct pointed to by 'table' using the 'free' function.
    free(table->stack);
    // Set the 'size' field of the symbols_table struct pointed to by 'table' to 0. This indicates that there are currently no elements in the table.
    table->size = 0;
    // Set the 'allocated_size' field of the symbols_table struct pointed to by 'table' to 0. This indicates that no memory has been allocated yet for the table.
    table->allocated_size = 0;
}

// Function declaration: setParams takes a pointer to a symbols 'symbol' as an argument and returns nothing (void). The function sets a procedure to point to the position above in the stack if it has parameters.
void setParams(symbols *symbol)
{
    // Cast the 'var_attributes' field of the symbols struct pointed to by 'symbol' to a procedure_av pointer and assign it to a new pointer 'av'.
    procedure_av *av = (procedure_av *)symbol->var_attributes;
    // Check if the 'num_params' field of the procedure_av struct pointed to by 'av' is not zero (i.e., the procedure has parameters).
    if (av->num_params)
    {
        // Set the 'params' field of the procedure_av struct pointed to by 'av' to the memory address of the symbols struct that is right after 'symbol' in the stack.
        av->params = symbol + 1; // Position in the stack right after
    }
    else
    {
        // If the procedure has no parameters, set the 'params' field of the procedure_av struct pointed to by 'av' to NULL.
        av->params = NULL;
    }
}

// Function declaration: appendSymbol takes two arguments - a pointer to a symbols_table 'table'  and a pointer to a symbols 'symbol'. The function appends the symbol to the symbols table and returns nothing (void).
void appendSymbol(symbols_table *table, symbols *symbol)
{
    // Check if the allocated size of the symbols table is equal to its current size (i.e., it needs to be resized).
    if (table->allocated_size == table->size)
    {
        // Resize the 'stack' field of the symbols_table struct pointed to by 'table' using the realloc function. Increase the allocated size by ALLOC_STEP (assumed to be a constant) and multiply the result by the size of symbols.
        table->stack = realloc(table->stack, (table->allocated_size + ALLOC_STEP) * sizeof(symbols));
    }
    // Check if the 'category' field of the symbols struct pointed to by 'symbol' is equal to PROCEDURE_C.
    if (symbol->category == PROCEDURE_C)
    {
        // If the symbol is a procedure, call the setParams function to update the 'params' field of the procedure_av struct.
        setParams(symbol);
    }
    // Copy the contents of the memory pointed to by 'symbol' to the memory pointed to by the 'stack' field of the symbols_table struct, at the position 'table->size', using the memcpy function. The amount of memory to be copied is the size of symbols.
    memcpy(&(table->stack[table->size]), symbol, sizeof(symbols));

    // Increment the 'size' field of the symbols_table struct pointed to by 'table' by 1, indicating that a new symbol has been added to the table.
    table->size++;
}

// Function declaration: findSymbol takes two arguments - a pointer to a symbols_table 'table'  and a char pointer 'ident'. The function returns an integer representing the position of the symbol in the table. If the symbol is not found, it returns -1.
int findSymbol(symbols_table *table, char *ident)
{
    // Initialize an integer 'it' to the value of the 'size' field of the symbols_table struct pointed to by 'table' minus 1. This will be used as an iterator to traverse the table in reverse.
    int it = table->size - 1;
    // Use a while loop to iterate through the symbols table in reverse, starting from the last element.
    while (it >= 0)
    {
        // Check if the 'id' field of the symbols struct at the current position 'it' in the symbols table is equal to the input 'ident' using the strcmp function.
        if (!strcmp(table->stack[it].id, ident))
        {
            // If the 'id' field matches the input 'ident', return the current position 'it' in the symbols table. The level check is not yet implemented.
            return it; // need to test the level
        }
        // Decrement the iterator 'it' by 1 to continue the loop.
        it--;
    }
    // If the input 'ident' is not found in the symbols table, return the iterator 'it', which will be -1 at this point.
    return it;
}

// Function declaration: removeSymbol takes two arguments - a pointer to a symbols_table 'table'  and an unsigned integer 'n'. The function removes 'n' symbols from the symbols table and returns nothing (void).
void removeSymbol(symbols_table *table, unsigned int n)
{
    // Check if the input 'n' is greater than the 'size' field of the symbols_table struct pointed to by 'table'.
    if (n > table->size)
    {
        // If 'n' is greater than the size of the symbols table, print an error message to the standard error output and terminate the program with a non-zero exit status (1).
        fprintf(stderr, "Tried to remove to many elements from the table!\n");
        exit(1);
    }
    // Use a while loop to unstack and free each element in the symbols table, decrementing 'n' until it reaches 0.
    while (n)
    {
        // Decrement the 'size' field of the symbols_table struct pointed to by 'table' by 1.
        table->size--;
        // Call the deleteAttributes function to free the memory associated with the attributes of the symbols struct at the current position 'table->size' in the symbols table.
        deleteAttributes( &(table->stack[table->size]) );
        // Decrement 'n' by 1 to continue the loop.
        n--;
    }
    // Reallocation phase: calculate the number of exceeding_blocks (number of unused memory blocks) by dividing the difference between 'allocated_size' and 'size' by ALLOC_STEP (assumed to be a constant).
    unsigned int exceeding_blocks = (table->allocated_size - table->size) / ALLOC_STEP;
    // Check if there are any exceeding_blocks.
    if (exceeding_blocks)
    {
        // If there are exceeding_blocks, calculate the new allocated size 'new_size' by subtracting the product of exceeding_blocks and ALLOC_STEP from 'allocated_size'.
        unsigned int new_size = table->allocated_size - exceeding_blocks * ALLOC_STEP;
        // Resize the 'stack' field of the symbols_table struct pointed to by 'table' using the realloc function, with the new allocated size 'new_size' multiplied by the size of symbols.
        table->stack = realloc(table->stack, new_size * sizeof(symbols));
        // Update the 'allocated_size' field of the symbols_table struct pointed to by 'table' with the new allocated size 'new_size'.
        table->allocated_size = new_size;
    }
}