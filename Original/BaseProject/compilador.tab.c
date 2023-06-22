/* A Bison parser, made by GNU Bison 3.7.5.  */

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 8 "compilador.y"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "utils/tabela_simb.h"
#include "utils/pilha_rotulos.h"
#include "utils/pilha_tipos.h"

int num_vars;
int num_params; // número de parâmetros do procedimento atual
int num_params_secao; // número de parâmetros da seção atual => seção é aquela separada por ';'
int num_params_chamada;
int nivel_lex;
int pos_var;
int qt_tipo_atual;
int referencia; // indica se a seção atual é por referência, se não for, é por cópia, auxilia nas verificacoes se eh ARMI e CRVI
int dentro_chamada_proc; // indica se está dentro de uma chamada de procedimento
int num_subprocs_proc_atual; // numero de sub processo contidos no processo atual
int atribui;

char buffer_mepa[128], proc_name[128], idents[128][128];
tabela_de_simbolos_t *ts, *pilha_atribuicao;
simbolo_t s, *sptr, *sptr_var_proc, *sptr_chamada_proc, *sptr_atribuicao, proc_atual, lista_simbolos[128];

struct pilha_rotulos pilha_rotulos, pilha_amem, pilha_procs; // pilha para o rotulo, calculo dos amem e para os procedimentos
struct pilha_tipos pilha_ident_esquerdo;
struct parametro lista_parametros[128]; 
struct cat_conteudo ti;

int str2token(const char *str){
   if (!strcmp(str, "integer")) return INTEGER_S;
   if (!strcmp(str, "boolean")) return BOOLEAN_S;
   return UNDEFINED_S;
}
short int proc_subnivel; // para o desvio de sub procedures dentro das procedures
char rot_str[4];
int rot_w;


#line 113 "compilador.tab.c"

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
  YYSYMBOL_LOWER_THEN_ELSE = 49,           /* LOWER_THEN_ELSE  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_programa = 51,                  /* programa  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_bloco = 53,                     /* bloco  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_55_3 = 55,                      /* $@3  */
  YYSYMBOL_tipo = 56,                      /* tipo  */
  YYSYMBOL_parte_declara_vars = 57,        /* parte_declara_vars  */
  YYSYMBOL_58_4 = 58,                      /* $@4  */
  YYSYMBOL_declara_vars = 59,              /* declara_vars  */
  YYSYMBOL_declara_var = 60,               /* declara_var  */
  YYSYMBOL_61_5 = 61,                      /* $@5  */
  YYSYMBOL_62_6 = 62,                      /* $@6  */
  YYSYMBOL_lista_id_var = 63,              /* lista_id_var  */
  YYSYMBOL_lista_idents = 64,              /* lista_idents  */
  YYSYMBOL_ident_params = 65,              /* ident_params  */
  YYSYMBOL_parte_declara_subrotinas = 66,  /* parte_declara_subrotinas  */
  YYSYMBOL_67_7 = 67,                      /* $@7  */
  YYSYMBOL_declara_proc = 68,              /* declara_proc  */
  YYSYMBOL_69_8 = 69,                      /* $@8  */
  YYSYMBOL_70_9 = 70,                      /* $@9  */
  YYSYMBOL_declara_func = 71,              /* declara_func  */
  YYSYMBOL_72_10 = 72,                     /* $@10  */
  YYSYMBOL_73_11 = 73,                     /* $@11  */
  YYSYMBOL_parametros_formais_ou_vazio = 74, /* parametros_formais_ou_vazio  */
  YYSYMBOL_parametros_formais = 75,        /* parametros_formais  */
  YYSYMBOL_parametros = 76,                /* parametros  */
  YYSYMBOL_secao_parametros_formais = 77,  /* secao_parametros_formais  */
  YYSYMBOL_78_12 = 78,                     /* $@12  */
  YYSYMBOL_var_ou_vazio = 79,              /* var_ou_vazio  */
  YYSYMBOL_comando_composto = 80,          /* comando_composto  */
  YYSYMBOL_comandos = 81,                  /* comandos  */
  YYSYMBOL_comando_vazio = 82,             /* comando_vazio  */
  YYSYMBOL_comando_sem_rotulo = 83,        /* comando_sem_rotulo  */
  YYSYMBOL_atribuicao_proc = 84,           /* atribuicao_proc  */
  YYSYMBOL_85_13 = 85,                     /* $@13  */
  YYSYMBOL_a_continua = 86,                /* a_continua  */
  YYSYMBOL_87_14 = 87,                     /* $@14  */
  YYSYMBOL_atribuicao = 88,                /* atribuicao  */
  YYSYMBOL_chama_procedimento = 89,        /* chama_procedimento  */
  YYSYMBOL_90_15 = 90,                     /* $@15  */
  YYSYMBOL_91_16 = 91,                     /* $@16  */
  YYSYMBOL_procedimento_sem_parametro = 92, /* procedimento_sem_parametro  */
  YYSYMBOL_comando_condicional = 93,       /* comando_condicional  */
  YYSYMBOL_94_17 = 94,                     /* $@17  */
  YYSYMBOL_95_18 = 95,                     /* $@18  */
  YYSYMBOL_else_ou_vazio = 96,             /* else_ou_vazio  */
  YYSYMBOL_comando_repetitivo = 97,        /* comando_repetitivo  */
  YYSYMBOL_98_19 = 98,                     /* $@19  */
  YYSYMBOL_99_20 = 99,                     /* $@20  */
  YYSYMBOL_lista_expressoes = 100,         /* lista_expressoes  */
  YYSYMBOL_101_21 = 101,                   /* $@21  */
  YYSYMBOL_expressao = 102,                /* expressao  */
  YYSYMBOL_relacao = 103,                  /* relacao  */
  YYSYMBOL_expressao_simples = 104,        /* expressao_simples  */
  YYSYMBOL_mais_menos_vazio = 105,         /* mais_menos_vazio  */
  YYSYMBOL_mais_menos_or = 106,            /* mais_menos_or  */
  YYSYMBOL_termo = 107,                    /* termo  */
  YYSYMBOL_vezes_div_and = 108,            /* vezes_div_and  */
  YYSYMBOL_procedimento_ou_vazio = 109,    /* procedimento_ou_vazio  */
  YYSYMBOL_fator = 110,                    /* fator  */
  YYSYMBOL_variavel = 111,                 /* variavel  */
  YYSYMBOL_numero = 112,                   /* numero  */
  YYSYMBOL_leitura = 113,                  /* leitura  */
  YYSYMBOL_leitura_itens = 114,            /* leitura_itens  */
  YYSYMBOL_item_leitura = 115,             /* item_leitura  */
  YYSYMBOL_escrita = 116,                  /* escrita  */
  YYSYMBOL_escreve_itens = 117             /* escreve_itens  */
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  169

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
       0,    94,    94,    93,   117,   126,   116,   149,   158,   158,
     165,   169,   170,   178,   180,   178,   184,   190,   205,   208,
     212,   229,   229,   230,   231,   241,   246,   239,   289,   297,
     287,   335,   335,   338,   343,   343,   355,   354,   370,   370,
     377,   384,   384,   386,   399,   400,   401,   402,   403,   404,
     415,   414,   424,   424,   425,   426,   429,   462,   478,   462,
     495,   513,   526,   513,   541,   541,   548,   555,   548,   576,
     575,   581,   591,   592,   607,   608,   609,   610,   611,   612,
     620,   639,   656,   657,   658,   661,   662,   663,   670,   688,
     691,   692,   693,   696,   700,   716,   768,   769,   777,   778,
     794,   805,   813,   815,   815,   817,   831,   833,   833
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
  "LOWER_THEN_ELSE", "$accept", "programa", "$@1", "bloco", "$@2", "$@3",
  "tipo", "parte_declara_vars", "$@4", "declara_vars", "declara_var",
  "$@5", "$@6", "lista_id_var", "lista_idents", "ident_params",
  "parte_declara_subrotinas", "$@7", "declara_proc", "$@8", "$@9",
  "declara_func", "$@10", "$@11", "parametros_formais_ou_vazio",
  "parametros_formais", "parametros", "secao_parametros_formais", "$@12",
  "var_ou_vazio", "comando_composto", "comandos", "comando_vazio",
  "comando_sem_rotulo", "atribuicao_proc", "$@13", "a_continua", "$@14",
  "atribuicao", "chama_procedimento", "$@15", "$@16",
  "procedimento_sem_parametro", "comando_condicional", "$@17", "$@18",
  "else_ou_vazio", "comando_repetitivo", "$@19", "$@20",
  "lista_expressoes", "$@21", "expressao", "relacao", "expressao_simples",
  "mais_menos_vazio", "mais_menos_or", "termo", "vezes_div_and",
  "procedimento_ou_vazio", "fator", "variavel", "numero", "leitura",
  "leitura_itens", "item_leitura", "escrita", "escreve_itens", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
