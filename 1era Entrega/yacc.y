%{
#define YYPARSER
#include "common.h"

static char* savedCode; /* stores code for later return */

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,lexeme);
  Error = TRUE;
  return 0;
}

static int yylex(void)
{ return nextToken(); }
  
main()
{
        yyparse();
} 

char * parse(void)
{ yyparse();
  return savedCode;
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
									| a_gotomain matrushkas;
									
a_gotomain				: { savedCode = copyString("goto, , ,main"); }
						
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
									
var               : IDTKN
									| IDTKN LEFTBTKN INTVALTKN RIGHTBTKN;
			
expstmt           : expstmt compoperator exp
									| exp;

compoperator      : LTTKN | LTETKN | GTTKN | GTETKN | EQUALTKN | NOTEQUALTKN | ORTKN | ANDTKN;

exp               : exp PLUSTKN term
									| exp MINUSTKN term
									| term;

term    					: term TIMESTKN factor
									| term DIVTKN factor
									| factor;

values            : INTVALTKN | DOUBLEVALTKN | STRINGVALTKN | TRUETKN | FALSETKN;

factor            : LEFTPTKN exp RIGHTPTKN
									| var
									| values
									| callstmt
									
callstmt          : IDTKN LEFTPTKN args RIGHTPTKN;

args              : /* empty */ | arglist
arglist           : arglist COMMATKN exp | exp;

returnstmt        : RETURNFUNCTKN exp SEMICOLONTKN
									| RETURNFUNCTKN SEMICOLONTKN;
									
matrushkas        : MATRUSHKATKN LEFTPTKN margs RIGHTPTKN OPENBLOCKTKN mbody ENDMATRUSHKATKN;

margs             : STRINGVALTKN COMMATKN STRINGVALTKN;

mbody             : mmessages
									| matrushkas;

mmessages         : mmessages mmessage
									| mmessage;
									
mmessage          : MESSAGETKN ASSIGNSECRETTKN exp SEMICOLONTKN;
									
		
%%