%{
#define YYPARSER 
#include "util/stack.c"
#include "util/hash.c"
	
#define YYSTYPE char *
	
static stack typeStack;
static struct hashrecord symbolTable[HASH_TABLE_SIZE];
static char* savedCode; /* stores code for later return */
static char* context;

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
		printf("Symbol %s on %s:%s\n", identifierName, contextName, symbolKind);
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
	printf("Pushing %s:%s\n", getTypeFromToken(token), value);
	
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

void checkType(int op, char* sender){
	//op
	// 1 - plus
	// 2 - minus
	// 3 - times
	// 4 - div
	
	printf("\nno mames quien me mando aca : %s\n\n", sender);
	int a = stackPop(&typeStack);
  int b = stackPop(&typeStack);
	
	// if operation_permitted(a,b,op);
	
	//printf("For OP: %s\tOP1:%s\tOP2:%s\r\n\r\n",opDict(op),getTypeFromToken(a),getTypeFromToken(b));
	//tecnicamente aqui deberia de insertar el resultado de operation_permitted
}

void checkAssign(char *a, char *op, char *b){
	printf("Identifier: %s\n", a);
	printf("Type of (identifier) %s\n", a);
	printf("Value of tmp: %s\n", b);
	printf("Type of (tmp): %s\n\n", getTypeFromToken(getTypeFromValue(b)));
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

program   				: secrets a_setGlobalContext vardeclarations functions { print_hash_table(symbolTable); }
									| secrets a_setGlobalContext functions
										
a_setGlobalContext: { setContext("global"); } 

secrets						: secrets secret
									| secret

secret						: CIPHERTKN STRINGVALTKN COMMATKN STRINGVALTKN SEMICOLONTKN

functions         : functions function
									| function;

function					: FUNCTKN type OPENBLOCKTKN IDTKN {setContext($4); save_symbol($2, $4, "global", "func");  } LEFTPTKN params RIGHTPTKN OPENBLOCKTKN funcbody returnstmt ENDFUNCTKN;

funcbody					: /* empty */ | vardeclarations blockstmts
									| blockstmts

params						: /* empty */ | paramlist;

paramlist         : paramlist COMMATKN param 
									| param;

param             : type IDTKN { save_symbol($1, $2, getContext(), "param"); };  /* no arrays as parameters... yet*/

						
vardeclarations   : vardeclarations vardeclaration SEMICOLONTKN;
							    | vardeclaration SEMICOLONTKN;

vardeclaration    : type IDTKN { save_symbol($1, $2, getContext(), "var"); }
								  | type IDTKN LEFTBTKN INTVALTKN RIGHTBTKN; /* int arreglo[3]; */

type   						: INTTKN | DOUBLETKN | STRINGTKN | BOOLTKN;


blockstmts        : blockstmts blockstmt;
									| blockstmt;

blockstmt         : assignstmt SEMICOLONTKN | ifstmt | iterstmt | iostmt SEMICOLONTKN | callstmt SEMICOLONTKN;

ifstmt            : IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDIFTKN
 									| IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ELSETKN blockstmts ENDIFTKN;

iterstmt					: WHILETKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDWHILETKN;

assignstmt        : IDTKN ASSIGNTKN expstmt { get_symbol($1, getContext(), "var");}
									| IDTKN LEFTBTKN INTVALTKN RIGHTBTKN ASSIGNTKN expstmt  { get_symbol($1, getContext(), "ary");};
									
iostmt            : READTKN var  { get_symbol($2, getContext(), "var");}
									| WRITETKN expstmt;
									
var               : identifier 
									| identifier LEFTBTKN INTVALTKN RIGHTBTKN;

identifier				: IDTKN;
			
expstmt           : expstmt compoperator exp
									| exp;

compoperator      : LTTKN | LTETKN | GTTKN | GTETKN | EQUALTKN | NOTEQUALTKN | ORTKN | ANDTKN;

exp               : exp PLUSTKN term 
									| exp MINUSTKN term 
									| term;

term    					: term TIMESTKN factor 
									| term DIVTKN factor 
									| factor;

values            : INTVALTKN 
									| DOUBLEVALTKN  
									| STRINGVALTKN   
									| TRUETKN  
									| FALSETKN;

factor            : LEFTPTKN exp RIGHTPTKN
									| var  { print("Pushing a var type into typeStack: %s\n", $1); pushType($1); get_symbol($1, getContext(), "var");}
									| values { print("Pushing constant type into typeStack: %s\n", $1); pushType($1); }
									| callstmt { print("Pushing function type into typeStack:%s\n", $1); pushType($1); ;

//faltaria checar que existen los args_context									
callstmt          : IDTKN LEFTPTKN args RIGHTPTKN  { get_symbol($1, "global", "func");};

args              : /* empty */ | arglist
arglist           : arglist COMMATKN exp | exp;

returnstmt        : RETURNFUNCTKN exp SEMICOLONTKN;
		
%%


int yyerror(char * message)
	
{ fprintf(outputFile,"Syntax error at line %d: %s\n",linecount,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}

char * parseA(void)
{ yyparse();
  return savedCode;
}