#endif

#define YYPACT_NINF (-117)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-72)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      17,   -10,    29,  -117,  -117,    15,     1,  -117,   -12,  -117,
       1,    23,  -117,    56,    38,  -117,    58,  -117,  -117,  -117,
      -3,  -117,    33,  -117,    35,    36,    37,    57,  -117,    48,
    -117,  -117,    24,  -117,  -117,    -6,  -117,    49,  -117,    30,
      43,    50,    50,    13,  -117,  -117,    51,    52,  -117,    -2,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
      73,  -117,  -117,  -117,    59,  -117,  -117,  -117,    19,    -9,
      13,    -5,    53,    13,  -117,    -6,    61,  -117,    -8,  -117,
    -117,    65,    30,    67,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,    13,    -9,    -9,    13,  -117,  -117,  -117,
      -7,  -117,    55,  -117,  -117,  -117,  -117,  -117,    62,  -117,
    -117,     5,  -117,  -117,    11,  -117,  -117,    73,  -117,     1,
      56,  -117,    -6,     7,    -7,  -117,    64,  -117,  -117,  -117,
      -9,  -117,  -117,  -117,    76,    13,  -117,    53,  -117,    13,
    -117,  -117,    34,  -117,    71,  -117,  -117,  -117,    -6,  -117,
    -117,    13,  -117,  -117,    30,    56,    75,  -117,    68,    69,
    -117,  -117,    -6,  -117,  -117,    74,  -117,    13,  -117
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     0,    20,     0,    19,
       0,     0,    18,    10,     0,     4,     0,     3,    43,    13,
       5,    24,     9,    12,     0,     0,     0,     0,    21,     0,
      11,    17,     0,    25,    28,     0,     6,     0,    23,     0,
       0,    43,    43,    84,    66,    50,     0,     0,    45,     0,
      41,    44,    46,    47,    49,    48,    22,     7,    14,    16,
      39,    26,    31,    32,     0,    82,    83,    61,    72,     0,
      84,    60,     0,    84,    40,     0,     0,    38,     0,    35,
      36,     0,     0,     0,    87,    79,    76,    74,    85,    86,
      75,    77,    78,    84,     0,     0,    84,   100,   101,    97,
      81,    89,    43,    96,    67,    52,    51,    55,     0,    54,
     105,     0,   104,   108,     0,    42,    15,    39,    33,     0,
      10,    29,     0,    73,    80,    99,     0,    92,    91,    90,
       0,    94,    93,    95,     0,    84,    58,     0,   102,    84,
     106,    34,     0,    27,     0,    62,    98,    88,     0,    53,
      56,    84,   103,   107,     0,    10,    65,    68,     0,    69,
      37,    30,     0,    63,    59,     0,    64,    84,    70
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -117,  -117,  -117,  -116,  -117,  -117,   -79,  -117,  -117,  -117,
      77,  -117,  -117,  -117,   -18,    92,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,    63,  -117,  -117,   -14,  -117,  -117,
      79,  -117,   -16,   -74,  -117,  -117,  -117,  -117,  -117,     2,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
     -60,  -117,   -43,  -117,    16,  -117,  -117,    14,  -117,  -117,
     -86,  -117,  -117,  -117,  -117,   -27,  -117,  -117
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     5,    14,    18,    27,    58,    15,    16,    22,
      23,    24,    76,    32,     8,     9,    20,    37,    28,    41,
      81,    29,    42,   144,    61,    62,    78,    79,   119,    80,
      48,    49,    63,    50,    51,    71,   106,   135,   149,   107,
     108,   151,   109,    52,    83,   156,   163,    53,    70,   134,
     158,   165,   159,    93,    68,    69,    94,   100,   130,   133,
     101,   102,   103,    54,   111,   112,    55,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,   115,    21,   121,   143,    35,    25,    26,    43,   125,
      74,    44,    95,   127,    10,   128,   117,    11,   105,    96,
       1,   118,    75,   -57,     3,    97,    84,   104,    45,     4,
     113,   137,    98,   129,   138,     7,    99,   139,    84,   161,
     140,    46,    47,     6,   147,    88,    89,    13,   145,    39,
      40,    65,    66,   126,    85,    86,    87,    88,    89,   154,
      10,    90,    91,    92,    -8,    17,    19,   -13,    35,    31,
      33,    34,    38,    56,   157,   160,    57,    59,    60,    72,
      73,    77,   122,   -57,    82,   116,   131,   110,   166,   120,
     136,   162,   150,   146,   148,   155,   153,   164,   -71,    30,
     167,   142,    12,   141,   132,    64,    36,   168,   124,   123,
     152
};

