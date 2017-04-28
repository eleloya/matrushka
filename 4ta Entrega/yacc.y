%{
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

program   				: secrets { generateTemporals();setContext("global");  }  vardeclarations functions { print_hash_table(symbolTable); }
									| secrets { generateTemporals();setContext("global");  } functions
										

secrets						: secrets secret
									| secret

secret						: CIPHERTKN STRINGVALTKN COMMATKN STRINGVALTKN SEMICOLONTKN

functions         : functions function
									| function;

function					: FUNCTKN type OPENBLOCKTKN IDTKN {setContext($4); save_symbol($2, $4, "global", "func");  } LEFTPTKN params RIGHTPTKN OPENBLOCKTKN funcbody returnstmt { checkStmt("ret", $4, $11);} ENDFUNCTKN;

funcbody					: /* empty */ | vardeclarations blockstmts
									| blockstmts

params						: /* empty */ | paramlist;

paramlist         : paramlist COMMATKN param 
									| param;

param             : type IDTKN { save_symbol($1, $2, getContext(), "param"); };  /* no arrays as parameters... yet*/

						
vardeclarations   : vardeclarations vardeclaration SEMICOLONTKN;
							    | vardeclaration SEMICOLONTKN;

vardeclaration    : type IDTKN { save_symbol($1, $2, getContext(), "var"); }
								  | type IDTKN LEFTBTKN INTVALTKN RIGHTBTKN { save_symbol($1, $2, getContext(), "ary"); } ; /* int arreglo[3]; */

type   						: INTTKN | DOUBLETKN | STRINGTKN | BOOLTKN;


blockstmts        : blockstmts blockstmt;
									| blockstmt;

blockstmt         : assignstmt SEMICOLONTKN | ifstmt | iterstmt | iostmt SEMICOLONTKN | callstmt SEMICOLONTKN;

ifstmt            : IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDIFTKN
 									| IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ELSETKN blockstmts ENDIFTKN;

iterstmt					: WHILETKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDWHILETKN;

assignstmt        : IDTKN ASSIGNTKN expstmt { get_symbol($1, getContext(), "var"); checkStmt("=", $1, $3); }
									| IDTKN LEFTBTKN INTVALTKN RIGHTBTKN ASSIGNTKN expstmt  { get_symbol($1, getContext(), "ary"); checkStmt("=", $1, $3); };
									
iostmt            : READTKN var  { get_symbol($2, getContext(), "var");}
									| WRITETKN expstmt;
									
var               : identifier 
									| identifier LEFTBTKN INTVALTKN RIGHTBTKN;

identifier				: IDTKN;
			
expstmt           : expstmt compoperator {pushOperator($2);} exp {cg_exp();} 
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

factor            : LEFTPTKN { pushOperator("("); } exp { removeFakeBottom(); } RIGHTPTKN
									| var  { /* printf("Pushing a var type into typeStack: %s\n", $1); */ get_symbol($1, getContext(), "var"); pushType($1, "id"); pushOperand($1, "id"); }
									| values { /* printf("Pushing constant type into typeStack: %s\n", $1); */ pushType($1, "const"); pushOperand($1, "const"); }
									| callstmt { /* printf("Pushing function type into typeStack:%s\n", $1); */ pushType($1, "func"); pushOperand($1, "func");} ;

//faltaria checar que existen los args_context									
callstmt          : IDTKN LEFTPTKN args RIGHTPTKN  { get_symbol($1, "global", "func"); };

// Me falta la semantica de variables
args              : /* empty */ | arglist
arglist           : arglist COMMATKN exp | exp;

returnstmt        : RETURNFUNCTKN exp SEMICOLONTKN { $$ = $2; };
		
%%


int yyerror(char * message)
	
{ fprintf(outputFile,"at line %d: %s\n",linecount,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}

char * parseA(void)
{ yyparse();
  return savedCode;
}
