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

#include "util/string_stack.c"
#include "util/int_stack.c"
#include "util/hash.c"
#define YYPARSER 
#define YYSTYPE char *
#define VERBOSE 1	
#define MAX_TMP_VARIABLES 1024
#define MAX_PROGRAM_SIZE 1000

/****************************************************************************/
/**                                                                        **/
/**                  GLOBAL VARIABLES FOR PARSER                           **/
/**                                                                        **/
/****************************************************************************/
		
static stack typeStack;
static stack operandStack;
static stack operatorStack;
static int_stack jumpStack;
static struct symbol SymbolTable[SYMBOL_TABLE_SIZE];
static char* scope;
static char* IRCode[MAX_PROGRAM_SIZE]; // TO-DO. Do this structure variable in size.


static int operatorStackFirstTime = TRUE;
static int operandStackFirstTime = TRUE;
static int temporals_counter = 1;
static int program_counter = 0;


/****************************************************************************/
/**                                                                        **/
/**                  ATTRIBUTE GRAMMAR FUNCTIONS                           **/
/**                                                                        **/
/****************************************************************************/


/*
* Used in the grammar rules (program,function) for changing the scope.
* It is important for example to save a new symbol.
* The program needs to know to wich scope the symbol belongs.
* Every time the grammar encounters a new "function" SetScope gets called.
*
*/
void PRG_SetScope(char *scopeName){
	if (NULL==scopeName){
		printf("LINE: %-4d  CALL: PRG_SetScope(NULL)\t", g_lineno);
		printf("FATAL: Null reference.\n");
		exit(EXIT_FAILURE);
	}
	
	if (strcmp(scopeName, "")==0){
		printf("LINE: %-4d  CALL: PRG_SetScope(\"\")\t", g_lineno);
		printf("FATAL: Can't set a empty scope\n");
		exit(EXIT_FAILURE);
	}
	
	if (scope!=NULL)
		free(scope);

	scope = strdup(scopeName);
	
	if(VERBOSE)
		printf("LINE: %-4d PGR_SetScope(%s)\n", g_lineno, scopeName);
}

/*
* Used in the grammar rules (param,vardeclaration,stmt) for checking current scope.
* Important before checking to wich scope should we save the symbol to.
*
*/
char * PRG_GetScope(){	
	if(VERBOSE)
		printf("LINE: %-4d PGR_GetScope() -> %s\n", g_lineno, scope);
	
	return scope;
}

/*
* Used in the grammar rules (expcmp,exp,term,factor) for semantic analysis.
*
*/
void EXP_PushOperator(char *op){
	//Always checking
	if (NULL==op){
		printf("LINE: %-4d  CALL: EXP_PushOperator(NULL)\t", g_lineno);
		printf("FATAL: Null reference.\n");
		exit(EXIT_FAILURE);
	}
	
	stackPush(&operatorStack,op);
	
	if(VERBOSE)
		printf("LINE: %-4d EXP_PushOperator(%s)\n", g_lineno, op);	
}

void save_symbol(char *typeName, char *identifierName, char *scopeName, char *symbolKind){
	int response;

	response = insert(SymbolTable, typeName, identifierName, scopeName, symbolKind);
	
	if(response!=0){
		printf("Symbol %s:%s on %s:%s\n", typeName, identifierName, scopeName, symbolKind);
		yyerror("ERROR: Redefinition of symbol");
	}
	
}
void get_symbol(char *identifierName, char *scopeName, char *symbolKind){
	/*
	We look for the same identifier both in the given scope and the global scope.
	*/
	int response_func;
	int response_local;
	int response_global;
	char *kind;
	
	//Function needs its own logic
	if(strcmp(symbolKind,"func")==0){
		response_func = member(SymbolTable, identifierName, scopeName);
		kind = memberKind(SymbolTable, identifierName, scopeName);
		//  Check for identifierName existance on global scope
		//  Also check for identifierName to be of type "func" (maybe the user is calling a identifier in global who is not a func)
		if(response_func==0 || strcmp(kind,"func")!=0){
			printf("Symbol %s on %s:%s\n", identifierName, scopeName, symbolKind);
			yyerror("ERROR: trying to use inexisting function");
			return;
			
		}
	}

	//Variables are search'd in both the local and global scope
	response_local  = member(SymbolTable, identifierName, scopeName);
	response_global = member(SymbolTable, identifierName, "global");
	if(response_local==0 && response_global==0){
		//printf("Symbol %s on %s:%s\n", identifierName, scopeName, symbolKind);
		yyerror("ERROR: trying to use inexisting variable");
		return;
	}
	
	
	//printf("Checking for '%s' symbol existance on scope %s of type %s\n", identifierName, scopeName, symbolKind);
}

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

