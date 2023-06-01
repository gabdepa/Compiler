#ifndef __SYMBOLS_TABLE__
#define __SYMBOLS_TABLE__

#include <stdbool.h>

enum symbol_type
{
    variable,
    parameter,
    procedure,
    function
};

enum variable_type
{
    pas_integer,
    pas_float,
    pas_boolean,
    undefined_type
};

enum passage_type
{
    copy_parameter,
    reference_parameter
};

/* 3 symbols type */
struct variable
{
    int type;
    int offset;
};

struct parameter
{
    int type;
    int offset;
    int passage;
};

struct procedure
{
    int label;
    int parameters_quantity;
    struct parameter list[128];
};
/*------------------------*/

struct symbol
{
    char *id;
    int category;
    int level;
    struct content
    {
        struct variable var;
        struct parameter param;
        struct procedure proc;
    } content;
};

struct symbol symbol_init(char *id, int cat, int level, struct content content);

struct symbol_table
{
    struct symbol *symbols;
    unsigned int quantity;
    unsigned int size;
};

void table_init(struct symbol_table **ts);

void push(struct symbol_table **ts, struct symbol s);

struct symbol pop(struct symbol_table **ts);

void remove_n(struct symbol_table **ts, int n);

struct symbol *search(struct symbol_table **ts, const char *name);

void set_type(struct symbol_table **ts, int category, int type, int quantity);

#endif