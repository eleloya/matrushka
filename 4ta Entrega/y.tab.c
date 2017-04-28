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
     CIPHERTKN = 268,
     INTTKN = 269,
     DOUBLETKN = 270,
     STRINGTKN = 271,
     BOOLTKN = 272,
     IDTKN = 273,
     INTVALTKN = 274,
     DOUBLEVALTKN = 275,
     STRINGVALTKN = 276,
     TRUETKN = 277,
     FALSETKN = 278,
     ASSIGNTKN = 279,
     PLUSTKN = 280,
     MINUSTKN = 281,
     TIMESTKN = 282,
     DIVTKN = 283,
     LTTKN = 284,
     LTETKN = 285,
     GTTKN = 286,
     GTETKN = 287,
     EQUALTKN = 288,
     NOTEQUALTKN = 289,
     ASSIGNSECRETTKN = 290,
     ORTKN = 291,
     ANDTKN = 292,
     LEFTPTKN = 293,
     RIGHTPTKN = 294,
     SEMICOLONTKN = 295,
     LEFTBTKN = 296,
     RIGHTBTKN = 297,
     COMMATKN = 298,
     OPENBLOCKTKN = 299
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
#define CIPHERTKN 268
#define INTTKN 269
#define DOUBLETKN 270
#define STRINGTKN 271
#define BOOLTKN 272
#define IDTKN 273
#define INTVALTKN 274
#define DOUBLEVALTKN 275
#define STRINGVALTKN 276
#define TRUETKN 277
#define FALSETKN 278
#define ASSIGNTKN 279
#define PLUSTKN 280
#define MINUSTKN 281
#define TIMESTKN 282
#define DIVTKN 283
#define LTTKN 284
#define LTETKN 285
#define GTTKN 286
#define GTETKN 287
#define EQUALTKN 288
#define NOTEQUALTKN 289
#define ASSIGNSECRETTKN 290
#define ORTKN 291
#define ANDTKN 292
#define LEFTPTKN 293
#define RIGHTPTKN 294
#define SEMICOLONTKN 295
#define LEFTBTKN 296
#define RIGHTBTKN 297
#define COMMATKN 298
#define OPENBLOCKTKN 299




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

#define YYPARSER 
#include "util/stack.c"
#include "util/string_stack.c"
#include "util/hash.c"
	
#define YYSTYPE char *
	
static stack typeStack;
static stringStack operandStack;
static stringStack operatorStack;
static stringStack temporalStack;
//Una estructura con direcciones temporales. O una funcion?
static stringStack jumps;
static stringStack quads;
static struct hashrecord symbolTable[HASH_TABLE_SIZE];
static char* savedCode; /* stores code for later return */
static char* context;


static int operatorStackFirstTime = TRUE;
static int operandStackFirstTime = TRUE;

void setContext(char *contextName){
	if (context!=NULL)
		free(context);
	//printf("\n\nSetting context as: %s\n", contextName);
	context = strdup(contextName);
}

char * getContext(){
	return context;
}

// save_symbol("int","counter","global","var")
// save_symbol("int","counter","global","func")
// save_symbol("int","counter","global","param")
void save_symbol(char *typeName, char *identifierName, char *contextName, char *symbolKind){
	static int firstTime = TRUE;
	int response;
	
	if(firstTime){
		init_hash_table(symbolTable);
		firstTime = FALSE;
	}
	response = insert(symbolTable, typeName, identifierName, contextName, symbolKind);
	
	if(response!=0){
		printf("Symbol %s:%s on %s:%s\n", typeName, identifierName, contextName, symbolKind);
		yyerror("ERROR: Redefinition of symbol");
	}
	
}