static const yytype_uint8 yycheck[] =
{
      43,    75,    18,    82,   120,    11,     9,    10,    14,    95,
      12,    17,    21,    20,    26,    22,    24,    29,    23,    28,
       3,    29,    24,    28,    34,    34,    19,    70,    34,     0,
      73,    26,    41,    40,    29,    34,    45,    26,    19,   155,
      29,    47,    48,    28,   130,    38,    39,    24,   122,    25,
      26,    38,    39,    96,    35,    36,    37,    38,    39,    25,
      26,    42,    43,    44,     8,    27,     8,    34,    11,    34,
      34,    34,    24,    24,   148,   154,    46,    34,    28,    28,
      28,     8,    15,    28,    25,    24,   102,    34,   162,    24,
      28,    16,   135,    29,    18,    24,   139,    29,    29,    22,
      26,   119,    10,   117,   102,    42,    27,   167,    94,    93,
     137
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    51,    34,     0,    52,    28,    34,    64,    65,
      26,    29,    65,    24,    53,    57,    58,    27,    54,     8,
      66,    82,    59,    60,    61,     9,    10,    55,    68,    71,
      60,    34,    63,    34,    34,    11,    80,    67,    24,    25,
      26,    69,    72,    14,    17,    34,    47,    48,    80,    81,
      83,    84,    93,    97,   113,   116,    24,    46,    56,    34,
      28,    74,    75,    82,    74,    38,    39,   102,   104,   105,
      98,    85,    28,    28,    12,    24,    62,     8,    76,    77,
      79,    70,    25,    94,    19,    35,    36,    37,    38,    39,
      42,    43,    44,   103,   106,    21,    28,    34,    41,    45,
     107,   110,   111,   112,   102,    23,    86,    89,    90,    92,
      34,   114,   115,   102,   117,    83,    24,    24,    29,    78,
      24,    56,    15,   104,   107,   110,   102,    20,    22,    40,
     108,    82,    89,   109,    99,    87,    28,    26,    29,    26,
      29,    77,    64,    53,    73,    83,    29,   110,    18,    88,
     102,    91,   115,   102,    25,    24,    95,    83,   100,   102,
      56,    53,    16,    96,    29,   101,    83,    26,   100
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    52,    51,    54,    55,    53,    56,    58,    57,
      57,    59,    59,    61,    62,    60,    63,    63,    64,    64,
      65,    67,    66,    66,    66,    69,    70,    68,    72,    73,
      71,    74,    74,    75,    76,    76,    78,    77,    79,    79,
      80,    81,    81,    82,    83,    83,    83,    83,    83,    83,
      85,    84,    87,    86,    86,    86,    88,    90,    91,    89,
      92,    94,    95,    93,    96,    96,    98,    99,    97,   101,
     100,   100,   102,   102,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   105,   106,   106,   106,   107,   107,
     108,   108,   108,   109,   109,   110,   110,   110,   110,   110,
     111,   112,   113,   114,   114,   115,   116,   117,   117
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     5,     1,     0,     3,
       0,     2,     1,     0,     0,     6,     3,     1,     3,     1,
       1,     0,     4,     3,     1,     0,     0,     7,     0,     0,
       9,     1,     1,     3,     3,     1,     0,     5,     1,     0,
       3,     1,     3,     0,     1,     1,     1,     1,     1,     1,
       0,     3,     0,     3,     1,     1,     1,     0,     0,     5,
       0,     0,     0,     7,     2,     0,     0,     0,     6,     0,
       4,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     2,     1,     1,     0,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     3,     2,
       1,     1,     4,     3,     1,     1,     4,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 94 "compilador.y"
            {
             geraCodigo (NULL, "INPP");
             nivel_lex = 0;
             proc_subnivel = 0;
             dentro_chamada_proc = 0;
             }
#line 1357 "compilador.tab.c"
    break;

  case 3: /* programa: PROGRAM IDENT $@1 ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  */
#line 101 "compilador.y"
                         {
             geraCodigo (NULL, "PARA");
             }
#line 1365 "compilador.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 117 "compilador.y"
              {
               sprintf(buffer_mepa, "DSVS R%02d", proc_subnivel);
               geraCodigo(NULL, buffer_mepa);
               pilha_rotulos_empilhar(&pilha_rotulos, proc_subnivel);
               proc_subnivel++;
               nivel_lex++;
               num_subprocs_proc_atual = 0;
              }
#line 1378 "compilador.tab.c"
    break;

  case 5: /* $@3: %empty  */
#line 126 "compilador.y"
              {
               pilha_rotulos_empilhar(&pilha_procs, num_subprocs_proc_atual);
               nivel_lex--;

               sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos));
               geraCodigo(rot_str, "NADA");
               pilha_rotulos_desempilhar(&pilha_rotulos);
              }
