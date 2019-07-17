/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammar.y" /* yacc.c:339  */

/**CFile***********************************************************************

  FileName    [grammar.y]

  PackageName [parser]

  Synopsis    [Grammar (for Yacc and Bison) of NuSMV input language]

  SeeAlso     [input.l]

  Author      [Andrei Tchaltsev, Marco Roveri]

  Copyright   [
  This file is part of the ``parser'' package of NuSMV version 2. 
  Copyright (C) 1998-2005 by CMU and ITC-irst. 

  NuSMV version 2 is free software; you can redistribute it and/or 
  modify it under the terms of the GNU Lesser General Public 
  License as published by the Free Software Foundation; either 
  version 2 of the License, or (at your option) any later version.

  NuSMV version 2 is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public 
  License along with this library; if not, write to the Free Software 
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.

  For more information on NuSMV see <http://nusmv.irst.itc.it>
  or email to <nusmv-users@irst.itc.it>.
  Please report bugs to <nusmv-users@irst.itc.it>.

  To contact the NuSMV development board, email to <nusmv@irst.itc.it>. ]

******************************************************************************/

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <setjmp.h>

#if HAVE_MALLOC_H
# if HAVE_SYS_TYPES_H
#  include <sys/types.h>
# endif  
# include <malloc.h>
#elif HAVE_SYS_MALLOC_H
# if HAVE_SYS_TYPES_H
#  include <sys/types.h>
# endif  
# include <sys/malloc.h>
#elif HAVE_STDLIB_H
# include <stdlib.h>
#endif

#include <limits.h>

#include "parserInt.h"
#include "utils/utils.h"
#include "utils/ustring.h"
#include "node/node.h"
#include "opt/opt.h"
#include "utils/error.h"

#include "symbols.h"
#include "mbp_symbols.h"

static char rcsid[] UTIL_UNUSED = "$Id: grammar.y,v 1.19.4.10.4.46.4.17 2007/05/17 09:23:22 nusmv Exp $";

#define YYMAXDEPTH INT_MAX

node_ptr parsed_tree; /* the returned value of parsing */

enum PARSE_MODE parse_mode_flag; /* the flag what should be parsed */

extern FILE * nusmv_stderr;
    
void yyerror ARGS((char *s));
void yyerror_lined ARGS((const char *s, int line));
static node_ptr context2maincontext ARGS((node_ptr context));


/* this enum is used to distinguish 
   different kinds of expressions: SIMPLE, NEXT, CTL and LTL.
   Since syntactically only one global kind of expressions exists,
   we have to invoke a special function which checks that an expression
   complies to the additional syntactic constrains.
   So, if an ltl-expression is expected then occurrences of NEXT or EBF
   operators will cause the termination of parsing.

   NB: An alternative to invoking a checking function would be to write quite
   intricate syntactic rules to distinguish all the cases.

   NB: This checking function could also be a part of the type checker,
   but it is more straightforward to write a separate function.
*/
 enum EXP_KIND {EXP_SIMPLE, EXP_NEXT, EXP_LTL, EXP_CTL, EXP_CTLG}; 

  static boolean isCorrectExp ARGS((node_ptr exp, enum EXP_KIND expectedKind));

  static int nusmv_parse_psl ARGS((void));

  /* below vars are used if input file contains game definition */
  static node_ptr mbp_parser_spec_list = Nil;
  static node_ptr mbp_parser_player_1 = Nil;
  static node_ptr mbp_parser_player_2 = Nil;

#line 178 "grammar.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 113 "grammar.y" /* yacc.c:355  */

  node_ptr node;
  int lineno;

#line 501 "grammar.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 518 "grammar.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1412

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  140
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  118
/* YYNRULES -- Number of rules.  */
#define YYNRULES  347
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  701

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   394

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   217,   217,   217,   247,   247,   254,   254,   269,   270,
     273,   274,   275,   279,   282,   284,   286,   289,   293,   294,
     295,   296,   297,   306,   315,   333,   334,   335,   336,   337,
     345,   353,   361,   366,   367,   368,   369,   370,   371,   373,
     376,   383,   385,   389,   394,   395,   399,   400,   401,   405,
     406,   407,   411,   412,   415,   416,   417,   423,   424,   425,
     428,   429,   433,   434,   437,   438,   442,   443,   444,   445,
     446,   447,   448,   451,   452,   457,   458,   459,   460,   461,
     462,   463,   465,   467,   469,   471,   472,   473,   474,   477,
     483,   484,   487,   488,   489,   490,   493,   494,   498,   499,
     502,   506,   507,   512,   513,   514,   515,   516,   517,   518,
     520,   525,   526,   528,   530,   537,   547,   548,   552,   553,
     554,   555,   559,   560,   564,   565,   568,   571,   572,   573,
     576,   577,   581,   582,   585,   586,   590,   591,   592,   593,
     594,   595,   603,   611,   619,   627,   630,   631,   632,   633,
     634,   635,   638,   639,   640,   644,   646,   647,   649,   650,
     652,   653,   655,   656,   658,   660,   663,   665,   667,   668,
     671,   675,   678,   679,   680,   681,   682,   683,   684,   694,
     697,   700,   703,   710,   711,   719,   727,   729,   730,   732,
     734,   739,   740,   741,   745,   746,   749,   750,   751,   752,
     755,   756,   759,   760,   761,   763,   768,   769,   784,   785,
     786,   787,   790,   793,   794,   795,   798,   799,   804,   805,
     807,   808,   809,   810,   811,   812,   813,   814,   815,   816,
     817,   818,   819,   820,   821,   822,   823,   824,   825,   826,
     836,   861,   862,   870,   886,   907,   908,   909,   910,   911,
     912,   918,   919,   923,   925,   926,   927,   928,   929,   941,
     942,   944,   945,   947,   949,   950,   952,   953,   955,   959,
     961,   962,   966,   968,   969,   971,   973,   978,   986,   988,
     990,   994,   997,  1000,  1005,  1008,  1009,  1012,  1015,  1024,
    1028,  1033,  1034,  1035,  1039,  1040,  1043,  1054,  1065,  1076,
    1077,  1079,  1082,  1085,  1088,  1092,  1099,  1108,  1111,  1113,
    1118,  1122,  1122,  1130,  1131,  1132,  1133,  1136,  1137,  1138,
    1139,  1140,  1148,  1149,  1150,  1153,  1155,  1157,  1159,  1161,
    1163,  1167,  1171,  1175,  1179,  1183,  1187,  1191,  1195,  1199,
    1203,  1215,  1216,  1217,  1220,  1221,  1224,  1224
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_GOTO", "TOK_CONSTRAINT",
  "TOK_MODULE", "TOK_PROCESS", "TOK_CONTEXT", "TOK_EU", "TOK_AU",
  "TOK_EBU", "TOK_ABU", "TOK_MINU", "TOK_MAXU", "TOK_VAR", "TOK_IVAR",
  "TOK_DEFINE", "TOK_INIT", "TOK_TRANS", "TOK_INVAR", "TOK_SPEC",
  "TOK_CTLSPEC", "TOK_CTLGSPEC", "TOK_LTLSPEC", "TOK_COMPUTE",
  "TOK_PSLSPEC", "TOK_CONSTANTS", "TOK_INVARSPEC", "TOK_FAIRNESS",
  "TOK_COMPASSION", "TOK_JUSTICE", "TOK_ISA", "TOK_ASSIGN", "TOK_OF",
  "TOK_CONS", "TOK_SEMI", "TOK_LP", "TOK_RP", "TOK_RB", "TOK_LCB",
  "TOK_RCB", "TOK_EQDEF", "TOK_TWODOTS", "TOK_SELF", "TOK_CASE",
  "TOK_ESAC", "TOK_COLON", "TOK_INCONTEXT", "TOK_SIMPWFF", "TOK_LTLWFF",
  "TOK_LTLPSL", "TOK_CTLWFF", "TOK_COMPWFF", "TOK_CTLGWFF", "TOK_ARRAY",
  "TOK_BOOLEAN", "TOK_INTEGER", "TOK_REAL", "TOK_WORD", "TOK_BOOL",
  "TOK_WORD1", "TOK_WAREAD", "TOK_WAWRITE", "TOK_ATOM", "TOK_FALSEEXP",
  "TOK_TRUEEXP", "TOK_NUMBER", "TOK_NUMBER_FRAC", "TOK_NUMBER_REAL",
  "TOK_NUMBER_EXP", "TOK_NUMBER_WORD", "TOK_COMMA", "TOK_IMPLIES",
  "TOK_IFF", "TOK_OR", "TOK_XOR", "TOK_XNOR", "TOK_AND", "TOK_NOT",
  "TOK_EX", "TOK_AX", "TOK_EF", "TOK_AF", "TOK_EG", "TOK_AG", "TOK_EE",
  "TOK_AA", "TOK_SINCE", "TOK_UNTIL", "TOK_TRIGGERED", "TOK_RELEASES",
  "TOK_EBF", "TOK_EBG", "TOK_ABF", "TOK_ABG", "TOK_BUNTIL", "TOK_MMIN",
  "TOK_MMAX", "TOK_OP_NEXT", "TOK_OP_GLOBAL", "TOK_OP_FUTURE",
  "TOK_OP_PREC", "TOK_OP_NOTPRECNOT", "TOK_OP_HISTORICAL", "TOK_OP_ONCE",
  "TOK_EQUAL", "TOK_NOTEQUAL", "TOK_LT", "TOK_GT", "TOK_LE", "TOK_GE",
  "TOK_UNION", "TOK_SETIN", "TOK_LSHIFT", "TOK_RSHIFT", "TOK_LROTATE",
  "TOK_RROTATE", "TOK_MOD", "TOK_PLUS", "TOK_MINUS", "TOK_TIMES",
  "TOK_DIVIDE", "TOK_NEXT", "TOK_SMALLINIT", "TOK_CONCATENATION", "TOK_LB",
  "TOK_DOT", "TOK_BIT", "TOK_GAME", "TOK_PLAYER_1", "TOK_PLAYER_2",
  "TOK_REACHTARGET", "TOK_AVOIDTARGET", "TOK_REACHDEADLOCK",
  "TOK_AVOIDDEADLOCK", "TOK_BUCHIGAME", "TOK_GENREACTIVITY", "TOK_PRED",
  "TOK_PREDSLIST", "TOK_MIRROR", "$accept", "begin", "$@1", "$@2", "$@3",
  "number", "integer", "number_word", "number_frac", "number_real",
  "number_exp", "subrange", "constant", "primary_expr",
  "case_element_list_expr", "case_element_expr", "concatination_expr",
  "multiplicative_expr", "additive_expr", "remainder_expr", "shift_expr",
  "set_expr", "set_list_expr", "union_expr", "in_expr", "relational_expr",
  "ctl_expr", "pure_ctl_expr", "ctl_and_expr", "ctl_or_expr",
  "ctl_iff_expr", "ctl_implies_expr", "ctl_basic_expr", "ltl_unary_expr",
  "pure_ltl_unary_expr", "ltl_binary_expr", "and_expr", "or_expr",
  "iff_expr", "implies_expr", "basic_expr", "setg_expr", "setg_list_expr",
  "uniong_expr", "ing_expr", "primg_expr", "relationalg_expr", "ctlg_expr",
  "pure_ctlg_expr", "ctlg_basic_expr", "simple_expression",
  "next_expression", "ctl_expression", "ltl_expression", "itype", "type",
  "type_value_list", "type_value", "complex_atom", "module_type",
  "simple_list_expression", "module_list", "module", "module_sign",
  "atom_list", "declarations", "declaration", "game_definition",
  "game_body", "game_body_element", "player_body", "player_body_element",
  "var", "var_decl_list", "var_decl", "input_var", "ivar_decl_list",
  "ivar_decl", "define", "define_list", "assign", "assign_list",
  "one_assign", "init", "invar", "trans", "fairness", "justice",
  "compassion", "invarspec", "ctlspec", "ltlspec", "pslspec", "ctlgspec",
  "constants", "constants_expression", "predicate_list", "predicate",
  "mirror", "player_num", "reachtarget", "avoidtarget", "reachdeadlock",
  "avoiddeadlock", "buchigame", "genreactivity", "compute",
  "compute_expression", "isa", "optsemi", "decl_var_id", "var_id",
  "command", "command_case", "context", "trace", "state", "$@4", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394
};
# endif

#define YYPACT_NINF -501

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-501)))

