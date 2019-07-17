/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_GRAMMAR_H_INCLUDED
# define YY_YY_GRAMMAR_H_INCLUDED
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
    TOK_GOTO = 258,
    TOK_CONSTRAINT = 259,
    TOK_MODULE = 260,
    TOK_PROCESS = 261,
    TOK_CONTEXT = 262,
    TOK_EU = 263,
    TOK_AU = 264,
    TOK_EBU = 265,
    TOK_ABU = 266,
    TOK_MINU = 267,
    TOK_MAXU = 268,
    TOK_VAR = 269,
    TOK_IVAR = 270,
    TOK_DEFINE = 271,
    TOK_INIT = 272,
    TOK_TRANS = 273,
    TOK_INVAR = 274,
    TOK_SPEC = 275,
    TOK_CTLSPEC = 276,
    TOK_CTLGSPEC = 277,
    TOK_LTLSPEC = 278,
    TOK_COMPUTE = 279,
    TOK_PSLSPEC = 280,
    TOK_CONSTANTS = 281,
    TOK_INVARSPEC = 282,
    TOK_FAIRNESS = 283,
    TOK_COMPASSION = 284,
    TOK_JUSTICE = 285,
    TOK_ISA = 286,
    TOK_ASSIGN = 287,
    TOK_OF = 288,
    TOK_CONS = 289,
    TOK_SEMI = 290,
    TOK_LP = 291,
    TOK_RP = 292,
    TOK_RB = 293,
    TOK_LCB = 294,
    TOK_RCB = 295,
    TOK_EQDEF = 296,
    TOK_TWODOTS = 297,
    TOK_SELF = 298,
    TOK_CASE = 299,
    TOK_ESAC = 300,
    TOK_COLON = 301,
    TOK_INCONTEXT = 302,
    TOK_SIMPWFF = 303,
    TOK_LTLWFF = 304,
    TOK_LTLPSL = 305,
    TOK_CTLWFF = 306,
    TOK_COMPWFF = 307,
    TOK_CTLGWFF = 308,
    TOK_ARRAY = 309,
    TOK_BOOLEAN = 310,
    TOK_INTEGER = 311,
    TOK_REAL = 312,
    TOK_WORD = 313,
    TOK_BOOL = 314,
    TOK_WORD1 = 315,
    TOK_WAREAD = 316,
    TOK_WAWRITE = 317,
    TOK_ATOM = 318,
    TOK_FALSEEXP = 319,
    TOK_TRUEEXP = 320,
    TOK_NUMBER = 321,
    TOK_NUMBER_FRAC = 322,
    TOK_NUMBER_REAL = 323,
    TOK_NUMBER_EXP = 324,
    TOK_NUMBER_WORD = 325,
    TOK_COMMA = 326,
    TOK_IMPLIES = 327,
    TOK_IFF = 328,
    TOK_OR = 329,
    TOK_XOR = 330,
    TOK_XNOR = 331,
    TOK_AND = 332,
    TOK_NOT = 333,
    TOK_EX = 334,
    TOK_AX = 335,
    TOK_EF = 336,
    TOK_AF = 337,
    TOK_EG = 338,
    TOK_AG = 339,
    TOK_EE = 340,
    TOK_AA = 341,
    TOK_SINCE = 342,
    TOK_UNTIL = 343,
    TOK_TRIGGERED = 344,
    TOK_RELEASES = 345,
    TOK_EBF = 346,
    TOK_EBG = 347,
    TOK_ABF = 348,
    TOK_ABG = 349,
    TOK_BUNTIL = 350,
    TOK_MMIN = 351,
    TOK_MMAX = 352,
    TOK_OP_NEXT = 353,
    TOK_OP_GLOBAL = 354,
    TOK_OP_FUTURE = 355,
    TOK_OP_PREC = 356,
    TOK_OP_NOTPRECNOT = 357,
    TOK_OP_HISTORICAL = 358,
    TOK_OP_ONCE = 359,
    TOK_EQUAL = 360,
    TOK_NOTEQUAL = 361,
    TOK_LT = 362,
    TOK_GT = 363,
    TOK_LE = 364,
    TOK_GE = 365,
    TOK_UNION = 366,
    TOK_SETIN = 367,
    TOK_LSHIFT = 368,
    TOK_RSHIFT = 369,
    TOK_LROTATE = 370,
    TOK_RROTATE = 371,
    TOK_MOD = 372,
    TOK_PLUS = 373,
    TOK_MINUS = 374,
    TOK_TIMES = 375,
    TOK_DIVIDE = 376,
    TOK_NEXT = 377,
    TOK_SMALLINIT = 378,
    TOK_CONCATENATION = 379,
    TOK_LB = 380,
    TOK_DOT = 381,
    TOK_BIT = 382,
    TOK_GAME = 383,
    TOK_PLAYER_1 = 384,
    TOK_PLAYER_2 = 385,
    TOK_REACHTARGET = 386,
    TOK_AVOIDTARGET = 387,
    TOK_REACHDEADLOCK = 388,
    TOK_AVOIDDEADLOCK = 389,
    TOK_BUCHIGAME = 390,
    TOK_GENREACTIVITY = 391,
    TOK_PRED = 392,
    TOK_PREDSLIST = 393,
    TOK_MIRROR = 394
  };
