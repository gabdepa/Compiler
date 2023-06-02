/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "compilador.y"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./utilsH/compilador.h"
#include "./utilsH/symbols_table.h"
#include "./utilsH/stack.h"

int num_vars;
int num_params; // número de parâmetros do procedure atual
int curr_section_params; // número de parâmetros da seção atual => seção é aquela separada por ';'
int curr_call_params;
int level_lex;
int pos_var;
int qt_type_atual;
int referencia; // indica se a seção atual é por referência, se não for, é por cópia
//int dentro_proc; /* indica se estamos dentro de um procedure, mas acho que não precisa por conta da forma das structs
//                     usada na linha ~470 */
int dentro_chamada_proc; // indica se está dentro de uma chamada de procedure
int nr_procs_for_curr_proc;
int atribui;

char mepa_buf[128], proc_name[128], idents[128][128];
struct symbol_table *ts, *pilha_atribuicao;
struct symbol s, *sptr, *sptr_var_proc, *sptr_chamada_proc, *sptr_atribuicao, curr_proc, list_symbols[128];
struct stack_int pilha_labels, pilha_amem, pilha_procs;
struct stack_symbols_table pilha_ident_esquerdo;
struct parameter list_parameters[128];
struct content ti;


int str2type(const char *str){
   if (!strcmp(str, "integer")) return pas_integer;
   if (!strcmp(str, "boolean")) return pas_boolean;
   return undefined_type;
}
short int rot_num;
char rot_str[4];
int rot_w;


