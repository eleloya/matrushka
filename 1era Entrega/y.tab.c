/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

#define YYPARSER 
#include "util/stack.c"

#define YYSTYPE char *
	
static stack typeStack;
static char* savedCode; /* stores code for later return */

/* Dictionary. Gets the string representation of a type token. 
TOKEN->STRING
 */
char *getTypeFromToken(int token){
	if(token==276){
		return "int";
	}else if(token==277){
		return "double";
	}else if(token==278){
		return "string";
	}else if(token==279){
		return "true";
	}else if(token==280){
		return "false";
	}else{
		return "undefined";
	}
}

/* Dictionary. Gets the Token type of a value. 
STRING->TOKEN 
*/
Token getTypeFromValue(char *value){
	Token token;
	if(strstr(value, "\"") != NULL) {
		token = STRINGVALTKN;
	}else if(strstr(value, ".") != NULL) {
		token = DOUBLEVALTKN;
	}else if(strstr(value, "true") != NULL) {
		token = TRUETKN;
	}else if(strstr(value, "false") != NULL) {
		token = FALSETKN;
	}else{
		token = INTVALTKN;
	}
	return token;
}

void pushType(char *value){
	static int firstTime = TRUE;
	
	Token token;
	token = getTypeFromValue(value);
	if(firstTime){
		stackInit(&typeStack);
		firstTime = FALSE;
	}
	
	stackPush(&typeStack,token);
	//printf("Pushed value:%s type:%s\n", value, getTypeFromToken(token));
	
}

char *opDict(int op){
	//op
	// 1 - plus
	// 2 - minus
	// 3 - times
	// 4 - div
	if(op==1)
		return " + ";
	if(op==2)
		return " - ";
	if(op==3)
		return " * ";
	if(op==4)
		return " / ";
	if(op==5)
		return " secret ";
	
	return "undefined";
}