#endif
/* Tokens.  */
#define TOK_GOTO 258
#define TOK_CONSTRAINT 259
#define TOK_MODULE 260
#define TOK_PROCESS 261
#define TOK_CONTEXT 262
#define TOK_EU 263
#define TOK_AU 264
#define TOK_EBU 265
#define TOK_ABU 266
#define TOK_MINU 267
#define TOK_MAXU 268
#define TOK_VAR 269
#define TOK_IVAR 270
#define TOK_DEFINE 271
#define TOK_INIT 272
#define TOK_TRANS 273
#define TOK_INVAR 274
#define TOK_SPEC 275
#define TOK_CTLSPEC 276
#define TOK_CTLGSPEC 277
#define TOK_LTLSPEC 278
#define TOK_COMPUTE 279
#define TOK_PSLSPEC 280
#define TOK_CONSTANTS 281
#define TOK_INVARSPEC 282
#define TOK_FAIRNESS 283
#define TOK_COMPASSION 284
#define TOK_JUSTICE 285
#define TOK_ISA 286
#define TOK_ASSIGN 287
#define TOK_OF 288
#define TOK_CONS 289
#define TOK_SEMI 290
#define TOK_LP 291
#define TOK_RP 292
#define TOK_RB 293
#define TOK_LCB 294
#define TOK_RCB 295
#define TOK_EQDEF 296
#define TOK_TWODOTS 297
#define TOK_SELF 298
#define TOK_CASE 299
#define TOK_ESAC 300
#define TOK_COLON 301
#define TOK_INCONTEXT 302
#define TOK_SIMPWFF 303
#define TOK_LTLWFF 304
#define TOK_LTLPSL 305
#define TOK_CTLWFF 306
#define TOK_COMPWFF 307
#define TOK_CTLGWFF 308
#define TOK_ARRAY 309
#define TOK_BOOLEAN 310
#define TOK_INTEGER 311
#define TOK_REAL 312
#define TOK_WORD 313
#define TOK_BOOL 314
#define TOK_WORD1 315
#define TOK_WAREAD 316
#define TOK_WAWRITE 317
#define TOK_ATOM 318
#define TOK_FALSEEXP 319
#define TOK_TRUEEXP 320
#define TOK_NUMBER 321
#define TOK_NUMBER_FRAC 322
#define TOK_NUMBER_REAL 323
#define TOK_NUMBER_EXP 324
#define TOK_NUMBER_WORD 325
#define TOK_COMMA 326
#define TOK_IMPLIES 327
#define TOK_IFF 328
#define TOK_OR 329
#define TOK_XOR 330
#define TOK_XNOR 331
#define TOK_AND 332
#define TOK_NOT 333
#define TOK_EX 334
#define TOK_AX 335
#define TOK_EF 336
#define TOK_AF 337
#define TOK_EG 338
#define TOK_AG 339
#define TOK_EE 340
#define TOK_AA 341
#define TOK_SINCE 342
#define TOK_UNTIL 343
#define TOK_TRIGGERED 344
#define TOK_RELEASES 345
#define TOK_EBF 346
#define TOK_EBG 347
#define TOK_ABF 348
#define TOK_ABG 349
#define TOK_BUNTIL 350
#define TOK_MMIN 351
#define TOK_MMAX 352
#define TOK_OP_NEXT 353
#define TOK_OP_GLOBAL 354
#define TOK_OP_FUTURE 355
#define TOK_OP_PREC 356
#define TOK_OP_NOTPRECNOT 357
#define TOK_OP_HISTORICAL 358
#define TOK_OP_ONCE 359
#define TOK_EQUAL 360
#define TOK_NOTEQUAL 361
#define TOK_LT 362
#define TOK_GT 363
#define TOK_LE 364
#define TOK_GE 365
#define TOK_UNION 366
#define TOK_SETIN 367
#define TOK_LSHIFT 368
#define TOK_RSHIFT 369
#define TOK_LROTATE 370
#define TOK_RROTATE 371
#define TOK_MOD 372
#define TOK_PLUS 373
#define TOK_MINUS 374
#define TOK_TIMES 375
#define TOK_DIVIDE 376
#define TOK_NEXT 377
#define TOK_SMALLINIT 378
#define TOK_CONCATENATION 379
#define TOK_LB 380
#define TOK_DOT 381
#define TOK_BIT 382
#define TOK_GAME 383
#define TOK_PLAYER_1 384
#define TOK_PLAYER_2 385
#define TOK_REACHTARGET 386
#define TOK_AVOIDTARGET 387
#define TOK_REACHDEADLOCK 388
#define TOK_AVOIDDEADLOCK 389
#define TOK_BUCHIGAME 390
#define TOK_GENREACTIVITY 391
#define TOK_PRED 392
#define TOK_PREDSLIST 393
#define TOK_MIRROR 394

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 113 "grammar.y" /* yacc.c:1909  */

  node_ptr node;
  int lineno;

#line 337 "grammar.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_H_INCLUDED  */
