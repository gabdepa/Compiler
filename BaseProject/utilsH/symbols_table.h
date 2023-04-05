#ifndef __SYMBOLS_TABLE__
#define __SYMBOLS_TABLE__

#define ALLOC_STEP 1024

#define CAT_INDEFINIDA 0
#define SIMPLE_VAR 1
#define FORMAL_PARAMETER 2
#define PROCEDURE 3

#define VALUE_PASSAGE 1
#define REFERENCE_PASSAGE 2

#define INT_TYPE 1

typedef struct symbols_s
{
    char *id;
    unsigned short int category;
    unsigned short int level;
    void *var_attributes;
} symbols;

typedef struct symbols_table_s
{
    symbols *stack;
    unsigned int size;
    unsigned int alloc_size;
} symbols_table;

typedef struct simple_var_av_s
{
    unsigned short int type;
    unsigned int off_set;
} simple_var_av;

typedef struct formal_parameter_av_s
{
    unsigned short int type;
    unsigned int off_set;
    unsigned short int passage;
} formal_parameter_av;

typedef struct procedure_av_s
{
    char *label;
    unsigned short int num_params;
    symbols *params;
} procedure_av;

// Function declaration: setSimpleVar takes two arguments, an unsigned short int 'type', and an unsigned int 'off_set', and returns a void pointer.
void *setSimpleVar(unsigned short int type, unsigned int off_set);
// Function declaration: deleteSimpleVar takes a void pointer 'simple_var' as an argument and returns nothing (void).
void deleteSimpleVar(void *var_simples);
// Function declaration: setFormalParameter takes three arguments - an unsigned short int 'type', an unsigned int 'off_set', and an unsigned short int 'passage'. It returns a void pointer.
void *setFormalParameter(unsigned short int type, unsigned int off_set, unsigned short int passage);
// Function declaration: deleteFormalParameter takes a void pointer 'formal_parameter' as an argument and returns nothing (void).
void deleteFormalParameter(void *parametro_formal);

// Function declaration: setProcedure takes two arguments - a constant character pointer 'label' and an unsigned short int 'num_params'. It returns a void pointer.
void *setProcedure(const char *label, unsigned short int num_params);
// Function declaration: deleteProcedure takes a void pointer 'procedure' as an argument and returns nothing (void).
void deleteProcedure(void *procedimento);

// Function declaration: setSymbol takes five arguments - a pointer to a symbols 'symbol' , a constant character pointer 'ident', two unsigned short ints 'cat' and 'niv', and a void pointer 'av'. The function returns nothing (void).
void setSymbol(symbols *simb, const char *ident, unsigned short int cat, unsigned short int niv, void *av);
// Function declaration: initializeSymbolsTable takes a pointer to a symbols_table 'table'  as an argument and returns nothing (void).
void initializeSymbolsTable(symbols_table *tab);
// Function declaration: deleteAttributes takes a pointer to a symbols 'symbol'  as an argument and returns nothing (void).
void deleteAttributes(symbols *simb);
// Function declaration: deleteSymbolsTable takes a pointer to a symbols_table 'table'  as an argument and returns nothing (void).
void deleteSymbolsTable(symbols_table *tab);

// Function declaration: setParams takes a pointer to a symbols 'symbol' as an argument and returns nothing (void). The function sets a procedure to point to the position above in the stack if it has parameters.
void setParams(symbols *simb);

// Function declaration: appendSymbol takes two arguments - a pointer to a symbols_table 'table'  and a pointer to a symbols 'symbol'. The function appends the symbol to the symbols table and returns nothing (void).
void appendSymbol(symbols_table *tab, symbols *simb);
// Function declaration: findSymbol takes two arguments - a pointer to a symbols_table 'table'  and a char pointer 'ident'. The function returns an integer representing the position of the symbol in the table. If the symbol is not found, it returns -1.
int findSymbol(symbols_table *tab, char *ident);
// Function declaration: removeSymbol takes two arguments - a pointer to a symbols_table 'table'  and an unsigned integer 'n'. The function removes 'n' symbols from the symbols table and returns nothing (void).
void removeSymbol(symbols_table *tab, unsigned int n);

#endif