#define YYTABLE_NINF -348

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      92,    61,     9,    36,   887,  -501,    35,   735,     9,  -501,
    -501,    95,  -501,   887,   887,   887,   887,   887,   887,   887,
     -45,  1234,   -68,  -501,  -501,   887,   887,  -501,   887,    44,
     100,   118,   150,  -501,  -501,  -501,   160,  -501,  -501,  -501,
    -501,   956,  1025,  1025,  1025,  1025,  1025,  1025,    91,   107,
      72,    72,    72,    72,   887,   887,   887,   887,   887,   887,
     887,   174,  1153,   224,  -501,   232,  -501,  -501,  -501,  -501,
    -501,  -501,   171,   140,    89,   165,   159,   189,  -501,   196,
     188,   740,  -501,  -501,  -501,  -501,   270,   228,   303,   334,
    -501,  -501,  -501,   276,  -501,  -501,  -501,   287,   287,   287,
     287,   287,   287,  -501,   735,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,   279,   252,  -501,   281,   285,  -501,
     289,   291,    15,   154,  -501,   158,   203,   205,   218,  1234,
    1234,  -501,  1258,  1234,  1234,  1234,  1234,  1234,  1234,    24,
      34,   581,  -501,  -501,  -501,   251,   253,   341,   888,  -501,
    -501,   373,   734,   -68,  -501,   297,    20,  -501,   322,   887,
     323,   887,   887,   887,   887,  -501,   309,  1189,   171,  -501,
    -501,  1089,  -501,  -501,  -501,  -501,  -501,  -501,  1025,  1025,
    -501,   315,   317,  1025,  1025,  1025,  1025,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,   343,   345,  1189,   171,   887,    72,
     887,   152,  1189,  1189,  1189,  1189,  1189,  1189,  1189,  1189,
     665,   665,   665,   665,   665,   665,   665,   665,   887,   887,
     887,   887,   887,   887,   887,   887,   887,   887,    29,   736,
     474,   474,  -501,  -501,   887,   887,   354,   354,   355,   357,
    -501,  -501,  -501,   275,  -501,  -501,  -501,  -501,  -501,   340,
    -501,   340,  -501,   340,   887,   887,  -501,   340,   372,   194,
      82,  1054,  1234,  1293,   341,  -501,  1234,  -501,  1234,  -501,
    1234,  -501,  1234,  -501,  1234,  -501,  1234,  -501,  1234,   294,
    1234,   296,  1293,   341,   472,   472,  1234,   179,  1293,  1293,
    1293,  1293,  1293,  1293,  -501,   340,  1234,  1234,  1234,  1234,
    1234,  1234,   358,   354,  -501,  -501,  -501,   887,  -501,  -501,
     887,   389,   391,   359,   361,  -501,  -501,   365,   321,   397,
    -501,    80,   187,  -501,  -501,  -501,  -501,  -501,  -501,   399,
    -501,    17,  -501,  -501,   171,   140,   140,    89,    89,   165,
     159,   159,  -501,   196,   188,   188,   188,   188,   188,   188,
    -501,  -501,  -501,  -501,   270,   228,   228,   228,  -501,   303,
    -501,  -501,    11,   371,   371,  -501,   887,   887,   887,   887,
     887,  1234,   887,   -45,  -501,   401,   887,   887,   441,   887,
     424,  -501,   371,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,   354,   354,  -501,  -501,  -501,   887,   887,   439,  -501,
     -20,   -18,   -14,   436,   444,   -12,  -501,  -501,  -501,  1234,
    -501,  -501,  -501,  -501,  -501,  -501,   817,  1234,   886,  1234,
    -501,   251,   483,  -501,  -501,   341,   341,   341,   341,   341,
     341,   -10,  -501,  -501,  -501,  -501,  -501,  -501,   484,  -501,
    -501,   477,  -501,  -501,   887,   887,  1025,  1025,  1025,  1025,
    1025,  1025,  1025,    72,  1025,    72,  -501,  -501,   887,  -501,
     462,  -501,   371,  -501,   -22,   371,  -501,    31,   371,   354,
     354,   354,   354,   354,   406,   354,   354,  -501,   400,    10,
     354,   354,   887,   354,  -501,   -21,     3,  -501,  -501,  -501,
      12,    84,   492,  -501,   887,   469,  -501,  -501,   887,   887,
    -501,  1054,  1234,   955,  1234,  1024,  -501,  1234,  -501,   887,
    -501,   496,   463,  -501,   365,   365,   365,  -501,   321,   514,
    1025,   516,  1025,   523,  -501,  -501,   223,    72,   195,  -501,
     180,     0,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
     500,  -501,   401,  -501,  -501,   493,  -501,  -501,  -501,   529,
     530,  -501,    45,  -501,   354,   887,   495,   534,  -501,   535,
     538,   506,  1234,   595,  1234,   639,   354,  -501,   887,  -501,
     539,  -501,   546,  -501,    -7,   286,    -1,  -501,  -501,  -501,
     460,   552,  -501,  -501,   557,  -501,   555,  -501,  -501,    -1,
     560,   887,  -501,   400,   887,    16,    16,   887,   887,   222,
    -501,  -501,   561,  -501,  -501,  -501,  -501,   645,  -501,   767,
    -501,  -501,   562,  -501,  -501,    72,  -501,  -501,  -501,  -501,
     132,  -501,   400,   475,   569,   887,   818,  -501,  -501,   570,
    -501,   571,   579,     7,    21,   572,   580,  -501,  -501,   887,
    -501,  -501,  -501,   588,  -501,   286,   887,   405,   585,  -501,
      90,   180,  -501,   354,   583,   586,  -501,  -501,   121,    -7,
    -501,   590,  -501,  -501,  -501,  -501,  -501,   887,   887,   354,
     593,   599,   600,  -501,   582,  -501,  -501,   505,   887,   601,
    -501
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       6,     0,     0,     0,     0,     1,     0,   241,     3,   208,
     209,   324,   346,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,   322,     0,     0,    28,     0,     0,
       0,     0,     0,    27,    18,    19,     8,    14,    15,    16,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,    21,    22,    24,    23,
      58,    25,    44,    46,    49,    52,    54,    57,    62,    64,
      66,    73,   101,    74,   111,   102,   116,   118,   122,   124,
     126,   182,     7,   213,   218,   251,   251,     0,     0,     0,
       0,     0,     0,   240,   241,   245,   246,   247,   248,   249,
     250,   210,   211,   323,     0,     0,   179,     0,     0,   180,
       0,     0,     0,     0,   181,     0,     0,     0,     0,     0,
       0,   138,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   136,   132,   134,   145,   128,   152,   172,
     154,     0,     0,   340,   294,     0,     0,    60,     0,    41,
       0,     0,     0,     0,     0,     8,     0,     0,    34,    89,
     110,     0,    75,    76,    77,    78,    79,    80,     0,     0,
      10,     0,     0,     0,     0,     0,     0,   103,   106,   108,
     104,   105,   107,   109,     9,     8,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   212,
     243,   244,   299,   300,     0,     0,   311,   311,     0,     0,
     242,   325,   344,     0,   329,   326,   328,   327,   330,     0,
     336,     0,   332,     0,     0,     0,   338,     0,   172,     0,
       0,   130,     0,     0,   140,   171,    20,   155,    20,   157,
      20,   161,    20,   163,    20,   167,    20,   159,     0,     0,
       0,     0,     0,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   334,     0,     0,     0,     0,     0,
       0,     0,     0,   311,   295,    33,    59,     0,    38,    42,
       0,     0,     0,     0,     0,     9,    90,    92,    96,    98,
     100,     0,     0,    11,    12,    85,    87,    86,    88,     0,
      17,     0,    29,    30,    45,    47,    48,    50,    51,    53,
      55,    56,    63,    65,    67,    68,    69,    70,    71,    72,
     113,   112,   115,   114,   117,   119,   120,   121,   125,   123,
     214,   216,     0,   259,   264,   270,     0,     0,     0,     0,
       0,     0,     0,     0,   288,   291,     0,     0,     0,     0,
       0,   273,     0,   219,   221,   222,   227,   223,   224,   225,
     226,   228,   229,   230,   231,   232,   233,   235,   234,   237,
     238,   239,   236,   220,   252,   253,   258,   254,   255,   256,
     257,   311,   311,   312,   303,   304,     0,     0,     0,   341,
       0,     0,     0,     0,     0,     0,   153,   139,   129,     0,
     156,   158,   162,   164,   168,   160,     0,     0,     0,     0,
     133,   135,     0,   141,   142,   146,   147,   148,   149,   150,
     151,     0,   173,   174,   175,   176,   177,   178,     0,   296,
      61,     0,    35,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    31,     0,   215,
       0,   313,   260,   261,     0,   265,   266,     0,   269,   311,
     311,   311,   311,   311,   311,   311,   311,   200,   292,     0,
     311,   311,     0,   311,   310,   272,   311,   301,   302,   206,
       0,     0,   345,   331,     0,     0,   337,   333,     0,     0,
     339,   131,     0,     0,     0,     0,   143,     0,   335,     0,
      43,     0,     0,    91,    93,    94,    95,    99,    97,     0,
       0,     0,     0,     0,   217,   262,     0,     0,     0,   267,
       0,     0,   278,   280,   279,   285,   286,   289,   287,   307,
       0,   290,     0,   284,   281,     0,   282,   318,   317,     0,
       0,   274,     0,   298,   311,     0,     0,     0,   342,     0,
       0,     0,     0,     0,     0,     0,   311,    39,     0,    82,
       0,    81,     0,    32,     0,     0,     0,   183,   184,   185,
       0,   202,   187,   191,     0,   192,     0,   314,   315,     0,
       0,     0,   201,   293,     0,     0,     0,     0,     0,     0,
     305,   207,     0,   343,   308,   309,   169,     0,   165,     0,
     144,   297,     0,    84,    83,     0,   193,   198,   199,   197,
       0,   194,   196,     0,     0,     0,     0,   263,   316,     0,
     268,     0,     0,     0,     0,     0,     0,   319,   320,     0,
     170,   166,    40,     0,   188,     0,     0,     0,     0,   203,
       0,     0,   271,   311,     0,     0,   275,   321,     0,     0,
     195,     0,   190,   205,   186,   204,   283,     0,     0,   311,
       0,     0,     0,   306,     0,   277,   276,     0,     0,     0,
     189
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -501,  -501,  -501,  -501,  -501,  1001,  -193,  -501,  -501,  -501,
    -501,   114,    47,    37,   478,  -501,   300,   304,   435,   305,
    -501,   433,  -501,   443,   948,  -501,    28,   -23,   -29,   181,
    -501,   185,  -168,   -24,   615,   440,   250,   430,  -501,   432,
       1,   377,  -501,   378,  -501,   -65,  -501,   536,   541,   157,
     -13,  -365,  -246,   -11,  -377,  -501,  -501,    13,  -362,  -500,
    -405,  -501,   658,  -501,  -501,  -501,  -501,   666,   576,  -501,
     591,  -501,   453,  -501,   204,  -501,  -501,   191,   461,  -501,
     465,  -501,  -501,   466,   468,   473,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  -110,  -501,   447,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,   316,  -501,   119,
    -354,   -98,  -501,  -501,     6,  -501,  -501,  -501
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     4,    64,    65,    66,    67,    68,
      69,    70,    71,    72,   158,   159,    73,    74,    75,    76,
      77,    78,   156,    79,    80,    81,    82,    83,   317,   318,
     319,   320,   321,    84,    85,    86,    87,    88,    89,    90,
     116,   144,   260,   145,   146,   147,   148,   149,   150,   259,
     509,   120,   125,    92,   682,   604,   640,   641,   642,   683,
     510,     8,     9,    94,   362,   229,   383,    10,   103,   104,
     230,   404,   405,   482,   483,   385,   485,   486,   406,   488,
     407,   505,   571,   408,   409,   410,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   499,   153,   154,   401,   234,
     105,   106,   107,   108,   109,   110,   402,   128,   403,   414,
     484,   572,    23,    24,   420,   243,   114,   115
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     117,   118,   490,   121,   122,    91,   330,   123,   423,   424,
     487,   322,   511,   498,     6,   513,   119,   516,   169,    91,
     124,   517,   567,   520,   546,   528,   155,   157,   506,   160,
     187,   188,   189,   190,   191,   192,   193,    11,   413,    12,
      13,   611,   568,   304,   674,   561,   605,   635,   479,   574,
     248,   126,   127,    14,    15,   477,   601,   643,   675,   567,
     306,     5,   249,   478,    16,   180,   360,   264,   143,   152,
     172,   173,   174,   175,   176,   177,   283,   550,   168,   568,
     161,   562,   480,   575,    17,    18,   617,    19,    20,    21,
     165,   307,   361,    -4,   636,    -4,    -4,    -2,    93,   197,
     165,   569,   570,   547,   548,   514,   515,   514,   515,    -4,
      -4,   514,   515,   514,   515,   514,   515,   181,   182,   400,
      -4,   576,   428,   492,   493,   547,   548,   685,   547,   548,
     113,   487,   618,   619,   551,   142,   162,     7,   180,   303,
      -4,    -4,   166,    -4,    -4,    -4,   618,   619,   169,   278,
     313,   314,   166,   429,   163,   575,   547,   548,   689,   280,
     160,   575,   311,   312,   183,   184,   185,   186,   472,   603,
     618,   619,   664,   610,    22,   473,   143,   143,   151,   143,
     143,   143,   143,   143,   143,   143,   164,   331,   143,   250,
     181,   182,   575,   252,   350,   351,   352,   353,   283,   329,
     613,   251,   -10,   665,   197,   253,   316,   316,   168,   203,
     204,   325,   326,   327,   328,   332,   178,   264,   333,   595,
      -2,   411,   412,   445,   446,   447,   448,   449,   450,   594,
      -4,   427,   179,   168,   609,   597,   598,   599,   600,   334,
     194,   670,   443,   142,   142,   444,   180,   142,   142,   142,
     142,   142,   142,   256,   678,   124,   124,   421,   607,   422,
     198,   608,   595,   425,   202,   257,   296,   297,   298,   299,
     300,   301,   579,   580,   199,   474,   207,   596,   597,   598,
     599,   600,   475,   205,   206,   657,   601,   261,   658,   180,
     267,   269,   271,   273,   275,   277,   200,   201,   181,   182,
     211,   451,   208,   209,   539,   222,   541,   210,   460,   143,
     143,   461,   228,   143,   241,   143,   244,   143,   242,   143,
     245,   143,   691,   143,   246,   143,   247,   143,   254,   143,
     255,   143,   143,   143,   305,   143,   143,   143,   143,   143,
     143,   181,   182,   143,   143,   143,   143,   143,   143,   497,
     637,   638,   180,   489,   606,   491,   415,   218,   219,   220,
     221,   495,   284,   500,   501,   285,   503,   308,   119,   310,
     124,   124,   590,    91,   592,   315,   142,   223,   224,   225,
     142,   323,   142,   324,   142,   -11,   142,   -12,   142,   413,
     142,   416,   142,   417,   142,   467,   468,   469,   142,   142,
     142,   418,   639,   419,   181,   182,   226,   227,   294,   426,
     142,   142,   142,   142,   142,   142,   232,   233,   143,   437,
     295,   439,   459,   430,   458,   431,   462,   432,   463,   433,
     464,   434,   465,   435,   481,   436,   476,   438,   534,   535,
     536,   413,   466,   442,   595,   296,   297,   298,   299,   300,
     301,   531,   532,   452,   453,   454,   455,   456,   457,   596,
     597,   598,   599,   600,   497,   543,   286,   287,   601,   470,
     471,   180,   639,   355,   356,   357,   143,   502,   296,   297,
     298,   299,   300,   301,   143,   142,   143,   504,   363,   565,
     365,   366,   367,   368,   533,   316,   316,   316,   316,   316,
     316,   577,   316,   335,   336,   512,   381,   518,   262,   337,
     338,   130,   530,   340,   341,   519,   586,   653,   654,   124,
     124,   526,   529,   181,   182,   544,   560,  -347,   494,   527,
     507,   508,   578,   587,   588,   131,    34,    35,    36,    37,
      38,    39,    40,   142,   626,   235,   236,   237,   238,   239,
     282,   142,   589,   142,   591,   296,   297,   298,   299,   300,
     301,   593,   621,   612,   614,   615,   616,   622,   316,   143,
     316,   143,   623,   624,   143,   632,   625,   633,   296,   297,
     298,   299,   300,   301,   634,   645,   521,   540,   646,   542,
      61,   141,   647,   648,   523,   650,   525,   659,   651,   662,
     666,   652,   667,   671,   655,   656,   672,   676,   552,   553,
     554,   555,   556,   557,   558,   559,   673,   262,   677,   563,
     564,   679,   566,   684,   687,   573,   694,   688,   690,   143,
     698,   143,   668,   628,   695,   696,   142,   309,   142,   700,
     697,   142,   339,   342,   131,    34,    35,   195,    37,    38,
      39,    40,   538,   681,   343,   537,   170,   359,   358,   282,
     602,   440,   354,   441,   602,   258,   111,   296,   297,   298,
     299,   300,   301,   265,   112,   692,   549,   630,   680,   581,
     240,   583,   384,   660,   585,   699,   545,   231,   119,   496,
     386,     0,     0,   620,   387,   388,   142,   389,   142,   166,
     263,    25,   390,     0,    26,   631,     0,     0,    27,    28,
     644,   296,   297,   298,   299,   300,   301,   296,   297,   298,
     299,   300,   301,   649,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,     0,     0,   627,
       0,   629,     0,   196,     0,     0,     0,     0,     0,   663,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,     0,
      25,     0,     0,    26,     0,     0,     0,    27,    28,     0,
       0,   602,     0,    61,    62,   602,     0,    63,     0,     0,
       0,     0,   686,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,   661,     0,     0,   693,     0,
       0,     0,    41,    42,    43,    44,    45,    46,    47,    48,
      49,     0,     0,     0,     0,    50,    51,    52,    53,     0,
       0,     0,    54,    55,    56,    57,    58,    59,    60,   296,
     297,   298,   299,   300,   301,   212,   213,   214,   215,   216,
     217,     0,    61,    62,    25,   669,    63,    26,     0,   302,
       0,    27,    28,     0,    95,    96,    97,    98,    99,   100,
     101,   102,     0,   152,     0,   382,     0,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   296,
     297,   298,   299,   300,   301,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,   522,     0,     0,     0,    50,
      51,    52,    53,     0,     0,     0,    54,    55,    56,    57,
      58,    59,    60,    25,     0,     0,    26,     0,     0,     0,
      27,    28,     0,     0,     0,     0,    61,    62,     0,     0,
      63,     0,     0,     0,     0,     0,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,   296,   297,
     298,   299,   300,   301,     0,    41,    42,    43,    44,    45,
      46,    47,    48,    49,   524,     0,     0,     0,    50,    51,
      52,    53,     0,     0,     0,    54,    55,    56,    57,    58,
      59,    60,    25,   288,   289,   290,   291,   292,   293,    27,
      28,     0,     0,     0,     0,    61,    62,     0,     0,    63,
       0,     0,     0,     0,     0,    29,    30,    31,    32,    33,
      34,    35,   165,    37,    38,    39,    40,   296,   297,   298,
     299,   300,   301,     0,    41,    42,    43,    44,    45,    46,
      47,    48,    49,   582,     0,     0,     0,    50,    51,    52,
      53,     0,     0,     0,    54,    55,    56,    57,    58,    59,
      60,    25,     0,     0,    26,     0,     0,     0,    27,    28,
       0,     0,     0,     0,   166,   167,     0,     0,    63,     0,
       0,     0,     0,     0,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,   296,   297,   298,   299,
     300,   301,     0,   171,    42,    43,    44,    45,    46,    47,
      48,    49,   584,     0,     0,     0,    50,    51,    52,    53,
       0,     0,     0,     0,     0,    25,   296,   297,   298,   299,
     300,   301,    27,    28,   266,   268,   270,   272,   274,   276,
     279,   281,     0,    61,    62,     0,     0,    63,    29,    30,
      31,    32,    33,    34,    35,   165,    37,    38,    39,    40,
     344,   345,   346,   347,   348,   349,     0,   171,    42,    43,
      44,    45,    46,    47,    48,    49,     0,     0,     0,     0,
      50,    51,    52,    53,     0,     0,     0,     0,     0,    25,
       0,     0,     0,     0,     0,     0,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   166,   167,     0,
       0,    63,    29,    30,    31,    32,    33,    34,    35,   195,
      37,    38,    39,    40,     0,    25,     0,     0,     0,     0,
       0,   196,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    30,
      31,    32,    33,    34,    35,   165,    37,    38,    39,    40,
       0,     0,     0,     0,     0,     0,     0,   196,     0,     0,
     129,   166,   167,   130,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   262,     0,     0,   131,    34,    35,
      36,    37,    38,    39,    40,     0,     0,   166,   167,     0,
       0,    63,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   131,    34,    35,   165,    37,    38,    39,    40,   262,
       0,     0,     0,     0,     0,     0,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     0,     0,     0,     0,     0,
       0,     0,    61,   141,     0,     0,   131,    34,    35,   165,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
       0,   282,     0,     0,     0,     0,   166,   263,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,   263
};