void get_symbol(char *identifierName, char *contextName, char *symbolKind){
	/*
	We look for the same identifier both in the given context and the global context.
	*/
	int response_func;
	int response_local;
	int response_global;
	char *kind;
	
	//Function needs its own logic
	if(strcmp(symbolKind,"func")==0){
		response_func = member(symbolTable, identifierName, contextName);
		kind = memberKind(symbolTable, identifierName, contextName);
		//  Check for identifierName existance on global scope
		//  Also check for identifierName to be of type "func" (maybe the user is calling a identifier in global who is not a func)
		if(response_func==0 || strcmp(kind,"func")!=0){
			printf("Symbol %s on %s:%s\n", identifierName, contextName, symbolKind);
			yyerror("ERROR: trying to use inexisting function");
			return;
			
		}
	}

	//Variables are search'd in both the local and global scope
	response_local  = member(symbolTable, identifierName, contextName);
	response_global = member(symbolTable, identifierName, "global");
	if(response_local==0 && response_global==0){
		//printf("Symbol %s on %s:%s\n", identifierName, contextName, symbolKind);
		yyerror("ERROR: trying to use inexisting variable");
		return;
	}
	
	
	//printf("Checking for '%s' symbol existance on context %s of type %s\n", identifierName, contextName, symbolKind);
}

/* Dictionary. Gets the string representation of a type token. 
TOKEN->STRING
 */
char *getTypeFromToken(int token){
	if(token==269){
		return "int";
	}else if(token==275){
		return "double";
	}else if(token==276){
		return "string";
	}else if(token==278){
		return "boolean";
	}else if(token==277){
		return "boolean";
	}else{
		return "undefined";
	}
}

int typeDict(char *typeName){
	if(typeName==NULL){
		return -1;
	}
	if(strcmp(typeName,"int")==0){
		return 1;
	}else if(strcmp(typeName,"double")==0){
		return 2;
	}else if(strcmp(typeName,"string")==0){
		return 3;
	}else if(strcmp(typeName,"boolean")==0){
		return 4;
	}else{
		return -1; // Undefined type
	}
}

/* Dictionary. Gets the Token type of a value. 
STRING->TOKEN 
*/
char *getTypeFromValue(char *value){
	if(strstr(value, "\"") != NULL) {
		return "string";
	}else if(strstr(value, ".") != NULL) {
		return "double";
	}else if(strstr(value, "true") != NULL) {
		return "boolean";
	}else if(strstr(value, "false") != NULL) {
		return "boolean";
	}else{
		return "int";
	}
}

void pushType(char *value, char *symbolKind){
	static int firstTime = TRUE;
	char *factorType;
	if(firstTime){
		stackInit(&typeStack);
		firstTime = FALSE;
	}
	
	if(strcmp(symbolKind,"const")==0){ // then is a constant
		factorType = getTypeFromValue(value);
		//printf("Retrived type for %s is %s\n\n", value, factorType);
	}else{ // then is a variable or a function
		factorType = memberType(symbolTable, value, getContext());
		//printf("Retrived type for %s is %s in context: %s\n\n", value, factorType, getContext());
	}
	
	// We must transform the type into a int because these stack only holds integers
	stackPush(&typeStack,typeDict(factorType));
	//DEBUG
	//printf("Pushing %d:%s:%s\n", typeDict(factorType), factorType, value);
	
}

void checkStmt(char *st, char *valuea, char *valueb){
	
	pushType(valuea, "var");
	
	//Llego aca?
	int a = stackPop(&typeStack);
  int b = stackPop(&typeStack);
	
	//DEBUG
	//printf("--> Checking statement '%s' for %s:%s\n", st, valuea, valueb);
	//printf("Popped: %d:%s\n",a,valuea);
	//printf("Popped: %d:%s\n",b,valueb);
	
	if(a!=b){
		if(strcmp(st,"=")==0)
			yyerror("ERROR: type conflict inside assignment");
		else
			yyerror("ERROR: type conflict inside return");
	}else{
		//DEBUG
		//printf("--> NOISE\n");
		
	}
}

void checkExp(char *op, char *valuea, char *valueb){
	int a = stackPop(&typeStack);
  int b = stackPop(&typeStack);
	
	// Aqui deberia tecnicamente hacer un cubo semantico
	// Verificar que la operacion con los dos tipos es permitida
	// Realmente, solo vamos a checar que sean del mismo tipo los dos operadores
	// if operation_permitted(a,b,op);
	
	//DEBUG
	//printf("Popped: %d:%s\n",a,valuea);
	//printf("Popped: %d:%s\n",b,valueb);
	
	if(a!=b){
		yyerror("ERROR: type conflict inside expression");
		//DEBUG
		//printf("Pushing %d:%s:%s\n", -1, valuea, valueb);
		stackPush(&typeStack,-1);
	}else{
		// Either one is fine really
		stackPush(&typeStack,a);
		//stackPush(&typeStack,b);
		
		//DEBUG
		//printf("Pushing %d:%s%s%s\n", a, valuea, op, valueb);
		
	}
	
	
	
	//printf("For OP: %s\tOP1:%s\tOP2:%s\r\n\r\n",opDict(op),getTypeFromToken(a),getTypeFromToken(b));
	//tecnicamente aqui deberia de insertar el resultado de operation_permitted
}