#line 114 "compilador.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "compilador.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_LABEL = 4,                      /* LABEL  */
  YYSYMBOL_TYPE = 5,                       /* TYPE  */
  YYSYMBOL_ARRAY = 6,                      /* ARRAY  */
  YYSYMBOL_OF = 7,                         /* OF  */
  YYSYMBOL_VAR = 8,                        /* VAR  */
  YYSYMBOL_PROCEDURE = 9,                  /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 10,                  /* FUNCTION  */
  YYSYMBOL_T_BEGIN = 11,                   /* T_BEGIN  */
  YYSYMBOL_T_END = 12,                     /* T_END  */
  YYSYMBOL_GOTO = 13,                      /* GOTO  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_DIV = 22,                       /* DIV  */
  YYSYMBOL_ATRIBUICAO = 23,                /* ATRIBUICAO  */
  YYSYMBOL_PONTO_E_VIRGULA = 24,           /* PONTO_E_VIRGULA  */
  YYSYMBOL_DOIS_PONTOS = 25,               /* DOIS_PONTOS  */
  YYSYMBOL_VIRGULA = 26,                   /* VIRGULA  */
  YYSYMBOL_PONTO = 27,                     /* PONTO  */
  YYSYMBOL_ABRE_PARENTESES = 28,           /* ABRE_PARENTESES  */
  YYSYMBOL_FECHA_PARENTESES = 29,          /* FECHA_PARENTESES  */
  YYSYMBOL_ABRE_COLCHETES = 30,            /* ABRE_COLCHETES  */
  YYSYMBOL_FECHA_COLCHETES = 31,           /* FECHA_COLCHETES  */
  YYSYMBOL_ABRE_CHAVES = 32,               /* ABRE_CHAVES  */
  YYSYMBOL_FECHA_CHAVES = 33,              /* FECHA_CHAVES  */
  YYSYMBOL_IDENT = 34,                     /* IDENT  */
  YYSYMBOL_MAIOR = 35,                     /* MAIOR  */
  YYSYMBOL_MENOR = 36,                     /* MENOR  */
  YYSYMBOL_IGUAL = 37,                     /* IGUAL  */
  YYSYMBOL_MAIS = 38,                      /* MAIS  */
  YYSYMBOL_MENOS = 39,                     /* MENOS  */
  YYSYMBOL_VEZES = 40,                     /* VEZES  */
  YYSYMBOL_NUMERO = 41,                    /* NUMERO  */
  YYSYMBOL_DIFERENTE = 42,                 /* DIFERENTE  */
  YYSYMBOL_MENOR_IGUAL = 43,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR_IGUAL = 44,               /* MAIOR_IGUAL  */
  YYSYMBOL_VALOR_BOOL = 45,                /* VALOR_BOOL  */
  YYSYMBOL_TIPO = 46,                      /* TIPO  */
  YYSYMBOL_READ = 47,                      /* READ  */
  YYSYMBOL_WRITE = 48,                     /* WRITE  */
  YYSYMBOL_49_lower_then_else_ = 49,       /* "lower_then_else"  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_programa = 51,                  /* programa  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_block = 53,                     /* block  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_55_3 = 55,                      /* $@3  */
  YYSYMBOL_parte_declara_vars = 56,        /* parte_declara_vars  */
  YYSYMBOL_57_4 = 57,                      /* $@4  */
  YYSYMBOL_declara_vars = 58,              /* declara_vars  */
  YYSYMBOL_declara_var = 59,               /* declara_var  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_type = 62,                      /* type  */
  YYSYMBOL_id_list = 63,                   /* id_list  */
  YYSYMBOL_ident_params = 64,              /* ident_params  */
  YYSYMBOL_list_id_var = 65,               /* list_id_var  */
  YYSYMBOL_parte_declara_subrotinas = 66,  /* parte_declara_subrotinas  */
  YYSYMBOL_declara_proc = 67,              /* declara_proc  */
  YYSYMBOL_68_7 = 68,                      /* $@7  */
  YYSYMBOL_69_8 = 69,                      /* $@8  */
  YYSYMBOL_70_9 = 70,                      /* $@9  */
  YYSYMBOL_declara_func = 71,              /* declara_func  */
  YYSYMBOL_72_10 = 72,                     /* $@10  */
  YYSYMBOL_73_11 = 73,                     /* $@11  */
  YYSYMBOL_74_12 = 74,                     /* $@12  */
  YYSYMBOL_parameters_formais_ou_nada = 75, /* parameters_formais_ou_nada  */
  YYSYMBOL_parameters_formais = 76,        /* parameters_formais  */
  YYSYMBOL_parameters = 77,                /* parameters  */
  YYSYMBOL_secao_parameters = 78,          /* secao_parameters  */
  YYSYMBOL_79_13 = 79,                     /* $@13  */
  YYSYMBOL_var_ou_nada = 80,               /* var_ou_nada  */
  YYSYMBOL_comando_composto = 81,          /* comando_composto  */
  YYSYMBOL_comandos = 82,                  /* comandos  */
  YYSYMBOL_comando_sem_label = 83,         /* comando_sem_label  */
  YYSYMBOL_leitura = 84,                   /* leitura  */
  YYSYMBOL_leitura_itens = 85,             /* leitura_itens  */
  YYSYMBOL_item_leitura = 86,              /* item_leitura  */
  YYSYMBOL_escrita = 87,                   /* escrita  */
  YYSYMBOL_escreve_itens = 88,             /* escreve_itens  */
  YYSYMBOL_atribuicao_proc = 89,           /* atribuicao_proc  */
  YYSYMBOL_90_14 = 90,                     /* $@14  */
  YYSYMBOL_a_continua = 91,                /* a_continua  */
  YYSYMBOL_92_15 = 92,                     /* $@15  */
  YYSYMBOL_atribuicao = 93,                /* atribuicao  */
  YYSYMBOL_procedure = 94,                 /* procedure  */
  YYSYMBOL_95_16 = 95,                     /* $@16  */
  YYSYMBOL_96_17 = 96,                     /* $@17  */
  YYSYMBOL_procedure_sem_parameter = 97,   /* procedure_sem_parameter  */
  YYSYMBOL_comando_repetitivo = 98,        /* comando_repetitivo  */
  YYSYMBOL_99_18 = 99,                     /* $@18  */
  YYSYMBOL_100_19 = 100,                   /* $@19  */
  YYSYMBOL_comando_sem_label_ou_composto = 101, /* comando_sem_label_ou_composto  */
  YYSYMBOL_comando_condicional = 102,      /* comando_condicional  */
  YYSYMBOL_103_20 = 103,                   /* $@20  */
  YYSYMBOL_104_21 = 104,                   /* $@21  */
  YYSYMBOL_else_ou_nada = 105,             /* else_ou_nada  */
  YYSYMBOL_list_expressoes = 106,          /* list_expressoes  */
  YYSYMBOL_107_22 = 107,                   /* $@22  */
  YYSYMBOL_expression = 108,               /* expression  */
  YYSYMBOL_relation = 109,                 /* relation  */
  YYSYMBOL_simple_expression = 110,        /* simple_expression  */
  YYSYMBOL_plus_minus_empty = 111,         /* plus_minus_empty  */
  YYSYMBOL_plus_minus_or = 112,            /* plus_minus_or  */
  YYSYMBOL_term = 113,                     /* term  */
  YYSYMBOL_times_div_and = 114,            /* times_div_and  */
  YYSYMBOL_procedure_ou_nada = 115,        /* procedure_ou_nada  */
  YYSYMBOL_factor = 116,                   /* factor  */
  YYSYMBOL_117_23 = 117                    /* $@23  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   114

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    78,    95,   106,    93,   126,   126,   131,
     135,   136,   139,   142,   139,   146,   150,   153,   155,   163,
     169,   178,   179,   180,   186,   191,   223,   184,   238,   246,
     277,   236,   290,   290,   292,   297,   297,   301,   300,   315,
     315,   318,   322,   322,   325,   326,   327,   328,   329,   330,
     333,   335,   335,   338,   352,   354,   354,   358,   357,   368,
     368,   369,   370,   373,   402,   420,   402,   437,   448,   455,
     448,   471,   471,   475,   488,   475,   504,   505,   511,   510,
     517,   523,   524,   535,   536,   537,   538,   539,   540,   544,
     562,   578,   579,   580,   583,   584,   585,   589,   606,   609,
     610,   611,   615,   619,   625,   624,   687,   692,   700,   701
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "LABEL",
  "TYPE", "ARRAY", "OF", "VAR", "PROCEDURE", "FUNCTION", "T_BEGIN",
  "T_END", "GOTO", "IF", "THEN", "ELSE", "WHILE", "DO", "OR", "AND", "NOT",
  "DIV", "ATRIBUICAO", "PONTO_E_VIRGULA", "DOIS_PONTOS", "VIRGULA",
  "PONTO", "ABRE_PARENTESES", "FECHA_PARENTESES", "ABRE_COLCHETES",
  "FECHA_COLCHETES", "ABRE_CHAVES", "FECHA_CHAVES", "IDENT", "MAIOR",
  "MENOR", "IGUAL", "MAIS", "MENOS", "VEZES", "NUMERO", "DIFERENTE",
  "MENOR_IGUAL", "MAIOR_IGUAL", "VALOR_BOOL", "TIPO", "READ", "WRITE",
  "\"lower_then_else\"", "$accept", "programa", "$@1", "block", "$@2",
  "$@3", "parte_declara_vars", "$@4", "declara_vars", "declara_var", "$@5",
  "$@6", "type", "id_list", "ident_params", "list_id_var",
  "parte_declara_subrotinas", "declara_proc", "$@7", "$@8", "$@9",
  "declara_func", "$@10", "$@11", "$@12", "parameters_formais_ou_nada",
  "parameters_formais", "parameters", "secao_parameters", "$@13",
  "var_ou_nada", "comando_composto", "comandos", "comando_sem_label",
  "leitura", "leitura_itens", "item_leitura", "escrita", "escreve_itens",
  "atribuicao_proc", "$@14", "a_continua", "$@15", "atribuicao",
  "procedure", "$@16", "$@17", "procedure_sem_parameter",
  "comando_repetitivo", "$@18", "$@19", "comando_sem_label_ou_composto",
  "comando_condicional", "$@20", "$@21", "else_ou_nada", "list_expressoes",
  "$@22", "expression", "relation", "simple_expression",
  "plus_minus_empty", "plus_minus_or", "term", "times_div_and",
  "procedure_ou_nada", "factor", "$@23", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-139)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-81)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -139,     7,    44,  -139,    11,    -7,    15,  -139,    35,  -139,
      15,    45,  -139,    62,    47,  -139,    63,  -139,  -139,  -139,
       5,    38,  -139,    41,    43,    46,    65,  -139,  -139,  -139,
    -139,     6,  -139,  -139,    -4,  -139,    32,    48,    51,    51,
      18,  -139,  -139,    53,    55,    24,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,    76,  -139,  -139,    61,  -139,
    -139,  -139,    16,   -12,    18,    -5,    54,    18,  -139,    -4,
      66,  -139,    10,  -139,  -139,    67,    32,    72,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,    18,   -12,   -12,
      18,  -139,  -139,  -139,    -3,  -139,  -139,  -139,  -139,  -139,
      64,  -139,  -139,    36,  -139,    37,  -139,  -139,  -139,    76,
    -139,    15,    62,  -139,    -6,   -13,    -3,  -139,    68,    70,
    -139,  -139,  -139,   -12,    75,    18,  -139,    54,  -139,    18,
    -139,  -139,    42,  -139,    71,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,    -6,  -139,  -139,    18,  -139,  -139,    32,    77,
      62,    78,  -139,    73,    74,  -139,  -139,  -139,    -6,  -139,
    -139,    79,    80,  -139,    18,  -139,  -139
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    18,     0,    17,
       0,     0,    16,     9,     0,     4,     0,     3,    23,    12,
       5,     8,    11,     0,     0,     0,     0,    21,    22,    10,
      20,     0,    24,    28,    49,     6,     0,     0,    33,    33,
      93,    68,    57,     0,     0,     0,    42,    48,    47,    44,
      45,    46,    15,    13,    19,    40,    25,    32,     0,    91,
      92,    73,    81,     0,    93,    67,     0,    93,    41,    49,
       0,    39,     0,    36,    37,     0,     0,     0,    96,    88,
      85,    83,    94,    95,    84,    86,    87,    93,     0,     0,
      93,   104,   106,   107,    90,    98,    69,    59,    58,    62,
       0,    61,    53,     0,    52,     0,    56,    43,    14,    40,
      34,     0,     9,    29,    49,    82,    89,   109,     0,   103,
     101,   100,    99,     0,     0,    93,    65,     0,    50,    93,
      54,    35,     0,    26,     0,    72,    71,    74,   108,   102,
     105,    97,    49,    60,    63,    93,    51,    55,     0,     0,
       9,    77,    70,     0,    78,    38,    27,    30,    49,    75,
      66,     0,     0,    76,    93,    31,    79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -139,  -139,  -139,  -110,  -139,  -139,  -139,  -139,  -139,    85,
    -139,  -139,   -75,   -15,    89,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,    69,  -139,  -139,    -9,  -139,
    -139,    81,  -139,   -31,  -139,  -139,   -18,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,    -8,  -139,  -139,  -139,  -139,  -139,
    -139,  -138,  -139,  -139,  -139,  -139,   -54,  -139,   -40,  -139,
      25,  -139,  -139,    26,  -139,  -139,   -77,  -139
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    18,    26,    15,    16,    21,    22,
      23,    70,    53,     8,     9,    31,    20,    27,    38,    75,
     149,    28,    39,   134,   162,    56,    57,    72,    73,   111,
      74,   135,    45,   136,    47,   103,   104,    48,   105,    49,
      65,    98,   125,   143,    99,   100,   145,   101,    50,    64,
     124,   137,    51,    77,   151,   159,   153,   161,   154,    87,
      62,    63,    88,    94,   123,   140,    95,   119
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   113,   133,    46,   152,    34,    78,     3,    40,    89,
      40,    41,   117,    41,    24,    25,    90,   120,    97,   121,
     163,     6,    91,   -64,    96,    82,    83,   106,    42,    92,
      42,    36,    37,    93,   109,    78,    68,   122,   107,   110,
     157,    43,    44,    43,    44,     5,   141,     4,    69,     7,
     118,    79,    80,    81,    82,    83,    59,    60,    84,    85,
      86,    10,   127,   129,    11,   128,   130,   148,    10,    13,
      -7,    19,   -12,   155,    17,    30,    34,    32,    52,    55,
      33,    66,    54,    67,    71,   144,    76,   114,   102,   147,
     108,   112,   126,   142,   158,   150,   132,   138,   -64,    12,
     131,   156,   160,   -80,   165,   164,    29,    35,    58,   146,
     166,   139,   115,     0,   116
};

static const yytype_int16 yycheck[] =
{
      40,    76,   112,    34,   142,    11,    19,     0,    14,    21,
      14,    17,    89,    17,     9,    10,    28,    20,    23,    22,
     158,    28,    34,    28,    64,    38,    39,    67,    34,    41,
      34,    25,    26,    45,    24,    19,    12,    40,    69,    29,
     150,    47,    48,    47,    48,    34,   123,     3,    24,    34,
      90,    35,    36,    37,    38,    39,    38,    39,    42,    43,
      44,    26,    26,    26,    29,    29,    29,    25,    26,    24,
       8,     8,    34,   148,    27,    34,    11,    34,    46,    28,
      34,    28,    34,    28,     8,   125,    25,    15,    34,   129,
      24,    24,    28,    18,    16,    24,   111,    29,    28,    10,
     109,    24,    29,    29,    24,    26,    21,    26,    39,   127,
     164,   119,    87,    -1,    88
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    52,     0,     3,    34,    28,    34,    63,    64,
      26,    29,    64,    24,    53,    56,    57,    27,    54,     8,
      66,    58,    59,    60,     9,    10,    55,    67,    71,    59,
      34,    65,    34,    34,    11,    81,    25,    26,    68,    72,
      14,    17,    34,    47,    48,    82,    83,    84,    87,    89,
      98,   102,    46,    62,    34,    28,    75,    76,    75,    38,
      39,   108,   110,   111,    99,    90,    28,    28,    12,    24,
      61,     8,    77,    78,    80,    69,    25,   103,    19,    35,
      36,    37,    38,    39,    42,    43,    44,   109,   112,    21,
      28,    34,    41,    45,   113,   116,   108,    23,    91,    94,
      95,    97,    34,    85,    86,    88,   108,    83,    24,    24,
      29,    79,    24,    62,    15,   110,   113,   116,   108,   117,
      20,    22,    40,   114,   100,    92,    28,    26,    29,    26,
      29,    78,    63,    53,    73,    81,    83,   101,    29,    94,
     115,   116,    18,    93,   108,    96,    86,   108,    25,    70,
      24,   104,   101,   106,   108,    62,    24,    53,    16,   105,
      29,   107,    74,   101,    26,    24,   106
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    52,    51,    54,    55,    53,    57,    56,    56,
      58,    58,    60,    61,    59,    62,    63,    63,    64,    65,
      65,    66,    66,    66,    68,    69,    70,    67,    72,    73,
      74,    71,    75,    75,    76,    77,    77,    79,    78,    80,
      80,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      84,    85,    85,    86,    87,    88,    88,    90,    89,    92,
      91,    91,    91,    93,    95,    96,    94,    97,    99,   100,
      98,   101,   101,   103,   104,   102,   105,   105,   107,   106,
     106,   108,   108,   109,   109,   109,   109,   109,   109,   110,
     110,   111,   111,   111,   112,   112,   112,   113,   113,   114,
     114,   114,   115,   115,   117,   116,   116,   116,   116,   116
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     5,     0,     3,     0,
       2,     1,     0,     0,     6,     1,     3,     1,     1,     3,
       1,     2,     2,     0,     0,     0,     0,     9,     0,     0,
       0,    11,     1,     0,     3,     3,     1,     0,     5,     1,
       0,     3,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     1,     1,     4,     3,     1,     0,     3,     0,
       3,     1,     1,     1,     0,     0,     5,     0,     0,     0,
       6,     1,     1,     0,     0,     7,     2,     0,     0,     4,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       2,     1,     1,     0,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     0,     0,     3,     1,     1,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 78 "compilador.y"
             {
             geraCodigo (NULL, "INPP");
             level_lex = 0;
             rot_num = 0;
             dentro_chamada_proc = 0;
             }
#line 1347 "compilador.tab.c"
    break;

  case 3: /* programa: $@1 PROGRAM IDENT ABRE_PARENTESES id_list FECHA_PARENTESES PONTO_E_VIRGULA block PONTO  */