static const yytype_int16 yycheck[] =
{
      13,    14,   367,    16,    17,     4,   199,    18,   254,   255,
     364,   179,   417,   375,     5,    35,    15,    35,    41,    18,
      19,    35,    43,    35,    46,    35,    25,    26,   382,    28,
      54,    55,    56,    57,    58,    59,    60,     1,    35,     3,
       4,    41,    63,   153,    37,    35,   546,    54,    37,    37,
      35,    96,    97,    17,    18,    38,    63,    58,    37,    43,
      40,     0,    47,    46,    28,    66,    37,   132,    21,   137,
      42,    43,    44,    45,    46,    47,   141,    46,    41,    63,
      36,    71,    71,    71,    48,    49,    41,    51,    52,    53,
      66,    71,    63,     1,   594,     3,     4,     5,    63,    62,
      66,   122,   123,   125,   126,   125,   126,   125,   126,    17,
      18,   125,   126,   125,   126,   125,   126,   118,   119,   229,
      28,    37,    40,   369,   370,   125,   126,    37,   125,   126,
      35,   485,   125,   126,   488,    21,    36,   128,    66,   152,
      48,    49,   118,    51,    52,    53,   125,   126,   171,   125,
     163,   164,   118,    71,    36,    71,   125,   126,    37,   125,
     159,    71,   161,   162,    50,    51,    52,    53,    88,   546,
     125,   126,    40,   550,   138,    95,   129,   130,    21,   132,
     133,   134,   135,   136,   137,   138,    36,   200,   141,    35,
     118,   119,    71,    35,   218,   219,   220,   221,   263,   198,
     562,    47,    42,    71,   167,    47,   178,   179,   171,   120,
     121,   183,   184,   185,   186,    63,   125,   282,    66,    39,
     128,   234,   235,   288,   289,   290,   291,   292,   293,     6,
     138,    37,   125,   196,    54,    55,    56,    57,    58,   202,
      66,   646,    63,   129,   130,    66,    66,   133,   134,   135,
     136,   137,   138,    35,   659,   254,   255,   251,    63,   253,
      36,    66,    39,   257,   124,    47,    72,    73,    74,    75,
      76,    77,   518,   519,    42,    88,   117,    54,    55,    56,
      57,    58,    95,   118,   119,    63,    63,   130,    66,    66,
     133,   134,   135,   136,   137,   138,   125,   126,   118,   119,
     112,   295,   113,   114,   472,    77,   474,   111,   307,   262,
     263,   310,    36,   266,    35,   268,    35,   270,    66,   272,
      35,   274,   687,   276,    35,   278,    35,   280,   125,   282,
     125,   284,   285,   286,    37,   288,   289,   290,   291,   292,
     293,   118,   119,   296,   297,   298,   299,   300,   301,    63,
      64,    65,    66,   366,   547,   368,   237,    87,    88,    89,
      90,   372,   111,   376,   377,   112,   379,    45,   367,    46,
     369,   370,   540,   372,   542,    66,   262,    74,    75,    76,
     266,    66,   268,    66,   270,    42,   272,    42,   274,    35,
     276,    36,   278,    36,   280,    74,    75,    76,   284,   285,
     286,   126,   595,    63,   118,   119,    72,    73,    35,    37,
     296,   297,   298,   299,   300,   301,   129,   130,   371,   125,
      47,   125,   303,   266,    66,   268,    37,   270,    37,   272,
      71,   274,    71,   276,    63,   278,    37,   280,   467,   468,
     469,    35,    77,   286,    39,    72,    73,    74,    75,    76,
      77,   464,   465,   296,   297,   298,   299,   300,   301,    54,
      55,    56,    57,    58,    63,   478,   125,   126,    63,    72,
      73,    66,   665,   223,   224,   225,   429,    36,    72,    73,
      74,    75,    76,    77,   437,   371,   439,    63,    14,   502,
      16,    17,    18,    19,   466,   467,   468,   469,   470,   471,
     472,   514,   474,   203,   204,    66,    32,    71,    36,   205,
     206,    39,    35,   208,   209,    71,   529,   615,   616,   518,
     519,    38,    38,   118,   119,    63,   126,    35,   371,    46,
     411,   412,    63,    37,    71,    63,    64,    65,    66,    67,
      68,    69,    70,   429,    38,    98,    99,   100,   101,   102,
      78,   437,    38,   439,    38,    72,    73,    74,    75,    76,
      77,    38,   575,    63,    71,    36,    36,    72,   540,   522,
     542,   524,    38,    38,   527,   588,    38,    38,    72,    73,
      74,    75,    76,    77,    38,   125,   429,   473,    36,   475,
     118,   119,    35,    38,   437,    35,   439,    36,   611,    37,
     125,   614,    33,    33,   617,   618,    35,    35,   489,   490,
     491,   492,   493,   494,   495,   496,    37,    36,    38,   500,
     501,    33,   503,    38,    41,   506,    33,    41,    38,   582,
     125,   584,   645,    38,    35,    35,   522,   159,   524,    38,
      58,   527,   207,   210,    63,    64,    65,    66,    67,    68,
      69,    70,   471,   666,   211,   470,    41,   227,   226,    78,
     546,   284,   222,   285,   550,   129,     8,    72,    73,    74,
      75,    76,    77,   132,     8,   688,   485,    38,   665,   522,
     104,   524,   229,    38,   527,   698,   482,    96,   687,   373,
     229,    -1,    -1,   574,   229,   229,   582,   229,   584,   118,
     119,    36,   229,    -1,    39,   586,    -1,    -1,    43,    44,
     596,    72,    73,    74,    75,    76,    77,    72,    73,    74,
      75,    76,    77,   609,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,   582,
      -1,   584,    -1,    78,    -1,    -1,    -1,    -1,    -1,   635,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      36,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,    -1,
      -1,   667,    -1,   118,   119,   671,    -1,   122,    -1,    -1,
      -1,    -1,   673,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    38,    -1,    -1,   689,    -1,
      -1,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    91,    92,    93,    94,    -1,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,    72,
      73,    74,    75,    76,    77,   105,   106,   107,   108,   109,
     110,    -1,   118,   119,    36,    37,   122,    39,    -1,   125,
      -1,    43,    44,    -1,   129,   130,   131,   132,   133,   134,
     135,   136,    -1,   137,    -1,   139,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    72,
      73,    74,    75,    76,    77,    -1,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    88,    -1,    -1,    -1,    91,
      92,    93,    94,    -1,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,    36,    -1,    -1,    39,    -1,    -1,    -1,
      43,    44,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,
     122,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    72,    73,
      74,    75,    76,    77,    -1,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    88,    -1,    -1,    -1,    91,    92,
      93,    94,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,    36,   105,   106,   107,   108,   109,   110,    43,
      44,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,   122,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    72,    73,    74,
      75,    76,    77,    -1,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    88,    -1,    -1,    -1,    91,    92,    93,
      94,    -1,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,    36,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,
      -1,    -1,    -1,    -1,   118,   119,    -1,    -1,   122,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    72,    73,    74,    75,
      76,    77,    -1,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    88,    -1,    -1,    -1,    91,    92,    93,    94,
      -1,    -1,    -1,    -1,    -1,    36,    72,    73,    74,    75,
      76,    77,    43,    44,   133,   134,   135,   136,   137,   138,
     139,   140,    -1,   118,   119,    -1,    -1,   122,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
     212,   213,   214,   215,   216,   217,    -1,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,
      -1,   122,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    78,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      36,   118,   119,    39,    -1,   122,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,   118,   119,    -1,
      -1,   122,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    63,    64,    65,    66,    67,    68,    69,    70,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,   119,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   141,   142,   143,   144,     0,     5,   128,   201,   202,
     207,     1,     3,     4,    17,    18,    28,    48,    49,    51,
      52,    53,   138,   252,   253,    36,    39,    43,    44,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      91,    92,    93,    94,    98,    99,   100,   101,   102,   103,
     104,   118,   119,   122,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   156,   157,   158,   159,   160,   161,   163,
     164,   165,   166,   167,   173,   174,   175,   176,   177,   178,
     179,   180,   193,    63,   203,   129,   130,   131,   132,   133,
     134,   135,   136,   208,   209,   240,   241,   242,   243,   244,
     245,   202,   207,    35,   256,   257,   180,   190,   190,   180,
     191,   190,   190,   193,   180,   192,    96,    97,   247,    36,
      39,    63,    78,    79,    80,    81,    82,    83,    84,    85,
      86,   119,   151,   152,   181,   183,   184,   185,   186,   187,
     188,   189,   137,   236,   237,   180,   162,   180,   154,   155,
     180,    36,    36,    36,    36,    66,   118,   119,   153,   167,
     174,    78,   166,   166,   166,   166,   166,   166,   125,   125,
      66,   118,   119,   151,   151,   151,   151,   173,   173,   173,
     173,   173,   173,   173,    66,    66,    78,   153,    36,    42,
     125,   126,   124,   120,   121,   118,   119,   117,   113,   114,
     111,   112,   105,   106,   107,   108,   109,   110,    87,    88,
      89,    90,    77,    74,    75,    76,    72,    73,    36,   205,
     210,   210,   129,   130,   239,   239,   239,   239,   239,   239,
     208,    35,    66,   255,    35,    35,    35,    35,    35,    47,
      35,    47,    35,    47,   125,   125,    35,    47,   187,   189,
     182,   189,    36,   119,   185,   188,   145,   189,   145,   189,
     145,   189,   145,   189,   145,   189,   145,   189,   125,   145,
     125,   145,    78,   185,   111,   112,   125,   126,   105,   106,
     107,   108,   109,   110,    35,    47,    72,    73,    74,    75,
      76,    77,   125,   190,   237,    37,    40,    71,    45,   154,
      46,   180,   180,   190,   190,    66,   166,   168,   169,   170,
     171,   172,   172,    66,    66,   166,   166,   166,   166,   180,
     146,   190,    63,    66,   153,   156,   156,   157,   157,   158,
     159,   159,   161,   163,   164,   164,   164,   164,   164,   164,
     173,   173,   173,   173,   175,   176,   176,   176,   179,   177,
      37,    63,   204,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,   139,   206,   212,   215,   218,   220,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     237,   238,   246,   248,   211,   212,   218,   220,   223,   224,
     225,   190,   190,    35,   249,   249,    36,    36,   126,    63,
     254,   254,   254,   192,   192,   254,    37,    37,    40,    71,
     189,   189,   189,   189,   189,   189,   189,   125,   189,   125,
     181,   183,   189,    63,    66,   185,   185,   185,   185,   185,
     185,   254,   189,   189,   189,   189,   189,   189,    66,   249,
     180,   180,    37,    37,    71,    71,    77,    74,    75,    76,
      72,    73,    88,    95,    88,    95,    37,    38,    46,    37,
      71,    63,   213,   214,   250,   216,   217,   250,   219,   190,
     191,   190,   192,   192,   189,   193,   247,    63,   198,   235,
     190,   190,    36,   190,    63,   221,   250,   249,   249,   190,
     200,   200,    66,    35,   125,   126,    35,    35,    71,    71,
      35,   189,    88,   189,    88,   189,    38,    46,    35,    38,
      35,   190,   190,   166,   168,   168,   168,   171,   169,   172,
     151,   172,   151,   190,    63,   214,    46,   125,   126,   217,
      46,   250,   249,   249,   249,   249,   249,   249,   249,   249,
     126,    35,    71,   249,   249,   190,   249,    43,    63,   122,
     123,   222,   251,   249,    37,    71,    37,   190,    63,   192,
     192,   189,    88,   189,    88,   189,   190,    37,    71,    38,
     172,    38,   172,    38,     6,    39,    54,    55,    56,    57,
      58,    63,   151,   194,   195,   199,   146,    63,    66,    54,
     194,    41,    63,   198,    71,    36,    36,    41,   125,   126,
     249,   190,    72,    38,    38,    38,    38,   189,    38,   189,
      38,   249,   190,    38,    38,    54,   199,    64,    65,   146,
     196,   197,   198,    58,   151,   125,    36,    35,    38,   151,
      35,   190,   190,   251,   251,   190,   190,    63,    66,    36,
      38,    38,    37,   151,    40,    71,   125,    33,   190,    37,
     200,    33,    35,    37,    37,    37,    35,    38,   200,    33,
     197,   190,   194,   199,    38,    37,   249,    41,    41,    37,
      38,   191,   190,   249,    33,    35,    35,    58,   125,   190,
      38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   140,   142,   141,   143,   141,   144,   141,   145,   145,
     146,   146,   146,   147,   148,   149,   150,   151,   152,   152,
     152,   152,   152,   152,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   154,   154,   155,   156,   156,   157,   157,   157,   158,
     158,   158,   159,   159,   160,   160,   160,   161,   161,   161,
     162,   162,   163,   163,   164,   164,   165,   165,   165,   165,
     165,   165,   165,   166,   166,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   169,   169,   169,   169,   170,   170,   171,   171,
     172,   173,   173,   174,   174,   174,   174,   174,   174,   174,
     174,   175,   175,   175,   175,   175,   176,   176,   177,   177,
     177,   177,   178,   178,   179,   179,   180,   181,   181,   181,
     182,   182,   183,   183,   184,   184,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   186,   186,   186,   186,   186,
     186,   186,   187,   187,   187,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   189,   189,   189,   189,   189,   189,   189,   190,
     191,   192,   193,   194,   194,   194,   194,   194,   194,   194,
     194,   195,   195,   195,   196,   196,   197,   197,   197,   197,
     198,   198,   199,   199,   199,   199,   200,   200,   201,   201,
     201,   201,   202,   203,   203,   203,   204,   204,   205,   205,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     207,   208,   208,   209,   209,   209,   209,   209,   209,   209,
     209,   210,   210,   211,   211,   211,   211,   211,   211,   212,
     212,   213,   213,   214,   215,   215,   216,   216,   217,   218,
     219,   219,   220,   221,   221,   222,   222,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   230,   231,   232,   233,
     234,   235,   235,   235,   236,   236,   237,   237,   238,   239,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   247,
     248,   249,   249,   250,   250,   250,   250,   251,   251,   251,
     251,   251,   252,   252,   252,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   254,   254,   254,   255,   255,   257,   256
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     0,     2,     1,     2,
       1,     2,     2,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       3,     4,     6,     3,     2,     4,     4,     4,     3,     6,
       8,     1,     2,     4,     1,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     3,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     1,     2,     2,     2,     2,     2,
       2,     6,     6,     7,     7,     3,     3,     3,     3,     2,
       1,     3,     1,     3,     3,     3,     1,     3,     1,     3,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     3,     3,     3,     3,     1,     3,     1,     3,
       3,     3,     1,     3,     1,     3,     1,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     2,     1,     3,
       2,     3,     3,     4,     6,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     1,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     3,     6,     7,     2,     3,     6,
       7,     2,     1,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,    10,
       4,     1,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     3,     4,     4,     1,     3,     1,     1,
       2,     2,     3,     1,     3,     4,     1,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     4,     1,     2,     1,     2,     4,     2,
       0,     5,     2,     0,     2,     4,     7,     7,     3,     3,
       3,     3,     3,     7,     3,     3,     3,     3,     1,     3,
       3,     0,     1,     3,     1,     2,     3,     6,     3,     1,
       1,     4,     4,     3,     3,     6,    10,     3,     6,     6,
       2,     0,     1,     1,     3,     3,     4,     1,     1,     3,
       3,     4,     1,     2,     1,     3,     3,     3,     3,     3,
       3,     5,     3,     5,     3,     5,     3,     5,     3,     5,
       2,     1,     3,     4,     1,     3,     0,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 217 "grammar.y" /* yacc.c:1646  */
    { 
  if (PARSE_MODULES != parse_mode_flag) {
    yyerror("unexpected MODULE definition encountered during parsing");
    YYABORT;
  }
#if HAVE_MBP
  /* By default unset the flag that this is a game declaration */
  unset_mbp_game(options);
#endif
}
#line 2287 "grammar.c" /* yacc.c:1646  */
    break;

  case 3:
#line 228 "grammar.y" /* yacc.c:1646  */
    {
                  if (!opt_mbp_game(options)) {/*this is a usual SMV file*/
                    parsed_tree = (yyvsp[0].node);
                  }
                  else {
                    /* this is a game (realizability problem) .
                       Return a Game with spec list on the left and a
                       module list on the right. This module list
                       contains two special modules (with names
                       PLAYER_1 and PLAYER_2) created from player
                       declarations.
                    */
                    parsed_tree = new_node(GAME,
                                           mbp_parser_spec_list,
                                           cons(mbp_parser_player_1,
                                                cons(mbp_parser_player_2, 
                                                     (yyvsp[0].node))));
                  }
                }
#line 2311 "grammar.c" /* yacc.c:1646  */
    break;

  case 4:
#line 247 "grammar.y" /* yacc.c:1646  */
    {
                  if (PARSE_COMMAND != parse_mode_flag) {
		    yyerror("unexpected command encountered during parsing");
		    YYABORT;
		  }
                }
#line 2322 "grammar.c" /* yacc.c:1646  */
    break;

  case 5:
#line 253 "grammar.y" /* yacc.c:1646  */
    {parsed_tree = (yyvsp[0].node);}
#line 2328 "grammar.c" /* yacc.c:1646  */
    break;

  case 6:
#line 254 "grammar.y" /* yacc.c:1646  */
    {
		  if (PARSE_LTL_EXPR != parse_mode_flag){
		    yyerror("unexpected expression encountered during parsing");
		    YYABORT;
		  }
                }
#line 2339 "grammar.c" /* yacc.c:1646  */
    break;

  case 7:
#line 260 "grammar.y" /* yacc.c:1646  */
    {parsed_tree = (yyvsp[0].node);}
#line 2345 "grammar.c" /* yacc.c:1646  */
    break;

  case 9:
#line 270 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2351 "grammar.c" /* yacc.c:1646  */
    break;

  case 11:
#line 274 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2357 "grammar.c" /* yacc.c:1646  */
    break;

  case 12:
#line 276 "grammar.y" /* yacc.c:1646  */
    {node_int_setcar((yyvsp[0].node), -(node_get_int((yyvsp[0].node)))); (yyval.node) = (yyvsp[0].node);}
#line 2363 "grammar.c" /* yacc.c:1646  */
    break;

  case 17:
#line 290 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(TWODOTS, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno));}
#line 2369 "grammar.c" /* yacc.c:1646  */
    break;

  case 22:
#line 298 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                 (yyval.node) = (yyvsp[0].node);
#else
                 yyerror("fractional constants are not supported.");
                 YYABORT;
#endif
               }