#line 1391 "compilador.tab.c"
    break;

  case 6: /* bloco: parte_declara_vars $@2 parte_declara_subrotinas $@3 comando_composto  */
#line 135 "compilador.y"
              {
               sprintf(buffer_mepa, "DMEM %d", pilha_rotulos_topo(&pilha_amem)); 
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_amem)); // Removo os pilha_rotulos_topo(&pilha_amem) elemento da tabela
               geraCodigo(NULL, buffer_mepa);
               pilha_rotulos_desempilhar(&pilha_amem);   // desempilho os rotulos removido s
              }
#line 1402 "compilador.tab.c"
    break;

  case 7: /* tipo: TIPO  */
#line 149 "compilador.y"
                   { (yyval.int_value) = str2token(token); }
#line 1408 "compilador.tab.c"
    break;

  case 8: /* $@4: %empty  */
#line 158 "compilador.y"
                    { num_vars = 0; }
#line 1414 "compilador.tab.c"
    break;

  case 9: /* parte_declara_vars: $@4 VAR declara_vars  */
#line 159 "compilador.y"
                             { 
               sprintf(buffer_mepa, "AMEM %d", num_vars);
               geraCodigo(NULL, buffer_mepa);

               pilha_rotulos_empilhar(&pilha_amem, num_vars);
            }
#line 1425 "compilador.tab.c"
    break;

  case 10: /* parte_declara_vars: %empty  */
#line 165 "compilador.y"
              {pilha_rotulos_empilhar(&pilha_amem, 0);}
#line 1431 "compilador.tab.c"
    break;

  case 13: /* $@5: %empty  */
#line 178 "compilador.y"
              { qt_tipo_atual = 0; }
#line 1437 "compilador.tab.c"
    break;

  case 14: /* $@6: %empty  */
#line 180 "compilador.y"
              { atribui_tipo(&ts, VARIAVEL_S, (yyvsp[0].int_value), qt_tipo_atual); }
#line 1443 "compilador.tab.c"
    break;

  case 16: /* lista_id_var: lista_id_var VIRGULA IDENT  */
#line 184 "compilador.y"
                                         {
               ti.var.deslocamento = num_vars;
               s = cria_simbolo(token, VARIAVEL_S, nivel_lex, ti); 
               insere_tabela(&ts, s);
               num_vars++; qt_tipo_atual++;
            }
#line 1454 "compilador.tab.c"
    break;

  case 17: /* lista_id_var: IDENT  */
#line 190 "compilador.y"
                    { 
               ti.var.deslocamento = num_vars;
               s = cria_simbolo(token, VARIAVEL_S, nivel_lex, ti); 
               insere_tabela(&ts, s);
               num_vars++; 
               qt_tipo_atual++;
            }
#line 1466 "compilador.tab.c"
    break;

  case 20: /* ident_params: IDENT  */
#line 213 "compilador.y"
              {
               strcpy(idents[num_params], token);
               lista_parametros[num_params].passagem = referencia ? PARAMETRO_REF_S : PARAMETRO_COPIA_S;
               num_params++;  // incrementa numero de parametros conforme a lista de identificadores
               num_params_secao++;    
              }
#line 1477 "compilador.tab.c"
    break;

  case 21: /* $@7: %empty  */
#line 229 "compilador.y"
                                                                 {num_subprocs_proc_atual++;}
#line 1483 "compilador.tab.c"
    break;

  case 25: /* $@8: %empty  */
#line 241 "compilador.y"
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
#line 1492 "compilador.tab.c"
    break;

  case 26: /* $@9: %empty  */
#line 246 "compilador.y"
              {
               sprintf(rot_str, "R%02d", proc_subnivel);
               sprintf(buffer_mepa, "ENPR %d", nivel_lex);
               geraCodigo(rot_str, buffer_mepa);
               
               ti.proc.rotulo = proc_subnivel;
               ti.proc.qtd_parametros = num_params;
               memcpy(ti.proc.lista, lista_parametros, sizeof(struct parametro)*num_params);
               s = cria_simbolo(proc_name, PROCEDIMENTO_S, nivel_lex, ti);
               insere_tabela(&ts, s);

               // atribui o deslocamento correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  lista_simbolos[i].conteudo.param.deslocamento = -TAM_INT + (i - (num_params-1)); 
                  insere_tabela(&ts, lista_simbolos[i]);
               }
               proc_subnivel++;
		         // Adiciona rotulos na pilha
               pilha_rotulos_empilhar(&pilha_amem, num_params);
              }
#line 1517 "compilador.tab.c"
    break;

  case 27: /* declara_proc: PROCEDURE IDENT $@8 parametros_formais_ou_vazio $@9 PONTO_E_VIRGULA bloco  */
#line 269 "compilador.y"
              {
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_amem)); // remove da pilha de amem os n rotulos ja empilhados
               sprintf(buffer_mepa, "RTPR %d, %d", nivel_lex, pilha_rotulos_topo(&pilha_amem));
               pilha_rotulos_desempilhar(&pilha_amem);
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_procs));
               pilha_rotulos_desempilhar(&pilha_procs);
               geraCodigo(NULL, buffer_mepa);
              }
#line 1530 "compilador.tab.c"
    break;

  case 28: /* $@10: %empty  */
#line 289 "compilador.y"
              {
               strcpy(proc_name, token);
               num_params = 0;
              }
#line 1539 "compilador.tab.c"
    break;

  case 29: /* $@11: %empty  */
