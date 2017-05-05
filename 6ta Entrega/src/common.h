#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXTOKENLEXEME 112
extern char lexeme[MAXTOKENLEXEME+1];
#define ENDFILETKN 0

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef int Token; 

extern FILE* inputFile;
extern FILE* outputFile;
extern int g_lineno;
extern int yyparse(void);

#endif