#line 2382 "grammar.c" /* yacc.c:1646  */
    break;

  case 23:
#line 307 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                 (yyval.node) = (yyvsp[0].node);
#else
                 yyerror("exponential constants are not supported.");
                 YYABORT;
#endif
               }
#line 2395 "grammar.c" /* yacc.c:1646  */
    break;

  case 24:
#line 316 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                 (yyval.node) = (yyvsp[0].node);
#else
                 yyerror("real constants are not supported.");
                 YYABORT;
#endif
               }
#line 2408 "grammar.c" /* yacc.c:1646  */
    break;

  case 26:
#line 334 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(UMINUS, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2414 "grammar.c" /* yacc.c:1646  */
    break;

  case 28:
#line 336 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(SELF,Nil,Nil);}
#line 2420 "grammar.c" /* yacc.c:1646  */
    break;

  case 29:
#line 338 "grammar.y" /* yacc.c:1646  */
    {
		      if (ATOM != node_get_type((yyvsp[-2].node)) && DOT != node_get_type((yyvsp[-2].node)) && ARRAY != node_get_type((yyvsp[-2].node)) && SELF != node_get_type((yyvsp[-2].node))) {
			yyerror_lined("incorrect DOT expression", (yyvsp[-1].lineno));
		        YYABORT;
		      }
		      (yyval.node) = new_lined_node(DOT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)) ;
		    }
