#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER
#include "y.tab.h"
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
extern int lineno;
#endif
#define MAXTOKENLEXEME 112
extern char lexeme[MAXTOKENLEXEME+1];
char *parse(void);
#endif