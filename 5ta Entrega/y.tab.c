/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IFTKN = 258,
     ENDIFTKN = 259,
     ELSETKN = 260,
     FUNCTKN = 261,
     ENDFUNCTKN = 262,
     RETURNFUNCTKN = 263,
     WHILETKN = 264,
     ENDWHILETKN = 265,
     READTKN = 266,
     WRITETKN = 267,
     CIPHERTKN = 268,
     INTTKN = 269,
     DOUBLETKN = 270,
     STRINGTKN = 271,
     BOOLTKN = 272,
     IDTKN = 273,
     INTVALTKN = 274,
     DOUBLEVALTKN = 275,
     STRINGVALTKN = 276,
     TRUETKN = 277,
     FALSETKN = 278,
     ASSIGNTKN = 279,
     PLUSTKN = 280,
     MINUSTKN = 281,
     TIMESTKN = 282,
     DIVTKN = 283,
     LTTKN = 284,
     LTETKN = 285,
     GTTKN = 286,
     GTETKN = 287,
     EQUALTKN = 288,
     NOTEQUALTKN = 289,
     ASSIGNSECRETTKN = 290,
     ORTKN = 291,
     ANDTKN = 292,
     LEFTPTKN = 293,
     RIGHTPTKN = 294,
     SEMICOLONTKN = 295,
     LEFTBTKN = 296,
     RIGHTBTKN = 297,
     COMMATKN = 298,
     OPENBLOCKTKN = 299
   };
#endif
/* Tokens.  */
#define IFTKN 258
#define ENDIFTKN 259
#define ELSETKN 260
#define FUNCTKN 261
#define ENDFUNCTKN 262
#define RETURNFUNCTKN 263
#define WHILETKN 264
#define ENDWHILETKN 265
#define READTKN 266
#define WRITETKN 267
#define CIPHERTKN 268
#define INTTKN 269
#define DOUBLETKN 270
#define STRINGTKN 271
#define BOOLTKN 272
#define IDTKN 273
#define INTVALTKN 274
#define DOUBLEVALTKN 275
#define STRINGVALTKN 276
#define TRUETKN 277
#define FALSETKN 278
#define ASSIGNTKN 279
#define PLUSTKN 280
#define MINUSTKN 281
#define TIMESTKN 282
#define DIVTKN 283
#define LTTKN 284
#define LTETKN 285
#define GTTKN 286
#define GTETKN 287
#define EQUALTKN 288
#define NOTEQUALTKN 289
#define ASSIGNSECRETTKN 290
#define ORTKN 291
#define ANDTKN 292
#define LEFTPTKN 293
#define RIGHTPTKN 294
#define SEMICOLONTKN 295
#define LEFTBTKN 296
#define RIGHTBTKN 297
#define COMMATKN 298
#define OPENBLOCKTKN 299




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

#include "util/string_stack.c"
#include "util/int_stack.c"
#include "util/hash.c"
#define YYPARSER 
#define YYSTYPE char *
#define VERBOSE 1
#define MAX_TMP_VARIABLES 1024
#define MAX_PROGRAM_SIZE 1000

/****************************************************************************/
/**                                                                        **/
/**                  GLOBAL VARIABLES FOR PARSER                           **/
/**                                                                        **/
/****************************************************************************/
		
static stack typeStack;
static stack operandStack;
static stack operatorStack;
static stack dimensionStack;
static stack cipherStack;
static int_stack jumpStack;
static struct symbol SymbolTable[SYMBOL_TABLE_SIZE];
static char* scope;
static char* IRCode[MAX_PROGRAM_SIZE]; // TO-DO. Do this structure variable in size.


static int operatorStackFirstTime = TRUE;
static int operandStackFirstTime = TRUE;
static int temporals_counter = 1;
static int program_counter = 0;

/****************************************************************************/
/**                                                                        **/
/**                         AUXILIARY  FUNCTIONS                           **/
/**                                                                        **/
/****************************************************************************/

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

char *getTypeFromSymbol(char *symbol, char *scope){
	//TO-DO check for nulls on symbol
	return memberType(SymbolTable, symbol, scope);
}

void DBG_PrintSymbolTable(struct symbol hashtable[]){
	printf("\nSYMBOL TABLE\n");
	printf("%15s  %10s  ------   -----  -------  ----\n","----------","----------");
	printf("%15s  %-10s  type     kind   address  num\n","identifier", "context");
	printf("%15s  %10s  ------   -----  -------  ----\n","----------","----------");
	
  for (int i=0; i< SYMBOL_TABLE_SIZE ; i++){
      if (NULL != hashtable[i].value)
				printf("%15s  %10s  %7s  %5s  %7d  %d\n", hashtable[i].value, hashtable[i].contextName, hashtable[i].typeName, hashtable[i].symbolKind, hashtable[i].memoryLocation, hashtable[i].number);
  }
}

void DBG_PrintIRCode(){
	printf("\nIR CODE\n");
	for(int i=0;i<program_counter;i++)
		printf("%5d: %s\n",i, IRCode[i]);
}

int PRG_SaveIRCode(){ 
	for(int i=0;i<program_counter;i++)
		fprintf(outputFile,"%s\n",IRCode[i]);
  return 1;
}

/****************************************************************************/
/**                                                                        **/
/**                  ATTRIBUTE GRAMMAR FUNCTIONS                           **/
/**                                                                        **/
/****************************************************************************/

//Recibe un operador valido de LEX. + - * / < > == != <= >= || &&
//Tambien en operand recibe el tipo de los operandos (int,int) (string,int)
// Al parecerer al de la derecha se le opera lo de la izquierda
char * PRG_SemanticCube(char* op, char *operand1, char *operand2){
		
	char *result_type;
	char *opcode;
	opcode = strdup("ERR");
	// (boolean, boolean)
	if(strcmp(operand1,"boolean")==0 && strcmp(operand2,"boolean")==0){
		if(strcmp(op,"==")==0){
			opcode = strdup("EQLV");
			result_type = strdup("boolean");
		}else if(strcmp(op,"!=")==0){
			opcode = strdup("NEQL");
			result_type = strdup("boolean");
		}else if(strcmp(op,"||")==0){
			opcode = strdup("ORVL");
			result_type = strdup("boolean");
		}else if(strcmp(op,"&&")==0){
			opcode = strdup("ANDV");
			result_type = strdup("boolean");
		}else{
			result_type = strdup("error");
		}
		stackPush(&operatorStack,opcode);
		return result_type;
	}
	
	// (int, int)
	if(strcmp(operand1,"int")==0 && strcmp(operand2,"int")==0){
		if(strcmp(op,"||")==0){
			result_type = strdup("error");
		}else if(strcmp(op,"&&")==0){
			result_type = strdup("error");
		}else if(strcmp(op,"==")==0){
			opcode = strdup("EQLV");
			result_type = strdup("boolean");
		}else if(strcmp(op,"!=")==0){
			opcode = strdup("NEQL");
			result_type = strdup("boolean");		
		}else if(strcmp(op,"<=")==0){
			opcode = strdup("LTEV");
			result_type = strdup("boolean");
		}else if(strcmp(op,">=")==0){
			opcode = strdup("GTEV");
			result_type = strdup("boolean");
		}else if(strcmp(op,"<")==0){
			opcode = strdup("LTVL");
			result_type = strdup("boolean");
		}else if(strcmp(op,">")==0){
			opcode = strdup("GTVL");
			result_type = strdup("boolean");
		}else if(strcmp(op,"/")==0){
			opcode = strdup("IDIV");
			result_type = strdup("int");
		}else if(strcmp(op,"*")==0){
			opcode = strdup("IMUL");
			result_type = strdup("int");
		}else if(strcmp(op,"+")==0){
			opcode = strdup("IADD");
			result_type = strdup("int");
		}else if(strcmp(op,"-")==0){
			opcode = strdup("ISUB");
			result_type = strdup("int");
		}else{
			result_type = strdup("error");
		}
		stackPush(&operatorStack,opcode);
		return result_type;
	}
	
	// (double, double) || (double, int) || (int, double)
	if( (strcmp(operand1,"double")==0 && strcmp(operand2,"double")==0) ||
		(strcmp(operand1,"double")==0 && strcmp(operand2,"int")==0) ||
	    (strcmp(operand1,"int")==0 && strcmp(operand2,"double")==0) ){
		if(strcmp(op,"||")==0){
			result_type = strdup("error");
		}else if(strcmp(op,"&&")==0){
			result_type = strdup("error");
		}else if(strcmp(op,"==")==0){
			opcode = strdup("EQLV");
			result_type = strdup("boolean");
		}else if(strcmp(op,"!=")==0){
			opcode = strdup("NEQL");
			result_type = strdup("boolean");		
		}else if(strcmp(op,"<=")==0){
			opcode = strdup("LTEV");
			result_type = strdup("boolean");
		}else if(strcmp(op,">=")==0){
			opcode = strdup("GTEV");
			result_type = strdup("boolean");
		}else if(strcmp(op,"<")==0){
			opcode = strdup("LTVL");
			result_type = strdup("boolean");
		}else if(strcmp(op,">")==0){
			opcode = strdup("GTVL");
			result_type = strdup("boolean");
		}else if(strcmp(op,"/")==0){
			opcode = strdup("DDIV");
			result_type = strdup("double");
		}else if(strcmp(op,"*")==0){
			opcode = strdup("DMUL");
			result_type = strdup("double");
		}else if(strcmp(op,"+")==0){
			opcode = strdup("DADD");
			result_type = strdup("double");
		}else if(strcmp(op,"-")==0){
			opcode = strdup("DSUB");
			result_type = strdup("double");
		}else{
			result_type = strdup("error");
		}
		stackPush(&operatorStack,opcode);
		return result_type;
	}
	
	// (string, string)
	if(strcmp(operand1,"string")==0 && strcmp(operand2,"string")==0){
		if(strcmp(op,"==")==0){
			opcode = strdup("EQST");
			result_type = strdup("boolean");
		}else if(strcmp(op,"!=")==0){
			opcode = strdup("NEQS");
			result_type = strdup("boolean");
		}else if(strcmp(op,"+")==0){
			opcode = strdup("SADD");
			result_type = strdup("string");
		}else{
			opcode = strdup("ERRR");
			result_type = strdup("error");
		}
		stackPush(&operatorStack,opcode);
		return result_type;
	}
	
	opcode = strdup("ERRR");
	stackPush(&operatorStack,opcode);			
	return strdup("error");
}

