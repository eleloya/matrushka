/*************************************/
/* File: matrushka.l                 */
/* Lex specifications for MATRUSHKA  */
/* Luis Loya                         */
/*************************************/

%{
#include "common.h"
#include "y.tab.c"

char lexeme[MAXTOKENLEXEME+1];
int g_lineno = 1;
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
"bool" yylval = strdup("boolean"); return BOOLTKN;
"cipher" return CIPHERTKN;
"true" yylval = strdup(yytext); return FALSETKN;
"false"  yylval = strdup(yytext); return FALSETKN;
"=" yylval = strdup(yytext); return ASSIGNTKN;
"+" yylval = strdup(yytext); return PLUSTKN;
"-" yylval = strdup(yytext); return MINUSTKN;
"*" yylval = strdup(yytext); return TIMESTKN;
"/" yylval = strdup(yytext); return DIVTKN;
"<" yylval = strdup("<"); return LTTKN;
"<=" yylval = strdup("<="); return LTETKN;
">" yylval = strdup(">"); return GTTKN;
">=" yylval = strdup(">="); return GTETKN;
"==" yylval = strdup("=="); return EQUALTKN;
"!=" yylval = strdup("!="); return NOTEQUALTKN;
"<<" yylval = strdup("<<"); return ASSIGNSECRETTKN;
"||" yylval = strdup("||"); return ORTKN;
"&&" yylval = strdup("&&"); return ANDTKN;
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
{newline} {g_lineno++;}
%%

int yywrap()
{
        return 1;
} 
