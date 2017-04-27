/*************************************/
/* File: matrushka.l                 */
/* Lex specifications for MATRUSHKA  */
/* Luis Loya                         */
/*************************************/

%{
#include "common.h"
#include "y.tab.c"

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
comments \/\/.*

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
"int" yylval = strdup("int"); return INTTKN;
"double" yylval = strdup("double"); return DOUBLETKN;
"string" yylval = strdup("string"); return STRINGTKN;
"bool" yylval = strdup("bool"); return BOOLTKN;
"cipher" return CIPHERTKN;
"true" yylval = strdup(yytext); return FALSETKN;
"false"  yylval = strdup(yytext); return FALSETKN;
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
{integer} yylval = strdup(yytext); return INTVALTKN;
{double} yylval = strdup(yytext); return DOUBLEVALTKN;
{string} yylval = strdup(yytext); return STRINGVALTKN;
{identifier} yylval = strdup(yytext); return IDTKN;
{whitespace} {/* Ignore it */};
{comments} {/*printf("Commnet: %s\n", yytext);*/ };
{newline} {linecount++;}
%%

int yywrap()
{
        return 1;
} 