#line 86 "compilador.y"
                         {
             geraCodigo (NULL, "PARA");
             }
#line 1355 "compilador.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 95 "compilador.y"
              {
               sprintf(mepa_buf, "DSVS R%02d", rot_num);
               geraCodigo(NULL, mepa_buf);
               stack_push(&pilha_labels, rot_num, NULL, NULL); // stack_int_push
               rot_num++;
               level_lex++;
               nr_procs_for_curr_proc = 0;
              }
#line 1368 "compilador.tab.c"
    break;

  case 5: /* $@3: %empty  */
#line 106 "compilador.y"
              {
               stack_push(&pilha_procs, nr_procs_for_curr_proc, NULL, NULL); // stack_int_push
               level_lex--;

               sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels));
               geraCodigo(rot_str, "NADA");
               stack_int_pop(&pilha_labels);
              }
#line 1381 "compilador.tab.c"
    break;

  case 6: /* block: parte_declara_vars $@2 parte_declara_subrotinas $@3 comando_composto  */
#line 116 "compilador.y"
              {
               sprintf(mepa_buf, "DMEM %d", stack_int_head(&pilha_amem));
               remove_n(&ts, stack_int_head(&pilha_amem));
               geraCodigo(NULL, mepa_buf);
               stack_int_pop(&pilha_amem);
              }
