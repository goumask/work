
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     FOR = 261,
     FUNCTION = 262,
     RETURN = 263,
     BREAK = 264,
     CONTINUE = 265,
     AND = 266,
     NOT = 267,
     OR = 268,
     LOCAL = 269,
     TRUE = 270,
     FALSE = 271,
     NIL = 272,
     EQUAL_EQUAL = 273,
     NOT_EQUAL = 274,
     PLUS_PLUS = 275,
     MINUS_MINUS = 276,
     LESS_EQUAL = 277,
     GREATER_EQUAL = 278,
     COLON_COLON = 279,
     DOT_DOT = 280,
     INT = 281,
     STR = 282,
     REAL = 283,
     ID = 284,
     UMINUS = 285
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define NOT 267
#define OR 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define EQUAL_EQUAL 273
#define NOT_EQUAL 274
#define PLUS_PLUS 275
#define MINUS_MINUS 276
#define LESS_EQUAL 277
#define GREATER_EQUAL 278
#define COLON_COLON 279
#define DOT_DOT 280
#define INT 281
#define STR 282
#define REAL 283
#define ID 284
#define UMINUS 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 69 "parser.y"

    int numInt;
    double numReal;
    char* string;
    struct id* exprNode; // Compiler says: unknown type name 'Id_t'



/* Line 1676 of yacc.c  */
#line 121 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