void checkAssign(char *a, char *op, char *b){
	printf("Identifier: %s\n", a);
	printf("Type of (identifier) %s\n", a);
	printf("Value of tmp: %s\n", b);
}

void genComparison(char *left, char *right){
	printf("Comparison for: %s and %s\n", left, right);
}

//
// Attributes for Expressions Code Generation
//

void pushOperator(char *op){
	// Unfortunely we need to add these to all attributes for expression code_generation
	if(operatorStackFirstTime){
		stringStackInit(&operatorStack);
		operatorStackFirstTime = FALSE;
	}
	
	stringStackPush(&operatorStack,op);
	printf("Pushed: %s to operatorStack\n", op);
	
}

void removeFakeBottom(){
	char *removedString = stringStackPop(&operatorStack);
	printf("Poped: %s from operatorStack\n", removedString);
	free(removedString);
}

void pushOperand(char *operand, char *kind){
	
	// I don't know why i'm asking for kind. I guess is important if the operator is of function kind. Time will tell.
	// It may prove important at code generation time.
	
	if(operandStackFirstTime){
		stringStackInit(&operandStack);
		operandStackFirstTime = FALSE;
	}
	
	stringStackPush(&operandStack, operand);
	printf("Pushed: %s:%s to operandStack\n", kind,operand);
	
}

void cg_exp(){
	//Si el top de pila de operadores = +, -, *, /, ||, &&, !=, <, <=, >=, > entonces
	//operador = stackOperadorTOP
	//operando1 = pop stackOperando
	//operando2 = pop stackOperando
	//resultado = obtenerVariableTemporalLibre
	
	//Generar cuadruplo operador operando1 operando2 resultado
	//Si alguno de los operandoros venia de los temporales, regresarlo
	//push pila_de_operandos(resultado)
	//pop pila-de-operadores
	
	char *operator = stringStackPop(&operatorStack);
	char *operand1 = stringStackPop(&operandStack);
	char *operand2 = stringStackPop(&operandStack);
	char *resultado = stringStackPop(&temporalStack);
	
	//If operand 1 or 2 have temporals, push them back to temporalStack... para hacer reuso de las temporales I GUESS
	stringStackPush(&operandStack,resultado);
	
	printf("  %3s %-8s %-5s %-5s\n\n",operator, operand1, operand2, resultado);
	
	//Creo que aqui deberia haber type-checking o dejarlo en la funcion anterior da igual
}