#line 1392 "compilador.tab.c"
    break;

  case 7: /* $@4: %empty  */
#line 126 "compilador.y"
                    { num_vars = 0; }
#line 1398 "compilador.tab.c"
    break;

  case 8: /* parte_declara_vars: $@4 VAR declara_vars  */
#line 126 "compilador.y"
                                                       { 
               sprintf(mepa_buf, "AMEM %d", num_vars);
               geraCodigo(NULL, mepa_buf);
               stack_push(&pilha_amem, num_vars, NULL, NULL); // stack_int_push
               }
#line 1408 "compilador.tab.c"
    break;

  case 9: /* parte_declara_vars: %empty  */
#line 131 "compilador.y"
              {stack_push(&pilha_amem, 0, NULL, NULL);}
#line 1414 "compilador.tab.c"
    break;

  case 12: /* $@5: %empty  */
#line 139 "compilador.y"
              { qt_type_atual = 0; }
#line 1420 "compilador.tab.c"
    break;

  case 13: /* $@6: %empty  */
#line 142 "compilador.y"
              { set_type(&ts, variable, (yyvsp[0].int_val), qt_type_atual); }
#line 1426 "compilador.tab.c"
    break;

  case 15: /* type: TIPO  */
#line 146 "compilador.y"
                   { (yyval.int_val) = str2type(token); }
#line 1432 "compilador.tab.c"
    break;

  case 18: /* ident_params: IDENT  */
#line 156 "compilador.y"
              {
               strcpy(idents[num_params], token);
               list_parameters[num_params].passage = referencia? reference_parameter : copy_parameter;
               num_params++;
               curr_section_params++;
              }
#line 1443 "compilador.tab.c"
    break;

  case 19: /* list_id_var: list_id_var VIRGULA IDENT  */
#line 163 "compilador.y"
                                       {
               ti.var.offset = num_vars;
               s = symbol_init(token, variable, level_lex, ti); 
               push(&ts, s);
               num_vars++; qt_type_atual++;
            }
#line 1454 "compilador.tab.c"
    break;

  case 20: /* list_id_var: IDENT  */
#line 169 "compilador.y"
                    { 
               ti.var.offset = num_vars;
               s = symbol_init(token, variable, level_lex, ti); 
               push(&ts, s);
               num_vars++; qt_type_atual++;
            }
#line 1465 "compilador.tab.c"
    break;

  case 21: /* parte_declara_subrotinas: parte_declara_subrotinas declara_proc  */
#line 178 "compilador.y"
                                                                {nr_procs_for_curr_proc++;}
#line 1471 "compilador.tab.c"
    break;

  case 24: /* $@7: %empty  */
#line 186 "compilador.y"
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
#line 1480 "compilador.tab.c"
    break;

  case 25: /* $@8: %empty  */
