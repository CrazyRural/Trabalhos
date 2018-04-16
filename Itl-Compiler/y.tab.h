/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_MAIN = 258,
    TOKEN_BEGIN = 259,
    TOKEN_VAR = 260,
    TOKEN_INT = 261,
    TOKEN_FLOAT = 262,
    TOKEN_DOUBLE = 263,
    TOKEN_CHAR = 264,
    TOKEN_BOOL = 265,
    TOKEN_STR = 266,
    TOKEN_NULL = 267,
    TOKEN_VOID = 268,
    TOKEN_IF = 269,
    TOKEN_ELSE = 270,
    TOKEN_ELSEIF = 271,
    TOKEN_SWITCH = 272,
    TOKEN_CASE = 273,
    TOKEN_DEFAULT = 274,
    TOKEN_IMP = 275,
    TOKEN_BREAK_ALL = 276,
    TOKEN_BREAK = 277,
    TOKEN_CONTINUE = 278,
    TOKEN_DO = 279,
    TOKEN_FOR = 280,
    TOKEN_WHILE = 281,
    TOKEN_PRINT = 282,
    TOKEN_ERROR = 283,
    TOKEN_STRUCT = 284,
    TOKEN_NOME = 285,
    TOKEN_NUM_INT = 286,
    TOKEN_NUM_FLOAT = 287,
    TOKEN_BOOLEAN_FALSE = 288,
    TOKEN_BOOLEAN_TRUE = 289,
    TOKEN_CARACTERE = 290,
    TOKEN_STRING = 291,
    TOKEN_POTENCIA = 292,
    TOKEN_MAIOR = 293,
    TOKEN_MENOR = 294,
    TOKEN_DIF = 295,
    TOKEN_IGUAL = 296,
    TOKEN_MAIORIGUAL = 297,
    TOKEN_MENORIGUAL = 298,
    TOKEN_E = 299,
    TOKEN_OU = 300,
    TOKEN_MAISIGUAL = 301,
    TOKEN_MENOSIGUAL = 302,
    TOKEN_VEZESIGUAL = 303,
    TOKEN_DIVIDEIGUAL = 304,
    TOKEN_PONTOIGUAL = 305,
    TOKEN_CONV_FLOAT = 306,
    TOKEN_CONV_INT = 307,
    TOKEN_ATR = 308,
    TOKEN_SCANF = 309,
    TOKEN_COMENT = 310,
    TOKEN_COM_INT = 311,
    TOKEN_COM_END = 312,
    TOKEN_LINECOMENT = 313,
    TOKEN_FUNCT = 314,
    TOKEN_RETURN = 315
  };
#endif
/* Tokens.  */
#define TOKEN_MAIN 258
#define TOKEN_BEGIN 259
#define TOKEN_VAR 260
#define TOKEN_INT 261
#define TOKEN_FLOAT 262
#define TOKEN_DOUBLE 263
#define TOKEN_CHAR 264
#define TOKEN_BOOL 265
#define TOKEN_STR 266
#define TOKEN_NULL 267
#define TOKEN_VOID 268
#define TOKEN_IF 269
#define TOKEN_ELSE 270
#define TOKEN_ELSEIF 271
#define TOKEN_SWITCH 272
#define TOKEN_CASE 273
#define TOKEN_DEFAULT 274
#define TOKEN_IMP 275
#define TOKEN_BREAK_ALL 276
#define TOKEN_BREAK 277
#define TOKEN_CONTINUE 278
#define TOKEN_DO 279
#define TOKEN_FOR 280
#define TOKEN_WHILE 281
#define TOKEN_PRINT 282
#define TOKEN_ERROR 283
#define TOKEN_STRUCT 284
#define TOKEN_NOME 285
#define TOKEN_NUM_INT 286
#define TOKEN_NUM_FLOAT 287
#define TOKEN_BOOLEAN_FALSE 288
#define TOKEN_BOOLEAN_TRUE 289
#define TOKEN_CARACTERE 290
#define TOKEN_STRING 291
#define TOKEN_POTENCIA 292
#define TOKEN_MAIOR 293
#define TOKEN_MENOR 294
#define TOKEN_DIF 295
#define TOKEN_IGUAL 296
#define TOKEN_MAIORIGUAL 297
#define TOKEN_MENORIGUAL 298
#define TOKEN_E 299
#define TOKEN_OU 300
#define TOKEN_MAISIGUAL 301
#define TOKEN_MENOSIGUAL 302
#define TOKEN_VEZESIGUAL 303
#define TOKEN_DIVIDEIGUAL 304
#define TOKEN_PONTOIGUAL 305
#define TOKEN_CONV_FLOAT 306
#define TOKEN_CONV_INT 307
#define TOKEN_ATR 308
#define TOKEN_SCANF 309
#define TOKEN_COMENT 310
#define TOKEN_COM_INT 311
#define TOKEN_COM_END 312
#define TOKEN_LINECOMENT 313
#define TOKEN_FUNCT 314
#define TOKEN_RETURN 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