#line 2432 "grammar.c" /* yacc.c:1646  */
    break;

  case 30:
#line 346 "grammar.y" /* yacc.c:1646  */
    { 
		      if (ATOM != node_get_type((yyvsp[-2].node)) && DOT != node_get_type((yyvsp[-2].node)) && ARRAY != node_get_type((yyvsp[-2].node)) && SELF != node_get_type((yyvsp[-2].node))) {
			yyerror_lined("incorrect DOT expression", (yyvsp[-1].lineno));
			YYABORT;
		      }
		      (yyval.node) = new_lined_node(DOT, (yyvsp[-2].node), (yyvsp[0].node), 2) ;
		    }
#line 2444 "grammar.c" /* yacc.c:1646  */
    break;

  case 31:
#line 354 "grammar.y" /* yacc.c:1646  */
    { 
		       if (ATOM != node_get_type((yyvsp[-3].node)) && DOT != node_get_type((yyvsp[-3].node)) && ARRAY != node_get_type((yyvsp[-3].node)) && SELF != node_get_type((yyvsp[-3].node))) {
			yyerror_lined("incorrect ARRAY expression", (yyvsp[-2].lineno));
			YYABORT;
		       }
		       (yyval.node) = new_lined_node(ARRAY, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno));
		     }
#line 2456 "grammar.c" /* yacc.c:1646  */
    break;

  case 32:
#line 362 "grammar.y" /* yacc.c:1646  */
    { 
			(yyval.node) = new_lined_node(BIT_SELECTION, (yyvsp[-5].node), 
			               new_lined_node(COLON, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno)), (yyvsp[-4].lineno));
		       }
#line 2465 "grammar.c" /* yacc.c:1646  */
    break;

  case 33:
#line 366 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2471 "grammar.c" /* yacc.c:1646  */
    break;

  case 34:
#line 367 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NOT, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2477 "grammar.c" /* yacc.c:1646  */
    break;

  case 35:
#line 368 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(CAST_BOOL, (yyvsp[-1].node), Nil, (yyvsp[-3].lineno)); }
#line 2483 "grammar.c" /* yacc.c:1646  */
    break;

  case 36:
#line 369 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(CAST_WORD1, (yyvsp[-1].node), Nil, (yyvsp[-3].lineno)); }
#line 2489 "grammar.c" /* yacc.c:1646  */
    break;

  case 37:
#line 370 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NEXT, (yyvsp[-1].node), Nil, (yyvsp[-3].lineno)); }
#line 2495 "grammar.c" /* yacc.c:1646  */
    break;

  case 38:
#line 371 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2501 "grammar.c" /* yacc.c:1646  */
    break;

  case 39:
#line 375 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(WAREAD, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-5].lineno)); }
#line 2507 "grammar.c" /* yacc.c:1646  */
    break;

  case 40:
#line 378 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(WAWRITE, (yyvsp[-5].node), new_node(WAWRITE, (yyvsp[-3].node), (yyvsp[-1].node)), (yyvsp[-6].lineno)); }
#line 2513 "grammar.c" /* yacc.c:1646  */
    break;

  case 41:
#line 384 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(CASE, (yyvsp[0].node), failure_make("case conditions are not exhaustive", FAILURE_CASE_NOT_EXHAUSTIVE, yylineno));}
#line 2519 "grammar.c" /* yacc.c:1646  */
    break;

  case 42:
#line 385 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(CASE, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2525 "grammar.c" /* yacc.c:1646  */
    break;

  case 43:
#line 390 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(COLON, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 2531 "grammar.c" /* yacc.c:1646  */
    break;

  case 45:
#line 395 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(CONCATENATION, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2537 "grammar.c" /* yacc.c:1646  */
    break;

  case 47:
#line 400 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(TIMES, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2543 "grammar.c" /* yacc.c:1646  */
    break;

  case 48:
#line 401 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(DIVIDE, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2549 "grammar.c" /* yacc.c:1646  */
    break;

  case 50:
#line 406 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(PLUS, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2555 "grammar.c" /* yacc.c:1646  */
    break;

  case 51:
#line 407 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(MINUS, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2561 "grammar.c" /* yacc.c:1646  */
    break;

  case 53:
#line 412 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(MOD, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2567 "grammar.c" /* yacc.c:1646  */
    break;

  case 55:
#line 416 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(LSHIFT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2573 "grammar.c" /* yacc.c:1646  */
    break;

  case 56:
#line 417 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(RSHIFT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2579 "grammar.c" /* yacc.c:1646  */
    break;

  case 59:
#line 425 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2585 "grammar.c" /* yacc.c:1646  */
    break;

  case 61:
#line 429 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(UNION, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno));}
#line 2591 "grammar.c" /* yacc.c:1646  */
    break;

  case 63:
#line 434 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(UNION, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2597 "grammar.c" /* yacc.c:1646  */
    break;

  case 65:
#line 438 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(SETIN, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2603 "grammar.c" /* yacc.c:1646  */
    break;

  case 67:
#line 443 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EQUAL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2609 "grammar.c" /* yacc.c:1646  */
    break;

  case 68:
#line 444 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NOTEQUAL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2615 "grammar.c" /* yacc.c:1646  */
    break;

  case 69:
#line 445 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(LT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2621 "grammar.c" /* yacc.c:1646  */
    break;

  case 70:
#line 446 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(GT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2627 "grammar.c" /* yacc.c:1646  */
    break;

  case 71:
#line 447 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(LE, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2633 "grammar.c" /* yacc.c:1646  */
    break;

  case 72:
#line 448 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(GE, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2639 "grammar.c" /* yacc.c:1646  */
    break;

  case 75:
#line 457 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EX, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2645 "grammar.c" /* yacc.c:1646  */
    break;

  case 76:
#line 458 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AX, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2651 "grammar.c" /* yacc.c:1646  */
    break;

  case 77:
#line 459 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EF, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2657 "grammar.c" /* yacc.c:1646  */
    break;

  case 78:
#line 460 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AF, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2663 "grammar.c" /* yacc.c:1646  */
    break;

  case 79:
#line 461 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EG, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2669 "grammar.c" /* yacc.c:1646  */
    break;

  case 80:
#line 462 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AG, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2675 "grammar.c" /* yacc.c:1646  */
    break;

  case 81:
#line 464 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-5].lineno)); }
#line 2681 "grammar.c" /* yacc.c:1646  */
    break;

  case 82:
#line 466 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-5].lineno)); }
#line 2687 "grammar.c" /* yacc.c:1646  */
    break;

  case 83:
#line 468 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(ABU, new_lined_node(AU, (yyvsp[-4].node), (yyvsp[-1].node), (yyvsp[-6].lineno)), (yyvsp[-2].node), (yyvsp[-6].lineno)); }
#line 2693 "grammar.c" /* yacc.c:1646  */
    break;

  case 84:
#line 470 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EBU, new_lined_node(EU, (yyvsp[-4].node), (yyvsp[-1].node), (yyvsp[-6].lineno)), (yyvsp[-2].node), (yyvsp[-6].lineno)); }
#line 2699 "grammar.c" /* yacc.c:1646  */
    break;

  case 85:
#line 471 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EBF, (yyvsp[0].node), (yyvsp[-1].node), (yyvsp[-2].lineno)); }
#line 2705 "grammar.c" /* yacc.c:1646  */
    break;

  case 86:
#line 472 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(ABF, (yyvsp[0].node), (yyvsp[-1].node), (yyvsp[-2].lineno)); }
#line 2711 "grammar.c" /* yacc.c:1646  */
    break;

  case 87:
#line 473 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EBG, (yyvsp[0].node), (yyvsp[-1].node), (yyvsp[-2].lineno)); }
#line 2717 "grammar.c" /* yacc.c:1646  */
    break;

  case 88:
#line 474 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(ABG, (yyvsp[0].node), (yyvsp[-1].node), (yyvsp[-2].lineno)); }
#line 2723 "grammar.c" /* yacc.c:1646  */
    break;

  case 89:
#line 477 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NOT, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2729 "grammar.c" /* yacc.c:1646  */
    break;

  case 91:
#line 484 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AND, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2735 "grammar.c" /* yacc.c:1646  */
    break;

  case 93:
#line 488 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(OR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2741 "grammar.c" /* yacc.c:1646  */
    break;

  case 94:
#line 489 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(XOR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2747 "grammar.c" /* yacc.c:1646  */
    break;

  case 95:
#line 490 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(XNOR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2753 "grammar.c" /* yacc.c:1646  */
    break;

  case 97:
#line 494 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(IFF, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2759 "grammar.c" /* yacc.c:1646  */
    break;

  case 99:
#line 499 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(IMPLIES, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2765 "grammar.c" /* yacc.c:1646  */
    break;

  case 103:
#line 512 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(OP_NEXT, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 2771 "grammar.c" /* yacc.c:1646  */
    break;

  case 104:
#line 513 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(OP_PREC, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 2777 "grammar.c" /* yacc.c:1646  */
    break;

  case 105:
#line 514 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(OP_NOTPRECNOT, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 2783 "grammar.c" /* yacc.c:1646  */
    break;

  case 106:
#line 515 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(OP_GLOBAL, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 2789 "grammar.c" /* yacc.c:1646  */
    break;

  case 107:
#line 516 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(OP_HISTORICAL, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 2795 "grammar.c" /* yacc.c:1646  */
    break;

  case 108:
#line 517 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(OP_FUTURE, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 2801 "grammar.c" /* yacc.c:1646  */
    break;

  case 109:
#line 518 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(OP_ONCE, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 2807 "grammar.c" /* yacc.c:1646  */
    break;

  case 110:
#line 520 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NOT, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2813 "grammar.c" /* yacc.c:1646  */
    break;

  case 112:
#line 527 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(UNTIL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno));}
#line 2819 "grammar.c" /* yacc.c:1646  */
    break;

  case 113:
#line 529 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(SINCE, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno));}
#line 2825 "grammar.c" /* yacc.c:1646  */
    break;

  case 114:
#line 531 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(NOT, 
                           new_lined_node(UNTIL,
			     new_lined_node(NOT, (yyvsp[-2].node), Nil, node_get_lineno((yyvsp[-2].node))), 
			     new_lined_node(NOT, (yyvsp[0].node), Nil, node_get_lineno((yyvsp[0].node))),
			     (yyvsp[-1].lineno)), Nil, (yyvsp[-1].lineno));
		  }
#line 2836 "grammar.c" /* yacc.c:1646  */
    break;

  case 115:
#line 538 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(NOT,
			  new_lined_node(SINCE,
			      new_lined_node(NOT, (yyvsp[-2].node), Nil, node_get_lineno((yyvsp[-2].node))),
			      new_lined_node(NOT, (yyvsp[0].node), Nil, node_get_lineno((yyvsp[0].node))),
			      (yyvsp[-1].lineno)), Nil, (yyvsp[-1].lineno));
		  }
#line 2847 "grammar.c" /* yacc.c:1646  */
    break;

  case 117:
#line 548 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AND, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2853 "grammar.c" /* yacc.c:1646  */
    break;

  case 119:
#line 553 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(OR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2859 "grammar.c" /* yacc.c:1646  */
    break;

  case 120:
#line 554 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(XOR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2865 "grammar.c" /* yacc.c:1646  */
    break;

  case 121:
#line 555 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(XNOR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2871 "grammar.c" /* yacc.c:1646  */
    break;

  case 123:
#line 560 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(IFF, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2877 "grammar.c" /* yacc.c:1646  */
    break;

  case 125:
#line 565 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(IMPLIES, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2883 "grammar.c" /* yacc.c:1646  */
    break;

  case 129:
#line 573 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2889 "grammar.c" /* yacc.c:1646  */
    break;

  case 131:
#line 577 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(UNION, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno));}
#line 2895 "grammar.c" /* yacc.c:1646  */
    break;

  case 133:
#line 582 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(UNION, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2901 "grammar.c" /* yacc.c:1646  */
    break;

  case 135:
#line 586 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(SETIN, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2907 "grammar.c" /* yacc.c:1646  */
    break;

  case 137:
#line 591 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(UMINUS, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2913 "grammar.c" /* yacc.c:1646  */
    break;

  case 139:
#line 593 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2919 "grammar.c" /* yacc.c:1646  */
    break;

  case 140:
#line 594 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NOT, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 2925 "grammar.c" /* yacc.c:1646  */
    break;

  case 141:
#line 596 "grammar.y" /* yacc.c:1646  */
    {
		      if (ATOM != node_get_type((yyvsp[-2].node)) && DOT != node_get_type((yyvsp[-2].node)) && ARRAY != node_get_type((yyvsp[-2].node)) && SELF != node_get_type((yyvsp[-2].node))) {
			yyerror_lined("incorrect DOT expression", (yyvsp[-1].lineno));
		        YYABORT;
		      }
		      (yyval.node) = new_lined_node(DOT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)) ;
		    }
#line 2937 "grammar.c" /* yacc.c:1646  */
    break;

  case 142:
#line 604 "grammar.y" /* yacc.c:1646  */
    {
			    if (ATOM != node_get_type((yyvsp[-2].node)) && DOT != node_get_type((yyvsp[-2].node)) && ARRAY != node_get_type((yyvsp[-2].node)) && SELF != node_get_type((yyvsp[-2].node))) {
			    yyerror_lined("incorrect DOT expression", (yyvsp[-1].lineno));
		    YYABORT;
		      }
		      (yyval.node) = new_lined_node(DOT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)) ;
		    }
#line 2949 "grammar.c" /* yacc.c:1646  */
    break;

  case 143:
#line 612 "grammar.y" /* yacc.c:1646  */
    { 
		       if (ATOM != node_get_type((yyvsp[-3].node)) && DOT != node_get_type((yyvsp[-3].node)) && ARRAY != node_get_type((yyvsp[-3].node)) && SELF != node_get_type((yyvsp[-3].node))) {
			yyerror_lined("incorrect ARRAY expression", (yyvsp[-2].lineno));
			YYABORT;
		       }
		       (yyval.node) = new_lined_node(ARRAY, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno));
		     }
#line 2961 "grammar.c" /* yacc.c:1646  */
    break;

  case 144:
#line 620 "grammar.y" /* yacc.c:1646  */
    { 
			(yyval.node) = new_lined_node(BIT_SELECTION, (yyvsp[-5].node), 
			               new_lined_node(COLON, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno)), (yyvsp[-4].lineno));
		       }
#line 2970 "grammar.c" /* yacc.c:1646  */
    break;

  case 146:
#line 630 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EQUAL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2976 "grammar.c" /* yacc.c:1646  */
    break;

  case 147:
#line 631 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NOTEQUAL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2982 "grammar.c" /* yacc.c:1646  */
    break;

  case 148:
#line 632 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(LT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2988 "grammar.c" /* yacc.c:1646  */
    break;

  case 149:
#line 633 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(GT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 2994 "grammar.c" /* yacc.c:1646  */
    break;

  case 150:
#line 634 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(LE, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3000 "grammar.c" /* yacc.c:1646  */
    break;

  case 151:
#line 635 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(GE, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3006 "grammar.c" /* yacc.c:1646  */
    break;

  case 153:
#line 639 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3012 "grammar.c" /* yacc.c:1646  */
    break;

  case 155:
#line 644 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGX, new_lined_node(EX, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)), 
							    new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-1].lineno));}
#line 3019 "grammar.c" /* yacc.c:1646  */
    break;

  case 156:
#line 646 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGX, new_lined_node(EX, (yyvsp[0].node), Nil, (yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3025 "grammar.c" /* yacc.c:1646  */
    break;

  case 157:
#line 647 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGX, new_lined_node(AX, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)), 
							    new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-1].lineno));}
#line 3032 "grammar.c" /* yacc.c:1646  */
    break;

  case 158:
#line 649 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGX, new_lined_node(AX, (yyvsp[0].node), Nil, (yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3038 "grammar.c" /* yacc.c:1646  */
    break;

  case 159:
#line 650 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGG, new_lined_node(AG, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)), 
							    new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-1].lineno));}
#line 3045 "grammar.c" /* yacc.c:1646  */
    break;

  case 160:
#line 652 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGG, new_lined_node(AG, (yyvsp[0].node), Nil, (yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3051 "grammar.c" /* yacc.c:1646  */
    break;

  case 161:
#line 653 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGF, new_lined_node(EF, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)), 
							    new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-1].lineno));}
#line 3058 "grammar.c" /* yacc.c:1646  */
    break;

  case 162:
#line 655 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGF, new_lined_node(EF, (yyvsp[0].node), Nil, (yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3064 "grammar.c" /* yacc.c:1646  */
    break;

  case 163:
#line 656 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGF, new_lined_node(AF, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)), 
							    new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-1].lineno));}
#line 3071 "grammar.c" /* yacc.c:1646  */
    break;

  case 164:
#line 658 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGF, new_lined_node(AF, (yyvsp[0].node), Nil, (yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3077 "grammar.c" /* yacc.c:1646  */
    break;

  case 165:
#line 661 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGU, new_lined_node(AU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-5].lineno)), 
							   new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-5].lineno));}
#line 3084 "grammar.c" /* yacc.c:1646  */
    break;

  case 166:
#line 664 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AGU, new_lined_node(AU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-6].lineno)), (yyvsp[-5].node), (yyvsp[-6].lineno));}
#line 3090 "grammar.c" /* yacc.c:1646  */
    break;

  case 167:
#line 665 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGG, new_lined_node(EG, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)), 
							    new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-1].lineno));}
#line 3097 "grammar.c" /* yacc.c:1646  */
    break;

  case 168:
#line 667 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGG, new_lined_node(EG, (yyvsp[0].node), Nil, (yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3103 "grammar.c" /* yacc.c:1646  */
    break;

  case 169:
#line 669 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGU, new_lined_node(EU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-5].lineno)), 
							   new_node(NUMBER, NODE_FROM_INT(0), Nil), (yyvsp[-5].lineno));}
#line 3110 "grammar.c" /* yacc.c:1646  */
    break;

  case 170:
#line 672 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EGU, new_lined_node(EU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-6].lineno)), (yyvsp[-5].node), (yyvsp[-6].lineno));}
#line 3116 "grammar.c" /* yacc.c:1646  */
    break;

  case 171:
#line 675 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(NOT, (yyvsp[0].node), Nil, (yyvsp[-1].lineno)); }
#line 3122 "grammar.c" /* yacc.c:1646  */
    break;

  case 173:
#line 679 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(IMPLIES, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3128 "grammar.c" /* yacc.c:1646  */
    break;

  case 174:
#line 680 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(IFF, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3134 "grammar.c" /* yacc.c:1646  */
    break;

  case 175:
#line 681 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(OR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3140 "grammar.c" /* yacc.c:1646  */
    break;

  case 176:
#line 682 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(XOR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3146 "grammar.c" /* yacc.c:1646  */
    break;

  case 177:
#line 683 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(XNOR,(yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3152 "grammar.c" /* yacc.c:1646  */
    break;

  case 178:
#line 684 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(AND, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno)); }
#line 3158 "grammar.c" /* yacc.c:1646  */
    break;

  case 179:
#line 694 "grammar.y" /* yacc.c:1646  */
    {if (!isCorrectExp((yyval.node), EXP_SIMPLE)) YYABORT;}
#line 3164 "grammar.c" /* yacc.c:1646  */
    break;

  case 180:
#line 697 "grammar.y" /* yacc.c:1646  */
    {if (!isCorrectExp((yyval.node), EXP_NEXT)) YYABORT;}
#line 3170 "grammar.c" /* yacc.c:1646  */
    break;

  case 181:
#line 700 "grammar.y" /* yacc.c:1646  */
    {if (!isCorrectExp((yyval.node), EXP_CTL)) YYABORT;}
#line 3176 "grammar.c" /* yacc.c:1646  */
    break;

  case 182:
#line 703 "grammar.y" /* yacc.c:1646  */
    {if (!isCorrectExp((yyval.node), EXP_LTL)) YYABORT;}
#line 3182 "grammar.c" /* yacc.c:1646  */
    break;

  case 183:
#line 710 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(BOOLEAN, Nil, Nil);}
#line 3188 "grammar.c" /* yacc.c:1646  */
    break;

  case 184:
#line 711 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                (yyval.node) = new_node(INTEGER, Nil, Nil);
#else
                yyerror("given token is not supported.");
                YYABORT;
#endif
              }
#line 3201 "grammar.c" /* yacc.c:1646  */
    break;

  case 185:
#line 719 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                (yyval.node) = new_node(REAL, Nil, Nil);
#else
                yyerror("given token is not supported.");
                YYABORT;
#endif 
}
#line 3214 "grammar.c" /* yacc.c:1646  */
    break;

  case 186:
#line 728 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(WORD, (yyvsp[-1].node), Nil, (yyvsp[-3].lineno));}
#line 3220 "grammar.c" /* yacc.c:1646  */
    break;

  case 188:
#line 731 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(SCALAR, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3226 "grammar.c" /* yacc.c:1646  */
    break;

  case 189:
#line 733 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(WORDARRAY, (yyvsp[-6].node), (yyvsp[-1].node), (yyvsp[-9].lineno));}
#line 3232 "grammar.c" /* yacc.c:1646  */
    break;

  case 190:
#line 735 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(ARRAY, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-3].lineno));}
#line 3238 "grammar.c" /* yacc.c:1646  */
    break;

  case 193:
#line 742 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(PROCESS, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 3244 "grammar.c" /* yacc.c:1646  */
    break;

  case 194:
#line 745 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons(find_atom((yyvsp[0].node)), Nil);}
#line 3250 "grammar.c" /* yacc.c:1646  */
    break;

  case 195:
#line 746 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons(find_atom((yyvsp[0].node)), (yyvsp[-2].node));}
#line 3256 "grammar.c" /* yacc.c:1646  */
    break;

  case 201:
#line 756 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(DOT, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].lineno));}
#line 3262 "grammar.c" /* yacc.c:1646  */
    break;

  case 202:
#line 759 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(MODTYPE, (yyvsp[0].node), Nil);}
#line 3268 "grammar.c" /* yacc.c:1646  */
    break;

  case 203:
#line 760 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(MODTYPE, (yyvsp[-2].node), Nil);}
#line 3274 "grammar.c" /* yacc.c:1646  */
    break;

  case 204:
#line 762 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(MODTYPE, (yyvsp[-3].node), (yyvsp[-1].node), node_get_lineno((yyvsp[-3].node)));}
#line 3280 "grammar.c" /* yacc.c:1646  */
    break;

  case 205:
#line 764 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(ARRAY, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-3].lineno));}
#line 3286 "grammar.c" /* yacc.c:1646  */
    break;

  case 206:
#line 768 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node),Nil);}
#line 3292 "grammar.c" /* yacc.c:1646  */
    break;

  case 207:
#line 769 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), (yyvsp[-2].node));}
#line 3298 "grammar.c" /* yacc.c:1646  */
    break;

  case 208:
#line 784 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), Nil);}
#line 3304 "grammar.c" /* yacc.c:1646  */
    break;

  case 209:
#line 785 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = Nil;}
#line 3310 "grammar.c" /* yacc.c:1646  */
    break;

  case 210:
#line 786 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), (yyvsp[-1].node));}
#line 3316 "grammar.c" /* yacc.c:1646  */
    break;

  case 211:
#line 787 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 3322 "grammar.c" /* yacc.c:1646  */
    break;

  case 212:
#line 791 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(MODULE, (yyvsp[-1].node), (yyvsp[0].node), (yyvsp[-2].lineno));}
#line 3328 "grammar.c" /* yacc.c:1646  */
    break;

  case 213:
#line 793 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(MODTYPE, (yyvsp[0].node), Nil);}
#line 3334 "grammar.c" /* yacc.c:1646  */
    break;

  case 214:
#line 794 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(MODTYPE, (yyvsp[-2].node), Nil);}
#line 3340 "grammar.c" /* yacc.c:1646  */
    break;

  case 215:
#line 796 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(MODTYPE, (yyvsp[-3].node), (yyvsp[-1].node));}
#line 3346 "grammar.c" /* yacc.c:1646  */
    break;

  case 216:
#line 798 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons(find_atom((yyvsp[0].node)), Nil);}
#line 3352 "grammar.c" /* yacc.c:1646  */
    break;

  case 217:
#line 799 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons(find_atom((yyvsp[0].node)), (yyvsp[-2].node));}
#line 3358 "grammar.c" /* yacc.c:1646  */
    break;

  case 218:
#line 804 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = Nil;}
#line 3364 "grammar.c" /* yacc.c:1646  */
    break;

  case 219:
#line 805 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), (yyvsp[-1].node));}
#line 3370 "grammar.c" /* yacc.c:1646  */
    break;

  case 240:
#line 837 "grammar.y" /* yacc.c:1646  */
    {
		       /* check that the game is not redeclared */
		       if (opt_mbp_game(options)) {
			 yyerror_lined("redefinition of a GAME", (yyvsp[-1].lineno));
		       }
		       /* set that this input file is a game declaration */
		       else {
#if !HAVE_MBP
             yyerror_lined("GAME declaration cannot be processes "
                           "because MBP package is not set up\n"
                           "Check --enable-mbp option of "
                           "the configure script\n", (yyvsp[-1].lineno));
             YYABORT;
#else
             set_mbp_game(options);
#endif
		       }

		       mbp_parser_spec_list = (yyvsp[0].node);
		       (yyval.node) = Nil;
		     }
#line 3396 "grammar.c" /* yacc.c:1646  */
    break;

  case 241:
#line 861 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=Nil;}
#line 3402 "grammar.c" /* yacc.c:1646  */
    break;

  case 242:
#line 863 "grammar.y" /* yacc.c:1646  */
    {if (Nil != (yyvsp[-1].node)) (yyval.node) = cons((yyvsp[-1].node),(yyvsp[0].node)); else (yyval.node) = (yyvsp[0].node);}
#line 3408 "grammar.c" /* yacc.c:1646  */
    break;

  case 243:
#line 871 "grammar.y" /* yacc.c:1646  */
    {
		       /* a player definition is converted to a module
			  definitino with a special name. This is done
			  to simplify the further flattening
		       */
		       if (mbp_parser_player_1 != Nil) {
			 yyerror_lined("redefinition of a PLAYER_1", (yyvsp[-1].lineno));
			 YYABORT;
		       }
		       mbp_parser_player_1 = new_lined_node(MODULE,
			   new_node(MODTYPE, 
			     new_node(ATOM,(node_ptr)find_string("PLAYER_1"),
				      Nil), Nil),  (yyvsp[0].node), (yyvsp[-1].lineno));
		       (yyval.node)=Nil;
		     }
#line 3428 "grammar.c" /* yacc.c:1646  */
    break;

  case 244:
#line 887 "grammar.y" /* yacc.c:1646  */
    {
		       /* a player definition is converted to a module
			  definitino with a special name. This is done
			  to simplify the further flattening
		       */
		       if (mbp_parser_player_2 != Nil) {
			 yyerror_lined("redefinition of a PLAYER_2", (yyvsp[-1].lineno));
			 YYABORT;
		       }
		       mbp_parser_player_2 = new_lined_node(MODULE,
			   new_node(MODTYPE, 
			     new_node(ATOM,(node_ptr)find_string("PLAYER_2"),
				      Nil), Nil), (yyvsp[0].node), (yyvsp[-1].lineno));
		       (yyval.node)=Nil;
		     }
#line 3448 "grammar.c" /* yacc.c:1646  */
    break;

  case 251:
#line 918 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = Nil; }
#line 3454 "grammar.c" /* yacc.c:1646  */
    break;

  case 252:
#line 919 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = cons((yyvsp[0].node), (yyvsp[-1].node)); }
#line 3460 "grammar.c" /* yacc.c:1646  */
    break;

  case 259:
#line 941 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(VAR, Nil, Nil, (yyvsp[0].lineno));}
#line 3466 "grammar.c" /* yacc.c:1646  */
    break;

  case 260:
#line 942 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(VAR, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 3472 "grammar.c" /* yacc.c:1646  */
    break;

  case 261:
#line 944 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), Nil);}
#line 3478 "grammar.c" /* yacc.c:1646  */
    break;

  case 262:
#line 945 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), (yyvsp[-1].node));}
#line 3484 "grammar.c" /* yacc.c:1646  */
    break;

  case 263:
#line 947 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(COLON, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3490 "grammar.c" /* yacc.c:1646  */
    break;

  case 264:
#line 949 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(IVAR, Nil, Nil, (yyvsp[0].lineno));}
#line 3496 "grammar.c" /* yacc.c:1646  */
    break;

  case 265:
#line 950 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(IVAR, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 3502 "grammar.c" /* yacc.c:1646  */
    break;

  case 266:
#line 952 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), Nil);}
#line 3508 "grammar.c" /* yacc.c:1646  */
    break;

  case 267:
#line 953 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), (yyvsp[-1].node));}
#line 3514 "grammar.c" /* yacc.c:1646  */
    break;

  case 268:
#line 955 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(COLON, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3520 "grammar.c" /* yacc.c:1646  */
    break;

  case 269:
#line 959 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(DEFINE, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 3526 "grammar.c" /* yacc.c:1646  */
    break;

  case 270:
#line 961 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = Nil;}
#line 3532 "grammar.c" /* yacc.c:1646  */
    break;

  case 271:
#line 962 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons(new_lined_node(EQDEF, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno)), (yyvsp[-4].node));}
#line 3538 "grammar.c" /* yacc.c:1646  */
    break;

  case 272:
#line 966 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(ASSIGN, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));}
#line 3544 "grammar.c" /* yacc.c:1646  */
    break;

  case 273:
#line 968 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = Nil;}
#line 3550 "grammar.c" /* yacc.c:1646  */
    break;

  case 274:
#line 969 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(AND, (yyvsp[-1].node), (yyvsp[0].node));}
#line 3556 "grammar.c" /* yacc.c:1646  */
    break;

  case 275:
#line 972 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(EQDEF, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-2].lineno));}
#line 3562 "grammar.c" /* yacc.c:1646  */
    break;

  case 276:
#line 974 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EQDEF,
					new_lined_node(SMALLINIT, (yyvsp[-4].node), Nil, (yyvsp[-6].lineno)),
					(yyvsp[-1].node), (yyvsp[-2].lineno));
		  }
#line 3571 "grammar.c" /* yacc.c:1646  */
    break;

  case 277:
#line 979 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(EQDEF,
					new_lined_node(NEXT, (yyvsp[-4].node), Nil, (yyvsp[-6].lineno)),
					(yyvsp[-1].node), (yyvsp[-2].lineno));
		  }
#line 3580 "grammar.c" /* yacc.c:1646  */
    break;

  case 278:
#line 986 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(INIT, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3586 "grammar.c" /* yacc.c:1646  */
    break;

  case 279:
#line 988 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(INVAR, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3592 "grammar.c" /* yacc.c:1646  */
    break;

  case 280:
#line 990 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(TRANS, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3598 "grammar.c" /* yacc.c:1646  */
    break;

  case 281:
#line 994 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(JUSTICE, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3604 "grammar.c" /* yacc.c:1646  */
    break;

  case 282:
#line 997 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(JUSTICE, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3610 "grammar.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1002 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(COMPASSION, cons((yyvsp[-4].node),(yyvsp[-2].node)), Nil, (yyvsp[-6].lineno));}
#line 3616 "grammar.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1005 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(INVARSPEC, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3622 "grammar.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1008 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(SPEC, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3628 "grammar.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1009 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(SPEC, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3634 "grammar.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1012 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(LTLSPEC, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3640 "grammar.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1016 "grammar.y" /* yacc.c:1646  */
    { 
  if (nusmv_parse_psl() != 0) {
    YYABORT;
  }
  (yyval.node) = new_lined_node(PSLSPEC, psl_parsed_tree, Nil, (yyvsp[0].lineno)); 
}
#line 3651 "grammar.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1024 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(CTLGSPEC, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3657 "grammar.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1029 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(CONSTANTS, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3663 "grammar.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1033 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = Nil;}
#line 3669 "grammar.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1034 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = cons((yyvsp[0].node), Nil);}
#line 3675 "grammar.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1035 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = cons((yyvsp[0].node), (yyvsp[-2].node));}
#line 3681 "grammar.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1039 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = cons((yyvsp[0].node), Nil);}
#line 3687 "grammar.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1040 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = cons((yyvsp[0].node), (yyvsp[-1].node));}
#line 3693 "grammar.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1044 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                   (yyval.node) = new_lined_node(PRED, (yyvsp[-1].node), 
                                       new_lined_node(NUMBER, 
                                                      (node_ptr) 0, Nil, (yyvsp[-2].lineno)), (yyvsp[-2].lineno));
#else
                   yyerror("given token is not supported.");
                   YYABORT;
#endif                 
                 }
#line 3708 "grammar.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1055 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                   (yyval.node) = new_lined_node(PRED, (yyvsp[-1].node), (yyvsp[-3].node), (yyvsp[-5].lineno));
#else
                   yyerror("given token is not supported.");
                   YYABORT;
#endif                 
                 }
#line 3721 "grammar.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1066 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                    (yyval.node) = new_lined_node(MIRROR, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));
#else
                    yyerror("given token is not supported.");
                    YYABORT;
#endif                 
                  }
#line 3734 "grammar.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1076 "grammar.y" /* yacc.c:1646  */
    {(yyval.lineno)=1;}
#line 3740 "grammar.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1077 "grammar.y" /* yacc.c:1646  */
    {(yyval.lineno)=2;}
