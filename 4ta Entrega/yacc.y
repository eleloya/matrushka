%{
#include "util/string_stack.c"
#include "util/hash.c"
#define YYPARSER 
#define YYSTYPE char *
#define VERBOSE 1	

/****************************************************************************/
/**                                                                        **/
/**                  GLOBAL VARIABLES FOR PARSER                           **/
/**                                                                        **/
/****************************************************************************/
		
static stack typeStack;
static stack operandStack;
static stack operatorStack;
static stack temporalStack;
static struct symbol SymbolTable[SYMBOL_TABLE_SIZE];
static char* scope;

static int operatorStackFirstTime = TRUE;
static int operandStackFirstTime = TRUE;

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
		printf("LINE: %-4d PGR_GetScope()->%s\n", g_lineno, scope);
	
	return scope;
}

// save_symbol("int","counter","global","var")
// save_symbol("int","counter","global","func")
// save_symbol("int","counter","global","param")
void save_symbol(char *typeName, char *identifierName, char *scopeName, char *symbolKind){
	static int firstTime = TRUE;
	int response;
	
	if(firstTime){
		init_hash_table(SymbolTable);
		firstTime = FALSE;
	}
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
		factorType = memberType(SymbolTable, value, PRG_GetScope());
		//printf("Retrived type for %s is %s in scope: %s\n\n", value, factorType, PRG_GetScope());
	}
	
	// We must transform the type into a int because these stack only holds integers
	stackPush(&typeStack,factorType);
	//DEBUG
	//printf("Pushing %d:%s:%s\n", typeDict(factorType), factorType, value);
	
}