#line 297 "compilador.y"
              {
               sprintf(rot_str, "R%02d", proc_subnivel);
               sprintf(buffer_mepa, "ENPR %d", nivel_lex);
               geraCodigo(rot_str, buffer_mepa);
               ti.proc.rotulo = proc_subnivel;
               ti.proc.qtd_parametros = num_params;
               memcpy(ti.proc.lista, lista_parametros, sizeof(struct parametro)*num_params);
               ti.var.tipo = (yyvsp[0].int_value);
               ti.var.deslocamento = -TAM_INT - num_params;
               s = cria_simbolo(proc_name, FUNCAO_S, nivel_lex, ti);
               insere_tabela(&ts, s);

               // atribui o deslocamento correto e coloca na pilha os símbolos
               for(int i = num_params-1; i >= 0; --i){
                  lista_simbolos[i].conteudo.param.deslocamento = -TAM_INT + (i - (num_params-1)); 
                  insere_tabela(&ts, lista_simbolos[i]);
               }
               proc_subnivel++; 
               pilha_rotulos_empilhar(&pilha_amem, num_params);
              }
#line 1564 "compilador.tab.c"
    break;

  case 30: /* declara_func: FUNCTION IDENT $@10 parametros_formais_ou_vazio DOIS_PONTOS tipo $@11 PONTO_E_VIRGULA bloco  */
#line 320 "compilador.y"
              {
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_amem));
               sprintf(buffer_mepa, "RTPR %d, %d", nivel_lex, pilha_rotulos_topo(&pilha_amem));
               pilha_rotulos_desempilhar(&pilha_amem);
               remove_n_tabela(&ts, pilha_rotulos_topo(&pilha_procs));
               pilha_rotulos_desempilhar(&pilha_procs);
               geraCodigo(NULL, buffer_mepa);
              }
#line 1577 "compilador.tab.c"
    break;

  case 36: /* $@12: %empty  */
#line 355 "compilador.y"
                   {num_params_secao = 0;}
#line 1583 "compilador.tab.c"
    break;

  case 37: /* secao_parametros_formais: var_ou_vazio $@12 lista_idents DOIS_PONTOS tipo  */
#line 359 "compilador.y"
                   {
                     // atribui tipo para os parâmetros dessa seção e coloca numa lista de símbolos a serem empilhados
                     for(int i = num_params-num_params_secao; i < num_params; ++i){
                        ti.param = lista_parametros[i];
                        ti.param.tipo = (yyvsp[0].int_value);
                        lista_simbolos[i] = cria_simbolo(idents[i], PARAMETRO_S, nivel_lex, ti);
                     }
                   }
#line 1596 "compilador.tab.c"
    break;

  case 38: /* var_ou_vazio: VAR  */
#line 370 "compilador.y"
                  {referencia = 1;}
#line 1602 "compilador.tab.c"
    break;

  case 39: /* var_ou_vazio: %empty  */
#line 370 "compilador.y"
                                      {referencia = 0;}
#line 1608 "compilador.tab.c"
    break;

  case 50: /* $@13: %empty  */
#line 415 "compilador.y"
                  { 
                     sptr_var_proc = busca_simbolo(&ts, token); 
                     pilha_tipos_empilhar(&pilha_ident_esquerdo, sptr_var_proc); // empilho nos tipos o simbolo buscado
                  }
#line 1617 "compilador.tab.c"
    break;

  case 51: /* atribuicao_proc: IDENT $@13 a_continua  */
#line 420 "compilador.y"
                  { 
                     pilha_tipos_desempilhar(&pilha_ident_esquerdo);
                  }
#line 1625 "compilador.tab.c"
    break;

  case 52: /* $@14: %empty  */
#line 424 "compilador.y"
                       {atribui = 1;}
#line 1631 "compilador.tab.c"
    break;

  case 53: /* a_continua: ATRIBUICAO $@14 atribuicao  */
#line 424 "compilador.y"
                                                 {atribui = 0;}
#line 1637 "compilador.tab.c"
    break;

  case 56: /* atribuicao: expressao  */
#line 429 "compilador.y"
             {
   sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);
   // verifica se o tipo da variavel eh compativel com a expressao
   if(sptr_var_proc->conteudo.var.tipo != (yyvsp[0].int_value)){ 
      fprintf(stderr, "ERRO:\n Tipo da variável é incompatível com o tipo da expressão. \n" ); 
      exit(1);
   }

   // conforme a categoria do tipo corrente 
   if (sptr_var_proc->categoria == VARIAVEL_S)
      sprintf(buffer_mepa, "ARMZ %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.var.deslocamento); // se variavel ARMZ nivel, deslocamento_variaveis
   else if (sptr_var_proc->categoria == PARAMETRO_S){ // caso seja por parametro pode ser por copia 
      if (sptr_var_proc->conteudo.param.passagem == PARAMETRO_COPIA_S)
         sprintf(buffer_mepa, "ARMZ %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.param.deslocamento); // se parametro copia ARMZ nivel, deslocamento_parametros
      else   // ou pode ser por referencia
         sprintf(buffer_mepa, "ARMI %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.param.deslocamento); // como eh por referencia aqui devemos armazenar indiretamente usando ARMI
   } else if (sptr_var_proc->categoria == FUNCAO_S){
         sprintf(buffer_mepa, "ARMZ %d, %d", sptr_var_proc->nivel, sptr_var_proc->conteudo.var.deslocamento); // ARMZ nivel, deslocamento_vars
   } else {
      fprintf(stderr, "ERRO:\n Procedimento atribuido a uma variável!\n"); // procedimento sendo atribuido a variavel 
      exit(1);
   }
   geraCodigo(NULL, buffer_mepa);
}
#line 1666 "compilador.tab.c"
    break;

  case 57: /* $@15: %empty  */
#line 462 "compilador.y"
             {
               sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);

              if(!sptr_var_proc){
                  fprintf(stderr, "ERRO:\n Procedimento não encontrado.\n"); 
                  exit(1);
              }
              sptr_atribuicao = sptr_var_proc;
              memcpy(&proc_atual, sptr_var_proc, sizeof(simbolo_t));

              if(proc_atual.categoria == FUNCAO_S ){
                  geraCodigo(NULL, "AMEM 1");
              }
              sprintf(proc_name, "CHPR R%02d, %d", sptr_var_proc->conteudo.proc.rotulo, nivel_lex);
             }
#line 1686 "compilador.tab.c"
    break;

  case 58: /* $@16: %empty  */
#line 478 "compilador.y"
             {
               num_params_chamada = 0;
               dentro_chamada_proc++;
             }
#line 1695 "compilador.tab.c"
    break;

  case 59: /* chama_procedimento: $@15 ABRE_PARENTESES $@16 lista_expressoes FECHA_PARENTESES  */
#line 484 "compilador.y"
             {
               dentro_chamada_proc--;
               if(num_params_chamada != proc_atual.conteudo.proc.qtd_parametros){
                   fprintf(stderr, "ERRO:\n Quantidade incorreta de parametros esperado %d recebido %d.\n",proc_atual.conteudo.proc.qtd_parametros,num_params_chamada); 
                   exit(1);
               }
               geraCodigo(NULL, proc_name);
             }
#line 1708 "compilador.tab.c"
    break;

  case 60: /* procedimento_sem_parametro: %empty  */
#line 495 "compilador.y"
              {
               sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);
               if(!sptr_var_proc){
                  fprintf(stderr, "ERRO:\n Procedimento não encontrado.\n"); 
                  exit(1);
               }
               sprintf(buffer_mepa, "CHPR R%02d, %d", sptr_var_proc->conteudo.proc.rotulo, nivel_lex);
               geraCodigo(NULL, buffer_mepa);
              }