/*
* Used in the grammar rules (program,function) for changing the scope.
* It is important for example to save a new symbol.
* The program needs to know to wich scope the symbol belongs.
* Every time the grammar encounters a new "function" SetScope gets called.
*
*/
void PRG_SetScope(char *scopeName){
	if (NULL==scopeName){
		printf("LINE: %-4d  CALL: PRG_SetScope(NULL)\t", g_lineno);
		printf("FATAL: Null reference.\n");
		exit(EXIT_FAILURE);
	}
	
	if (strcmp(scopeName, "")==0){
		printf("LINE: %-4d  CALL: PRG_SetScope(\"\")\t", g_lineno);
		printf("FATAL: Can't set a empty scope\n");
		exit(EXIT_FAILURE);
	}
	
	if (scope!=NULL)
		free(scope);

	scope = strdup(scopeName);
	
	if(VERBOSE)
		printf("LINE: %-4d PGR_SetScope(%s)\n", g_lineno, scopeName);
}

/*
* Used in the grammar rules (param,vardeclaration,stmt) for checking current scope.
* Important before checking to wich scope should we save the symbol to.
*
*/
char * PRG_GetScope(){
	if(VERBOSE)
		printf("LINE: %-4d PGR_GetScope() -> %s\n", g_lineno, scope);
	
	return scope;
}

int PRG_GetFunctionVariablesNum(char *identifier){
	//Gotta search for all the identifiers wich context is that of "identifier"
	//return that but minus one
	int era_size = 0;
	//This takes a little while tho
	
	for(int i=0;i<SYMBOL_TABLE_SIZE;i++){
		if(NULL != SymbolTable[i].value){
			if(strcmp(SymbolTable[i].contextName,identifier)==0){
				era_size++;
			}
		}
	}	
	return era_size;
}

void PRG_ERAUpdate(){
	/* Esta rutina es para hacer anotaciones al final del IR_CODE
	   que el VM debe de leer */
	
	char *function_name;
	int function_era_size;
	char function_era_size_string[MAX_TMP_VARIABLES];
	
	IRCode[program_counter] = strdup(".data:");
	program_counter++;
	
	for(int i=0;i<SYMBOL_TABLE_SIZE;i++){
		if(NULL != SymbolTable[i].value){
			if(strcmp(SymbolTable[i].symbolKind,"func")==0){
				function_name = SymbolTable[i].value;
				function_era_size = PRG_GetFunctionVariablesNum(function_name);
				sprintf(function_era_size_string, "%d", function_era_size);
				
				IRCode[program_counter] = concat("era_size_",concat(function_name,concat(": ", function_era_size_string)));
				program_counter++;
			}
		}
	}
	
	
	
	//Esta rutina es para hacerlo inline en el IR_CODE
	/*
	char *function_name;
	int function_era_size;
	char *function_era_size_string;
	char *era_string;
	
	for(int i=0;i<SYMBOL_TABLE_SIZE;i++){
		if(NULL != SymbolTable[i].value){
			if(strcmp(SymbolTable[i].symbolKind,"func")==0){
				function_name = SymbolTable[i].value;
				function_era_size = PRG_GetFunctionVariablesNum(function_name);
				era_string = concat("*era_size_",concat(function_name,"*"));
				printf("%s: %d\n", function_name, function_era_size);
				//Now scan the IR For ocurrences of *era_size_FUNCNAME*
				//replace it with function_era_size
				for(int j=0;j<program_counter;j++){
					if(strstr(era_string,IRCode[j])){
						printf("On line %d there is a era_size reference for %s \n", j, era_string);
					}
				}
			}
		}
	}	

	*/
}

void PRG_SaveSymbol(char *typeName, char *identifierName, char *scopeName, char *symbolKind){
	int response;

	response = insert(SymbolTable, typeName, identifierName, scopeName, symbolKind);
	
	if(response!=0){
		printf("LINE: %-4d CALL: PRG_SaveSymbol(%s,%s,%s,%s)\n", g_lineno,typeName,identifierName, scopeName, symbolKind);
		printf("FATAL: Identifier was already previously declared \n");
		exit(EXIT_FAILURE);
	}
	
}

void PRG_GetSymbol(char *identifierName, char *scopeName, char *symbolKind){
	/*
	We look for the same identifier both in the given scope and the global scope.
	*/
	int response_func;
	int response_local;
	int response_global;
	char *kind;
	
	//Function needs its own logic
	if(strcmp(symbolKind,"func")==0){
		response_func = member(SymbolTable, identifierName, scopeName);
		kind = memberKind(SymbolTable, identifierName, scopeName);
		//  Check for identifierName existance on global scope
		//  Also check for identifierName to be of type "func" (maybe the user is calling a identifier in global that is not a func)
		if(response_func==0 || strcmp(kind,"func")!=0){
			printf("LINE: %-4d CALL: PRG_GetSymbol(%s,%s,%s)\n", g_lineno,identifierName, scopeName, symbolKind);
			printf("FATAL: Trying to call undeclared function\n");
			exit(EXIT_FAILURE);
		}
	}

	//Variables are search'd in both the local and global scope
	response_local  = member(SymbolTable, identifierName, scopeName);
	response_global = member(SymbolTable, identifierName, "global");
	int response_ary_local =  member(SymbolTable, concat(identifierName,"_0"), scopeName);
	int response_ary_global = member(SymbolTable, concat(identifierName,"_0"), "global");
	
	if( response_local==0 && response_global==0 && response_ary_local==0 && response_ary_global==0 ){
		printf("LINE: %-4d CALL: PRG_GetSymbol(%s,%s,%s)\n", g_lineno,identifierName, scopeName, symbolKind);
		printf("FATAL: Trying to access undeclared variable\n");
		exit(EXIT_FAILURE);
	}
	
	
	//printf("Checking for '%s' symbol existance on scope %s of type %s\n", identifierName, scopeName, symbolKind);
}

