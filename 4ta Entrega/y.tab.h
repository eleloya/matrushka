/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     IFTKN = 258,
     ENDIFTKN = 259,
     ELSETKN = 260,
     FUNCTKN = 261,
     ENDFUNCTKN = 262,
     RETURNFUNCTKN = 263,
     WHILETKN = 264,
     ENDWHILETKN = 265,
     READTKN = 266,
     WRITETKN = 267,
     IDTKN = 268,
     MATRUSHKATKN = 269,
     ENDMATRUSHKATKN = 270,
     MESSAGETKN = 271,
     INTTKN = 272,
     DOUBLETKN = 273,
     STRINGTKN = 274,
     BOOLTKN = 275,
     INTVALTKN = 276,
     DOUBLEVALTKN = 277,
     STRINGVALTKN = 278,
     TRUETKN = 279,
     FALSETKN = 280,
     ASSIGNTKN = 281,
     PLUSTKN = 282,
     MINUSTKN = 283,
     TIMESTKN = 284,
     DIVTKN = 285,
     LTTKN = 286,
     LTETKN = 287,
     GTTKN = 288,
     GTETKN = 289,
     EQUALTKN = 290,
     NOTEQUALTKN = 291,
     ASSIGNSECRETTKN = 292,
     ORTKN = 293,
     ANDTKN = 294,
     LEFTPTKN = 295,
     RIGHTPTKN = 296,
     SEMICOLONTKN = 297,
     LEFTBTKN = 298,
     RIGHTBTKN = 299,
     COMMATKN = 300,
     OPENBLOCKTKN = 301
   };
#endif
/* Tokens.  */
#define IFTKN 258
#define ENDIFTKN 259
#define ELSETKN 260
#define FUNCTKN 261
#define ENDFUNCTKN 262
#define RETURNFUNCTKN 263
#define WHILETKN 264
#define ENDWHILETKN 265
#define READTKN 266
#define WRITETKN 267
#define IDTKN 268
#define MATRUSHKATKN 269
#define ENDMATRUSHKATKN 270
#define MESSAGETKN 271
#define INTTKN 272
#define DOUBLETKN 273
#define STRINGTKN 274
#define BOOLTKN 275
#define INTVALTKN 276
#define DOUBLEVALTKN 277
#define STRINGVALTKN 278
#define TRUETKN 279
#define FALSETKN 280
#define ASSIGNTKN 281
#define PLUSTKN 282
#define MINUSTKN 283
#define TIMESTKN 284
#define DIVTKN 285
#define LTTKN 286
#define LTETKN 287
#define GTTKN 288
#define GTETKN 289
#define EQUALTKN 290
#define NOTEQUALTKN 291
#define ASSIGNSECRETTKN 292
#define ORTKN 293
#define ANDTKN 294
#define LEFTPTKN 295
#define RIGHTPTKN 296
#define SEMICOLONTKN 297
#define LEFTBTKN 298
#define RIGHTBTKN 299
#define COMMATKN 300
#define OPENBLOCKTKN 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