#line 1722 "compilador.tab.c"
    break;

  case 61: /* $@17: %empty  */
#line 513 "compilador.y"
                                  {
                        if ((yyvsp[0].int_value) != BOOLEAN_S){
                           fprintf(stderr, "ERRO:\n Expressão do If não é booleana!\n");
                           exit(1);
                        }

                        sprintf(buffer_mepa, "DSVF R%02d", proc_subnivel+1);
                        geraCodigo(NULL, buffer_mepa);

                        pilha_rotulos_empilhar(&pilha_rotulos, proc_subnivel);
                        proc_subnivel += 2;
                     }
#line 1739 "compilador.tab.c"
    break;

  case 62: /* $@18: %empty  */
#line 526 "compilador.y"
                                        {
                        sprintf(buffer_mepa, "DSVS R%02d", pilha_rotulos_topo(&pilha_rotulos));
                        geraCodigo(NULL, buffer_mepa);

                        sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos)+1);
                        geraCodigo(rot_str, "NADA");

                     }
#line 1752 "compilador.tab.c"
    break;

  case 63: /* comando_condicional: IF expressao $@17 THEN comando_sem_rotulo $@18 else_ou_vazio  */
#line 534 "compilador.y"
                                    {
                        sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos));
                        geraCodigo(rot_str, "NADA");
                        pilha_rotulos_desempilhar(&pilha_rotulos);
                     }
#line 1762 "compilador.tab.c"
    break;

  case 66: /* $@19: %empty  */
#line 548 "compilador.y"
                           {
                        pilha_rotulos_empilhar(&pilha_rotulos, proc_subnivel);
                         
                        sprintf(rot_str, "R%02d", proc_subnivel);
                        geraCodigo(rot_str, "NADA");
                        proc_subnivel += 2;
                     }
#line 1774 "compilador.tab.c"
    break;

  case 67: /* $@20: %empty  */
#line 555 "compilador.y"
                               {
                        sprintf(buffer_mepa, "DSVF R%02d", pilha_rotulos_topo(&pilha_rotulos)+1);
                        geraCodigo(NULL, buffer_mepa); 
                     }
#line 1783 "compilador.tab.c"
    break;

  case 68: /* comando_repetitivo: WHILE $@19 expressao $@20 DO comando_sem_rotulo  */
#line 560 "compilador.y"
                                        {
                        sprintf(buffer_mepa, "DSVS R%02d", pilha_rotulos_topo(&pilha_rotulos));
                        geraCodigo(NULL, buffer_mepa);
                        sprintf(rot_str, "R%02d", pilha_rotulos_topo(&pilha_rotulos)+1);
                        geraCodigo(rot_str, "NADA");
                        pilha_rotulos_desempilhar(&pilha_rotulos);
                     }
#line 1795 "compilador.tab.c"
    break;

  case 69: /* $@21: %empty  */
#line 576 "compilador.y"
                  {  
                     num_params_chamada++;   // conforme a lista de expressoes incrementados a quantidade de parametros da expressao
                  }
#line 1803 "compilador.tab.c"
    break;

  case 71: /* lista_expressoes: expressao  */
#line 582 "compilador.y"
                  {
                     num_params_chamada++;
                  }
#line 1811 "compilador.tab.c"
    break;

  case 72: /* expressao: expressao_simples  */
#line 591 "compilador.y"
                                { (yyval.int_value) = (yyvsp[0].int_value); }
#line 1817 "compilador.tab.c"
    break;

  case 73: /* expressao: expressao_simples relacao expressao_simples  */
#line 592 "compilador.y"
                                                         {
               // verifica se o tipos das variaveis a serem comparadas sao compativeis
               if ((yyvsp[-2].int_value) != (yyvsp[0].int_value)){
                  fprintf(stderr, "ERRO:\n Comparação entre expressões de tipos diferentes!\n");
                  exit(1);
               }
               geraCodigo(NULL, (yyvsp[-1].str_value));
               (yyval.int_value) = BOOLEAN_S;
            }
#line 1831 "compilador.tab.c"
    break;

  case 74: /* relacao: IGUAL  */
#line 607 "compilador.y"
                        { (yyval.str_value) = "CMIG"; }
#line 1837 "compilador.tab.c"
    break;

  case 75: /* relacao: DIFERENTE  */
#line 608 "compilador.y"
                        { (yyval.str_value) = "CMDG"; }
#line 1843 "compilador.tab.c"
    break;

  case 76: /* relacao: MENOR  */
#line 609 "compilador.y"
                        { (yyval.str_value) = "CMME"; }