void PRG_Initialize(){
	PRG_SetScope("global");
	
	stackInit(&operandStack);
	stackInit(&typeStack);
	stackInit(&operatorStack);
	stackInit(&dimensionStack);
	int_stackInit(&jumpStack);
	init_hash_table(SymbolTable);
	
	for(int i=0;i<MAX_PROGRAM_SIZE;i++)
		IRCode[i] = NULL;
	
	char *instruction;
	instruction = strdup("ERAS *era_size_main*");
	IRCode[program_counter] = instruction;
	program_counter++;
	
	instruction = strdup("CALL _main");
	IRCode[program_counter] = instruction;
	program_counter++;
	
	instruction = strdup("");
	IRCode[program_counter] = instruction;
	program_counter++;
}

void PRG_PushCipher(char * cipher_algorithm, char * cipher_key){
	char *cipher_key_clean;
	static int cipher_first_time = TRUE;
	
	if(strstr(cipher_algorithm, "aes256")){
		cipher_algorithm = "-aes-256-cbc";
	}else if(strstr(cipher_algorithm, "blowfish")){
		cipher_algorithm = "-bf-cbc";
	}else if(strstr(cipher_algorithm, "des")){
		cipher_algorithm = "-des-cbc";
	}else{
		//ERROR
		printf("LINE: %-4d CALL: PRG_PushCipher(%s, %s)\n", g_lineno, cipher_algorithm, cipher_key);
		printf("FATAL: Unknow algorithm %s. Can only do aes256, blowfish and des \n", cipher_algorithm);
		exit(EXIT_FAILURE);
	}
	
	// Las strings llegan con todo y \"comillas\"
	// Esta subrutina las quita
	cipher_key_clean = strdup(cipher_key);
	cipher_key_clean = strtok(cipher_key_clean,"\"");

	if(cipher_first_time){
		stackInit(&cipherStack);
		cipher_first_time = FALSE;
	}
	//We push to the cipherStack on pairs 
	stackPush(&cipherStack, cipher_algorithm);
	stackPush(&cipherStack, cipher_key_clean);
}

void PRG_EncryptCode(){
	char *cipher_algorithm;
	char *cipher_key;
	char *command;
	char *tmp_string[2];
	
	while(cipherStack.size!=0){
		cipher_key = stackPop(&cipherStack);
		cipher_algorithm = stackPop(&cipherStack);
		
		//This is other level magic 
		tmp_string[0] = concat("openssl enc -a ", cipher_algorithm);
		command = strdup(tmp_string[0]);
		free(tmp_string[0]);
		tmp_string[0] = concat(" -k ", cipher_key);
		tmp_string[1] = concat(command, tmp_string[0]);
		free(tmp_string[0]);
		tmp_string[0] = concat(tmp_string[1], " -out /tmp/babushka.sec");
		free(command);
		free(tmp_string[1]);
		command = strdup(tmp_string[0]);   // open ssl enc -a -aes-256-cbc -k password
		free(tmp_string[0]);
		
		printf("\n%s\n", command);
		
		FILE *crypto_engine = popen(command, "w");
		for(int i=0;i<program_counter;i++){
			fprintf(crypto_engine, "%s\n", IRCode[i]);
		}
	  pclose(crypto_engine);
		
		//Now the encrypted code is in /tmp/babushka.sec
		//We must read it back and replace IRCode
		FILE *cryptedfile;
		char * buffer = (char *)malloc(100 * sizeof(char));
		size_t len = 0;
		ssize_t linelen;
		
		cryptedfile = fopen("/tmp/babushka.sec","r");
		if (cryptedfile==NULL){
			printf("LINE: %-4d  CALL: PRG_EncryptCode()\n", g_lineno);
			printf("FATAL: Could not open encrypted file /tmp/babushka.sec\n");
			exit(EXIT_FAILURE);
		}
		
		//Here we are going to replace IRCode with wathever it is on babushka.sec
		program_counter = 0;
		if(strcmp(cipher_algorithm,"-aes-256-cbc")==0)
			IRCode[program_counter] = strdup("ASKP AES");
		if(strcmp(cipher_algorithm,"-des-cbc")==0)
			IRCode[program_counter] = strdup("ASKP DES");
		if(strcmp(cipher_algorithm,"-bf-cbc")==0)
			IRCode[program_counter] = strdup("ASKP BLOWFISH");
		program_counter++;
		while ((linelen = getline(&buffer,&len,cryptedfile))>0){
			buffer[strlen(buffer) - 1] = 0;
			IRCode[program_counter] = strdup(buffer);
			program_counter++;
		}
		
		fclose(cryptedfile);
		free(buffer);
		
		//Now we delete the file /tmp/babushka.sec
	}
}

/*
* Used in the grammar rules (expcmp,exp,term,factor) for semantic analysis.
*
*/

//TO-DO Meter estos dos a EXP_PushOperand
void pushType(char *value, char *symbolKind){
	char *factorType;
	
	
	if(strcmp(symbolKind,"const")==0){ // then is a constant
		factorType = getTypeFromValue(value);
		//printf("Retrived type for %s is %s\n\n", value, factorType);
	}else{ // then is a variable or a function
		factorType = memberType(SymbolTable, value, PRG_GetScope());
		if(!factorType)
			factorType = memberType(SymbolTable, concat(value,"_0"), PRG_GetScope());
		//printf("Retrived type for %s is %s in scope: %s\n\n", value, factorType, PRG_GetScope());
	}
		
	// We must transform the type into a int because these stack only holds integers
	stackPush(&typeStack,factorType);
}

void pushOperand(char *operand, char *kind){
	int offset;
	char offset_string[MAX_PROGRAM_SIZE];
	
	

	//A lo mejor deberia checar que sea permitido. Pero no pasarian por flex ni bison...
	if(strcmp(kind,"func")==0){
		stackPush(&operandStack, operand);
	}else if(strcmp(kind,"const")==0){
		stackPush(&operandStack, operand);
	}else{
		
	//Else means that it is not a function, it is not a constnat.
	//So it means it must be within reach of the stack.
	//We can calculate that if we know the index of the variable in the stack
	offset = memberNumber(SymbolTable, operand, PRG_GetScope());
	sprintf(offset_string, "%d", offset);

	int response_global = member(SymbolTable, operand, "global");
	int response_local = member(SymbolTable, operand, PRG_GetScope());
	int response_ary_global = member(SymbolTable, concat(operand,"_0"), PRG_GetScope());
	int response_ary_local = member(SymbolTable, concat(operand,"_0"), PRG_GetScope());
	if(response_local){
			offset = memberNumber(SymbolTable, operand, PRG_GetScope());	
			sprintf(offset_string, "%d", offset);
			operand = concat("(",concat("\%STACK",concat("+",concat(offset_string,")"))));
	}else if(response_global){
		offset = memberNumber(SymbolTable, operand, "global");	
		sprintf(offset_string, "%d", offset);
		operand = concat("(",concat("\%GLOBALS",concat("+",concat(offset_string,")"))));
	}else if(response_ary_local){
		offset = memberNumber(SymbolTable, concat(operand,"_0"), PRG_GetScope());	
		sprintf(offset_string, "%d", offset);
		operand = concat("[",concat("\%STACK",concat("+",concat(offset_string,"]"))));
	}else if(response_ary_global){
		offset = memberNumber(SymbolTable, concat(operand,"_0"), "global");	
		sprintf(offset_string, "%d", offset);
		operand = concat("[",concat("\%GLOBALS",concat("+",concat(offset_string,"]"))));
	}
	
	stackPush(&operandStack, operand);	
	}
}

void EXP_PushOperand(char *operand, char *symbolKind){
	//TO-DO Check for NULLS
	

	//Check for the existance of a variable before even continuing.
	if(strcmp(symbolKind,"var")==0)
		PRG_GetSymbol(operand, PRG_GetScope(), "var"); 

	//Later is the same for both expressions
	pushType(operand, symbolKind); 
	pushOperand(operand, symbolKind);
	
	if(VERBOSE)
		printf("LINE: %-4d EXP_PushOperand(%s,%s)\n", g_lineno, operand,symbolKind);
}