void checkType(int op){
	//op
	// 1 - plus
	// 2 - minus
	// 3 - times
	// 4 - div
	
	int a = stackPop(&typeStack);
  int b = stackPop(&typeStack);
	
	// if operation_permitted(a,b,op);
	
	//printf("For OP: %s\tOP1:%s\tOP2:%s\r\n\r\n",opDict(op),getTypeFromToken(a),getTypeFromToken(b));
	//tecnicamente aqui deberia de insertar el resultado de operation_permitted
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 298 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   263

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    12,    16,    19,    20,    23,    26,
      29,    35,    37,    39,    41,    43,    46,    48,    61,    73,
      84,    85,    87,    91,    93,    96,    99,   101,   103,   105,
     107,   109,   111,   119,   129,   137,   142,   150,   154,   158,
     160,   165,   167,   171,   173,   175,   177,   179,   181,   183,
     185,   187,   189,   193,   197,   199,   203,   207,   209,   211,
     213,   215,   217,   219,   223,   225,   227,   229,   234,   235,
     237,   241,   243,   247,   250,   259,   267,   271,   273,   275,
     278,   280,   281,   287,   289,   291,   293,   295
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    50,    53,    76,    -1,    49,    53,
      76,    -1,    49,    50,    76,    -1,    49,    76,    -1,    -1,
      50,    51,    -1,    51,    42,    -1,    52,    13,    -1,    52,
      13,    43,    21,    44,    -1,    17,    -1,    18,    -1,    19,
      -1,    20,    -1,    53,    54,    -1,    54,    -1,     6,    52,
      46,    13,    40,    55,    41,    46,    50,    58,    75,     7,
      -1,     6,    52,    46,    13,    40,    55,    41,    46,    58,
      75,     7,    -1,     6,    52,    46,    13,    40,    55,    41,
      46,    75,     7,    -1,    -1,    56,    -1,    56,    45,    57,
      -1,    57,    -1,    52,    13,    -1,    58,    59,    -1,    59,
      -1,    62,    -1,    60,    -1,    61,    -1,    63,    -1,    72,
      -1,     3,    40,    66,    41,    46,    58,     4,    -1,     3,
      40,    66,    41,    46,    58,     5,    58,     4,    -1,     9,
      40,    66,    41,    46,    58,    10,    -1,    13,    26,    66,
      42,    -1,    13,    43,    21,    44,    26,    66,    42,    -1,
      11,    64,    42,    -1,    12,    66,    42,    -1,    65,    -1,
      65,    43,    21,    44,    -1,    13,    -1,    66,    67,    68,
      -1,    68,    -1,    31,    -1,    32,    -1,    33,    -1,    34,
      -1,    35,    -1,    36,    -1,    38,    -1,    39,    -1,    68,
      27,    69,    -1,    68,    28,    69,    -1,    69,    -1,    69,
      29,    71,    -1,    69,    30,    71,    -1,    71,    -1,    21,
      -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,    40,
      68,    41,    -1,    64,    -1,    70,    -1,    72,    -1,    13,
      40,    73,    41,    -1,    -1,    74,    -1,    74,    45,    68,
      -1,    68,    -1,     8,    68,    42,    -1,     8,    42,    -1,
      14,    40,    77,    41,    46,    50,    78,    15,    -1,    14,
      40,    77,    41,    46,    78,    15,    -1,    23,    45,    23,
      -1,    79,    -1,    76,    -1,    79,    80,    -1,    80,    -1,
      -1,    16,    37,    68,    81,    42,    -1,    62,    -1,    60,
      -1,    61,    -1,    63,    -1,    72,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   113,   113,   114,   115,   116,   118,   120,   121,   123,
     124,   126,   126,   126,   126,   128,   129,   131,   132,   133,
     136,   136,   138,   139,   141,   143,   144,   146,   146,   146,
     146,   146,   148,   149,   151,   153,   154,   156,   157,   159,
     160,   162,   164,   165,   167,   167,   167,   167,   167,   167,
     167,   167,   169,   170,   171,   173,   174,   175,   177,   178,
     179,   180,   181,   183,   184,   185,   186,   188,   190,   190,
     191,   191,   193,   194,   196,   197,   199,   201,   202,   204,
     205,   207,   207,   207,   207,   207,   207,   207
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IFTKN", "ENDIFTKN", "ELSETKN",
  "FUNCTKN", "ENDFUNCTKN", "RETURNFUNCTKN", "WHILETKN", "ENDWHILETKN",
  "READTKN", "WRITETKN", "IDTKN", "MATRUSHKATKN", "ENDMATRUSHKATKN",
  "MESSAGETKN", "INTTKN", "DOUBLETKN", "STRINGTKN", "BOOLTKN", "INTVALTKN",
  "DOUBLEVALTKN", "STRINGVALTKN", "TRUETKN", "FALSETKN", "ASSIGNTKN",
  "PLUSTKN", "MINUSTKN", "TIMESTKN", "DIVTKN", "LTTKN", "LTETKN", "GTTKN",
  "GTETKN", "EQUALTKN", "NOTEQUALTKN", "ASSIGNSECRETTKN", "ORTKN",
  "ANDTKN", "LEFTPTKN", "RIGHTPTKN", "SEMICOLONTKN", "LEFTBTKN",
  "RIGHTBTKN", "COMMATKN", "OPENBLOCKTKN", "$accept", "program",
  "a_gotomain", "vardeclarations", "vardeclaration", "type", "functions",
  "function", "params", "paramlist", "param", "blockstmts", "blockstmt",
  "ifstmt", "iterstmt", "assignstmt", "iostmt", "var", "identifier",
  "expstmt", "compoperator", "exp", "term", "values", "factor", "callstmt",
  "args", "arglist", "returnstmt", "matrushkas", "margs", "mbody",
  "mmessages", "mmessage", "@1", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    48,    48,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    53,    53,    54,    54,    54,
      55,    55,    56,    56,    57,    58,    58,    59,    59,    59,
      59,    59,    60,    60,    61,    62,    62,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    68,    69,    69,    69,    70,    70,
      70,    70,    70,    71,    71,    71,    71,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    77,    78,    78,    79,
      79,    81,    80,    80,    80,    80,    80,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     3,     2,     0,     2,     2,     2,
       5,     1,     1,     1,     1,     2,     1,    12,    11,    10,
       0,     1,     3,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     7,     9,     7,     4,     7,     3,     3,     1,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     4,     0,     1,
       3,     1,     3,     2,     8,     7,     3,     1,     1,     2,
       1,     0,     5,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     1,     0,     0,    11,    12,    13,    14,
       0,     0,     0,     0,    16,     5,     0,     0,     7,     0,
       4,     8,     9,    15,     3,     0,     0,     0,     2,     0,
       0,     0,     0,     0,    20,    76,     0,    10,     0,     0,
      21,    23,     0,     0,     0,     0,     0,     0,     0,    84,
      85,    83,    86,    87,    78,     0,    77,    80,    24,     0,
       0,     0,     0,    41,     0,    39,    41,    58,    59,    60,
      61,    62,     0,    64,     0,    43,    54,    65,    57,    66,
       0,    68,     0,     0,     0,    75,    79,     0,    22,     0,
       0,    37,     0,     0,    44,    45,    46,    47,    48,    49,
      50,    51,    38,     0,     0,     0,     0,     0,     0,    71,
       0,    69,     0,    81,    74,     0,     0,     0,    26,    28,
      29,    27,    30,    31,     0,     0,     0,     0,    63,    42,
      52,    53,    55,    56,    35,    67,     0,     0,     0,    73,
       0,     0,    25,     0,    19,     0,     0,    40,    70,     0,
      82,    72,     0,    18,     0,     0,     0,    17,    32,     0,
      34,    36,     0,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    10,    11,    12,    13,    14,    39,    40,
      41,   117,   118,   119,   120,   121,   122,    73,    65,    74,
     103,    75,    76,    77,    78,    79,   110,   111,   124,    54,
      27,    55,    56,    57,   138
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -111
static const yytype_int16 yypact[] =
{
    -111,     9,    97,  -111,   243,   -17,  -111,  -111,  -111,  -111,
      97,   -28,    29,    32,  -111,  -111,     4,    41,  -111,    32,
    -111,  -111,    23,  -111,  -111,    59,    61,    33,  -111,    56,
      55,    81,    62,    68,   243,  -111,    80,  -111,   100,    83,
      84,  -111,    85,    93,   122,     3,    44,   104,    80,  -111,
    -111,  -111,  -111,  -111,  -111,   137,   144,  -111,  -111,   108,
     243,     3,     3,  -111,   116,   124,   139,  -111,  -111,  -111,
    -111,  -111,     3,  -111,   130,    58,   -11,  -111,  -111,  -111,
       3,     3,   149,     3,   156,  -111,  -111,   119,  -111,   166,
     177,  -111,   161,   118,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,     3,     3,     3,     3,     3,   142,    58,
     150,   138,   151,    58,  -111,    36,   131,   223,  -111,  -111,
    -111,  -111,  -111,  -111,   187,   157,   160,   170,  -111,    58,
     -11,   -11,  -111,  -111,  -111,  -111,     3,   191,   180,  -111,
       6,   223,  -111,   217,  -111,   246,   246,  -111,    58,     3,
    -111,  -111,   231,  -111,   216,   230,   154,  -111,  -111,   246,
    -111,  -111,   241,  -111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,   -31,    -9,     2,   213,    50,  -111,  -111,
     186,  -105,  -110,   -26,   -19,    17,    19,   193,  -111,   -59,
    -111,   -68,    -3,  -111,    14,   -36,  -111,  -111,  -109,    69,
    -111,   182,  -111,   192,  -111
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      53,    18,    89,    90,    93,    48,    16,   142,   143,     3,
      49,   141,    53,   109,    21,   113,    66,    50,   106,   107,
      53,   108,    49,    17,    67,    68,    69,    70,    71,    50,
      49,   142,   152,   104,   105,   129,    38,    50,     4,    18,
     154,   155,    22,    72,   142,   142,     5,   140,   151,    66,
      25,   123,   142,    51,   162,    52,   116,    67,    68,    69,
      70,    71,    38,    23,    26,    51,    29,    52,   148,    23,
      80,    15,    30,    51,    32,    52,    72,    33,   139,    20,
     123,   123,    24,    42,    81,   104,   105,    82,    28,    43,
     156,    44,    45,    46,     5,    34,    47,     6,     7,     8,
       9,   130,   131,     4,    35,   123,    31,    18,    36,   123,
     123,     5,    37,    58,     6,     7,     8,     9,   123,   123,
     132,   133,    42,   123,    59,    61,   123,   115,    43,    60,
      44,    45,    46,    62,    42,    63,     6,     7,     8,     9,
      43,    83,    44,    45,    46,   104,   105,    42,     6,     7,
       8,     9,    85,    43,    87,    44,    45,    46,    91,   128,
      47,    94,    95,    96,    97,    98,    99,    92,   100,   101,
     112,   114,   102,    94,    95,    96,    97,    98,    99,    81,
     100,   101,   127,   136,   134,    94,    95,    96,    97,    98,
      99,   135,   100,   101,   144,   137,   161,    94,    95,    96,
      97,    98,    99,   145,   100,   101,   146,   125,    94,    95,
      96,    97,    98,    99,   147,   100,   101,   149,   126,    42,
     158,   159,   150,    19,   153,    43,    42,    44,    45,    46,
      84,   115,    43,    42,    44,    45,    46,    64,   157,    43,
     160,    44,    45,    46,    42,   163,    88,     0,    86,    42,
      43,     0,    44,    45,    46,    43,     0,    44,    45,    46,
       6,     7,     8,     9
};

static const yytype_int16 yycheck[] =
{
      36,    10,    61,    62,    72,    36,     4,   117,   117,     0,
      36,   116,    48,    81,    42,    83,    13,    36,    29,    30,
      56,    80,    48,    40,    21,    22,    23,    24,    25,    48,
      56,   141,   141,    27,    28,   103,    34,    56,     6,    48,
     145,   146,    13,    40,   154,   155,    14,   115,    42,    13,
      46,    87,   162,    36,   159,    36,    87,    21,    22,    23,
      24,    25,    60,    13,    23,    48,    43,    48,   136,    19,
      26,     2,    13,    56,    41,    56,    40,    21,    42,    10,
     116,   117,    13,     3,    40,    27,    28,    43,    19,     9,
     149,    11,    12,    13,    14,    40,    16,    17,    18,    19,
      20,   104,   105,     6,    23,   141,    45,   116,    46,   145,
     146,    14,    44,    13,    17,    18,    19,    20,   154,   155,
     106,   107,     3,   159,    41,    40,   162,     8,     9,    45,
      11,    12,    13,    40,     3,    13,    17,    18,    19,    20,
       9,    37,    11,    12,    13,    27,    28,     3,    17,    18,
      19,    20,    15,     9,    46,    11,    12,    13,    42,    41,
      16,    31,    32,    33,    34,    35,    36,    43,    38,    39,
      21,    15,    42,    31,    32,    33,    34,    35,    36,    40,
      38,    39,    21,    45,    42,    31,    32,    33,    34,    35,
      36,    41,    38,    39,     7,    44,    42,    31,    32,    33,
      34,    35,    36,    46,    38,    39,    46,    41,    31,    32,
      33,    34,    35,    36,    44,    38,    39,    26,    41,     3,
       4,     5,    42,    10,     7,     9,     3,    11,    12,    13,
      48,     8,     9,     3,    11,    12,    13,    44,     7,     9,
      10,    11,    12,    13,     3,     4,    60,    -1,    56,     3,
       9,    -1,    11,    12,    13,     9,    -1,    11,    12,    13,
      17,    18,    19,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    49,     0,     6,    14,    17,    18,    19,    20,
      50,    51,    52,    53,    54,    76,    52,    40,    51,    53,
      76,    42,    13,    54,    76,    46,    23,    77,    76,    43,
      13,    45,    41,    21,    40,    23,    46,    44,    52,    55,
      56,    57,     3,     9,    11,    12,    13,    16,    50,    60,
      61,    62,    63,    72,    76,    78,    79,    80,    13,    41,
      45,    40,    40,    13,    64,    65,    13,    21,    22,    23,
      24,    25,    40,    64,    66,    68,    69,    70,    71,    72,
      26,    40,    43,    37,    78,    15,    80,    46,    57,    66,
      66,    42,    43,    68,    31,    32,    33,    34,    35,    36,
      38,    39,    42,    67,    27,    28,    29,    30,    66,    68,
      73,    74,    21,    68,    15,     8,    50,    58,    59,    60,
      61,    62,    63,    72,    75,    41,    41,    21,    41,    68,
      69,    69,    71,    71,    42,    41,    45,    44,    81,    42,
      68,    58,    59,    75,     7,    46,    46,    44,    68,    26,
      42,    42,    75,     7,    58,    58,    66,     7,     4,     5,
      10,    42,    58,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 118 "yacc.y"
    { savedCode = "perro"; }
    break;

  case 39:
#line 159 "yacc.y"
    { (yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 40:
#line 160 "yacc.y"
    {(yyval)=(yyvsp[(1) - (4)]);}
    break;

  case 41:
#line 162 "yacc.y"
    { (yyval)= (yyvsp[(1) - (1)]);}
    break;

  case 52:
#line 169 "yacc.y"
    {  printf("OPERATION ( + ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); pushType((yyvsp[(1) - (3)])); pushType((yyvsp[(3) - (3)])); checkType(1); }
    break;

  case 53:
#line 170 "yacc.y"
    {   printf("OPERATION ( - ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); pushType((yyvsp[(1) - (3)])); pushType((yyvsp[(3) - (3)])); checkType(1); }
    break;

  case 54:
#line 171 "yacc.y"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 55:
#line 173 "yacc.y"
    {  printf("OPERATION ( * ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); pushType((yyvsp[(1) - (3)])); pushType((yyvsp[(3) - (3)])); checkType(1);  }
    break;

  case 56:
#line 174 "yacc.y"
    {  printf("OPERATION ( / ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); pushType((yyvsp[(1) - (3)])); pushType((yyvsp[(3) - (3)])); checkType(1); }
    break;

  case 57:
#line 175 "yacc.y"
    { (yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 58:
#line 177 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 59:
#line 178 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 60:
#line 179 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 61:
#line 180 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 62:
#line 181 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 64:
#line 184 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 65:
#line 185 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 66:
#line 186 "yacc.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 67:
#line 188 "yacc.y"
    {(yyval)=(yyvsp[(1) - (4)]);}
    break;

  case 81:
#line 207 "yacc.y"
    { checkType(5); }
    break;


/* Line 1267 of yacc.c.  */
#line 1766 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 210 "yacc.y"



int yyerror(char * message)
{ fprintf(outputFile,"Syntax error at line %d: %s\n",linecount,message);
  fprintf(outputFile,"Current token: %d", yychar);
  //printToken(yychar,lexeme);
  return 0;
}

char * parseA(void)
{ yyparse();
  return savedCode;
}