#line 1849 "compilador.tab.c"
    break;

  case 77: /* relacao: MENOR_IGUAL  */
#line 610 "compilador.y"
                        { (yyval.str_value) = "CMEG"; }
#line 1855 "compilador.tab.c"
    break;

  case 78: /* relacao: MAIOR_IGUAL  */
#line 611 "compilador.y"
                        { (yyval.str_value) = "CMAG"; }
#line 1861 "compilador.tab.c"
    break;

  case 79: /* relacao: MAIOR  */
#line 612 "compilador.y"
                        { (yyval.str_value) = "CMMA"; }
#line 1867 "compilador.tab.c"
    break;

  case 80: /* expressao_simples: expressao_simples mais_menos_or termo  */
#line 620 "compilador.y"
                                                          {
                     if (strcmp((yyvsp[-1].str_value), "DISJ") == 0){
                        // caso seja uma disjuncao verifica se ambos os tipos sao booleanos
                        if ((yyvsp[-2].int_value) != BOOLEAN_S || (yyvsp[0].int_value) != BOOLEAN_S){
                           fprintf(stderr, "ERRO:\n Operação booleana entre operandos não booleanos!\n");
                           exit(1);
                        }
                        (yyval.int_value) = BOOLEAN_S;
                     }
                     else {
                        if ((yyvsp[-2].int_value) != INTEGER_S || (yyvsp[0].int_value) != INTEGER_S){
                           fprintf(stderr, "ERRO:\n Operação de inteiros com operandos não inteiros!\n");
                           exit(1);
                        }
                        (yyval.int_value) = INTEGER_S;
                     }
                     
                     geraCodigo(NULL, (yyvsp[-1].str_value)); // gera codigo DISJ
                  }
#line 1891 "compilador.tab.c"
    break;

  case 81: /* expressao_simples: mais_menos_vazio termo  */
#line 639 "compilador.y"
                                          {
                     if ( strcmp((yyvsp[-1].str_value), "VAZIO") != 0){
                        if ((yyvsp[0].int_value) != INTEGER_S){
                           fprintf(stderr, "ERRO:\n Operação inválida, esperado inteiros.\n");
                           exit(1);
                        }else{
                           (yyval.int_value) = INTEGER_S;
                        }
                     } else {
                        (yyval.int_value) = (yyvsp[0].int_value);
                     }
                     
                     if ( strcmp((yyvsp[-1].str_value), "MENOS") == 0 )
                        geraCodigo(NULL, "INVR");
                  }
#line 1911 "compilador.tab.c"
    break;

  case 82: /* mais_menos_vazio: MAIS  */
#line 656 "compilador.y"
                          { (yyval.str_value) = "MAIS"; }
#line 1917 "compilador.tab.c"
    break;

  case 83: /* mais_menos_vazio: MENOS  */
#line 657 "compilador.y"
                          { (yyval.str_value) = "MENOS"; }
#line 1923 "compilador.tab.c"
    break;

  case 84: /* mais_menos_vazio: %empty  */
#line 658 "compilador.y"
                          { (yyval.str_value) = "VAZIO"; }
#line 1929 "compilador.tab.c"
    break;

  case 85: /* mais_menos_or: MAIS  */
#line 661 "compilador.y"
                      { (yyval.str_value) = strdup("SOMA"); }
#line 1935 "compilador.tab.c"
    break;

  case 86: /* mais_menos_or: MENOS  */
#line 662 "compilador.y"
                       { (yyval.str_value) = strdup("SUBT"); }
#line 1941 "compilador.tab.c"
    break;

  case 87: /* mais_menos_or: OR  */
#line 663 "compilador.y"
                    { (yyval.str_value) = strdup("DISJ"); }
#line 1947 "compilador.tab.c"
    break;

  case 88: /* termo: termo vezes_div_and fator  */
#line 670 "compilador.y"
                                  { 
         if (strcmp((yyvsp[-1].str_value), "CONJ") == 0){
            // caso seja uma conjuncao verificamos se ambos os tipos sao booleanos
            if ((yyvsp[-2].int_value) != BOOLEAN_S || (yyvsp[0].int_value) != BOOLEAN_S){
               fprintf(stderr, "ERRO:\n Operação booleana entre operandos não booleanos!\n");
               exit(1);
            }
            (yyval.int_value) = BOOLEAN_S;
         }
         else {
            if ((yyvsp[-2].int_value) != INTEGER_S || (yyvsp[0].int_value) != INTEGER_S){
               fprintf(stderr, "ERRO:\n Operação de inteiros com operandos não inteiros!\n");
               exit(1);
            }
            (yyval.int_value) = INTEGER_S;
         }
         geraCodigo(NULL, (yyvsp[-1].str_value));
      }
#line 1970 "compilador.tab.c"
    break;

  case 90: /* vezes_div_and: VEZES  */
#line 691 "compilador.y"
                       { (yyval.str_value) = strdup("MULT"); }
#line 1976 "compilador.tab.c"
    break;

  case 91: /* vezes_div_and: DIV  */
#line 692 "compilador.y"
                     { (yyval.str_value) = strdup("DIVI"); }
#line 1982 "compilador.tab.c"
    break;

  case 92: /* vezes_div_and: AND  */
#line 693 "compilador.y"
                     { (yyval.str_value) = strdup("CONJ"); }
#line 1988 "compilador.tab.c"
    break;

  case 93: /* procedimento_ou_vazio: chama_procedimento  */
#line 696 "compilador.y"
                                          {
                        sptr_var_proc = pilha_tipos_topo(&pilha_ident_esquerdo);
                        pilha_tipos_desempilhar(&pilha_ident_esquerdo);
                     }
#line 1997 "compilador.tab.c"
    break;

  case 94: /* procedimento_ou_vazio: comando_vazio  */
#line 700 "compilador.y"
                                     {

                        sptr = pilha_tipos_topo(&pilha_ident_esquerdo); 
                        pilha_tipos_desempilhar(&pilha_ident_esquerdo); 
                     }
