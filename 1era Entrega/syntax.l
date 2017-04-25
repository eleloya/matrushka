/*************************************/
/* File: matrushka.l                 */
/* Lex specifications for MATRUSHKA  */
/* Luis Loya                         */
/*************************************/

%{
#include <stdio.h>
#include "y.tab.h"
int linecount = 0;
%}
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