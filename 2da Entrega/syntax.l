/*************************************/
/* File: matrushka.l                 */
/* Lex specifications for MATRUSHKA  */
/* Luis Loya                         */
/*************************************/

%{
#include "common.h"
//#include "y.tab.h"

char lexeme[MAXTOKENLEXEME+1];
int linecount = 1;
%}
%option yylineno


integer -?[0-9]+
double -?[0-9]+\.[0-9]+
string \"(\\.|[^\\"])*\"
identifier [a-zA-Z]+[a-zA-Z0-9_]*
whitespace [ \t]+
newline \n

/* Empezamos con las palabras reservadas */
/* Seguido de los operadores */
/* Seguido de los numeros */
/* Seguido de los identificadores */
%%
"if" return IFTKN;
"endi" return ENDIFTKN;
"else" return ELSETKN;
"func" return FUNCTKN;
"endf" return ENDFUNCTKN;
"return" return RETURNFUNCTKN;
"while" return WHILETKN;
"endw" return ENDWHILETKN;
"read" return READTKN;
"write" return WRITETKN;
"message" return MESSAGETKN;
"matrushka" return MATRUSHKATKN;
"endm" return ENDMATRUSHKATKN;
"int" return INTTKN;
"double" return DOUBLETKN;
"string" return STRINGTKN;
"bool" return BOOLTKN;
"true" return TRUETKN;
"false" return FALSETKN;
"=" return ASSIGNTKN;
"+" return PLUSTKN;
"-" return MINUSTKN;
"*" return TIMESTKN;
"/" return DIVTKN;
"<" return LTTKN;
"<=" return LTETKN;
">" return GTTKN;
">=" return GTETKN;
"==" return EQUALTKN;
"!=" return NOTEQUALTKN;
"<<" return ASSIGNSECRETTKN;
"||" return ORTKN;
"&&" return ANDTKN;
"(" return LEFTPTKN;
")" return RIGHTPTKN;
";" return SEMICOLONTKN;
"[" return LEFTBTKN;
"]" return RIGHTBTKN;
"," return COMMATKN;
":" return OPENBLOCKTKN;
{integer} return INTVALTKN;
{double} return DOUBLEVALTKN;
{string} return STRINGVALTKN;
{identifier} return IDTKN;
{whitespace} {/* Ignore it */};
{newline} {linecount++;}
%%

int yywrap()
{
        return 1;
} 


void printToken( Token token, const char* lexeme ){ 
	switch (token){ 
		case IFTKN: fprintf(outputFile, "reserved word: %s\n",lexeme); break;
    case ELSETKN: fprintf(outputFile, "reserved word: %s\n",lexeme); break;
    case ENDIFTKN: fprintf(outputFile, "reserved word: %s\n",lexeme); break;
		case FUNCTKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case ENDFUNCTKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case RETURNFUNCTKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
    case WHILETKN: fprintf(outputFile, "reserved word: %s\n",lexeme); break;
    case ENDWHILETKN: fprintf(outputFile, "reserved word: %s\n",lexeme); break;
    case READTKN: fprintf(outputFile, "reserved word: %s\n",lexeme); break;
    case WRITETKN: fprintf(outputFile, "reserved word: %s\n",lexeme); break;
		case INTTKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case DOUBLETKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case STRINGTKN:  fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case BOOLTKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case MATRUSHKATKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case ENDMATRUSHKATKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
		case MESSAGETKN: fprintf(outputFile, "reserved word: %s\n", lexeme); break;
    case ASSIGNTKN: fprintf(outputFile,"=\n"); break;
    case PLUSTKN: fprintf(outputFile,"+\n"); break;
    case MINUSTKN: fprintf(outputFile,"-\n"); break;
    case TIMESTKN: fprintf(outputFile,"*\n"); break;
    case DIVTKN: fprintf(outputFile,"/\n"); break;
    case LTTKN: fprintf(outputFile,"<\n"); break;
		case LTETKN: fprintf(outputFile,"<=\n"); break;
		case GTTKN: fprintf(outputFile,">\n"); break;
		case GTETKN: fprintf(outputFile,">=\n"); break;
    case EQUALTKN: fprintf(outputFile,"==\n"); break;
		case NOTEQUALTKN: fprintf(outputFile,"!=\n"); break;
		case ASSIGNSECRETTKN: fprintf(outputFile,"<<\n"); break;
		case ORTKN: fprintf(outputFile,"||\n"); break;
		case ANDTKN: fprintf(outputFile,"&&\n"); break;
    case LEFTPTKN: fprintf(outputFile,"(\n"); break;
    case RIGHTPTKN: fprintf(outputFile,")\n"); break;
    case SEMICOLONTKN: fprintf(outputFile,";\n"); break;
		case LEFTBTKN: fprintf(outputFile,"[\n"); break;
		case RIGHTBTKN: fprintf(outputFile,"]\n"); break;
		case COMMATKN: fprintf(outputFile,",\n"); break;
		case OPENBLOCKTKN: fprintf(outputFile,":\n"); break;
    case ENDFILETKN: fprintf(outputFile,"EOF\n"); break;
    case INTVALTKN: fprintf(outputFile, "INTEGER val = %s\n",lexeme); break;
		case DOUBLEVALTKN: fprintf(outputFile, "DOUBLE val = %s\n",lexeme); break;
		case STRINGVALTKN: fprintf(outputFile, "STRING val = %s\n",lexeme); break;
		case TRUETKN:  fprintf(outputFile, "BOOL val = %s\n",lexeme); break;
		case FALSETKN: fprintf(outputFile, "BOOL val = %s\n",lexeme); break;
    case IDTKN: fprintf(outputFile, "IDENTIFIER, name = %s\n",lexeme); break;
    default: fprintf(outputFile,"undefined token: %d\n",token);
  }
}


Token nextToken(void){ 
  Token token;
  yyin = inputFile;
  yyout = outputFile;
  token = yylex();
  strncpy(lexeme,yytext,MAXTOKENLEXEME);
  fprintf(outputFile,"%4d: ",linecount);
  printToken(token,lexeme);
  return token;
}