#line 2007 "compilador.tab.c"
    break;

  case 95: /* fator: variavel procedimento_ou_vazio  */
#line 717 "compilador.y"
                               { 

         if(!sptr){
            fprintf(stderr, "ERRO: Variável não encontrada!\n");
            exit(1);
         }
         
         (yyval.int_value) = sptr->conteudo.var.tipo;

         int proximo = 0;
         if (sptr->categoria == VARIAVEL_S){
            if (dentro_chamada_proc){
               if (num_params_chamada >= sptr_var_proc->conteudo.proc.qtd_parametros){ // se a localizacao desse parametro no procedimento excede a quantidade declarada
                  fprintf(stderr, "ERRO: Excesso de parâmetros em chamada de procedimento!\n");
                  exit(1);
               }
               if (sptr_var_proc->conteudo.proc.lista[num_params_chamada].passagem == PARAMETRO_REF_S){
                  sprintf(buffer_mepa, "CREN %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);   // se o tipo desse paramtro for por referencia entao CREN
               }
               else if (sptr_var_proc->conteudo.proc.lista[num_params_chamada].passagem == PARAMETRO_COPIA_S){
                  sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
               } 

            } else if (sptr_var_proc && sptr_var_proc->categoria != FUNCAO_S){
               sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
            } else if (atribui && (sptr_var_proc && sptr_var_proc->categoria == FUNCAO_S) && sptr_atribuicao->categoria != FUNCAO_S){
               sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
            } else {
               proximo = 1;
            }

         }
         else if (sptr->categoria == PARAMETRO_S){
            if (sptr->conteudo.param.passagem == PARAMETRO_COPIA_S)
               sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.param.deslocamento);
            else {
               if(sptr_var_proc->conteudo.proc.lista[num_params_chamada].passagem == PARAMETRO_REF_S){
                  sprintf(buffer_mepa, "CRVL %d, %d", sptr->nivel, sptr->conteudo.param.deslocamento);
               } else {
                  sprintf(buffer_mepa, "CRVI %d, %d", sptr->nivel, sptr->conteudo.param.deslocamento); 
               }
            }
         } else if (sptr->categoria != FUNCAO_S){
            fprintf(stderr, "ERRO: Procedimento tratado como variável!!\n");
            exit(1);
         } else {
            proximo = 1;
         }
         if(!proximo)
            geraCodigo(NULL, buffer_mepa);
      }
#line 2063 "compilador.tab.c"
    break;

  case 97: /* fator: VALOR_BOOL  */
#line 769 "compilador.y"
                   {
         (yyval.int_value) = BOOLEAN_S;
         if(strcmp(token, "True") == 0)
            sprintf (buffer_mepa, "CRCT %d", 1);
         else
            sprintf (buffer_mepa, "CRCT %d", 0);
         geraCodigo(NULL, buffer_mepa);
      }
#line 2076 "compilador.tab.c"
    break;

  case 98: /* fator: ABRE_PARENTESES expressao FECHA_PARENTESES  */
#line 777 "compilador.y"
                                                   { (yyval.int_value) = (yyvsp[-1].int_value); }
#line 2082 "compilador.tab.c"
    break;

  case 99: /* fator: NOT fator  */
#line 778 "compilador.y"
                  {
         if ((yyvsp[0].int_value) != BOOLEAN_S){
            fprintf(stderr, "ERRO: Operação booleana entre operandos não booleanos!\n");
            exit(1);
         }
         (yyval.int_value) = BOOLEAN_S;
         geraCodigo(NULL, "NEGA");
       }
#line 2095 "compilador.tab.c"
    break;

  case 100: /* variavel: IDENT  */
#line 795 "compilador.y"
         {
            sptr = busca_simbolo(&ts, token);
            pilha_tipos_empilhar(&pilha_ident_esquerdo, busca_simbolo(&ts, token));
         }
#line 2104 "compilador.tab.c"
    break;

  case 101: /* numero: NUMERO  */
#line 805 "compilador.y"
               {
         (yyval.int_value) = INTEGER_S;
         sprintf (buffer_mepa, "CRCT %d", atoi(token));
         geraCodigo(NULL, buffer_mepa);
      }
#line 2114 "compilador.tab.c"
    break;

  case 105: /* item_leitura: IDENT  */
#line 818 "compilador.y"
               {
                  geraCodigo(NULL, "LEIT");
                  sptr = busca_simbolo(&ts, token);
                  if(!sptr || sptr->categoria == PROCEDIMENTO_S){
                     fprintf(stderr, "ERRO:\n Uso incorreto da leitura no procedimento\n"); 
                     exit(1);
                  }
                  sprintf(buffer_mepa, "ARMZ %d, %d", sptr->nivel, sptr->conteudo.var.deslocamento);
                  geraCodigo(NULL, buffer_mepa);
               }
#line 2129 "compilador.tab.c"
    break;

  case 107: /* escreve_itens: escreve_itens VIRGULA expressao  */
#line 833 "compilador.y"
                                               {geraCodigo(NULL, "IMPR");}
#line 2135 "compilador.tab.c"
    break;

  case 108: /* escreve_itens: expressao  */
#line 833 "compilador.y"
                                                                                      {geraCodigo(NULL, "IMPR");}
#line 2141 "compilador.tab.c"
    break;


#line 2145 "compilador.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 836 "compilador.y"


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
   inicializa(&ts);
   inicializa(&pilha_atribuicao);
   pilha_rotulos_inicializar(&pilha_rotulos);
   pilha_rotulos_inicializar(&pilha_amem);
   pilha_rotulos_inicializar(&pilha_procs);
   pilha_tipos_inicializar(&pilha_ident_esquerdo);

   yyin=fp;
   yyparse();

   pilha_rotulos_destruir(&pilha_rotulos);
   pilha_rotulos_destruir(&pilha_amem);
   pilha_rotulos_destruir(&pilha_procs);
   pilha_tipos_destruir(&pilha_ident_esquerdo);

   return 0;
}