void generateTemporals(){
	stringStackInit(&temporalStack);
	// This is just for testing, a proper function is orderly needed.
	stringStackPush(&temporalStack,"T25");
	stringStackPush(&temporalStack,"T24");
	stringStackPush(&temporalStack,"T23");
	stringStackPush(&temporalStack,"T22");
	stringStackPush(&temporalStack,"T21");
	stringStackPush(&temporalStack,"T20");
	stringStackPush(&temporalStack,"T19");
	stringStackPush(&temporalStack,"T18");
	stringStackPush(&temporalStack,"T17");
	stringStackPush(&temporalStack,"T16");
	stringStackPush(&temporalStack,"T15");
	stringStackPush(&temporalStack,"T14");
	stringStackPush(&temporalStack,"T13");
	stringStackPush(&temporalStack,"T12");
	stringStackPush(&temporalStack,"T11");
	stringStackPush(&temporalStack,"T10");
	stringStackPush(&temporalStack,"T9");
	stringStackPush(&temporalStack,"T8");
	stringStackPush(&temporalStack,"T7");
	stringStackPush(&temporalStack,"T6");
	stringStackPush(&temporalStack,"T5");
	stringStackPush(&temporalStack,"T4");
	stringStackPush(&temporalStack,"T3");
	stringStackPush(&temporalStack,"T2");
	stringStackPush(&temporalStack,"T1");
	
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
#line 524 "y.tab.c"

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   170

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    14,    17,    19,    25,
      28,    30,    31,    32,    46,    47,    50,    52,    53,    55,
      59,    61,    64,    68,    71,    74,    80,    82,    84,    86,
      88,    91,    93,    96,    98,   100,   103,   106,   114,   124,
     132,   136,   143,   146,   149,   151,   156,   158,   159,   164,
     166,   168,   170,   172,   174,   176,   178,   180,   182,   183,
     188,   189,   194,   196,   197,   202,   203,   208,   210,   212,
     214,   216,   218,   220,   221,   222,   228,   230,   232,   234,
     239,   240,   242,   246,   248
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    -1,    49,    47,    59,    51,    -1,    -1,
      49,    48,    51,    -1,    49,    50,    -1,    50,    -1,    13,
      21,    43,    21,    40,    -1,    51,    52,    -1,    52,    -1,
      -1,    -1,     6,    61,    44,    18,    53,    38,    56,    39,
      44,    55,    86,    54,     7,    -1,    -1,    59,    62,    -1,
      62,    -1,    -1,    57,    -1,    57,    43,    58,    -1,    58,
      -1,    61,    18,    -1,    59,    60,    40,    -1,    60,    40,
      -1,    61,    18,    -1,    61,    18,    41,    19,    42,    -1,
      14,    -1,    15,    -1,    16,    -1,    17,    -1,    62,    63,
      -1,    63,    -1,    66,    40,    -1,    64,    -1,    65,    -1,
      67,    40,    -1,    83,    40,    -1,     3,    38,    70,    39,
      44,    62,     4,    -1,     3,    38,    70,    39,    44,    62,
       5,    62,     4,    -1,     9,    38,    70,    39,    44,    62,
      10,    -1,    18,    24,    70,    -1,    18,    41,    19,    42,
      24,    70,    -1,    11,    68,    -1,    12,    70,    -1,    69,
      -1,    69,    41,    19,    42,    -1,    18,    -1,    -1,    70,
      72,    71,    73,    -1,    73,    -1,    29,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    36,    -1,
      37,    -1,    -1,    73,    25,    74,    76,    -1,    -1,    73,
      26,    75,    76,    -1,    76,    -1,    -1,    76,    27,    77,
      80,    -1,    -1,    76,    28,    78,    80,    -1,    80,    -1,
      19,    -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,
      -1,    -1,    38,    81,    73,    82,    39,    -1,    68,    -1,
      79,    -1,    83,    -1,    18,    38,    84,    39,    -1,    -1,
      85,    -1,    85,    43,    73,    -1,    73,    -1,     8,    73,
      40,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   345,   345,   345,   346,   346,   349,   350,   352,   354,
     355,   357,   357,   357,   359,   359,   360,   362,   362,   364,
     365,   367,   370,   371,   373,   374,   376,   376,   376,   376,
     379,   380,   382,   382,   382,   382,   382,   384,   385,   387,
     389,   390,   392,   393,   395,   396,   398,   400,   400,   401,
     403,   403,   403,   403,   403,   403,   403,   403,   405,   405,
     406,   406,   407,   409,   409,   410,   410,   411,   413,   414,
     415,   416,   417,   419,   419,   419,   420,   421,   422,   425,
     428,   428,   429,   429,   431
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IFTKN", "ENDIFTKN", "ELSETKN",
  "FUNCTKN", "ENDFUNCTKN", "RETURNFUNCTKN", "WHILETKN", "ENDWHILETKN",
  "READTKN", "WRITETKN", "CIPHERTKN", "INTTKN", "DOUBLETKN", "STRINGTKN",
  "BOOLTKN", "IDTKN", "INTVALTKN", "DOUBLEVALTKN", "STRINGVALTKN",
  "TRUETKN", "FALSETKN", "ASSIGNTKN", "PLUSTKN", "MINUSTKN", "TIMESTKN",
  "DIVTKN", "LTTKN", "LTETKN", "GTTKN", "GTETKN", "EQUALTKN",
  "NOTEQUALTKN", "ASSIGNSECRETTKN", "ORTKN", "ANDTKN", "LEFTPTKN",
  "RIGHTPTKN", "SEMICOLONTKN", "LEFTBTKN", "RIGHTBTKN", "COMMATKN",
  "OPENBLOCKTKN", "$accept", "program", "@1", "@2", "secrets", "secret",
  "functions", "function", "@3", "@4", "funcbody", "params", "paramlist",
  "param", "vardeclarations", "vardeclaration", "type", "blockstmts",
  "blockstmt", "ifstmt", "iterstmt", "assignstmt", "iostmt", "var",
  "identifier", "expstmt", "@5", "compoperator", "exp", "@6", "@7", "term",
  "@8", "@9", "values", "factor", "@10", "@11", "callstmt", "args",
  "arglist", "returnstmt", 0
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
     295,   296,   297,   298,   299
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    47,    46,    48,    46,    49,    49,    50,    51,
      51,    53,    54,    52,    55,    55,    55,    56,    56,    57,
      57,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      62,    62,    63,    63,    63,    63,    63,    64,    64,    65,
      66,    66,    67,    67,    68,    68,    69,    71,    70,    70,
      72,    72,    72,    72,    72,    72,    72,    72,    74,    73,
      75,    73,    73,    77,    76,    78,    76,    76,    79,    79,
      79,    79,    79,    81,    82,    80,    80,    80,    80,    83,
      84,    84,    85,    85,    86
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     2,     1,     5,     2,
       1,     0,     0,    13,     0,     2,     1,     0,     1,     3,
       1,     2,     3,     2,     2,     5,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     2,     2,     7,     9,     7,
       3,     6,     2,     2,     1,     4,     1,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     1,     0,     4,     0,     4,     1,     1,     1,
       1,     1,     1,     0,     0,     5,     1,     1,     1,     4,
       0,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     7,     0,     1,     0,     0,     6,
       0,    26,    27,    28,    29,     0,     0,     0,     0,     5,
      10,     0,     3,     0,    23,    24,     0,     9,     8,    22,
       0,     0,     0,    11,    25,     0,    17,     0,    18,    20,
       0,     0,     0,    21,    14,    19,     0,     0,     0,     0,
       0,     0,     0,    16,    31,    33,    34,     0,     0,     0,
       0,     0,    46,    42,    44,    46,    68,    69,    70,    71,
      72,    73,    76,    43,    49,    62,    77,    67,    78,     0,
      80,     0,     0,    12,    15,    30,    32,    35,    36,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    47,    58,    60,    63,    65,    40,    83,     0,    81,
       0,     0,     0,     0,     0,     0,    74,     0,     0,     0,
       0,     0,    79,     0,     0,    84,    13,     0,     0,    45,
       0,    48,    59,    61,    64,    66,    82,     0,     0,     0,
      75,    41,    37,     0,    39,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     8,     3,     4,    19,    20,    35,   112,
      51,    37,    38,    39,    15,    16,    17,    53,    54,    55,
      56,    57,    58,    72,    64,    73,   117,   101,    74,   118,
     119,    75,   120,   121,    76,    77,    92,   130,    78,   108,
     109,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -102
static const yytype_int16 yypact[] =
{
      -1,     9,    15,    65,  -102,    17,  -102,    74,    27,  -102,
      35,  -102,  -102,  -102,  -102,   101,    -4,    40,    74,    27,
    -102,    37,    27,    45,  -102,    33,    48,  -102,  -102,  -102,
      81,    84,    62,  -102,  -102,    72,    74,    75,    68,  -102,
      95,    86,    74,  -102,    34,  -102,    87,    99,   110,     4,
     -10,   132,    34,    64,  -102,  -102,  -102,   108,   111,   112,
       4,     4,  -102,  -102,   114,   115,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,   113,    13,    42,  -102,  -102,  -102,     4,
       4,   135,     4,  -102,    64,  -102,  -102,  -102,  -102,    90,
     102,   137,     4,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,   113,    13,   118,   116,
     119,    -6,   151,   120,   121,   124,    13,     4,     4,     4,
       4,     4,  -102,     4,   136,  -102,  -102,    64,    64,  -102,
     123,    13,    42,    42,  -102,  -102,    13,     4,    50,    54,
    -102,   113,  -102,    64,  -102,    94,  -102
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -102,  -102,  -102,  -102,  -102,   160,   152,    -9,  -102,  -102,
    -102,  -102,  -102,   126,   125,    -8,    -7,   -47,   -52,  -102,
    -102,  -102,  -102,   122,  -102,   -58,  -102,  -102,   -76,  -102,
    -102,  -101,  -102,  -102,  -102,   -12,  -102,  -102,   -44,  -102,
    -102,  -102
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -5
static const yytype_int16 yytable[] =
{
      59,    85,    89,    90,   107,    84,   111,    23,    59,    59,
      27,    26,     1,    27,    79,     6,   116,   132,   133,   102,
     103,   106,    65,    66,    67,    68,    69,    70,    80,    40,
       5,    81,    85,    18,   125,    40,    24,    46,   102,   103,
      59,   131,    71,    47,    23,    48,    49,   136,    11,    12,
      13,    14,    50,    46,   142,   143,    21,    46,    25,    47,
      10,    48,    49,    47,   144,    48,    49,    46,    50,   104,
     105,    -4,    50,    47,    30,    48,    49,    28,     1,   141,
     138,   139,    50,    59,    59,    29,    85,    85,    11,    12,
      13,    14,    31,    85,    59,    59,   145,    46,   146,    59,
      32,    59,    33,    47,    34,    48,    49,    18,   134,   135,
      36,    42,    50,    43,    41,    11,    12,    13,    14,    93,
      94,    95,    96,    97,    98,    60,    99,   100,    62,   113,
      44,    93,    94,    95,    96,    97,    98,    61,    99,   100,
      82,   114,    93,    94,    95,    96,    97,    98,    86,    99,
     100,    87,    88,    80,   110,    91,   115,   122,   126,   123,
     137,   124,   140,     9,   127,   128,   129,    22,    45,    52,
      63
};

static const yytype_uint8 yycheck[] =
{
      44,    53,    60,    61,    80,    52,    82,    15,    52,    53,
      19,    18,    13,    22,    24,     0,    92,   118,   119,    25,
      26,    79,    18,    19,    20,    21,    22,    23,    38,    36,
      21,    41,    84,     6,    40,    42,    40,     3,    25,    26,
      84,   117,    38,     9,    52,    11,    12,   123,    14,    15,
      16,    17,    18,     3,     4,     5,    21,     3,    18,     9,
      43,    11,    12,     9,    10,    11,    12,     3,    18,    27,
      28,     6,    18,     9,    41,    11,    12,    40,    13,   137,
     127,   128,    18,   127,   128,    40,   138,   139,    14,    15,
      16,    17,    44,   145,   138,   139,   143,     3,     4,   143,
      19,   145,    18,     9,    42,    11,    12,     6,   120,   121,
      38,    43,    18,    18,    39,    14,    15,    16,    17,    29,
      30,    31,    32,    33,    34,    38,    36,    37,    18,    39,
      44,    29,    30,    31,    32,    33,    34,    38,    36,    37,
       8,    39,    29,    30,    31,    32,    33,    34,    40,    36,
      37,    40,    40,    38,    19,    41,    19,    39,     7,    43,
      24,    42,    39,     3,    44,    44,    42,    15,    42,    44,
      48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    46,    49,    50,    21,     0,    47,    48,    50,
      43,    14,    15,    16,    17,    59,    60,    61,     6,    51,
      52,    21,    51,    60,    40,    18,    61,    52,    40,    40,
      41,    44,    19,    18,    42,    53,    38,    56,    57,    58,
      61,    39,    43,    18,    44,    58,     3,     9,    11,    12,
      18,    55,    59,    62,    63,    64,    65,    66,    67,    83,
      38,    38,    18,    68,    69,    18,    19,    20,    21,    22,
      23,    38,    68,    70,    73,    76,    79,    80,    83,    24,
      38,    41,     8,    86,    62,    63,    40,    40,    40,    70,
      70,    41,    81,    29,    30,    31,    32,    33,    34,    36,
      37,    72,    25,    26,    27,    28,    70,    73,    84,    85,
      19,    73,    54,    39,    39,    19,    73,    71,    74,    75,
      77,    78,    39,    43,    42,    40,     7,    44,    44,    42,
      82,    73,    76,    76,    80,    80,    73,    24,    62,    62,
      39,    70,     4,     5,    10,    62,     4
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
        case 2:
#line 345 "yacc.y"
    { generateTemporals();setContext("global");  }
    break;

  case 3:
#line 345 "yacc.y"
    { print_hash_table(symbolTable); }
    break;

  case 4:
#line 346 "yacc.y"
    { generateTemporals();setContext("global");  }
    break;

  case 11:
#line 357 "yacc.y"
    {setContext((yyvsp[(4) - (4)])); save_symbol((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), "global", "func");  }
    break;

  case 12:
#line 357 "yacc.y"
    { checkStmt("ret", (yyvsp[(4) - (11)]), (yyvsp[(11) - (11)]));}
    break;

  case 21:
#line 367 "yacc.y"
    { save_symbol((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), getContext(), "param"); }
    break;

  case 24:
#line 373 "yacc.y"
    { save_symbol((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), getContext(), "var"); }
    break;

  case 25:
#line 374 "yacc.y"
    { save_symbol((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), getContext(), "ary"); }
    break;

  case 40:
#line 389 "yacc.y"
    { get_symbol((yyvsp[(1) - (3)]), getContext(), "var"); checkStmt("=", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 41:
#line 390 "yacc.y"
    { get_symbol((yyvsp[(1) - (6)]), getContext(), "ary"); checkStmt("=", (yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])); }
    break;

  case 42:
#line 392 "yacc.y"
    { get_symbol((yyvsp[(2) - (2)]), getContext(), "var");}
    break;

  case 47:
#line 400 "yacc.y"
    {pushOperator((yyvsp[(2) - (2)]));}
    break;

  case 48:
#line 400 "yacc.y"
    {cg_exp();}
    break;

  case 58:
#line 405 "yacc.y"
    {pushOperator("+");}
    break;

  case 59:
#line 405 "yacc.y"
    { checkExp("+", (yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); cg_exp();}
    break;

  case 60:
#line 406 "yacc.y"
    {pushOperator("-");}
    break;

  case 61:
#line 406 "yacc.y"
    { checkExp("-", (yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); cg_exp();}
    break;

  case 63:
#line 409 "yacc.y"
    {pushOperator("*");}
    break;

  case 64:
#line 409 "yacc.y"
    { checkExp("*", (yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); cg_exp();}
    break;

  case 65:
#line 410 "yacc.y"
    {pushOperator("/");}
    break;

  case 66:
#line 410 "yacc.y"
    { checkExp("/", (yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); cg_exp();}
    break;

  case 73:
#line 419 "yacc.y"
    { pushOperator("("); }
    break;

  case 74:
#line 419 "yacc.y"
    { removeFakeBottom(); }
    break;

  case 76:
#line 420 "yacc.y"
    { /* printf("Pushing a var type into typeStack: %s\n", $1); */ get_symbol((yyvsp[(1) - (1)]), getContext(), "var"); pushType((yyvsp[(1) - (1)]), "id"); pushOperand((yyvsp[(1) - (1)]), "id"); }
    break;

  case 77:
#line 421 "yacc.y"
    { /* printf("Pushing constant type into typeStack: %s\n", $1); */ pushType((yyvsp[(1) - (1)]), "const"); pushOperand((yyvsp[(1) - (1)]), "const"); }
    break;

  case 78:
#line 422 "yacc.y"
    { /* printf("Pushing function type into typeStack:%s\n", $1); */ pushType((yyvsp[(1) - (1)]), "func"); pushOperand((yyvsp[(1) - (1)]), "func");}
    break;

  case 79:
#line 425 "yacc.y"
    { get_symbol((yyvsp[(1) - (4)]), "global", "func"); }
    break;

  case 84:
#line 431 "yacc.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;


/* Line 1267 of yacc.c.  */
#line 2005 "y.tab.c"
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


#line 433 "yacc.y"



int yyerror(char * message)
	
{ fprintf(outputFile,"at line %d: %s\n",linecount,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}

char * parseA(void)
{ yyparse();
  return savedCode;
}