#line 191 "compilador.y"
              {
               sprintf(rot_str, "R%02d", rot_num);
               sprintf(mepa_buf, "ENPR %d", level_lex);
               geraCodigo(rot_str, mepa_buf);
               
               ti.proc.label = rot_num;
               ti.proc.parameters_quantity = num_params;

               memcpy(ti.proc.list, list_parameters, sizeof(struct parameter)*num_params);
               
               // for(int i = 0; i < num_params; ++i){
               //    printf("proc.list[%d] tem type %d e passado por %d \n", i, ti.proc.list[i].type, ti.proc.list[i].passage);
               // }
               printf("nome: %s level: %d desloca: %d\n",proc_name, level_lex, ti.var.offset);

               s = symbol_init(proc_name, procedure, level_lex, ti);
               push(&ts, s);

               // atribui o offset correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  list_symbols[i].content.param.offset = -4 + (i - (num_params-1)); 
                  printf(">>>>>>>>> Parametro %s tem offset %d\n", list_symbols[i].id, list_symbols[i].content.param.offset);
                  push(&ts, list_symbols[i]);
               }
               rot_num++; // para o desvio de procedures dentro dessa procedure
               stack_push(&pilha_amem, num_params, NULL, NULL); // stack_int_push

               // dentro_proc = 1;
              }
#line 1514 "compilador.tab.c"
    break;

  case 26: /* $@9: %empty  */
#line 223 "compilador.y"
              {
               remove_n(&ts, stack_int_head(&pilha_amem));
               sprintf(mepa_buf, "RTPR %d, %d", level_lex, stack_int_head(&pilha_amem));
               stack_int_pop(&pilha_amem);
               remove_n(&ts, stack_int_head(&pilha_procs));
               stack_int_pop(&pilha_procs);
               geraCodigo(NULL, mepa_buf);
              }
#line 1527 "compilador.tab.c"
    break;

  case 28: /* $@10: %empty  */
#line 238 "compilador.y"
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
#line 1536 "compilador.tab.c"
    break;

  case 29: /* $@11: %empty  */
#line 246 "compilador.y"
              {
               sprintf(rot_str, "R%02d", rot_num);
               sprintf(mepa_buf, "ENPR %d", level_lex);
               geraCodigo(rot_str, mepa_buf);
               
               ti.proc.label = rot_num;
               ti.proc.parameters_quantity = num_params;

               memcpy(ti.proc.list, list_parameters, sizeof(struct parameter)*num_params);
               
               // for(int i = 0; i < num_params; ++i){
               //    printf("proc.list[%d] tem type %d e passado por %d \n", i, ti.proc.list[i].type, ti.proc.list[i].passage);
               // }
               ti.var.type = (yyvsp[0].int_val);
               ti.var.offset = -4 - num_params;
               s = symbol_init(proc_name, function, level_lex, ti);
               push(&ts, s);

               // atribui o offset correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  list_symbols[i].content.param.offset = -4 + (i - (num_params-1)); 
                  push(&ts, list_symbols[i]);
               }
               rot_num++; // para o desvio de procedures dentro dessa procedure
               stack_push(&pilha_amem, num_params, NULL, NULL); // stack_int_push

               // dentro_proc = 1;
              }
#line 1569 "compilador.tab.c"
    break;

  case 30: /* $@12: %empty  */
#line 277 "compilador.y"
              {
               remove_n(&ts, stack_int_head(&pilha_amem));
               sprintf(mepa_buf, "RTPR %d, %d", level_lex, stack_int_head(&pilha_amem));
               stack_int_pop(&pilha_amem);

               remove_n(&ts, stack_int_head(&pilha_procs));
               stack_int_pop(&pilha_procs);
               geraCodigo(NULL, mepa_buf);
              }
#line 1583 "compilador.tab.c"
    break;

  case 37: /* $@13: %empty  */
#line 301 "compilador.y"
                   {curr_section_params = 0;}
#line 1589 "compilador.tab.c"
    break;

  case 38: /* secao_parameters: var_ou_nada $@13 id_list DOIS_PONTOS type  */
#line 305 "compilador.y"
                   {
                     // atribui type para os parâmetros dessa seção e coloca numa list de símbolos a serem empilhados
                     for(int i = num_params-curr_section_params; i < num_params; ++i){
                        ti.param = list_parameters[i];
                        ti.param.type = (yyvsp[0].int_val);
                        list_symbols[i] = symbol_init(idents[i], parameter, level_lex, ti);
                     }
                   }
#line 1602 "compilador.tab.c"
    break;

  case 39: /* var_ou_nada: VAR  */
#line 315 "compilador.y"
                 {referencia = 1;}
#line 1608 "compilador.tab.c"
    break;

  case 40: /* var_ou_nada: %empty  */
#line 315 "compilador.y"
                                     {referencia = 0;}
#line 1614 "compilador.tab.c"
    break;

  case 53: /* item_leitura: IDENT  */
#line 339 "compilador.y"
               {
                  geraCodigo(NULL, "LEIT");
                  sptr = search(&ts, token);
                  if(!sptr || sptr->category == procedure){
                     fprintf(stderr, "COMPILATION ERROR!!!\n Wrong use of read()\n"); 
                     exit(1);
                  }
                  sprintf(mepa_buf, "ARMZ %d, %d", sptr->level, sptr->content.var.offset);
                  geraCodigo(NULL, mepa_buf);
               }
#line 1629 "compilador.tab.c"
    break;

  case 55: /* escreve_itens: escreve_itens VIRGULA expression  */
#line 354 "compilador.y"
                                                {geraCodigo(NULL, "IMPR");}
#line 1635 "compilador.tab.c"
    break;

  case 56: /* escreve_itens: expression  */
#line 354 "compilador.y"
                                                                                        {geraCodigo(NULL, "IMPR");}
#line 1641 "compilador.tab.c"
    break;

  case 57: /* $@14: %empty  */
#line 358 "compilador.y"
                  { 
                     // printf("Buscando o token %s\n", token);
                     sptr_var_proc = search(&ts, token); 
                     stack_push(NULL, 0, &pilha_ident_esquerdo, sptr_var_proc); // symbols_table_push
                  }
#line 1651 "compilador.tab.c"
    break;

  case 58: /* atribuicao_proc: IDENT $@14 a_continua  */
