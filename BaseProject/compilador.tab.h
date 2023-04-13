/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_COMPILADOR_TAB_H_INCLUDED
# define YY_YY_COMPILADOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    VAR = 259,                     /* VAR  */
    T_BEGIN = 260,                 /* T_BEGIN  */
    T_END = 261,                   /* T_END  */
    LABEL = 262,                   /* LABEL  */
    TYPE = 263,                    /* TYPE  */
    ARRAY = 264,                   /* ARRAY  */
    OF = 265,                      /* OF  */
    PROCEDURE = 266,               /* PROCEDURE  */
    FUNCTION = 267,                /* FUNCTION  */
    GOTO = 268,                    /* GOTO  */
    IF = 269,                      /* IF  */
    THEN = 270,                    /* THEN  */
    ELSE = 271,                    /* ELSE  */
    FOR = 272,                     /* FOR  */
    DO = 273,                      /* DO  */
    WHILE = 274,                   /* WHILE  */
    OR = 275,                      /* OR  */
    AND = 276,                     /* AND  */
    NOT = 277,                     /* NOT  */
    DIV = 278,                     /* DIV  */
    ASTERISCO = 279,               /* ASTERISCO  */
    ATRIBUICAO = 280,              /* ATRIBUICAO  */
    PONTO_E_VIRGULA = 281,         /* PONTO_E_VIRGULA  */
    DOIS_PONTOS = 282,             /* DOIS_PONTOS  */
    VIRGULA = 283,                 /* VIRGULA  */
    PONTO = 284,                   /* PONTO  */
    ABRE_PARENTESES = 285,         /* ABRE_PARENTESES  */
    FECHA_PARENTESES = 286,        /* FECHA_PARENTESES  */
    ABRE_COLCHETES = 287,          /* ABRE_COLCHETES  */
    FECHA_COLCHETES = 288,         /* FECHA_COLCHETES  */
    ABRE_CHAVES = 289,             /* ABRE_CHAVES  */
    FECHA_CHAVES = 290,            /* FECHA_CHAVES  */
    MAIOR = 291,                   /* MAIOR  */
    MENOR = 292,                   /* MENOR  */
    NUMERO = 293,                  /* NUMERO  */
    IDENT = 294                    /* IDENT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_COMPILADOR_TAB_H_INCLUDED  */