#line 3746 "grammar.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1080 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(REACHTARGET, NODE_FROM_INT((yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-3].lineno));}
#line 3752 "grammar.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1083 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(AVOIDTARGET, NODE_FROM_INT((yyvsp[-2].lineno)), (yyvsp[-1].node), (yyvsp[-3].lineno));}
#line 3758 "grammar.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1086 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(REACHDEADLOCK, NODE_FROM_INT((yyvsp[-1].lineno)), Nil, (yyvsp[-2].lineno));}
#line 3764 "grammar.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1089 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(AVOIDDEADLOCK, NODE_FROM_INT((yyvsp[-1].lineno)), Nil, (yyvsp[-2].lineno));}
#line 3770 "grammar.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1094 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(BUCHIGAME, NODE_FROM_INT((yyvsp[-4].lineno)),
					    new_lined_node(MBP_EXP_LIST,
							 reverse((yyvsp[-2].node)), Nil, (yyvsp[-3].lineno)),
					    (yyvsp[-5].lineno));}
#line 3779 "grammar.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1102 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(GENREACTIVITY, NODE_FROM_INT((yyvsp[-8].lineno)),
				          new_lined_node(MBP_TWO_EXP_LISTS,
						reverse((yyvsp[-6].node)), reverse((yyvsp[-2].node)), (yyvsp[-4].lineno)),
					    (yyvsp[-9].lineno));}
#line 3788 "grammar.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1108 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(COMPUTE, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3794 "grammar.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1112 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(MINU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-5].lineno)); }
#line 3800 "grammar.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1114 "grammar.y" /* yacc.c:1646  */
    { (yyval.node) = new_lined_node(MAXU, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[-5].lineno)); }
#line 3806 "grammar.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1118 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(ISA, (yyvsp[0].node), Nil);}
#line 3812 "grammar.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1122 "grammar.y" /* yacc.c:1646  */
    {}
#line 3818 "grammar.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1131 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(DOT, (yyvsp[-2].node), (yyvsp[0].node));}
#line 3824 "grammar.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1132 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(DOT, (yyvsp[-2].node), (yyvsp[0].node));}
#line 3830 "grammar.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1133 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(ARRAY, (yyvsp[-3].node), (yyvsp[-1].node));}
#line 3836 "grammar.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1137 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(SELF,Nil,Nil);}
#line 3842 "grammar.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1138 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(DOT, (yyvsp[-2].node), (yyvsp[0].node));}
#line 3848 "grammar.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1139 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(DOT, (yyvsp[-2].node), (yyvsp[0].node));}
#line 3854 "grammar.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1140 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_node(ARRAY, (yyvsp[-3].node), (yyvsp[-1].node));}
#line 3860 "grammar.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1148 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 3866 "grammar.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1149 "grammar.y" /* yacc.c:1646  */
    {return(1);}
#line 3872 "grammar.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1150 "grammar.y" /* yacc.c:1646  */
    {return(1);}
#line 3878 "grammar.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1154 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(GOTO, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3884 "grammar.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1156 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(INIT, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3890 "grammar.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1158 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(JUSTICE, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3896 "grammar.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1160 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(TRANS, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3902 "grammar.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1162 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(CONSTRAINT, (yyvsp[-1].node), Nil, (yyvsp[-2].lineno));}
#line 3908 "grammar.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1164 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(SIMPWFF,
                             new_node(CONTEXT, Nil, (yyvsp[-1].node)), Nil, (yyvsp[-2].lineno));
                 }
#line 3916 "grammar.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1168 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(SIMPWFF,
                       new_node(CONTEXT, context2maincontext((yyvsp[-1].node)), (yyvsp[-3].node)), Nil, (yyvsp[-4].lineno));
                 }
#line 3924 "grammar.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1172 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(CTLWFF,
                             new_node(CONTEXT, Nil, (yyvsp[-1].node)), Nil, (yyvsp[-2].lineno));
                 }
#line 3932 "grammar.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1176 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(CTLWFF,
                       new_node(CONTEXT, context2maincontext((yyvsp[-1].node)), (yyvsp[-3].node)), Nil, (yyvsp[-4].lineno));
                 }
#line 3940 "grammar.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1180 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(CTLGWFF,
                             new_node(CONTEXT, Nil, (yyvsp[-1].node)), Nil, (yyvsp[-2].lineno));
                 }
#line 3948 "grammar.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1184 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(CTLGWFF,
		            new_node(CONTEXT, context2maincontext((yyvsp[-1].node)), (yyvsp[-3].node)), Nil, (yyvsp[-4].lineno));
                 }
#line 3956 "grammar.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1188 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(LTLWFF,
                             new_node(CONTEXT, Nil, (yyvsp[-1].node)), Nil, (yyvsp[-2].lineno));
                 }
#line 3964 "grammar.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1192 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(LTLWFF,
                       new_node(CONTEXT, context2maincontext((yyvsp[-1].node)), (yyvsp[-3].node)), Nil, (yyvsp[-4].lineno));
                 }
#line 3972 "grammar.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1196 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(COMPWFF,
                             new_node(CONTEXT, Nil, (yyvsp[-1].node)), Nil, (yyvsp[-2].lineno));
                 }
#line 3980 "grammar.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1200 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = new_lined_node(COMPWFF,
                       new_node(CONTEXT, context2maincontext((yyvsp[-1].node)), (yyvsp[-3].node)), Nil, (yyvsp[-4].lineno));
                 }
#line 3988 "grammar.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1204 "grammar.y" /* yacc.c:1646  */
    {
#if HAVE_MATHSAT 
                  (yyval.node) = new_lined_node(PREDS_LIST, (yyvsp[0].node), Nil, (yyvsp[-1].lineno));
#else
                  yyerror("given token is not supported.");
                  YYABORT;
#endif
                }
#line 4001 "grammar.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1215 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = find_atom((yyvsp[0].node));}
#line 4007 "grammar.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1216 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = find_node(DOT, (yyvsp[-2].node), (yyvsp[0].node));}
#line 4013 "grammar.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1217 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = find_node(ARRAY, (yyvsp[-3].node), (yyvsp[-1].node));}
#line 4019 "grammar.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1220 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (node_ptr)find_atom((yyvsp[0].node));}
#line 4025 "grammar.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1221 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = find_node(DOT, (yyvsp[-2].node), find_atom((yyvsp[0].node)));}
#line 4031 "grammar.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1224 "grammar.y" /* yacc.c:1646  */
    {parser_parse_real_unset(); }
#line 4037 "grammar.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1226 "grammar.y" /* yacc.c:1646  */
    {
                     parser_parse_real_set(); 
                     (yyval.node) = find_node(DOT, (yyvsp[-2].node), find_atom((yyvsp[0].node)));
                   }
#line 4046 "grammar.c" /* yacc.c:1646  */
    break;


#line 4050 "grammar.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1233 "grammar.y" /* yacc.c:1906  */



/* Additional source code */
/* outputs the current token with the provided string and then may terminate */
void yyerror(char *s)
{
    extern options_ptr options;
    extern char yytext[];
    
    start_parsing_err();
    fprintf(nusmv_stderr, "at token \"%s\": %s\n", yytext, s);
    if (opt_batch(options)) finish_parsing_err();
}

/* the same as yyerror, except at first it sets the line number and does
 not output the current token 
*/
void yyerror_lined(const char *s, int line)
{
    extern options_ptr options;
    extern int yylineno;

    /*set the line number */
    yylineno = line;

    start_parsing_err();
    fprintf(nusmv_stderr, ": %s\n", s);
    if (opt_batch(options)) finish_parsing_err();
}

int yywrap()
{
  return(1);
}

/* This function is used to build the internal structure of the
   context (e.g. module instance name) from the parse tree. The
   function is needed since with the grammar it is not possible/simple
   to build directly the desired structure. */
static node_ptr context2maincontext(node_ptr context) {
  switch(node_get_type(context)) {
  case ATOM:
    return find_node(DOT, Nil, find_atom(context));
  case DOT: {
    node_ptr t = context2maincontext(car(context));
    return find_node(DOT, t, find_atom(cdr(context)));
  }
  case ARRAY: {
    node_ptr t = context2maincontext(car(context));
    return find_node(ARRAY, t, find_atom(cdr(context)));
  }
  default:
    fprintf(nusmv_stderr, "context2maincontext: undefined token \"%d\"\n",
	    node_get_type(context));
    nusmv_assert(false);
  }
}

/* this functions checks that the expression is formed syntactically correct.
   Takes the expression to be checked, the expected kind of the 
   expression. Returns true if the expression is formed correctly, and 
   false otherwise.
   See enum EXP_KIND for more info about syntactic well-formedness.
*/
static boolean isCorrectExp(node_ptr exp, enum EXP_KIND expectedKind)
{
  switch(node_get_type(exp))
    {
      /* atomic expression (or thier operands have been checked earlier) */
    case FAILURE:
    case FALSEEXP:
    case TRUEEXP:
    case NUMBER:
    case NUMBER_WORD:
    case NUMBER_FRAC: 
    case NUMBER_REAL:
    case NUMBER_EXP:
    case TWODOTS:
    case DOT:
    case ATOM:
    case SELF:
    case ARRAY:
    case BIT_SELECTION:
      return true;

      /* unary operators incompatible with LTL and CTL operator */
    case CAST_BOOL:
    case CAST_WORD1:
      if (EXP_LTL == expectedKind || EXP_CTL == expectedKind) {
	return isCorrectExp(car(exp), EXP_SIMPLE);
      } 
      /* unary operators compatible with LTL and CTL operator */
    case NOT: 
    case UMINUS:
      return isCorrectExp(car(exp), expectedKind);
      
      /* binary opertors incompatible with LTL and CTL operator */
    case CASE: case COLON:
    case CONCATENATION: 
    case TIMES: case DIVIDE: case PLUS :case MINUS: case MOD: 
    case LSHIFT: case RSHIFT: case LROTATE: case RROTATE: 
    case WAREAD: case WAWRITE: /* AC ADDED THESE */
    case UNION: case SETIN: 
    case EQUAL: case NOTEQUAL: case LT: case GT: case LE: case GE: 
      if (EXP_LTL == expectedKind || EXP_CTL == expectedKind) {
	return isCorrectExp(car(exp), EXP_SIMPLE)
	  && isCorrectExp(cdr(exp), EXP_SIMPLE);
      } 
      /* binary opertors compatible LTL and CTL operator */
    case AND: case OR: case XOR: case XNOR: case IFF: case IMPLIES: 
      return isCorrectExp(car(exp), expectedKind)
	&& isCorrectExp(cdr(exp), expectedKind);

      /* next expression */
    case NEXT: 
      if (EXP_NEXT != expectedKind) {
	yyerror_lined("unexpected 'next' operator", node_get_lineno(exp));
	return false;
      }
      return isCorrectExp(car(exp), EXP_SIMPLE); /* NEXT cannot contain NEXT */

      /* CTL unary expressions */
    case EX: case AX: case EF: case AF: case EG: case AG: 
    case ABU: case EBU:
    case EBF: case ABF: case EBG: case ABG: 
      if (EXP_CTL != expectedKind) {
	yyerror_lined("unexpected CTL operator", node_get_lineno(exp));
	return false;
      }
      return isCorrectExp(car(exp), EXP_CTL); /* continue to check CTL */
      
      /* CTL binary expressions */
    case AU: case EU: 
      if (EXP_CTL != expectedKind) {
	yyerror_lined("unexpected CTL operator", node_get_lineno(exp));
	return false;
      }
      return isCorrectExp(car(exp), EXP_CTL)
	&& isCorrectExp(cdr(exp), EXP_CTL); /* continue to check CTL */


      /* LTL unary expressions */
    case OP_NEXT: case OP_PREC: case OP_NOTPRECNOT: case OP_GLOBAL:
    case OP_HISTORICAL: case OP_FUTURE: case OP_ONCE:
      if (EXP_LTL != expectedKind) {
	yyerror_lined("unexpected LTL operator", node_get_lineno(exp));
	return false;
      }
      return isCorrectExp(car(exp), EXP_LTL); /* continue to check LTL */


      /* LTL binary expressions */
    case UNTIL: case SINCE: 
      if (EXP_LTL != expectedKind) {
	yyerror_lined("unexpected LTL operator", node_get_lineno(exp));
	return false;
      }
      return isCorrectExp(car(exp), EXP_LTL)
	&& isCorrectExp(cdr(exp), EXP_LTL); /* continue to check LTL */

    default: nusmv_assert(false); /* unknown expression */
    }
  return false; /* should never be invoked */
}


static int nusmv_parse_psl() 
{
  int res;
  res = psl_yyparse();
  return res;  
}