#line 364 "compilador.y"
                  { 
                     stack_symbols_table_pop(&pilha_ident_esquerdo);
                  }
#line 1659 "compilador.tab.c"
    break;

  case 59: /* $@15: %empty  */
#line 368 "compilador.y"
                       {atribui = 1;}
#line 1665 "compilador.tab.c"
    break;

  case 60: /* a_continua: ATRIBUICAO $@15 atribuicao  */
#line 368 "compilador.y"
                                                {atribui = 0;}
#line 1671 "compilador.tab.c"
    break;

  case 63: /* atribuicao: expression  */
#line 373 "compilador.y"
                       {
   sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);
   if(sptr_var_proc->content.var.type != (yyvsp[0].int_val)){
      fprintf(stderr, "COMPILATION ERROR!!!\n Variable type differs from expression type.\n"); 
      exit(1);
   }
   /* search posição da variable */
   
   // pode ser indireto
   // printf("%s: %d", sptr_var_proc->id, sptr_var_proc->category);
   if (sptr_var_proc->category == variable)
      sprintf(mepa_buf, "ARMZ %d, %d", sptr_var_proc->level, sptr_var_proc->content.var.offset);
   else if (sptr_var_proc->category == parameter){
      if (sptr_var_proc->content.param.passage == copy_parameter)
         sprintf(mepa_buf, "ARMZ %d, %d", sptr_var_proc->level, sptr_var_proc->content.param.offset);
      else
         sprintf(mepa_buf, "ARMI %d, %d", sptr_var_proc->level, sptr_var_proc->content.param.offset);
   } else if (sptr_var_proc->category == function){
         sprintf(mepa_buf, "ARMZ %d, %d", sptr_var_proc->level, sptr_var_proc->content.var.offset);
   } else {
      fprintf(stderr, "Procedimento tratado como variável!\n");
      exit(1);
   }
   geraCodigo(NULL, mepa_buf);
}
#line 1701 "compilador.tab.c"
    break;

  case 64: /* $@16: %empty  */
#line 402 "compilador.y"
             {
               sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);

              if(!sptr_var_proc){
                  fprintf(stderr, "COMPILATION ERROR!!!\n Procedure not found.\n"); 
                  exit(1);
              }
              sptr_atribuicao = sptr_var_proc;
              memcpy(&curr_proc, sptr_var_proc, sizeof(struct symbol));
            //   printf("curr_proc.category = %d\n", curr_proc.category);
            //   printf("fun: %d\n", function);
            //   printf("proc: %d\n", procedure);
              if(curr_proc.category == function ){
                  geraCodigo(NULL, "AMEM 1");
              }
              sprintf(proc_name, "CHPR R%02d, %d", sptr_var_proc->content.proc.label, level_lex);
             }
#line 1723 "compilador.tab.c"
    break;

  case 65: /* $@17: %empty  */
#line 420 "compilador.y"
             {
               curr_call_params = 0;
               dentro_chamada_proc++;
             }
#line 1732 "compilador.tab.c"
    break;

  case 66: /* procedure: $@16 ABRE_PARENTESES $@17 list_expressoes FECHA_PARENTESES  */
#line 426 "compilador.y"
             {
               dentro_chamada_proc--;
               if(curr_call_params != curr_proc.content.proc.parameters_quantity){
                   fprintf(stderr, "COMPILATION ERROR!!!\n Wrong number of parameters.\n"); 
                   exit(1);
               }
               geraCodigo(NULL, proc_name);
             }
#line 1745 "compilador.tab.c"
    break;

  case 67: /* procedure_sem_parameter: %empty  */
#line 437 "compilador.y"
              {
               sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);
               if(!sptr_var_proc){
                  fprintf(stderr, "COMPILATION ERROR!!!\n Procedure not found.\n"); 
                  exit(1);
               }
               sprintf(mepa_buf, "CHPR R%02d, %d", sptr_var_proc->content.proc.label, level_lex);
               geraCodigo(NULL, mepa_buf);
              }
#line 1759 "compilador.tab.c"
    break;

  case 68: /* $@18: %empty  */
#line 448 "compilador.y"
                           {
                        stack_push(&pilha_labels, rot_num, NULL, NULL); // stack_int_push
                         
                        sprintf(rot_str, "R%02d", rot_num);
                        geraCodigo(rot_str, "NADA");
                        rot_num += 2;
                     }
#line 1771 "compilador.tab.c"
    break;

  case 69: /* $@19: %empty  */
#line 455 "compilador.y"
                                {
                        sprintf(mepa_buf, "DSVF R%02d", stack_int_head(&pilha_labels)+1);
                        geraCodigo(NULL, mepa_buf); // falta testar expressão
                     }
#line 1780 "compilador.tab.c"
    break;

  case 70: /* comando_repetitivo: WHILE $@18 expression $@19 DO comando_sem_label_ou_composto  */
#line 460 "compilador.y"
                                                   {
                        sprintf(mepa_buf, "DSVS R%02d", stack_int_head(&pilha_labels));
                        geraCodigo(NULL, mepa_buf);

                        sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels)+1);
                        geraCodigo(rot_str, "NADA");

                        stack_int_pop(&pilha_labels);
                     }
#line 1794 "compilador.tab.c"
    break;

  case 73: /* $@20: %empty  */
#line 475 "compilador.y"
                                   {
                        if ((yyvsp[0].int_val) != pas_boolean){
                           fprintf(stderr, "COMPILATION ERROR!!!\n If expression is not boolean!\n");
                           exit(1);
                        }

                        sprintf(mepa_buf, "DSVF R%02d", rot_num+1);
                        geraCodigo(NULL, mepa_buf); // falta testar expressão
                        
                        stack_push(&pilha_labels, rot_num, NULL, NULL);// stack_int_push
                        rot_num += 2;
                     }
#line 1811 "compilador.tab.c"
    break;

  case 74: /* $@21: %empty  */
#line 488 "compilador.y"
                                                   {
                        sprintf(mepa_buf, "DSVS R%02d", stack_int_head(&pilha_labels));
                        geraCodigo(NULL, mepa_buf);

                        sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels)+1);
                        geraCodigo(rot_str, "NADA");

                     }