void checkStmt(char *st, char *valuea, char *valueb){
	
	pushType(valuea, "var");
	
	//Llego aca?
	char * a = stackPop(&typeStack);
  char * b = stackPop(&typeStack);
	
	//DEBUG
	//printf("--> Checking statement '%s' for %s:%s\n", st, valuea, valueb);
	//printf("CHECK(%s) Popped: %d\n",st,a);
	//printf("CHECK(%s) Popped: %d\n",st,b);
	
	if(strcmp(a,b)!=0){
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
	char * a = stackPop(&typeStack);
  char * b = stackPop(&typeStack);
	
	// Aqui deberia tecnicamente hacer un cubo semantico
	// Verificar que la operacion con los dos tipos es permitida
	// Realmente, solo vamos a checar que sean del mismo tipo los dos operadores
	// if operation_permitted(a,b,op);
	
	//DEBUG
	printf("check(%s): %s:%s\n",op,a,valueb);
	printf("check(%s): %s:%s\n",op,b,valuea);
	
	if(strcmp(a,b)!=0){
		yyerror("ERROR: type conflict inside expression");
		//DEBUG
		//printf("Pushing %d:%s:%s\n", -1, valuea, valueb);
		stackPush(&typeStack,"null");
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

void pushOperator(char *op){
	// Unfortunely we need to add these to all attributes for expression code_generation
	if(operatorStackFirstTime){
		stackInit(&operatorStack);
		operatorStackFirstTime = FALSE;
	}
	
	stackPush(&operatorStack,op);
	printf("Pushed: %s to operatorStack\n", op);
	
}

void pushOperand(char *operand, char *kind){
	
	// I don't know why i'm asking for kind. I guess is important if the operator is of function kind. Time will tell.
	// It may prove important at code generation time.
	
	if(operandStackFirstTime){
		stackInit(&operandStack);
		operandStackFirstTime = FALSE;
	}
	
	stackPush(&operandStack, operand);
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
	
	char *operator = stackPop(&operatorStack);
	char *operand1 = stackPop(&operandStack);
	char *operand2 = stackPop(&operandStack);
	char *resultado = stackPop(&temporalStack);
	
	//If operand 1 or 2 have temporals, push them back to temporalStack... para hacer reuso de las temporales I GUESS
	stackPush(&operandStack,resultado);
	
	printf("  %3s %-8s %-5s %-5s\n\n",operator, operand1, operand2, resultado);
	
	//Creo que aqui deberia haber type-checking o dejarlo en la funcion anterior da igual
}

void generateTemporals(){
	stackInit(&temporalStack);
	// This is just for testing, a proper function is orderly needed.
	stackPush(&temporalStack,"T25");
	stackPush(&temporalStack,"T24");
	stackPush(&temporalStack,"T23");
	stackPush(&temporalStack,"T22");
	stackPush(&temporalStack,"T21");
	stackPush(&temporalStack,"T20");
	stackPush(&temporalStack,"T19");
	stackPush(&temporalStack,"T18");
	stackPush(&temporalStack,"T17");
	stackPush(&temporalStack,"T16");
	stackPush(&temporalStack,"T15");
	stackPush(&temporalStack,"T14");
	stackPush(&temporalStack,"T13");
	stackPush(&temporalStack,"T12");
	stackPush(&temporalStack,"T11");
	stackPush(&temporalStack,"T10");
	stackPush(&temporalStack,"T9");
	stackPush(&temporalStack,"T8");
	stackPush(&temporalStack,"T7");
	stackPush(&temporalStack,"T6");
	stackPush(&temporalStack,"T5");
	stackPush(&temporalStack,"T4");
	stackPush(&temporalStack,"T3");
	stackPush(&temporalStack,"T2");
	stackPush(&temporalStack,"T1");
	
}

%}

//Reserved Words
%token IFTKN ENDIFTKN ELSETKN FUNCTKN ENDFUNCTKN RETURNFUNCTKN WHILETKN ENDWHILETKN READTKN WRITETKN CIPHERTKN
//Types declaration
%token INTTKN DOUBLETKN STRINGTKN BOOLTKN
//Constants
%token IDTKN INTVALTKN DOUBLEVALTKN STRINGVALTKN TRUETKN FALSETKN
//Operators
%token ASSIGNTKN PLUSTKN MINUSTKN TIMESTKN DIVTKN LTTKN LTETKN GTTKN GTETKN EQUALTKN NOTEQUALTKN ASSIGNSECRETTKN ORTKN ANDTKN
//Syntax
%token LEFTPTKN RIGHTPTKN SEMICOLONTKN LEFTBTKN RIGHTBTKN COMMATKN OPENBLOCKTKN


%%

program   				: secrets { generateTemporals();PRG_SetScope("global");  }  vardeclarations functions { print_hash_table(SymbolTable); }
									| secrets { generateTemporals();PRG_SetScope("global");  } functions
										

secrets						: secrets secret
									| secret

secret						: CIPHERTKN STRINGVALTKN COMMATKN STRINGVALTKN SEMICOLONTKN

functions         : functions function
									| function;

function					: FUNCTKN type OPENBLOCKTKN IDTKN {PRG_SetScope($4); save_symbol($2, $4, "global", "func");  } LEFTPTKN params RIGHTPTKN OPENBLOCKTKN funcbody returnstmt { checkStmt("ret", $4, $11);} ENDFUNCTKN;

funcbody					: /* empty */ | vardeclarations blockstmts
									| blockstmts

params						: /* empty */ | paramlist;

paramlist         : paramlist COMMATKN param 
									| param;

param             : type IDTKN { save_symbol($1, $2, PRG_GetScope(), "param"); };  /* no arrays as parameters... yet*/

						
vardeclarations   : vardeclarations vardeclaration SEMICOLONTKN;
							    | vardeclaration SEMICOLONTKN;

vardeclaration    : type IDTKN { save_symbol($1, $2, PRG_GetScope(), "var"); }
								  | type IDTKN LEFTBTKN INTVALTKN RIGHTBTKN { save_symbol($1, $2, PRG_GetScope(), "ary"); } ; /* int arreglo[3]; */

type   						: INTTKN | DOUBLETKN | STRINGTKN | BOOLTKN;


blockstmts        : blockstmts blockstmt;
									| blockstmt;

blockstmt         : assignstmt SEMICOLONTKN | ifstmt | iterstmt | iostmt SEMICOLONTKN | callstmt SEMICOLONTKN;

ifstmt            : IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDIFTKN
 									| IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ELSETKN blockstmts ENDIFTKN;

iterstmt					: WHILETKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDWHILETKN;

assignstmt        : IDTKN ASSIGNTKN expstmt { get_symbol($1, PRG_GetScope(), "var"); checkStmt("=", $1, $3); }
									| IDTKN LEFTBTKN INTVALTKN RIGHTBTKN ASSIGNTKN expstmt  { get_symbol($1, PRG_GetScope(), "ary"); checkStmt("=", $1, $3); };
									
iostmt            : READTKN var  { get_symbol($2, PRG_GetScope(), "var");}
									| WRITETKN expstmt;
									
var               : identifier 
									| identifier LEFTBTKN INTVALTKN RIGHTBTKN;

identifier				: IDTKN;
			
expstmt           : expstmt compoperator {pushOperator($2);} exp {checkExp("<>", $1, $4); cg_exp();} 
									| exp;

compoperator      : LTTKN | LTETKN | GTTKN | GTETKN | EQUALTKN | NOTEQUALTKN | ORTKN | ANDTKN;

exp               : exp PLUSTKN {pushOperator("+");} term { checkExp("+", $1, $4); cg_exp();} 
									| exp MINUSTKN {pushOperator("-");}  term  { checkExp("-", $1, $4); cg_exp();}
									| term;

term    					: term TIMESTKN {pushOperator("*");}  factor  { checkExp("*", $1, $4); cg_exp();}
									| term DIVTKN {pushOperator("/");} factor  { checkExp("/", $1, $4); cg_exp();}
									| factor

values            : INTVALTKN 
									| DOUBLEVALTKN  
									| STRINGVALTKN   
									| TRUETKN  
									| FALSETKN;

factor            : LEFTPTKN { /* Unnecesary to add a fake bottom */ } exp { /* Unnecesary to remove a fake bottom */ } RIGHTPTKN
									| var  { /* printf("Pushing a var type into typeStack: %s\n", $1); */ get_symbol($1, PRG_GetScope(), "var"); pushType($1, "id"); pushOperand($1, "id"); }
									| values { /* printf("Pushing constant type into typeStack: %s\n", $1); */ pushType($1, "const"); pushOperand($1, "const"); }
									| callstmt { /* printf("Pushing function type into typeStack:%s\n", $1); */ pushType($1, "func"); pushOperand($1, "func");} ;

//faltaria checar que existen los args_scope									
callstmt          : IDTKN LEFTPTKN args RIGHTPTKN  { get_symbol($1, "global", "func"); };

// Me falta la semantica de variables
args              : /* empty */ | arglist
arglist           : arglist COMMATKN exp | exp;

returnstmt        : RETURNFUNCTKN exp SEMICOLONTKN { $$ = $2; };
		
%%


int yyerror(char * message)
	
{ fprintf(outputFile,"at line %d: %s\n",g_lineno,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}