/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 53 "parser.bison" /* yacc.c:1913  */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Node* root;

#line 57 "parser.h" /* yacc.c:1913  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    TK_INT = 259,
    TK_FLOAT = 260,
    TK_BOOLEAN = 261,
    TYPE_INT = 262,
    TYPE_FLOAT = 263,
    TYPE_BOOLEAN = 264,
    ASSIGN = 265,
    PLUS = 266,
    MINUS = 267,
    MULT = 268,
    DIV = 269,
    MOD = 270,
    EQ = 271,
    DIF = 272,
    LT = 273,
    LTE = 274,
    GT = 275,
    GTE = 276,
    IF = 277,
    THEN = 278,
    ELSE = 279,
    WHILE = 280,
    RETURN = 281,
    PAR_OPEN = 282,
    PAR_CLOSE = 283,
    RECT_OPEN = 284,
    RECT_CLOSE = 285,
    BRACKET_OPEN = 286,
    BRACKET_CLOSE = 287,
    SEMI = 288,
    COMMA = 289,
    COMMENT_BEGIN = 290,
    COMMENT_END = 291,
    MAIN = 292,
    READ = 293,
    WRITE = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "parser.bison" /* yacc.c:1913  */

    int intValue;
    int boolValue;
    float floatValue;
    char charValue;
    char* stringValue;
    Node* nodeValue;
    Type* typeValue;
    ParamList* paramValue;
    Expr* exprValue;

#line 121 "parser.h" /* yacc.c:1913  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