#line 1824 "compilador.tab.c"
    break;

  case 75: /* comando_condicional: IF expression $@20 THEN comando_sem_label_ou_composto $@21 else_ou_nada  */
#line 496 "compilador.y"
                                 {
                        sprintf(rot_str, "R%02d", stack_int_head(&pilha_labels));
                        geraCodigo(rot_str, "NADA");

                        stack_int_pop(&pilha_labels);
                     }
#line 1835 "compilador.tab.c"
    break;

  case 78: /* $@22: %empty  */
#line 511 "compilador.y"
                  {  
                     // curr_section_params++;
                     curr_call_params++;
                  }
#line 1844 "compilador.tab.c"
    break;

  case 80: /* list_expressoes: expression  */
#line 518 "compilador.y"
                  {
                     // curr_section_params++;
                     curr_call_params++;
                  }
#line 1853 "compilador.tab.c"
    break;

  case 81: /* expression: simple_expression  */
#line 523 "compilador.y"
                                 { (yyval.int_val) = (yyvsp[0].int_val); }
#line 1859 "compilador.tab.c"
    break;

  case 82: /* expression: simple_expression relation simple_expression  */
#line 524 "compilador.y"
                                                          {
               if ((yyvsp[-2].int_val) != (yyvsp[0].int_val)){
                  fprintf(stderr, "COMPILATION ERROR!!!\nCannot compare expressions with different types!\n");
                  exit(1);
               }
               geraCodigo(NULL, (yyvsp[-1].str));
               (yyval.int_val) = pas_boolean;
            }
#line 1872 "compilador.tab.c"
    break;

  case 83: /* relation: IGUAL  */
#line 535 "compilador.y"
                         { (yyval.str) = "CMIG"; }
#line 1878 "compilador.tab.c"
    break;

  case 84: /* relation: DIFERENTE  */
#line 536 "compilador.y"
                        { (yyval.str) = "CMDG"; }
#line 1884 "compilador.tab.c"
    break;

  case 85: /* relation: MENOR  */
#line 537 "compilador.y"
                        { (yyval.str) = "CMME"; }
#line 1890 "compilador.tab.c"
    break;

  case 86: /* relation: MENOR_IGUAL  */
#line 538 "compilador.y"
                        { (yyval.str) = "CMEG"; }
#line 1896 "compilador.tab.c"
    break;

  case 87: /* relation: MAIOR_IGUAL  */
#line 539 "compilador.y"
                        { (yyval.str) = "CMAG"; }
#line 1902 "compilador.tab.c"
    break;

  case 88: /* relation: MAIOR  */
#line 540 "compilador.y"
                        { (yyval.str) = "CMMA"; }
#line 1908 "compilador.tab.c"
    break;

  case 89: /* simple_expression: simple_expression plus_minus_or term  */
#line 544 "compilador.y"
                                                         {
                     if (strcmp((yyvsp[-1].str), "DISJ") == 0){
                        if ((yyvsp[-2].int_val) != pas_boolean || (yyvsp[0].int_val) != pas_boolean){
                           fprintf(stderr, "COMPILATION ERROR!!!\n Boolean operation with non-boolean operands!\n");
                           exit(1);
                        }
                        (yyval.int_val) = pas_boolean;
                     }
                     else {
                        if ((yyvsp[-2].int_val) != pas_integer || (yyvsp[0].int_val) != pas_integer){
                           fprintf(stderr, "COMPILATION ERROR!!!\n Integer operation with non-integer operands!\n");
                           exit(1);
                        }
                        (yyval.int_val) = pas_integer;
                     }
                     
                     geraCodigo(NULL, (yyvsp[-1].str));
                  }
#line 1931 "compilador.tab.c"
    break;

  case 90: /* simple_expression: plus_minus_empty term  */
#line 562 "compilador.y"
                                         {
                     if ( strcmp((yyvsp[-1].str), "VAZIO") != 0){
                        if ((yyvsp[0].int_val) != pas_integer){
                           fprintf(stderr, "COMPILATION ERROR!!!\n Sign on non integer type!\n");
                           exit(1);
                        }
                        (yyval.int_val) = pas_integer;
                     } else {
                        (yyval.int_val) = (yyvsp[0].int_val);
                     }
                     
                     if ( strcmp((yyvsp[-1].str), "MENOS") == 0 )
                        geraCodigo(NULL, "INVR");
                  }
#line 1950 "compilador.tab.c"
    break;

  case 91: /* plus_minus_empty: MAIS  */
#line 578 "compilador.y"
                          { (yyval.str) = "MAIS"; }
#line 1956 "compilador.tab.c"
    break;

  case 92: /* plus_minus_empty: MENOS  */
#line 579 "compilador.y"
                          { (yyval.str) = "MENOS"; }
#line 1962 "compilador.tab.c"
    break;

  case 93: /* plus_minus_empty: %empty  */
#line 580 "compilador.y"
                          { (yyval.str) = "VAZIO"; }
#line 1968 "compilador.tab.c"
    break;

  case 94: /* plus_minus_or: MAIS  */
#line 583 "compilador.y"
                      { (yyval.str) = strdup("SOMA"); }
#line 1974 "compilador.tab.c"
    break;

  case 95: /* plus_minus_or: MENOS  */
#line 584 "compilador.y"
                       { (yyval.str) = strdup("SUBT"); }
#line 1980 "compilador.tab.c"
    break;

  case 96: /* plus_minus_or: OR  */
#line 585 "compilador.y"
                    { (yyval.str) = strdup("DISJ"); }
#line 1986 "compilador.tab.c"
    break;

  case 97: /* term: term times_div_and factor  */
#line 589 "compilador.y"
                                 { 
         if (strcmp((yyvsp[-1].str), "CONJ") == 0){
            if ((yyvsp[-2].int_val) != pas_boolean || (yyvsp[0].int_val) != pas_boolean){
               fprintf(stderr, "COMPILATION ERROR!!!\n Boolean operation with non-boolean operands!\n");
               exit(1);
            }
            (yyval.int_val) = pas_boolean;
         }
         else {
            if ((yyvsp[-2].int_val) != pas_integer || (yyvsp[0].int_val) != pas_integer){
               fprintf(stderr, "COMPILATION ERROR!!!\n Integer operation with non-integer operands!\n");
               exit(1);
            }
            (yyval.int_val) = pas_integer;
         }
         geraCodigo(NULL, (yyvsp[-1].str));
      }