void EXP_PushOperator(char *op){
	//Always checking
	if (NULL==op){
		printf("LINE: %-4d  CALL: EXP_PushOperator(NULL)\n", g_lineno);
		printf("FATAL: Null reference.\n");
		exit(EXIT_FAILURE);
	}
	
	stackPush(&operatorStack,op);
	
	if(VERBOSE)
		printf("LINE: %-4d EXP_PushOperator(%s)\n", g_lineno, op);	
}

void IR_AddGotoF(char *operand){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddGotoF(%s)\n", g_lineno, operand);
	
	char *instruction = concat("GTOF ", operand);
	IRCode[program_counter] = instruction;
	int_stackPush(&jumpStack, program_counter);
	program_counter++;
}

void IR_AddASSIGN(char *identifier, char *expression){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddASSIGN(%s,%s)\n", g_lineno, identifier,expression);
	// "= " + expression + " " + identifier
	// = T1 A
	char * instruction = concat("MOVE ", expression);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, identifier);
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeFUNCTION(char *identifier){
	char *instruction = concat("_", identifier);
	instruction = concat(instruction, ":");
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeFUNCTIONEND(){
	char *instruction;
	
	//TO-DO Hacer la instruccion de termino function, dependiente del tipo
	//ENDI, ENDD, ENDS, ENDB
	//Asi sabemos que return dar por default
	
	// Ponemos un RET por si las moscas y la funcion no declaro un return
	instruction = strdup("ENDF");
	IRCode[program_counter] = instruction;
	program_counter++;


	instruction = strdup("");
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_AddIOREAD(char * identifier){
	char *identifier_type;
	char *instruction;
	
	if(VERBOSE)
		printf("LINE: %-4d IR_AddIOREAD(%s)\n", g_lineno, identifier);
	//The intermiadiate opcode on the other hand would probably need to be special for each kind of variable
	identifier_type = getTypeFromSymbol(identifier, PRG_GetScope());
	
	int offset;	
	char offset_string[MAX_PROGRAM_SIZE];
	char *offset_identifier;
	int response_global = member(SymbolTable, identifier, "global");
	
	if(response_global){
		offset = memberNumber(SymbolTable, identifier, "global");	
		sprintf(offset_string, "%d", offset);
		offset_identifier = concat("(",concat("\%GLOBALS",concat("+",concat(offset_string,")"))));
	}else{
		offset = memberNumber(SymbolTable, identifier, PRG_GetScope());	
		sprintf(offset_string, "%d", offset);
		offset_identifier = concat("(",concat("\%STACK",concat("+",concat(offset_string,")"))));
	}

	if(strcmp(identifier_type,"int")==0){
		instruction = concat("IGET ", offset_identifier);
	}else if(strcmp(identifier_type,"double")==0){
		instruction = concat("DGET ", offset_identifier);
	}else if(strcmp(identifier_type,"boolean")==0){
		instruction = concat("BGET ", offset_identifier);
	}else if(strcmp(identifier_type,"string")==0){
		instruction = concat("SGET ", offset_identifier);
	}
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeIOWRITE(){
	char *expression_type;
	char *expression;
	char *instruction;
	
	//Semantic Check
	//nada, cero, nothing, no needed
	expression_type = stackPop(&typeStack);
	expression = stackPop(&operandStack);
	
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeIOWRITE(%s)\n", g_lineno, expression);
	
	
	//I will not make a IR_AddIOWRITE. I can keep it here just fine.
	if(strcmp(expression_type,"int")==0){
		instruction = concat("IPUT ", expression);
	}else if(strcmp(expression_type,"double")==0){
		instruction = concat("DPUT ", expression);
	}else if(strcmp(expression_type,"boolean")==0){
		instruction = concat("BPUT ", expression);
	}else if(strcmp(expression_type,"string")==0){
		instruction = concat("SPUT ", expression);
	}
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeIOREAD(char *identifier){
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeIOREAD(%s)\n", g_lineno, identifier);	
	
	//Semantic Check
	//Look for the identifier to be declared previously in the symbol table
	//Otherwise were would we save what we read
	//This is an easy one, is it not? ;)
	PRG_GetSymbol(identifier, PRG_GetScope(), "var"); 
	
	
	IR_AddIOREAD(identifier);
}

void IR_MakeARGYASSIGN(char *identifier){
	char *identifier_type;
	char *expression_type;
	char *expression;
	
	char *index_expression;
	//Semantic chec
	//Look for the identifier to be declared previously
	PRG_GetSymbol(concat(identifier,"_0"), PRG_GetScope(), "var"); 
	
	identifier_type = getTypeFromSymbol(concat(identifier,"_0"), PRG_GetScope());
	expression_type = stackPop(&typeStack);
	if(strcmp(identifier_type,expression_type)!=0){
		printf("LINE: %-4d CALL: IR_MakeARGYASSIGN(%s)\n", g_lineno, identifier);
		printf("FATAL: Type mismatch. Trying to assign %s to an array \"%s\" of type %s \n", expression_type, identifier, identifier_type);
		exit(EXIT_FAILURE);
	}
	
	//The expression to assign
	expression = stackPop(&operandStack);
	
	int offset;	
	char offset_string[MAX_PROGRAM_SIZE];

	//This gives use the base address for the array
	int response_global = member(SymbolTable, concat(identifier,"_0"), "global");
	int response_local = member(SymbolTable, concat(identifier,"_0"), PRG_GetScope());
	if(response_local){
		offset = memberNumber(SymbolTable, concat(identifier,"_0"), PRG_GetScope());	
		sprintf(offset_string, "%d", offset);
		identifier = concat("[",concat("\%STACK",concat("+",concat(offset_string,"]"))));
	}else if(response_global){
		offset = memberNumber(SymbolTable, concat(identifier,"_0"), "global");	
		sprintf(offset_string, "%d", offset);
		identifier = concat("[",concat("\%GLOBALS",concat("+",concat(offset_string,"]"))));
	}
	
	char * instruction = concat("MOVE ", expression);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, identifier);
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeASSIGN(char *identifier){
	char *identifier_type;
	char *expression_type;
	char *expression;
	
	//Semantic Check
	//Look for the identifier to be declared previously in the symbol table
	//In assignment. The symbol to look for is either a var, or a parameter.
	PRG_GetSymbol(identifier, PRG_GetScope(), "var"); 
	
	//Semantic Check
	// Check that the identifier and the expression have the same type
	identifier_type = getTypeFromSymbol(identifier, PRG_GetScope());
	expression_type = stackPop(&typeStack);
	
	if(strcmp(identifier_type,expression_type)!=0){
		printf("LINE: %-4d CALL: IR_MakeASSIGN(%s)\n", g_lineno, identifier);
		printf("FATAL: Type mismatch. Trying to assign %s to a \"%s\" of type %s \n", expression_type, identifier, identifier_type);
		exit(EXIT_FAILURE);
	}
	
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeASSIGN(%s)\n", g_lineno, identifier);
	
	expression = stackPop(&operandStack);
	
	int offset;	
	char offset_string[MAX_PROGRAM_SIZE];

	int response_global = member(SymbolTable, identifier, "global");
	int response_local = member(SymbolTable, identifier, PRG_GetScope());
	int response_ary_global = member(SymbolTable, concat(identifier,"_0"), "global");
	int response_ary_local = member(SymbolTable, concat(identifier,"_0"), PRG_GetScope());
	
	if(response_local){
		offset = memberNumber(SymbolTable, identifier, PRG_GetScope());	
		sprintf(offset_string, "%d", offset);
		identifier = concat("(",concat("\%STACK",concat("+",concat(offset_string,")"))));
	}else if(response_global){
		offset = memberNumber(SymbolTable, identifier, "global");	
		sprintf(offset_string, "%d", offset);
		identifier = concat("(",concat("\%GLOBALS",concat("+",concat(offset_string,")"))));
	}else if(response_ary_local){
		offset = memberNumber(SymbolTable, concat(identifier,"_0"), PRG_GetScope());	
		sprintf(offset_string, "%d", offset);
		identifier = concat("[",concat("\%STACK",concat("+",concat(offset_string,"]"))));
	}else if(response_ary_global){
		offset = memberNumber(SymbolTable, concat(identifier,"_0"), "global");	
		sprintf(offset_string, "%d", offset);
		identifier = concat("[",concat("\%GLOBALS",concat("+",concat(offset_string,"]"))));
	}

	//Code generation
	IR_AddASSIGN(identifier,expression);
}

void IR_MakeWHILE(){
	char *expression;
	char *expression_type;
	char *instruction;
	
	expression = stackPop(&operandStack);
	expression_type = stackPop(&typeStack);
	
	if(strcmp(expression_type,"boolean")!=0){
		printf("LINE: %-4d CALL: IR_MakeWHILE()\n", g_lineno);
		printf("FATAL: While Iterator only accepts boolean arguments \n");
		exit(EXIT_FAILURE);
	}
	
	instruction = concat("GTOF ", expression);
	IRCode[program_counter] = instruction;
	int_stackPush(&jumpStack,program_counter);
	program_counter++;
}

void IR_MakeENDWHILE(){
	// The stack looks like this here
	// 2: La direccion del gotof
	// 1: La direccion del comienzo del while, antes de la exp
	
	// POP jumpStack
	// Rellenar IR pasado con program_counter+1 (uno despues del goto incondicional)
	int while_condition_address = int_stackPop(&jumpStack);
	char jmp_address[MAX_PROGRAM_SIZE+1];
	sprintf(jmp_address, " %d", program_counter + 2);
	
	char *while_condition_instruction = IRCode[while_condition_address];
	while_condition_instruction = concat(while_condition_instruction, jmp_address);
	IRCode[while_condition_address] = strdup(while_condition_instruction);
	
	// POP jumpStack
	// Generar instruccion de goto incondicional al poped
	int while_beginning_address = int_stackPop(&jumpStack);
	sprintf(jmp_address, " %d", while_beginning_address +1);
	char *instruction = concat("GOTO ", jmp_address);
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeIF(){
	char *typeName = stackPop(&typeStack);
	char *operand = stackPop(&operandStack);
	
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeIF()\n", g_lineno);
	
	//Semantic Check	
	if (strcmp(typeName,"boolean")!=0){
		printf("LINE: %-4d  CALL: IR_MakeIF()\t\n", g_lineno);
		printf("FATAL: Conditional only accepts boolean. Using %s won't work\n", typeName);
		exit(EXIT_FAILURE);
	}
	
	//Code Generation Subroutine
	IR_AddGotoF(operand);
}

void IR_MakeELSEIF(){
	int previous_if_address = int_stackPop(&jumpStack);
	
	//GENERAR GOTO _____
	char *instruction;
	instruction = strdup("GOTO ");
	IRCode[program_counter] = instruction;
	int_stackPush(&jumpStack, program_counter);
	program_counter++;
	
	//SACAR FALSO DE PILA-DE-SALTOS
	char *previous_if_instruction;
	char jmp_address[MAX_PROGRAM_SIZE];
	sprintf(jmp_address, "%d", program_counter+1);

	previous_if_instruction = IRCode[previous_if_address];
	
	// "GOTOF var" + " " + JMP_ADDRESS
	previous_if_instruction  = concat(previous_if_instruction, " ");
	previous_if_instruction  = concat(previous_if_instruction, jmp_address);
	
	IRCode[previous_if_address] = strdup(previous_if_instruction);
	free(previous_if_instruction);
}

void IR_MakeENDIF(){
	
	int previous_if_address = int_stackPop(&jumpStack);
	char jmp_address[MAX_PROGRAM_SIZE];
	
	char *instruction = IRCode[previous_if_address];
	sprintf(jmp_address, "%d", program_counter+1);		
	
	char *new_instruction_tmp1;
	char *new_instruction;
	

	
	// "GOTOF var" + " " + JMP_ADDRESS
	new_instruction_tmp1  = concat(instruction, " ");
	new_instruction  = concat(new_instruction_tmp1, jmp_address);
	
	free(new_instruction_tmp1);
	free(instruction);
	
	IRCode[previous_if_address] = new_instruction;
}

void IR_MakeRETURN(){
	char *identifier_type;
	char *expression_type;
	char *expression;
	char *instruction;
	
	//Semantic Check
	// Check type of current scope (current function basically)
	// Compare it with whatever type is on typeStack
	identifier_type = getTypeFromSymbol(PRG_GetScope(), PRG_GetScope());
	expression_type = stackPop(&typeStack);
	
	if(strcmp(identifier_type,expression_type)!=0){
			printf("LINE: %-4d CALL: IR_MakeRETURN()\n", g_lineno);
			printf("FATAL: Type mismatch. Trying to return %s in a %s function\n", expression_type, identifier_type);
			exit(EXIT_FAILURE);
	}
	
	//Code generation
	expression = stackPop(&operandStack);
	
	instruction = concat("RETV ", expression);
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeERA(char *identifier){
	//This shit has to generate code that says how much space to push into the stackfram
	//How much? Well that depends on the number of variables (temps,vars and params for a function)
	
	//int era_size = PRG_GetFunctionVariablesNum(identifier);
	//char era_size_string[MAX_TMP_VARIABLES];
	//sprintf(era_size_string, "%d", era_size);
	
	//This brings up a problem. Cant have variabels having the prefix erasize_
	char *era_size_string = concat("era_size_", identifier);
	char *instruction = concat("ERAS *", era_size_string);
	instruction = concat(instruction,"*");
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeSTACKPUSH(){
	char *expression_type;
	char *expression;
	char *instruction;
	
	//Semantics check
	expression_type = stackPop(&typeStack);
	//Deberia de checar que existe este tipo en la lista de parametros de la funcion de jodido
	//Deberia ir quitandolos tho.
	
	//Code generation
	//Push by value, unless string.. maybe
	expression = stackPop(&operandStack);
	instruction = concat("PUSH ", expression);
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeCALL(char *identifier){ 
	char *instruction;
	char suffix_for_temporal_variable[MAX_PROGRAM_SIZE];
	char *temporal_variable;
	
	sprintf(suffix_for_temporal_variable, "%d", temporals_counter++);
	temporal_variable = concat("T", suffix_for_temporal_variable);
	
	PRG_SaveSymbol(getTypeFromSymbol(identifier, "global"), temporal_variable, PRG_GetScope(), "tmp"); 
	
	EXP_PushOperand(temporal_variable, PRG_GetScope());
	temporal_variable = stackPop(&operandStack);
	stackPush(&operandStack,temporal_variable);
	instruction = concat("CALL _", identifier);
	IRCode[program_counter] = instruction;
	program_counter++;
	
	
	instruction = concat("POPV ", temporal_variable);
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeVER(){
	// Hubo una llamada a[exp]
	char *operand = stackPop(&operandStack);
	stackPop(&typeStack);
	char *instruction;
	
	instruction = concat("AVER ", operand);
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeVERA(){
	// Hubo una llamada a[exp]
	char *operand = stackPop(&operandStack);
	stackPop(&typeStack);
	char *instruction;
	
	instruction = concat("VERA ", operand);
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeVERB(){
	// Hubo una llamada a[exp]
	char *operand = stackPop(&operandStack);
	stackPop(&typeStack);
	char *instruction;
	
	instruction = concat("VERB ", operand);
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeMULTIVER(char *identifier){
	// Hubo una llamada a[exp][exp]
	char *operandB = stackPop(&operandStack);
	stackPop(&typeStack);
	
	char *instruction;

	char *operandA = stackPop(&operandStack);
	stackPop(&typeStack);
	
	char *firstDimension = memberType(SymbolTable, identifier, "_dim");
	
	instruction = concat("MVER ", concat(operandA, concat(" ", concat(operandB, concat(" ", firstDimension)))));
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_MakeEXP(){
	char *operator = stackPop(&operatorStack);
	char *operand1_type = stackPop(&typeStack);
  char *operand2_type = stackPop(&typeStack);
	char *operand1 = stackPop(&operandStack);
	char *operand2 = stackPop(&operandStack);
	char *temporal_variable;
	char *temporal_variable_type;
	char suffix_for_temporal_variable[MAX_TMP_VARIABLES];
	//Semantic Analysis
	//We check the type of the two operands with the help of a semantic cube
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeEXP() // Checking Semantics (%s,%s,%s)\n", g_lineno, operator, operand1_type, operand2_type);
	
	temporal_variable_type = PRG_SemanticCube(operator,operand1_type,operand2_type);
	
	if(strcmp(temporal_variable_type,"error")==0){
		printf("LINE: %-4d CALL: IR_MakeEXP(%s)\n", g_lineno, operator);
		printf("FATAL: Type mismatch between operators. Can't do \"%s %s %s\" \n", operand1_type,operator,operand2_type);
		exit(EXIT_FAILURE);
	}else{
		stackPush(&typeStack,temporal_variable_type);
		operator = stackPop(&operatorStack);		
	}
	
	
	
	//push pila_de_operandos(resultado)
	//pop pila-de-operadores
	
	//Calculate suffix for temporal variable
	//EJ. T1,T2,T3...T30,T31 ...T122,T123...
	sprintf(suffix_for_temporal_variable, "%d", temporals_counter++);
	temporal_variable = concat("T", suffix_for_temporal_variable);
	
	PRG_SaveSymbol(temporal_variable_type, temporal_variable, PRG_GetScope(), "tmp"); 
	
	//Pusheamos al stack de operadores la variable temporal donde se guarda el resultado
	EXP_PushOperand(temporal_variable, PRG_GetScope());
	temporal_variable = stackPop(&operandStack);
	stackPush(&operandStack,temporal_variable);
	
	//Code generation subroutine;	
	if(VERBOSE)
		printf("LINE: %-4d IR_AddEXP(%s,%s,%s,%s)\n", g_lineno, operator,operand1,operand2, temporal_variable);
	
	// IADD OPA OPB T1
	char * instruction = concat(operator, " ");
	instruction = concat(instruction, operand1);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, operand2);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, temporal_variable);
	
	IRCode[program_counter] = instruction;
	program_counter++;
	
}

void save_ary_symbol(char *type, char *identifier, char *range){
	char identifier_index[MAX_TMP_VARIABLES+1];
	int rangeindex;
	char *array_identifier;
	rangeindex = atoi(range);
	for(int i=0;i<rangeindex;i++){
		sprintf(identifier_index, "_%d", i);
		array_identifier = concat(identifier,identifier_index);
		PRG_SaveSymbol(type, array_identifier, PRG_GetScope(), "var");
		free(array_identifier);
	}
}

void save_multiary_symbol(char *type, char *identifier, char *first_dimension, char *second_dimension){
	char identifier_index[MAX_TMP_VARIABLES+1];
	char *array_identifier;
	int first_dimension_range;
	int second_dimension_range;
	int index = 0;
	first_dimension_range = atoi(first_dimension);
	second_dimension_range = atoi(second_dimension);
	
	
	
	for(int i=0;i<first_dimension_range;i++){
		for(int j=0;j<second_dimension_range;j++){
			sprintf(identifier_index, "_%d", index);
			array_identifier = concat(identifier,identifier_index);
			PRG_SaveSymbol(type, array_identifier, PRG_GetScope(), "var");
			free(array_identifier);
			index++;
		}
	}
	
	//Ugly hack
	//Guardamos la primera dimension como Type y la secondDimesion como Kind
	PRG_SaveSymbol(first_dimension, identifier, "_dim", second_dimension); 
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 1380 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNRULES -- Number of states.  */
#define YYNSTATES  170

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    10,    11,    16,    17,    20,    22,
      23,    24,    31,    34,    36,    37,    38,    51,    52,    55,
      57,    58,    60,    64,    66,    69,    73,    76,    79,    85,
      94,    96,    98,   100,   102,   105,   107,   110,   113,   115,
     117,   120,   123,   133,   146,   147,   148,   149,   150,   160,
     161,   165,   173,   174,   185,   186,   189,   192,   194,   199,
     200,   209,   211,   212,   217,   219,   221,   223,   225,   227,
     229,   231,   233,   235,   236,   241,   243,   245,   247,   248,
     253,   254,   259,   261,   263,   265,   267,   269,   271,   272,
     273,   279,   281,   283,   285,   286,   292,   293,   295,   299,
     301
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    -1,    50,    47,    61,    53,    49,    -1,
      -1,    50,    48,    53,    49,    -1,    -1,    50,    51,    -1,
      51,    -1,    -1,    -1,    13,    21,    43,    21,    52,    40,
      -1,    53,    54,    -1,    54,    -1,    -1,    -1,     6,    63,
      44,    18,    55,    38,    58,    39,    44,    57,    56,     7,
      -1,    -1,    61,    64,    -1,    64,    -1,    -1,    59,    -1,
      59,    43,    60,    -1,    60,    -1,    63,    18,    -1,    61,
      62,    40,    -1,    62,    40,    -1,    63,    18,    -1,    63,
      18,    41,    19,    42,    -1,    63,    18,    41,    19,    42,
      41,    19,    42,    -1,    14,    -1,    15,    -1,    16,    -1,
      17,    -1,    64,    65,    -1,    65,    -1,    73,    40,    -1,
      97,    40,    -1,    66,    -1,    70,    -1,    76,    40,    -1,
      93,    40,    -1,     3,    38,    80,    67,    39,    44,    64,
       4,    68,    -1,     3,    38,    80,    67,    39,    44,    64,
       5,    69,    64,     4,    68,    -1,    -1,    -1,    -1,    -1,
       9,    72,    38,    80,    71,    39,    44,    64,    10,    -1,
      -1,    18,    24,    80,    -1,    18,    41,    80,    42,    75,
      24,    80,    -1,    -1,    18,    41,    80,    42,    41,    80,
      74,    42,    24,    80,    -1,    -1,    11,    77,    -1,    12,
      80,    -1,    79,    -1,    79,    41,    80,    42,    -1,    -1,
      79,    41,    80,    42,    41,    80,    78,    42,    -1,    18,
      -1,    -1,    80,    82,    81,    83,    -1,    83,    -1,    29,
      -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,
      -1,    36,    -1,    37,    -1,    -1,    83,    85,    84,    86,
      -1,    86,    -1,    26,    -1,    25,    -1,    -1,    86,    27,
      87,    90,    -1,    -1,    86,    28,    88,    90,    -1,    90,
      -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,    23,
      -1,    -1,    -1,    38,    91,    83,    92,    39,    -1,    77,
      -1,    89,    -1,    93,    -1,    -1,    18,    94,    38,    95,
      39,    -1,    -1,    96,    -1,    96,    43,    83,    -1,    83,
      -1,     8,    80,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1234,  1234,  1234,  1235,  1235,  1236,  1238,  1239,  1241,
    1241,  1241,  1243,  1244,  1246,  1246,  1246,  1248,  1248,  1249,
    1251,  1251,  1253,  1254,  1256,  1259,  1260,  1262,  1263,  1264,
    1266,  1266,  1266,  1266,  1269,  1270,  1272,  1272,  1272,  1272,
    1272,  1272,  1274,  1275,  1277,  1278,  1279,  1281,  1281,  1282,
    1284,  1285,  1286,  1286,  1287,  1289,  1290,  1292,  1293,  1294,
    1294,  1296,  1298,  1298,  1299,  1301,  1301,  1301,  1301,  1301,
    1301,  1301,  1301,  1303,  1303,  1304,  1305,  1305,  1307,  1307,
    1308,  1308,  1309,  1311,  1312,  1313,  1314,  1315,  1317,  1317,
    1317,  1318,  1319,  1320,  1322,  1322,  1325,  1325,  1326,  1326,
    1328
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IFTKN", "ENDIFTKN", "ELSETKN",
  "FUNCTKN", "ENDFUNCTKN", "RETURNFUNCTKN", "WHILETKN", "ENDWHILETKN",
  "READTKN", "WRITETKN", "CIPHERTKN", "INTTKN", "DOUBLETKN", "STRINGTKN",
  "BOOLTKN", "IDTKN", "INTVALTKN", "DOUBLEVALTKN", "STRINGVALTKN",
  "TRUETKN", "FALSETKN", "ASSIGNTKN", "PLUSTKN", "MINUSTKN", "TIMESTKN",
  "DIVTKN", "LTTKN", "LTETKN", "GTTKN", "GTETKN", "EQUALTKN",
  "NOTEQUALTKN", "ASSIGNSECRETTKN", "ORTKN", "ANDTKN", "LEFTPTKN",
  "RIGHTPTKN", "SEMICOLONTKN", "LEFTBTKN", "RIGHTBTKN", "COMMATKN",
  "OPENBLOCKTKN", "$accept", "program", "@1", "@2", "eraupdate", "secrets",
  "secret", "@3", "functions", "function", "@4", "@5", "funcbody",
  "params", "paramlist", "param", "vardeclarations", "vardeclaration",
  "type", "blockstmts", "blockstmt", "ifstmt", "a_openif", "a_closeif",
  "a_elseif", "iterstmt", "@6", "a_savejump", "assignstmt", "@7",
  "a_range", "iostmt", "var", "@8", "identifier", "expstmt", "@9",
  "compoperator", "exp", "@10", "additiveoperator", "term", "@11", "@12",
  "values", "factor", "@13", "@14", "callstmt", "@15", "args", "arglist",
  "returnstmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    47,    46,    48,    46,    49,    50,    50,    51,
      52,    51,    53,    53,    55,    56,    54,    57,    57,    57,
      58,    58,    59,    59,    60,    61,    61,    62,    62,    62,
      63,    63,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    66,    66,    67,    68,    69,    71,    70,    72,
      73,    73,    74,    73,    75,    76,    76,    77,    77,    78,
      77,    79,    81,    80,    80,    82,    82,    82,    82,    82,
      82,    82,    82,    84,    83,    83,    85,    85,    87,    86,
      88,    86,    86,    89,    89,    89,    89,    89,    91,    92,
      90,    90,    90,    90,    94,    93,    95,    95,    96,    96,
      97
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     0,     4,     0,     2,     1,     0,
       0,     6,     2,     1,     0,     0,    12,     0,     2,     1,
       0,     1,     3,     1,     2,     3,     2,     2,     5,     8,
       1,     1,     1,     1,     2,     1,     2,     2,     1,     1,
       2,     2,     9,    12,     0,     0,     0,     0,     9,     0,
       3,     7,     0,    10,     0,     2,     2,     1,     4,     0,
       8,     1,     0,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     1,     1,     1,     1,     1,     1,     0,     0,
       5,     1,     1,     1,     0,     5,     0,     1,     3,     1,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,     0,     0,     2,     8,     0,     1,     0,     0,     7,
       0,    30,    31,    32,    33,     0,     0,     0,     0,     6,
      13,    10,     6,     0,    26,    27,     0,     5,    12,     0,
       3,    25,     0,     0,    11,     0,    14,    28,     0,     0,
      20,     0,     0,    21,    23,     0,    29,     0,     0,    24,
      17,    22,     0,     0,    49,     0,     0,    94,    15,     0,
      19,    35,    38,    39,     0,     0,     0,     0,     0,    61,
      83,    84,    85,    86,    87,    88,    91,    57,   100,    64,
      75,    92,    82,    93,     0,    61,    55,    56,     0,     0,
       0,     0,    18,    34,    36,    40,    41,    37,    44,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    62,
      77,    76,    73,    78,    80,     0,    50,     0,    96,    16,
       0,    89,     0,     0,     0,     0,     0,    47,    54,    99,
       0,    97,     0,     0,    58,    63,    74,    79,    81,     0,
       0,     0,    95,     0,     0,    90,     0,     0,    52,     0,
      98,     0,    59,     0,     0,    51,    45,    46,     0,     0,
       0,    42,     0,    60,    48,     0,     0,    53,    45,    43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     8,    27,     3,     4,    29,    19,    20,
      38,    91,    58,    42,    43,    44,    15,    16,    17,    60,
      61,    62,   120,   161,   162,    63,   139,    84,    64,   154,
     141,    65,    76,   158,    77,    78,   123,   109,    79,   124,
     112,    80,   125,   126,    81,    82,    99,   133,    83,    90,
     130,   131,    67
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -99
static const yytype_int16 yypact[] =
{
      -7,    -4,    22,    -1,   -99,   -28,   -99,    40,    34,   -99,
      20,   -99,   -99,   -99,   -99,   122,    19,    25,    40,    34,
     -99,   -99,    34,    37,   -99,    21,     0,   -99,   -99,    38,
     -99,   -99,    41,    47,   -99,    39,   -99,    43,    49,    66,
      40,    46,    51,    48,   -99,    75,   -99,    53,    40,   -99,
      55,   -99,    61,    30,   -99,    82,    30,   -20,   -99,    55,
     123,   -99,   -99,   -99,    62,    64,    67,    68,    30,    72,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,    76,   141,     3,
       4,   -99,   -99,   -99,    80,   -99,   -99,   141,    30,    30,
      81,   118,   123,   -99,   -99,   -99,   -99,   -99,   141,    30,
      30,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,    30,   141,   113,    30,   -99,
      88,     3,   127,    30,    30,    30,    30,   141,    92,     3,
      90,    97,   104,   114,   110,     3,     4,   -99,   -99,   115,
      30,   128,   -99,    30,   123,   -99,    30,   121,   141,    30,
       3,    71,   141,   123,   120,   141,   -99,   -99,   124,   112,
     143,   -99,   123,   -99,   -99,    30,    15,   141,   -99,   -99
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -99,   -99,   -99,   -99,   146,   -99,   173,   -99,   164,    -6,
     -99,   -99,   -99,   -99,   -99,   132,   131,   -12,   -10,   -48,
     -53,   -99,   -99,    14,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,   -99,   129,   -99,   -99,   -54,   -99,   -99,   -98,   -99,
     -99,    59,   -99,   -99,   -99,   -89,   -99,   -99,   -50,   -99,
     -99,   -99,   -99
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -95
static const yytype_int16 yytable[] =
{
      66,   121,    87,    23,    88,    -4,     1,    93,    26,    66,
      66,    92,     1,    28,    98,    10,    28,     5,    52,   168,
     129,    89,     6,    53,    54,   135,    55,    56,   110,   111,
      45,   113,   114,    57,   116,   117,   137,   138,    45,    93,
      18,    21,    66,    25,    33,   150,   122,    23,    69,    70,
      71,    72,    73,    74,    11,    12,    13,    14,    52,    24,
      35,   127,    32,    53,    54,    36,    55,    56,    75,    11,
      12,    13,    14,    57,    52,   156,   157,    31,    34,    53,
      54,    37,    55,    56,    39,    41,   148,    40,    46,    57,
      47,    48,   152,    49,    66,   155,   151,    50,    93,    68,
      85,    66,    94,    66,    95,   159,    93,    96,    97,    66,
     -94,   167,    66,    93,   166,    52,    66,   100,   115,   118,
      53,    54,   164,    55,    56,   119,    52,   132,    18,   142,
      57,    53,    54,   140,    55,    56,    11,    12,    13,    14,
     143,    57,   101,   102,   103,   104,   105,   106,   144,   107,
     108,   146,   149,   145,   147,   128,   101,   102,   103,   104,
     105,   106,   160,   107,   108,   153,   163,   165,    30,   134,
     101,   102,   103,   104,   105,   106,     9,   107,   108,    22,
      51,    59,   169,   136,    86
};

static const yytype_uint8 yycheck[] =
{
      50,    99,    56,    15,    24,     6,    13,    60,    18,    59,
      60,    59,    13,    19,    68,    43,    22,    21,     3,     4,
     118,    41,     0,     8,     9,   123,    11,    12,    25,    26,
      40,    27,    28,    18,    88,    89,   125,   126,    48,    92,
       6,    21,    92,    18,    44,   143,   100,    59,    18,    19,
      20,    21,    22,    23,    14,    15,    16,    17,     3,    40,
      19,   115,    41,     8,     9,    18,    11,    12,    38,    14,
      15,    16,    17,    18,     3,     4,     5,    40,    40,     8,
       9,    42,    11,    12,    41,    19,   140,    38,    42,    18,
      39,    43,   146,    18,   144,   149,   144,    44,   151,    38,
      18,   151,    40,   153,    40,   153,   159,    40,    40,   159,
      38,   165,   162,   166,   162,     3,   166,    41,    38,    38,
       8,     9,    10,    11,    12,     7,     3,    39,     6,    39,
      18,     8,     9,    41,    11,    12,    14,    15,    16,    17,
      43,    18,    29,    30,    31,    32,    33,    34,    44,    36,
      37,    41,    24,    39,    39,    42,    29,    30,    31,    32,
      33,    34,    42,    36,    37,    44,    42,    24,    22,    42,
      29,    30,    31,    32,    33,    34,     3,    36,    37,    15,
      48,    50,   168,   124,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    46,    50,    51,    21,     0,    47,    48,    51,
      43,    14,    15,    16,    17,    61,    62,    63,     6,    53,
      54,    21,    53,    62,    40,    18,    63,    49,    54,    52,
      49,    40,    41,    44,    40,    19,    18,    42,    55,    41,
      38,    19,    58,    59,    60,    63,    42,    39,    43,    18,
      44,    60,     3,     8,     9,    11,    12,    18,    57,    61,
      64,    65,    66,    70,    73,    76,    93,    97,    38,    18,
      19,    20,    21,    22,    23,    38,    77,    79,    80,    83,
      86,    89,    90,    93,    72,    18,    77,    80,    24,    41,
      94,    56,    64,    65,    40,    40,    40,    40,    80,    91,
      41,    29,    30,    31,    32,    33,    34,    36,    37,    82,
      25,    26,    85,    27,    28,    38,    80,    80,    38,     7,
      67,    83,    80,    81,    84,    87,    88,    80,    42,    83,
      95,    96,    39,    92,    42,    83,    86,    90,    90,    71,
      41,    75,    39,    43,    44,    39,    41,    39,    80,    24,
      83,    64,    80,    44,    74,    80,     4,     5,    78,    64,
      42,    68,    69,    42,    10,    24,    64,    80,     4,    68
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 1234 "yacc.y"
    {  PRG_Initialize(); }
    break;

  case 3:
#line 1234 "yacc.y"
    { PRG_EncryptCode(); PRG_SaveIRCode(); }
    break;

  case 4:
#line 1235 "yacc.y"
    {  PRG_Initialize(); }
    break;

  case 5:
#line 1235 "yacc.y"
    { PRG_EncryptCode(); PRG_SaveIRCode(); }
    break;

  case 6:
#line 1236 "yacc.y"
    { PRG_ERAUpdate(); }
    break;

  case 10:
#line 1241 "yacc.y"
    { PRG_PushCipher((yyvsp[(2) - (4)]),(yyvsp[(4) - (4)])); }
    break;

  case 14:
#line 1246 "yacc.y"
    { IR_MakeFUNCTION((yyvsp[(4) - (4)])); PRG_SetScope((yyvsp[(4) - (4)])); PRG_SaveSymbol((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), "global", "func");  }
    break;

  case 15:
#line 1246 "yacc.y"
    { IR_MakeFUNCTIONEND(); }
    break;

  case 24:
#line 1256 "yacc.y"
    { PRG_SaveSymbol((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), PRG_GetScope(), "param"); }
    break;

  case 27:
#line 1262 "yacc.y"
    { PRG_SaveSymbol((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), PRG_GetScope(), "var"); }
    break;

  case 28:
#line 1263 "yacc.y"
    { save_ary_symbol((yyvsp[(1) - (5)]),(yyvsp[(2) - (5)]),(yyvsp[(4) - (5)])); }
    break;

  case 29:
#line 1264 "yacc.y"
    { save_multiary_symbol((yyvsp[(1) - (8)]),(yyvsp[(2) - (8)]),(yyvsp[(4) - (8)]),(yyvsp[(7) - (8)])); }
    break;

  case 44:
#line 1277 "yacc.y"
    { IR_MakeIF(); }
    break;

  case 45:
#line 1278 "yacc.y"
    { IR_MakeENDIF(); }
    break;

  case 46:
#line 1279 "yacc.y"
    { IR_MakeELSEIF(); }
    break;

  case 47:
#line 1281 "yacc.y"
    { IR_MakeWHILE(); }
    break;

  case 48:
#line 1281 "yacc.y"
    { IR_MakeENDWHILE(); }
    break;

  case 49:
#line 1282 "yacc.y"
    { int_stackPush(&jumpStack, program_counter); }
    break;

  case 50:
#line 1284 "yacc.y"
    { IR_MakeASSIGN((yyvsp[(1) - (3)])); }
    break;

  case 51:
#line 1285 "yacc.y"
    { IR_MakeARGYASSIGN((yyvsp[(1) - (7)])); }
    break;

  case 52:
#line 1286 "yacc.y"
    {IR_MakeMULTIVER((yyvsp[(1) - (6)]));}
    break;

  case 53:
#line 1286 "yacc.y"
    { IR_MakeARGYASSIGN((yyvsp[(1) - (10)])); }
    break;

  case 54:
#line 1287 "yacc.y"
    {IR_MakeVER();}
    break;

  case 55:
#line 1289 "yacc.y"
    { IR_MakeIOREAD((yyvsp[(2) - (2)])); }
    break;

  case 56:
#line 1290 "yacc.y"
    {IR_MakeIOWRITE(); }
    break;

  case 58:
#line 1293 "yacc.y"
    { IR_MakeVER(); }
    break;

  case 59:
#line 1294 "yacc.y"
    {IR_MakeMULTIVER((yyvsp[(1) - (6)]));}
    break;

  case 62:
#line 1298 "yacc.y"
    {  EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 63:
#line 1298 "yacc.y"
    { IR_MakeEXP(); }
    break;

  case 73:
#line 1303 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 74:
#line 1303 "yacc.y"
    { IR_MakeEXP();}
    break;

  case 78:
#line 1307 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 79:
#line 1307 "yacc.y"
    { IR_MakeEXP();}
    break;

  case 80:
#line 1308 "yacc.y"
    { EXP_PushOperator((yyvsp[(2) - (2)])); }
    break;

  case 81:
#line 1308 "yacc.y"
    { IR_MakeEXP();}
    break;

  case 88:
#line 1317 "yacc.y"
    { /* fake bottom */ }
    break;

  case 89:
#line 1317 "yacc.y"
    { /* fake bottom */ }
    break;

  case 91:
#line 1318 "yacc.y"
    { EXP_PushOperand((yyvsp[(1) - (1)]), "var"); }
    break;

  case 92:
#line 1319 "yacc.y"
    { EXP_PushOperand((yyvsp[(1) - (1)]), "const"); }
    break;

  case 93:
#line 1320 "yacc.y"
    {  IR_MakeCALL((yyvsp[(1) - (1)])); }
    break;

  case 94:
#line 1322 "yacc.y"
    { IR_MakeERA((yyvsp[(1) - (1)]));}
    break;

  case 95:
#line 1322 "yacc.y"
    { PRG_GetSymbol((yyvsp[(1) - (5)]), "global", "func"); }
    break;

  case 98:
#line 1326 "yacc.y"
    {IR_MakeSTACKPUSH(); }
    break;

  case 99:
#line 1326 "yacc.y"
    {IR_MakeSTACKPUSH(); }
    break;

  case 100:
#line 1328 "yacc.y"
    { IR_MakeRETURN(); }
    break;


/* Line 1267 of yacc.c.  */
#line 2971 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1330 "yacc.y"



int yyerror(char * message)
	
{ fprintf(stderr,"at line %d: %s\n",g_lineno,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}
