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
} symbols_t;

typedef struct simple_var_av_s
{
    unsigned short int type;
    unsigned int off_set;
} simple_var_av_t;

typedef struct formal_parameter_av_s
{
    unsigned short int type;
    unsigned int off_set;
    unsigned short int passage;
} formal_parameter_av_t;

typedef struct procedure_av_s
{
    char *label;
    unsigned short int num_params;
    symbols_t *params;
} procedure_av_t;

typedef struct symbols_table_s
{
    symbols_t *stack;
    unsigned int size;
    unsigned int alloc_size;
} symbols_table_t;

void *new_simple_var(unsigned short int type, unsigned int off_set);
void destruct_simple_var(void *var_simples);

void *new_formal_parameter(unsigned short int type, unsigned int off_set, unsigned short int passage);
void destruct_formal_parameter(void *parametro_formal);

void *new_procedure(const char *label, unsigned short int num_params);
void destruct_procedure(void *procedimento);

void set_symbol(symbols_t *simb, const char *ident, unsigned short int cat, unsigned short int niv, void *av);
symbols_t *symbols_table_head(symbols_table_t *tab);

void init_symbols_table(symbols_table_t *tab);
void destruct_symbols_table(symbols_table_t *tab);
void symbols_table_append(symbols_table_t *tab, symbols_t *simb);
int symbols_table_search(symbols_table_t *tab, char *ident);
void symbols_table_remove(symbols_table_t *tab, unsigned int n);

#endif