#line 2008 "compilador.tab.c"
    break;

  case 99: /* times_div_and: VEZES  */
#line 609 "compilador.y"
                       { (yyval.str) = strdup("MULT"); }
#line 2014 "compilador.tab.c"
    break;

  case 100: /* times_div_and: DIV  */
#line 610 "compilador.y"
                     { (yyval.str) = strdup("DIVI"); }
#line 2020 "compilador.tab.c"
    break;

  case 101: /* times_div_and: AND  */
#line 611 "compilador.y"
                     { (yyval.str) = strdup("CONJ"); }
#line 2026 "compilador.tab.c"
    break;

  case 102: /* procedure_ou_nada: procedure  */
#line 615 "compilador.y"
                             {
                        sptr_var_proc = stack_symbols_table_head(&pilha_ident_esquerdo);
                        stack_symbols_table_pop(&pilha_ident_esquerdo);
                     }
#line 2035 "compilador.tab.c"
    break;

  case 103: /* procedure_ou_nada: %empty  */
#line 619 "compilador.y"
                       {
                        sptr = stack_symbols_table_head(&pilha_ident_esquerdo); 
                        stack_symbols_table_pop(&pilha_ident_esquerdo); 
                     }
#line 2044 "compilador.tab.c"
    break;

  case 104: /* $@23: %empty  */
#line 625 "compilador.y"
         {
            sptr = search(&ts, token);
            stack_push(NULL, 0, &pilha_ident_esquerdo, search(&ts, token));//symbols_table_push

         }
#line 2054 "compilador.tab.c"
    break;

  case 105: /* factor: IDENT $@23 procedure_ou_nada  */
#line 629 "compilador.y"
                             { 

         if(!sptr){
            printf("Variável não encontrada\n");
            exit(1);
         }
         
         // printf("Variavel %s level %d, offset %d\n", sptr->id, sptr->level, sptr->content.var.offset);
         (yyval.int_val) = sptr->content.var.type;
         // pode ser indireto
         int flag = 0;
         if (sptr->category == variable){
            
            if (dentro_chamada_proc){
               int qtd_params = sptr_var_proc->content.proc.parameters_quantity;
               // printf("curr: %d actual: %d\n", curr_call_params, qtd_params);
               if (curr_call_params >= qtd_params){
                  fprintf(stderr, "COMPILATION ERROR! Excesso de parâmetros em função!!\n");
                  exit(1);
               }
               if (sptr_var_proc->content.proc.list[curr_call_params].passage == reference_parameter){
                  sprintf(mepa_buf, "CREN %d, %d", sptr->level, sptr->content.var.offset);
               }
               else if (sptr_var_proc->content.proc.list[curr_call_params].passage == copy_parameter){
                  sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.var.offset);
               }else {
                  fprintf(stderr, "INTERNAL ERROR: parameter não é nem copia nem referencia\n");
                  exit(1);
               }
            } else if (sptr_var_proc && sptr_var_proc->category != function){
               sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.var.offset);
            } else if (atribui && (sptr_var_proc && sptr_var_proc->category == function) && sptr_atribuicao->category != function){
               sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.var.offset);

            } else {
               flag = 1;
            }

         }
         else if (sptr->category == parameter){
            if (sptr->content.param.passage == copy_parameter)
               sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.param.offset);
            else {
               if(sptr_var_proc->content.proc.list[curr_call_params].passage == reference_parameter){
                  sprintf(mepa_buf, "CRVL %d, %d", sptr->level, sptr->content.param.offset);
               } else {
                  sprintf(mepa_buf, "CRVI %d, %d", sptr->level, sptr->content.param.offset);
               }
            }
         } else if (sptr->category != function){
            fprintf(stderr, "Procedimento tratado como variável!!\n");
            exit(1);
         } else {
            flag = 1;
         }
         if(!flag)
            geraCodigo(NULL, mepa_buf);
      }
#line 2117 "compilador.tab.c"
    break;

  case 106: /* factor: NUMERO  */
#line 687 "compilador.y"
               {
         (yyval.int_val) = pas_integer;
         sprintf (mepa_buf, "CRCT %d", atoi(token));
         geraCodigo(NULL, mepa_buf);
      }
#line 2127 "compilador.tab.c"
    break;

  case 107: /* factor: VALOR_BOOL  */
#line 692 "compilador.y"
                   {
         (yyval.int_val) = pas_boolean;
         if(strcmp(token, "True") == 0)
            sprintf (mepa_buf, "CRCT %d", 1);
         else
            sprintf (mepa_buf, "CRCT %d", 0);
         geraCodigo(NULL, mepa_buf);
      }
#line 2140 "compilador.tab.c"
    break;

  case 108: /* factor: ABRE_PARENTESES expression FECHA_PARENTESES  */
#line 700 "compilador.y"
                                                    { (yyval.int_val) = (yyvsp[-1].int_val); }
#line 2146 "compilador.tab.c"
    break;

  case 109: /* factor: NOT factor  */
#line 701 "compilador.y"
                   {
         if ((yyvsp[0].int_val) != pas_boolean){
            fprintf(stderr, "COMPILATION ERROR!!! Boolean operation with non-boolean value!\n");
            exit(1);
         }
         (yyval.int_val) = pas_boolean;
         geraCodigo(NULL, "NEGA");
       }
#line 2159 "compilador.tab.c"
    break;


#line 2163 "compilador.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 717 "compilador.y"


int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
   table_init(&ts);
   table_init(&pilha_atribuicao);
   stack_init(&pilha_labels, NULL);
   stack_init(&pilha_amem, NULL);
   stack_init(&pilha_procs, NULL);
   stack_init(NULL, &pilha_ident_esquerdo);

   yyin=fp;
   yyparse();

   stack_int_destruct(&pilha_labels);
   stack_int_destruct(&pilha_amem);
   stack_int_destruct(&pilha_procs);
   stack_symbols_table_destruct(&pilha_ident_esquerdo);

   return 0;
}