char *getTypeFromSymbol(char *symbol){
	//TO-DO check for nulls on symbol
	
	return memberType(SymbolTable, symbol, PRG_GetScope());
}

void SMT_CheckStatement(char *st, char *symbol){
	//TO-DO Check for NULLS
	char *typeName;
	
	if(strcmp(st,"return")==0){
		typeName = symbol;
	}else{
		typeName = getTypeFromSymbol(symbol);
	}
	
	char * returnVal = stackPop(&typeStack);	
	if(VERBOSE)
		printf("LINE: %-4d SMT_CheckStatement(%s,%s) // stackPOP(typeStack)=%s  \n", g_lineno, st,symbol, returnVal);
	
	//TO-DO Should really abort here. Use previous convention for closing
	if(strcmp(typeName,returnVal)!=0){
		if(strcmp(st,"=")==0)
			yyerror("ERROR: type conflict inside assignment");
		else
			yyerror("ERROR: type conflict inside return");
	}else{
		//DEBUG
		//printf("--> NOISE\n");
		
	}
	
	
	if(VERBOSE)
		printf("LINE: %-4d SMT_CheckStatement(%s,%s)\n", g_lineno, st,symbol);
	
	free(returnVal);
}

void checkAssign(char *a, char *op, char *b){
	printf("Identifier: %s\n", a);
	printf("Type of (identifier) %s\n", a);
	printf("Value of tmp: %s\n", b);
}

void IR_AddGotoF(char *operand){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddGotoF(%s)\n", g_lineno, operand);
	
	char *instruction = concat("GOTOF ", operand);
	IRCode[program_counter] = instruction;
	int_stackPush(&jumpStack, program_counter);
	program_counter++;
}

