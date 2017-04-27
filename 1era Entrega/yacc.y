%{
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

%}


%token IFTKN 
%token ENDIFTKN 
%token ELSETKN FUNCTKN ENDFUNCTKN RETURNFUNCTKN WHILETKN ENDWHILETKN READTKN WRITETKN IDTKN
%token MATRUSHKATKN ENDMATRUSHKATKN MESSAGETKN
%token INTTKN DOUBLETKN STRINGTKN BOOLTKN
%token INTVALTKN DOUBLEVALTKN STRINGVALTKN TRUETKN FALSETKN
%token ASSIGNTKN PLUSTKN MINUSTKN TIMESTKN DIVTKN LTTKN LTETKN GTTKN GTETKN EQUALTKN NOTEQUALTKN ASSIGNSECRETTKN ORTKN ANDTKN
%token LEFTPTKN RIGHTPTKN SEMICOLONTKN LEFTBTKN RIGHTBTKN COMMATKN OPENBLOCKTKN


%%
program   				: a_gotomain vardeclarations functions matrushkas
									| a_gotomain functions matrushkas
									| a_gotomain vardeclarations matrushkas
									| a_gotomain matrushkas;
									
a_gotomain				: { savedCode = "perro"; }
						
vardeclarations   : vardeclarations vardeclaration
							    | vardeclaration SEMICOLONTKN;

vardeclaration    : type IDTKN
								  | type IDTKN LEFTBTKN INTVALTKN RIGHTBTKN; /* int arreglo[3]; */

type   						: INTTKN | DOUBLETKN | STRINGTKN | BOOLTKN;

functions         : functions function
									| function;

function					: FUNCTKN type OPENBLOCKTKN IDTKN LEFTPTKN params RIGHTPTKN OPENBLOCKTKN vardeclarations blockstmts returnstmt ENDFUNCTKN;
   					 			| FUNCTKN type OPENBLOCKTKN IDTKN LEFTPTKN params RIGHTPTKN OPENBLOCKTKN blockstmts returnstmt ENDFUNCTKN;
   					 			| FUNCTKN type OPENBLOCKTKN IDTKN LEFTPTKN params RIGHTPTKN OPENBLOCKTKN returnstmt ENDFUNCTKN;


params						: /* empty */ | paramlist;

paramlist         : paramlist COMMATKN param 
									| param;

param             : type IDTKN;  /* no arrays as parameters... yet*/

blockstmts        : blockstmts blockstmt
									| blockstmt;

blockstmt         : assignstmt | ifstmt | iterstmt | iostmt | callstmt;

ifstmt            : IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDIFTKN
 									| IFTKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ELSETKN blockstmts ENDIFTKN;

iterstmt					: WHILETKN LEFTPTKN expstmt RIGHTPTKN OPENBLOCKTKN blockstmts ENDWHILETKN;

assignstmt        : IDTKN ASSIGNTKN expstmt SEMICOLONTKN
									| IDTKN LEFTBTKN INTVALTKN RIGHTBTKN ASSIGNTKN expstmt SEMICOLONTKN;
									
iostmt            : READTKN var SEMICOLONTKN
									| WRITETKN expstmt SEMICOLONTKN;
									
var               : identifier { $$=$1;} 
									| identifier LEFTBTKN INTVALTKN RIGHTBTKN {$$=$1;};

identifier				: IDTKN { $$= $1;}
			
expstmt           : expstmt compoperator exp
									| exp;

compoperator      : LTTKN | LTETKN | GTTKN | GTETKN | EQUALTKN | NOTEQUALTKN | ORTKN | ANDTKN;

exp               : exp PLUSTKN term {  printf("OPERATION ( + ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",$1,$3); pushType($1); pushType($3); checkType(1); }
									| exp MINUSTKN term {   printf("OPERATION ( - ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",$1,$3); pushType($1); pushType($3); checkType(1); }
									| term { $$=$1; };

term    					: term TIMESTKN factor {  printf("OPERATION ( * ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",$1,$3); pushType($1); pushType($3); checkType(1);  }
									| term DIVTKN factor {  printf("OPERATION ( / ) %s,%s\nAQUI DEBERIAMOS CHECAR EN EL SYMBOL TABLE LOS TIPOS\n\n",$1,$3); pushType($1); pushType($3); checkType(1); }
									| factor { $$=$1;};

values            : INTVALTKN {$$=$1;}
									| DOUBLEVALTKN  {$$=$1;} 
									| STRINGVALTKN   {$$=$1;}
									| TRUETKN   {$$=$1;}
									| FALSETKN  {$$=$1;};

factor            : LEFTPTKN exp RIGHTPTKN
									| var {$$=$1;}
									| values {$$=$1;}
									| callstmt {$$=$1;}
									
callstmt          : IDTKN LEFTPTKN args RIGHTPTKN {$$=$1;};

args              : /* empty */ | arglist
arglist           : arglist COMMATKN exp | exp;

returnstmt        : RETURNFUNCTKN exp SEMICOLONTKN
									| RETURNFUNCTKN SEMICOLONTKN;
									
matrushkas        : MATRUSHKATKN LEFTPTKN margs RIGHTPTKN OPENBLOCKTKN vardeclarations mbody ENDMATRUSHKATKN
									| MATRUSHKATKN LEFTPTKN margs RIGHTPTKN OPENBLOCKTKN mbody ENDMATRUSHKATKN;

margs             : STRINGVALTKN COMMATKN STRINGVALTKN;

mbody             : mmessages
									| matrushkas;

mmessages         : mmessages mmessage
									| mmessage;
									
mmessage          : MESSAGETKN ASSIGNSECRETTKN exp { checkType(5); } SEMICOLONTKN | assignstmt | ifstmt | iterstmt | iostmt | callstmt;
									
		
%%


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
