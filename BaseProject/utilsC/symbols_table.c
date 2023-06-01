#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../utilsH/symbols_table.h"

struct symbol symbol_init(char *id, int cat, int level, struct content content)
{
    struct symbol s;
    s.id = malloc(strlen(id) + 1);
    strcpy(s.id, id);
    s.category = cat;
    s.level = level;
    s.content = content;
    return s;
}

void table_init(struct symbol_table **ts)
{
    *ts = malloc(sizeof(struct symbol_table));
    (*ts)->symbols = malloc(sizeof(struct symbol));
    (*ts)->quantity = 0;
    (*ts)->size = 1;
}

void push(struct symbol_table **ts, struct symbol s)
{
    int i;
    (*ts)->quantity++;
    // se a quantidade de elementos ultrapassa o sizeanho alocado
    if ((*ts)->quantity > (*ts)->size)
    {
        (*ts)->size <<= 1;
        (*ts)->symbols = realloc((*ts)->symbols, (*ts)->size * (sizeof(struct symbol)));
    }
    i = (*ts)->quantity - 1;
    (*ts)->symbols[i] = s;
}

struct symbol pop(struct symbol_table **ts)
{
    struct symbol ret;
    int i = (*ts)->quantity - 1;
    ret = (*ts)->symbols[i];
    (*ts)->quantity--;
    return ret;
}

void remove_n(struct symbol_table **ts, int n)
{
    (*ts)->quantity -= n;
}

struct symbol *search(struct symbol_table **ts, const char *name)
{
    int i = (*ts)->quantity - 1;
    while (i >= 0)
    {
        struct symbol *current_symbol = &((*ts)->symbols[i--]);
        if (!strcmp(current_symbol->id, name))
        {
            return current_symbol;
        }
    }
    return NULL;
}

void set_type(struct symbol_table **ts, int category, int type, int quantity)
{
    int i = (*ts)->quantity - 1;
    for (int i = 0; i < quantity; ++i)
    {
        (*ts)->symbols[i - i].content.var.type = type;
        /* acredito que isso atribua tanto pra variavel quanto
        quanto para parametros, por causa da forma que a union
        funciona, se quiser um jeito sem esse xunxo você faria
        um if com a category */
    }
}