void IR_AddEXP(char *operator, char *operandA, char *operandB, char *resultado){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddEXP(%s,%s,%s,%s)\n", g_lineno, operator,operandA,operandB, resultado);
	
	// + OPA OPB T1
	char * instruction = concat(operator, " ");
	instruction = concat(instruction, operandA);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, operandB);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, resultado);
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_AddASSIGN(char *identifier, char *expression){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddASSIGN(%s,%s)\n", g_lineno, identifier,expression);
	// "= " + expression + " " + identifier
	// = T1 A
	char * instruction = concat("= ", expression);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, identifier);
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_AddIOREAD(char * identifier){
	char *identifier_type;
	char *instruction;
	
	if(VERBOSE)
		printf("LINE: %-4d IR_AddIOREAD(%s)\n", g_lineno, identifier);
	//The intermiadiate opcode on the other hand would probably need to be special for each kind of variable
	identifier_type = getTypeFromSymbol(identifier);
	
	if(strcmp(identifier_type,"int")==0){
		instruction = concat("iread ", identifier);
	}else if(strcmp(identifier_type,"double")==0){
		instruction = concat("dread ", identifier);
	}else if(strcmp(identifier_type,"boolean")==0){
		instruction = concat("bread ", identifier);
	}else if(strcmp(identifier_type,"string")==0){
		instruction = concat("sread ", identifier);
	}
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeIOWRITE(){
	char *expression_type;
	char *expression;
	char *instruction;
	
	//Semantic Check
	//nada, cero, nothing, no needed
	expression_type = stackPop(&typeStack);
	expression = stackPop(&operandStack);
	
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeIOWRITE(%s)\n", g_lineno, expression);
	
	
	//I will not make a IR_AddIOWRITE. I can keep it here just fine.
	if(strcmp(expression_type,"int")==0){
		instruction = concat("iwrite ", expression);
	}else if(strcmp(expression_type,"double")==0){
		instruction = concat("dwrite ", expression);
	}else if(strcmp(expression_type,"boolean")==0){
		instruction = concat("bwrite ", expression);
	}else if(strcmp(expression_type,"string")==0){
		instruction = concat("swrite ", expression);
	}
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeIOREAD(char *identifier){
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeIOREAD(%s)\n", g_lineno, identifier);	
	
	//Semantic Check
	//Look for the identifier to be declared previously in the symbol table
	//Otherwise were would we save what we read
	//This is an easy one, is it not? ;)
	get_symbol(identifier, PRG_GetScope(), "var"); 
	
	
	IR_AddIOREAD(identifier);
}

void IR_MakeASSIGN(char *identifier){
	char *identifier_type;
	char *expression_type;
	char *expression;
	
	//Semantic Check
	//Look for the identifier to be declared previously in the symbol table
	//In assignment. The symbol to look for is either a var, or a parameter.
	get_symbol(identifier, PRG_GetScope(), "var"); 
	
	//Semantic Check
	// Check that the identifier and the expression have the same type
	identifier_type = getTypeFromSymbol(identifier);
	expression_type = stackPop(&typeStack);
	
	if(strcmp(identifier_type,expression_type)!=0){
		printf("LINE: %-4d CALL: IR_MakeASSIGN(%s)\n", g_lineno, identifier);
		printf("FATAL: Type mismatch. Trying to assign %s to a \"%s\" of type %s \n", expression_type, identifier, identifier_type);
		exit(EXIT_FAILURE);
	}
	
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeASSIGN(%s)\n", g_lineno, identifier);
	
	expression = stackPop(&operandStack);
	//Code generation
	IR_AddASSIGN(identifier,expression);
}

void IR_MakeIF(){
	char *typeName = stackPop(&typeStack);
	char *operand = stackPop(&operandStack);
	
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeIF()\n", g_lineno);
	
	//Semantic Check	
	if (strcmp(typeName,"boolean")!=0){
		printf("LINE: %-4d  CALL: IR_MakeIF()\t", g_lineno);
		printf("FATAL: Returned operand %s:%s is not boolean\n", operand, typeName);
		exit(EXIT_FAILURE);
	}
	
	//Code Generation Subroutine
	IR_AddGotoF(operand);
}

void IR_MakeELSEIF(){
	int previous_if_address = int_stackPop(&jumpStack);
	
	//GENERAR GOTO _____
	char *instruction;
	instruction = strdup("GOTO ");
	IRCode[program_counter] = instruction;
	int_stackPush(&jumpStack, program_counter);
	program_counter++;
	
	//SACAR FALSO DE PILA-DE-SALTOS
	char *previous_if_instruction;
	char jmp_address[MAX_PROGRAM_SIZE];
	sprintf(jmp_address, "%d", program_counter);

	previous_if_instruction = IRCode[previous_if_address];
	
	// "GOTOF var" + " " + JMP_ADDRESS
	previous_if_instruction  = concat(previous_if_instruction, " ");
	previous_if_instruction  = concat(previous_if_instruction, jmp_address);
	
	IRCode[previous_if_address] = strdup(previous_if_instruction);
	free(previous_if_instruction);
}

void IR_MakeENDIF(){
	
	int previous_if_address = int_stackPop(&jumpStack);
	char jmp_address[MAX_PROGRAM_SIZE];
	
	char *instruction = IRCode[previous_if_address];
	sprintf(jmp_address, "%d", program_counter);		
	
	char *new_instruction_tmp1;
	char *new_instruction;
	

	
	// "GOTOF var" + " " + JMP_ADDRESS
	new_instruction_tmp1  = concat(instruction, " ");
	new_instruction  = concat(new_instruction_tmp1, jmp_address);
	
	free(new_instruction_tmp1);
	free(instruction);
	
	IRCode[previous_if_address] = new_instruction;
}

void IR_MakeEXP(){
	char *operator = stackPop(&operatorStack);
	char *operand1_type = stackPop(&typeStack);
  	char *operand2_type = stackPop(&typeStack);
	char *operand1 = stackPop(&operandStack);
	char *operand2 = stackPop(&operandStack);
	char *temporal_variable;
	char suffix_for_temporal_variable[MAX_TMP_VARIABLES];

	//Semantic Analysis
	//We check the type of the two operands with the help of a semantic cube
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeEXP() // Checking Semantics (%s,%s,%s)\n", g_lineno, operator, operand1_type, operand2_type);
	
	// I need the cubo semantico aqui.
	// Actualmente solo estoy checando que los operadores sean del mismo tipo.
	if(strcmp(operand1_type,operand2_type)!=0){
		printf("LINE: %-4d CALL: IR_MakeEXP(%s)\n", g_lineno, operator);
		printf("FATAL: Type mismatch between operators \n");
		exit(EXIT_FAILURE);
	}else{
		// Aqui deberia pushear el tipo regresado del cubo semantico realmente
		// temporal_variable_type
		stackPush(&typeStack,operand1_type);		
	}
	
	//push pila_de_operandos(resultado)
	//pop pila-de-operadores
	
	//Calculate suffix for temporal variable
	//EJ. T1,T2,T3...T30,T31 ...T122,T123...
	sprintf(suffix_for_temporal_variable, "%d", temporals_counter++);
	temporal_variable = concat("T", suffix_for_temporal_variable);
	
	//Aqui es donde brilla el cubo semantico chingao. En vez de usar operand1_type.
	//Guardamos la temporal en la tabla de simbolos.
	save_symbol(operand1_type, temporal_variable, PRG_GetScope(), "tmp"); 
	
	//Pusheamos al stack de operadores la variable temporal donde se guarda el resultado
	stackPush(&operandStack,temporal_variable);


	//Code generation subroutine;
	IR_AddEXP(operator,operand1,operand2,temporal_variable);
}

void pushType(char *value, char *symbolKind){
	char *factorType;
	
	if(strcmp(symbolKind,"const")==0){ // then is a constant
		factorType = getTypeFromValue(value);
		//printf("Retrived type for %s is %s\n\n", value, factorType);
	}else{ // then is a variable or a function
		factorType = memberType(SymbolTable, value, PRG_GetScope());
		//printf("Retrived type for %s is %s in scope: %s\n\n", value, factorType, PRG_GetScope());
	}
	
	// We must transform the type into a int because these stack only holds integers
	stackPush(&typeStack,factorType);
}

void pushOperand(char *operand, char *kind){
	//A lo mejor deberia checar que sea permitido. Pero no pasarian por flex ni bison...
	stackPush(&operandStack, operand);
}

void EXP_PushOperand(char *operand, char *symbolKind){
	//TO-DO Check for NULLS
	
	//Check for the existance of a variable before even continuing.
	if(strcmp(symbolKind,"var")==0)
		get_symbol(operand, PRG_GetScope(), "var"); 
	
	//Later is the same for both expressions
	pushType(operand, symbolKind); 
	pushOperand(operand, symbolKind);
	
	if(VERBOSE)
		printf("LINE: %-4d EXP_PushOperand(%s,%s)\n", g_lineno, operand,symbolKind);
}

void PRG_Initialize(){
	PRG_SetScope("global");
	
	stackInit(&operandStack);
	stackInit(&typeStack);
	stackInit(&operatorStack);
	int_stackInit(&jumpStack);
	init_hash_table(SymbolTable);
	
	for(int i=0;i<MAX_PROGRAM_SIZE;i++)
		IRCode[i] = NULL;
}

void DBG_PrintSymbolTable(struct symbol hashtable[]){
	printf("\nSYMBOL TABLE\n");
	printf("%15s  %10s  ------   -----  -------  ----\n","----------","----------");
	printf("%15s  %-10s  type     kind   address  key\n","identifier", "context");
	printf("%15s  %10s  ------   -----  -------  ----\n","----------","----------");
	
  for (int i=0; i< SYMBOL_TABLE_SIZE ; i++){
      if (NULL != hashtable[i].value)
				printf("%15s  %10s  %7s  %5s  %7d  %d\n", hashtable[i].value, hashtable[i].contextName, hashtable[i].typeName, hashtable[i].symbolKind, hashtable[i].memoryLocation, i);
  }
}

void DBG_PrintIRCode(){
	printf("\nIR CODE\n");
	for(int i=0;i<program_counter;i++)
		printf("%5d: %s\n",i, IRCode[i]);
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
#line 711 "y.tab.c"

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
#define YYLAST   164

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  151

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
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    14,    17,    19,    25,
      28,    30,    31,    32,    46,    47,    50,    52,    53,    55,
      59,    61,    64,    68,    71,    74,    80,    82,    84,    86,
      88,    91,    93,    96,    98,   100,   103,   106,   116,   129,
     130,   131,   132,   140,   144,   151,   154,   157,   159,   164,
     166,   167,   172,   174,   176,   178,   180,   182,   184,   186,
     188,   190,   191,   196,   197,   202,   204,   205,   210,   211,
     216,   218,   220,   222,   224,   226,   228,   229,   230,   236,
     238,   240,   242,   247,   248,   250,   254,   256
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    -1,    49,    47,    59,    51,    -1,    -1,
      49,    48,    51,    -1,    49,    50,    -1,    50,    -1,    13,
      21,    43,    21,    40,    -1,    51,    52,    -1,    52,    -1,
      -1,    -1,     6,    61,    44,    18,    53,    38,    56,    39,
      44,    55,    89,    54,     7,    -1,    -1,    59,    62,    -1,
      62,    -1,    -1,    57,    -1,    57,    43,    58,    -1,    58,
      -1,    61,    18,    -1,    59,    60,    40,    -1,    60,    40,
      -1,    61,    18,    -1,    61,    18,    41,    19,    42,    -1,
      14,    -1,    15,    -1,    16,    -1,    17,    -1,    62,    63,
      -1,    63,    -1,    69,    40,    -1,    64,    -1,    68,    -1,
      70,    40,    -1,    86,    40,    -1,     3,    38,    73,    65,
      39,    44,    62,     4,    66,    -1,     3,    38,    73,    65,
      39,    44,    62,     5,    67,    62,     4,    66,    -1,    -1,
      -1,    -1,     9,    38,    73,    39,    44,    62,    10,    -1,
      18,    24,    73,    -1,    18,    41,    19,    42,    24,    73,
      -1,    11,    71,    -1,    12,    73,    -1,    72,    -1,    72,
      41,    19,    42,    -1,    18,    -1,    -1,    73,    75,    74,
      76,    -1,    76,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    34,    -1,    36,    -1,    37,    -1,
      -1,    76,    25,    77,    79,    -1,    -1,    76,    26,    78,
      79,    -1,    79,    -1,    -1,    79,    27,    80,    83,    -1,
      -1,    79,    28,    81,    83,    -1,    83,    -1,    19,    -1,
      20,    -1,    21,    -1,    22,    -1,    23,    -1,    -1,    -1,
      38,    84,    76,    85,    39,    -1,    71,    -1,    82,    -1,
      86,    -1,    18,    38,    87,    39,    -1,    -1,    88,    -1,
      88,    43,    76,    -1,    76,    -1,     8,    76,    40,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   532,   532,   532,   533,   533,   536,   537,   539,   541,
     542,   544,   544,   544,   546,   546,   547,   549,   549,   551,
     552,   554,   557,   558,   560,   561,   563,   563,   563,   563,
     566,   567,   569,   569,   569,   569,   569,   571,   572,   574,
     575,   576,   578,   580,   581,   583,   584,   586,   587,   589,
     591,   591,   592,   594,   594,   594,   594,   594,   594,   594,
     594,   596,   596,   597,   597,   598,   600,   600,   601,   601,
     602,   604,   605,   606,   607,   608,   610,   610,   610,   611,
     612,   613,   615,   618,   618,   619,   619,   621
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
  "blockstmt", "ifstmt", "a_openif", "a_closeif", "a_elseif", "iterstmt",
  "assignstmt", "iostmt", "var", "identifier", "expstmt", "@5",
  "compoperator", "exp", "@6", "@7", "term", "@8", "@9", "values",
  "factor", "@10", "@11", "callstmt", "args", "arglist", "returnstmt", 0
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
      66,    67,    68,    69,    69,    70,    70,    71,    71,    72,
      74,    73,    73,    75,    75,    75,    75,    75,    75,    75,
      75,    77,    76,    78,    76,    76,    80,    79,    81,    79,
      79,    82,    82,    82,    82,    82,    84,    85,    83,    83,
      83,    83,    86,    87,    87,    88,    88,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     2,     1,     5,     2,
       1,     0,     0,    13,     0,     2,     1,     0,     1,     3,
       1,     2,     3,     2,     2,     5,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     2,     2,     9,    12,     0,
       0,     0,     7,     3,     6,     2,     2,     1,     4,     1,
       0,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     1,     0,     4,     0,     4,
       1,     1,     1,     1,     1,     1,     0,     0,     5,     1,
       1,     1,     4,     0,     1,     3,     1,     3
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
       0,     0,    49,    45,    47,    49,    71,    72,    73,    74,
      75,    76,    79,    46,    52,    65,    80,    70,    81,     0,
      83,     0,     0,    12,    15,    30,    32,    35,    36,    39,
       0,     0,     0,    53,    54,    55,    56,    57,    58,    59,
      60,    50,    61,    63,    66,    68,    43,    86,     0,    84,
       0,     0,     0,     0,     0,     0,    77,     0,     0,     0,
       0,     0,    82,     0,     0,    87,    13,     0,     0,    48,
       0,    51,    62,    64,    67,    69,    85,     0,     0,     0,
      78,    44,     0,    42,    40,    41,    37,     0,     0,    40,
      38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     8,     3,     4,    19,    20,    35,   112,
      51,    37,    38,    39,    15,    16,    17,    53,    54,    55,
     113,   146,   147,    56,    57,    58,    72,    64,    73,   117,
     101,    74,   118,   119,    75,   120,   121,    76,    77,    92,
     130,    78,   108,   109,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int16 yypact[] =
{
       5,     0,    37,    14,   -76,    -2,   -76,   121,    29,   -76,
      24,   -76,   -76,   -76,   -76,    95,    17,    41,   121,    29,
     -76,    21,    29,    32,   -76,    34,    47,   -76,   -76,   -76,
      60,    71,    50,   -76,   -76,    64,   121,    54,    63,   -76,
     103,    69,   121,   -76,    35,   -76,    94,   101,   106,    -7,
      -5,   132,    35,    65,   -76,   -76,   -76,   102,   104,   105,
      -7,    -7,   -76,   -76,   100,   108,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,    97,    45,     2,   -76,   -76,   -76,    -7,
      -7,   124,    -7,   -76,    65,   -76,   -76,   -76,   -76,    97,
      86,   128,    -7,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,    97,    45,   109,   107,
     110,    -1,   142,   112,   111,   114,    45,    -7,    -7,    -7,
      -7,    -7,   -76,    -7,   129,   -76,   -76,   113,    65,   -76,
     115,    45,     2,     2,   -76,   -76,    45,    -7,    65,    55,
     -76,    97,    51,   -76,   -76,   -76,   -76,    65,    96,   -76,
     -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   -76,   -76,   155,   144,     4,   -76,   -76,
     -76,   -76,   -76,   118,   117,    -9,    -8,   -50,   -52,   -76,
     -76,    13,   -76,   -76,   -76,   -76,   116,   -76,   -57,   -76,
     -76,   -75,   -76,   -76,   -37,   -76,   -76,   -76,   -35,   -76,
     -76,   -44,   -76,   -76,   -76
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -5
static const yytype_int16 yytable[] =
{
      59,    85,    84,    89,    90,   107,    23,   111,    59,    59,
      26,    65,    66,    67,    68,    69,    70,   116,     1,    79,
      -4,     5,   106,    27,   102,   103,    27,     1,    40,   104,
     105,    71,    85,    80,    40,    18,    81,     6,    46,   125,
      59,    10,   131,    23,    47,    21,    48,    49,   136,    11,
      12,    13,    14,    50,    46,   144,   145,    24,    46,    25,
      47,    28,    48,    49,    47,   143,    48,    49,    46,    50,
     102,   103,    29,    50,    47,    30,    48,    49,   139,    32,
     141,   132,   133,    50,    59,   134,   135,    85,   142,    33,
      85,    31,    34,    41,    59,    59,    85,   148,    59,    46,
     149,    18,    36,    59,    59,    47,    42,    48,    49,    11,
      12,    13,    14,    44,    50,    93,    94,    95,    96,    97,
      98,    43,    99,   100,    62,   114,    93,    94,    95,    96,
      97,    98,    60,    99,   100,    11,    12,    13,    14,    61,
      82,    91,    86,   110,    87,    88,    80,   115,   122,   126,
     123,   127,   124,   137,   140,   128,   129,   138,     9,    22,
      45,    52,   150,     0,    63
};

static const yytype_int16 yycheck[] =
{
      44,    53,    52,    60,    61,    80,    15,    82,    52,    53,
      18,    18,    19,    20,    21,    22,    23,    92,    13,    24,
       6,    21,    79,    19,    25,    26,    22,    13,    36,    27,
      28,    38,    84,    38,    42,     6,    41,     0,     3,    40,
      84,    43,   117,    52,     9,    21,    11,    12,   123,    14,
      15,    16,    17,    18,     3,     4,     5,    40,     3,    18,
       9,    40,    11,    12,     9,    10,    11,    12,     3,    18,
      25,    26,    40,    18,     9,    41,    11,    12,   128,    19,
     137,   118,   119,    18,   128,   120,   121,   139,   138,    18,
     142,    44,    42,    39,   138,   139,   148,   147,   142,     3,
       4,     6,    38,   147,   148,     9,    43,    11,    12,    14,
      15,    16,    17,    44,    18,    29,    30,    31,    32,    33,
      34,    18,    36,    37,    18,    39,    29,    30,    31,    32,
      33,    34,    38,    36,    37,    14,    15,    16,    17,    38,
       8,    41,    40,    19,    40,    40,    38,    19,    39,     7,
      43,    39,    42,    24,    39,    44,    42,    44,     3,    15,
      42,    44,   149,    -1,    48
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
      18,    55,    59,    62,    63,    64,    68,    69,    70,    86,
      38,    38,    18,    71,    72,    18,    19,    20,    21,    22,
      23,    38,    71,    73,    76,    79,    82,    83,    86,    24,
      38,    41,     8,    89,    62,    63,    40,    40,    40,    73,
      73,    41,    84,    29,    30,    31,    32,    33,    34,    36,
      37,    75,    25,    26,    27,    28,    73,    76,    87,    88,
      19,    76,    54,    65,    39,    19,    76,    74,    77,    78,
      80,    81,    39,    43,    42,    40,     7,    39,    44,    42,
      85,    76,    79,    79,    83,    83,    76,    24,    44,    62,
      39,    73,    62,    10,     4,     5,    66,    67,    62,     4,
      66
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
#line 532 "yacc.y"
    { PRG_Initialize(); }
    break;

  case 3:
#line 532 "yacc.y"
    { DBG_PrintSymbolTable(SymbolTable); DBG_PrintIRCode(); }
    break;

  case 4:
#line 533 "yacc.y"
    { PRG_Initialize(); }
    break;

  case 11:
#line 544 "yacc.y"
    {PRG_SetScope((yyvsp[(4) - (4)])); save_symbol((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), "global", "func");  }
    break;

  case 12:
#line 544 "yacc.y"
    { SMT_CheckStatement("return", (yyvsp[(2) - (11)]));}
    break;

  case 21:
#line 554 "yacc.y"
    { save_symbol((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), PRG_GetScope(), "param"); }
    break;

  case 24:
#line 560 "yacc.y"
    { save_symbol((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), PRG_GetScope(), "var"); }
    break;

  case 39:
#line 574 "yacc.y"
    { IR_MakeIF(); }
    break;

  case 40:
#line 575 "yacc.y"
    { IR_MakeENDIF(); }
    break;

  case 41:
#line 576 "yacc.y"
    { IR_MakeELSEIF(); }
    break;

  case 43:
#line 580 "yacc.y"
    { IR_MakeASSIGN((yyvsp[(1) - (3)])); }
    break;

  case 45:
#line 583 "yacc.y"
    { IR_MakeIOREAD((yyvsp[(2) - (2)])); }
    break;

  case 46:
#line 584 "yacc.y"
    {IR_MakeIOWRITE(); }
    break;

  case 50:
#line 591 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 51:
#line 591 "yacc.y"
    { IR_MakeEXP(); }
    break;

  case 61:
#line 596 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 62:
#line 596 "yacc.y"
    { IR_MakeEXP();}
    break;

  case 63:
#line 597 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 64:
#line 597 "yacc.y"
    { IR_MakeEXP();}
    break;

  case 66:
#line 600 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 67:
#line 600 "yacc.y"
    { IR_MakeEXP();}
    break;

  case 68:
#line 601 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 69:
#line 601 "yacc.y"
    { IR_MakeEXP();}
    break;

  case 76:
#line 610 "yacc.y"
    { /* fake bottom */ }
    break;

  case 77:
#line 610 "yacc.y"
    { /* fake bottom */ }
    break;

  case 79:
#line 611 "yacc.y"
    { EXP_PushOperand((yyvsp[(1) - (1)]), "var");  }
    break;

  case 80:
#line 612 "yacc.y"
    { EXP_PushOperand((yyvsp[(1) - (1)]), "const"); }
    break;

  case 81:
#line 613 "yacc.y"
    { EXP_PushOperand((yyvsp[(1) - (1)]), "func");  }
    break;

  case 82:
#line 615 "yacc.y"
    { get_symbol((yyvsp[(1) - (4)]), "global", "func"); }
    break;

  case 87:
#line 621 "yacc.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;


/* Line 1267 of yacc.c.  */
#line 2203 "y.tab.c"
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


#line 623 "yacc.y"



int yyerror(char * message)
	
{ fprintf(outputFile,"at line %d: %s\n",g_lineno,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}
