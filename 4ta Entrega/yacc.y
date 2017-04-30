%{
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
/**                  ATTRIBUTE GRAMMAR FUNCTIONS                           **/
/**                                                                        **/
/****************************************************************************/


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

/*
* Used in the grammar rules (expcmp,exp,term,factor) for semantic analysis.
*
*/
void EXP_PushOperator(char *op){
	//Always checking
	if (NULL==op){
		printf("LINE: %-4d  CALL: EXP_PushOperator(NULL)\t", g_lineno);
		printf("FATAL: Null reference.\n");
		exit(EXIT_FAILURE);
	}
	
	stackPush(&operatorStack,op);
	
	if(VERBOSE)
		printf("LINE: %-4d EXP_PushOperator(%s)\n", g_lineno, op);	
}

void save_symbol(char *typeName, char *identifierName, char *scopeName, char *symbolKind){
	int response;

	response = insert(SymbolTable, typeName, identifierName, scopeName, symbolKind);
	
	if(response!=0){
		printf("Symbol %s:%s on %s:%s\n", typeName, identifierName, scopeName, symbolKind);
		yyerror("ERROR: Redefinition of symbol");
	}
	
}
void get_symbol(char *identifierName, char *scopeName, char *symbolKind){
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
		//  Also check for identifierName to be of type "func" (maybe the user is calling a identifier in global who is not a func)
		if(response_func==0 || strcmp(kind,"func")!=0){
			printf("Symbol %s on %s:%s\n", identifierName, scopeName, symbolKind);
			yyerror("ERROR: trying to use inexisting function");
			return;
			
		}
	}

	//Variables are search'd in both the local and global scope
	response_local  = member(SymbolTable, identifierName, scopeName);
	response_global = member(SymbolTable, identifierName, "global");
	if(response_local==0 && response_global==0){
		//printf("Symbol %s on %s:%s\n", identifierName, scopeName, symbolKind);
		yyerror("ERROR: trying to use inexisting variable");
		return;
	}
	
	
	//printf("Checking for '%s' symbol existance on scope %s of type %s\n", identifierName, scopeName, symbolKind);
}

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

char *getTypeFromSymbol(char *symbol){
	//TO-DO check for nulls on symbol
	
	return memberType(SymbolTable, symbol, PRG_GetScope());
}

void SMT_CheckStatement(char *st, char *symbol){
	//TO-DO Check for NULLS
	char *typeName;
	
	if(strcmp(st,"return")==0){
		typeName = symbol;
	}else{
		typeName = getTypeFromSymbol(symbol);
	}
	
	char * returnVal = stackPop(&typeStack);	
	if(VERBOSE)
		printf("LINE: %-4d SMT_CheckStatement(%s,%s) // stackPOP(typeStack)=%s  \n", g_lineno, st,symbol, returnVal);
	
	//TO-DO Should really abort here. Use previous convention for closing
	if(strcmp(typeName,returnVal)!=0){
		if(strcmp(st,"=")==0)
			yyerror("ERROR: type conflict inside assignment");
		else
			yyerror("ERROR: type conflict inside return");
	}else{
		//DEBUG
		//printf("--> NOISE\n");
		
	}
	
	
	if(VERBOSE)
		printf("LINE: %-4d SMT_CheckStatement(%s,%s)\n", g_lineno, st,symbol);
	
	free(returnVal);
}

void checkAssign(char *a, char *op, char *b){
	printf("Identifier: %s\n", a);
	printf("Type of (identifier) %s\n", a);
	printf("Value of tmp: %s\n", b);
}

void IR_AddGotoF(char *operand){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddGotoF(%s)\n", g_lineno, operand);
	
	char *instruction = concat("GOTOF ", operand);
	IRCode[program_counter] = instruction;
	int_stackPush(&jumpStack, program_counter);
	program_counter++;
}

void IR_AddEXP(char *operator, char *operandA, char *operandB, char *resultado){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddEXP(%s,%s,%s,%s)\n", g_lineno, operator,operandA,operandB, resultado);
	
	// + OPA OPB T1
	char * instruction = concat(operator, " ");
	instruction = concat(instruction, operandA);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, operandB);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, resultado);
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_AddASSIGN(char *identifier, char *expression){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddASSIGN(%s,%s)\n", g_lineno, identifier,expression);
	// "= " + expression + " " + identifier
	// = T1 A
	char * instruction = concat("= ", expression);
	instruction = concat(instruction, " ");
	instruction = concat(instruction, identifier);
	
	IRCode[program_counter] = instruction;
	program_counter++;
}

void IR_AddIOREAD(char * identifier){
	char *identifier_type;
	char *instruction;
	
	if(VERBOSE)
		printf("LINE: %-4d IR_AddIOREAD(%s)\n", g_lineno, identifier);
	//The intermiadiate opcode on the other hand would probably need to be special for each kind of variable
	identifier_type = getTypeFromSymbol(identifier);
	
	if(strcmp(identifier_type,"int")==0){
		instruction = concat("iread ", identifier);
	}else if(strcmp(identifier_type,"double")==0){
		instruction = concat("dread ", identifier);
	}else if(strcmp(identifier_type,"boolean")==0){
		instruction = concat("bread ", identifier);
	}else if(strcmp(identifier_type,"string")==0){
		instruction = concat("sread ", identifier);
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
		instruction = concat("iwrite ", expression);
	}else if(strcmp(expression_type,"double")==0){
		instruction = concat("dwrite ", expression);
	}else if(strcmp(expression_type,"boolean")==0){
		instruction = concat("bwrite ", expression);
	}else if(strcmp(expression_type,"string")==0){
		instruction = concat("swrite ", expression);
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
	get_symbol(identifier, PRG_GetScope(), "var"); 
	
	
	IR_AddIOREAD(identifier);
}

void IR_MakeASSIGN(char *identifier){
	char *identifier_type;
	char *expression_type;
	char *expression;
	
	//Semantic Check
	//Look for the identifier to be declared previously in the symbol table
	//In assignment. The symbol to look for is either a var, or a parameter.
	get_symbol(identifier, PRG_GetScope(), "var"); 
	
	//Semantic Check
	// Check that the identifier and the expression have the same type
	identifier_type = getTypeFromSymbol(identifier);
	expression_type = stackPop(&typeStack);
	
	if(strcmp(identifier_type,expression_type)!=0){
		printf("LINE: %-4d CALL: IR_MakeASSIGN(%s)\n", g_lineno, identifier);
		printf("FATAL: Type mismatch. Trying to assign %s to a \"%s\" of type %s \n", expression_type, identifier, identifier_type);
		exit(EXIT_FAILURE);
	}
	
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeASSIGN(%s)\n", g_lineno, identifier);
	
	expression = stackPop(&operandStack);
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
	
	instruction = concat("GOTOF ", expression);
	IRCode[program_counter] = instruction;
	int_stackPush(&jumpStack,program_counter);
	program_counter++;
}

void IR_MakeENDWHILE(){
	// The stack looks like this here
	// 2: La direccion del gotof
	// 1: La direccion del comienzo del while, antes de la exp
	
	// POP jumpStack
	// Rellenar IR pasado con program_counter
	int while_condition_address = int_stackPop(&jumpStack);
	char jmp_address[MAX_PROGRAM_SIZE+1];
	sprintf(jmp_address, " %d", program_counter);
	
	char *while_condition_instruction = IRCode[while_condition_address];
	while_condition_instruction = concat(while_condition_instruction, jmp_address);
	IRCode[while_condition_address] = strdup(while_condition_instruction);
	
	// POP jumpStack
	// Generar instruccion de goto incondicional al poped
	int while_beginning_address = int_stackPop(&jumpStack);
	sprintf(jmp_address, " %d", while_beginning_address);
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
		printf("LINE: %-4d  CALL: IR_MakeIF()\t", g_lineno);
		printf("FATAL: Returned operand %s:%s is not boolean\n", operand, typeName);
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
	sprintf(jmp_address, "%d", program_counter);

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
	sprintf(jmp_address, "%d", program_counter);		
	
	char *new_instruction_tmp1;
	char *new_instruction;
	

	
	// "GOTOF var" + " " + JMP_ADDRESS
	new_instruction_tmp1  = concat(instruction, " ");
	new_instruction  = concat(new_instruction_tmp1, jmp_address);
	
	free(new_instruction_tmp1);
	free(instruction);
	
	IRCode[previous_if_address] = new_instruction;
}

void IR_MakeEXP(){
	char *operator = stackPop(&operatorStack);
	char *operand1_type = stackPop(&typeStack);
  	char *operand2_type = stackPop(&typeStack);
	char *operand1 = stackPop(&operandStack);
	char *operand2 = stackPop(&operandStack);
	char *temporal_variable;
	char suffix_for_temporal_variable[MAX_TMP_VARIABLES];

	//Semantic Analysis
	//We check the type of the two operands with the help of a semantic cube
	if(VERBOSE)
		printf("LINE: %-4d IR_MakeEXP() // Checking Semantics (%s,%s,%s)\n", g_lineno, operator, operand1_type, operand2_type);
	
	// I need the cubo semantico aqui.
	// Actualmente solo estoy checando que los operadores sean del mismo tipo.
	if(strcmp(operand1_type,operand2_type)!=0){
		printf("LINE: %-4d CALL: IR_MakeEXP(%s)\n", g_lineno, operator);
		printf("FATAL: Type mismatch between operators \n");
		exit(EXIT_FAILURE);
	}else{
		// Aqui deberia pushear el tipo regresado del cubo semantico realmente
		// temporal_variable_type
		stackPush(&typeStack,operand1_type);		
	}
	
	//push pila_de_operandos(resultado)
	//pop pila-de-operadores
	
	//Calculate suffix for temporal variable
	//EJ. T1,T2,T3...T30,T31 ...T122,T123...
	sprintf(suffix_for_temporal_variable, "%d", temporals_counter++);
	temporal_variable = concat("T", suffix_for_temporal_variable);
	
	//Aqui es donde brilla el cubo semantico chingao. En vez de usar operand1_type.
	//Guardamos la temporal en la tabla de simbolos.
	save_symbol(operand1_type, temporal_variable, PRG_GetScope(), "tmp"); 
	
	//Pusheamos al stack de operadores la variable temporal donde se guarda el resultado
	stackPush(&operandStack,temporal_variable);


	//Code generation subroutine;
	IR_AddEXP(operator,operand1,operand2,temporal_variable);
}

void pushType(char *value, char *symbolKind){
	char *factorType;
	
	if(strcmp(symbolKind,"const")==0){ // then is a constant
		factorType = getTypeFromValue(value);
		//printf("Retrived type for %s is %s\n\n", value, factorType);
	}else{ // then is a variable or a function
		factorType = memberType(SymbolTable, value, PRG_GetScope());
		//printf("Retrived type for %s is %s in scope: %s\n\n", value, factorType, PRG_GetScope());
	}
	
	// We must transform the type into a int because these stack only holds integers
	stackPush(&typeStack,factorType);
}

void pushOperand(char *operand, char *kind){
	//A lo mejor deberia checar que sea permitido. Pero no pasarian por flex ni bison...
	stackPush(&operandStack, operand);
}

void EXP_PushOperand(char *operand, char *symbolKind){
	//TO-DO Check for NULLS
	
	//Check for the existance of a variable before even continuing.
	if(strcmp(symbolKind,"var")==0)
		get_symbol(operand, PRG_GetScope(), "var"); 
	
	//Later is the same for both expressions
	pushType(operand, symbolKind); 
	pushOperand(operand, symbolKind);
	
	if(VERBOSE)
		printf("LINE: %-4d EXP_PushOperand(%s,%s)\n", g_lineno, operand,symbolKind);
}

void PRG_Initialize(){
	PRG_SetScope("global");
	
	stackInit(&operandStack);
	stackInit(&typeStack);
	stackInit(&operatorStack);
	int_stackInit(&jumpStack);
	init_hash_table(SymbolTable);
	
	for(int i=0;i<MAX_PROGRAM_SIZE;i++)
		IRCode[i] = NULL;
}

void DBG_PrintSymbolTable(struct symbol hashtable[]){
	printf("\nSYMBOL TABLE\n");
	printf("%15s  %10s  ------   -----  -------  ----\n","----------","----------");
	printf("%15s  %-10s  type     kind   address  key\n","identifier", "context");
	printf("%15s  %10s  ------   -----  -------  ----\n","----------","----------");
	
  for (int i=0; i< SYMBOL_TABLE_SIZE ; i++){
      if (NULL != hashtable[i].value)
				printf("%15s  %10s  %7s  %5s  %7d  %d\n", hashtable[i].value, hashtable[i].contextName, hashtable[i].typeName, hashtable[i].symbolKind, hashtable[i].memoryLocation, i);
  }
}

void DBG_PrintIRCode(){
	printf("\nIR CODE\n");
	for(int i=0;i<program_counter;i++)
		printf("%5d: %s\n",i, IRCode[i]);
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

program   		: secrets { PRG_Initialize(); }  vardeclarations functions { DBG_PrintSymbolTable(SymbolTable); DBG_PrintIRCode(); }
				| secrets { PRG_Initialize(); } functions 
										

secrets			: secrets secret
				| secret

secret			: CIPHERTKN STRINGVALTKN COMMATKN STRINGVALTKN SEMICOLONTKN

functions       : functions function
				| function;

function		: FUNCTKN type OPENBLOCKTKN IDTKN {PRG_SetScope($4); save_symbol($2, $4, "global", "func");  } LEFTPTKN params RIGHTPTKN OPENBLOCKTKN funcbody returnstmt { SMT_CheckStatement("return", $2);} ENDFUNCTKN;

funcbody		: /* empty */ | vardeclarations blockstmts
				| blockstmts

params			: /* empty */ | paramlist;

paramlist       : paramlist COMMATKN param 
				| param;

param           : type IDTKN { save_symbol($1, $2, PRG_GetScope(), "param"); };

						
vardeclarations : vardeclarations vardeclaration SEMICOLONTKN;
				| vardeclaration SEMICOLONTKN;

vardeclaration  : type IDTKN { save_symbol($1, $2, PRG_GetScope(), "var"); }
				| type IDTKN LEFTBTKN INTVALTKN RIGHTBTKN; // NOT YET

type   			: INTTKN | DOUBLETKN | STRINGTKN | BOOLTKN;


blockstmts      : blockstmts blockstmt;
				| blockstmt;

blockstmt       : assignstmt SEMICOLONTKN | ifstmt | iterstmt | iostmt SEMICOLONTKN | callstmt SEMICOLONTKN;

ifstmt          : IFTKN LEFTPTKN expstmt a_openif RIGHTPTKN OPENBLOCKTKN blockstmts ENDIFTKN a_closeif
 				| IFTKN LEFTPTKN expstmt a_openif RIGHTPTKN OPENBLOCKTKN blockstmts ELSETKN a_elseif blockstmts ENDIFTKN a_closeif;

a_openif		: { IR_MakeIF(); }
a_closeif		: { IR_MakeENDIF(); }
a_elseif		: { IR_MakeELSEIF(); }

iterstmt		: WHILETKN a_savejump LEFTPTKN expstmt { IR_MakeWHILE(); } RIGHTPTKN OPENBLOCKTKN blockstmts ENDWHILETKN { IR_MakeENDWHILE(); };
a_savejump		: { int_stackPush(&jumpStack, program_counter); }

assignstmt      : IDTKN ASSIGNTKN expstmt { IR_MakeASSIGN($1); }
				| IDTKN LEFTBTKN INTVALTKN RIGHTBTKN ASSIGNTKN expstmt; //NOT YET
									
iostmt          : READTKN var  { IR_MakeIOREAD($2); }
				| WRITETKN expstmt {IR_MakeIOWRITE(); };
									
var             : identifier 
				| identifier LEFTBTKN INTVALTKN RIGHTBTKN;

identifier		: IDTKN;
			
expstmt         : expstmt compoperator { EXP_PushOperator($2); } exp { IR_MakeEXP(); } 
				| exp;

compoperator    : LTTKN | LTETKN | GTTKN | GTETKN | EQUALTKN | NOTEQUALTKN | ORTKN | ANDTKN;

exp             : exp PLUSTKN { EXP_PushOperator($2); } term { IR_MakeEXP();} 
				| exp MINUSTKN { EXP_PushOperator($2); }  term  { IR_MakeEXP();}
				| term;

term    		: term TIMESTKN { EXP_PushOperator($2); }  factor  { IR_MakeEXP();}
				| term DIVTKN { EXP_PushOperator($2); } factor  { IR_MakeEXP();}
				| factor

values          : INTVALTKN 
				| DOUBLEVALTKN  
				| STRINGVALTKN   
				| TRUETKN  
				| FALSETKN;

factor			: LEFTPTKN { /* fake bottom */ } exp { /* fake bottom */ } RIGHTPTKN
				| var  { EXP_PushOperand($1, "var");  }
				| values { EXP_PushOperand($1, "const"); }
				| callstmt { EXP_PushOperand($1, "func");  } ;

callstmt        : IDTKN LEFTPTKN args RIGHTPTKN  { get_symbol($1, "global", "func"); };

// Me falta la semantica de variables
args            : /* empty */ | arglist
arglist         : arglist COMMATKN exp | exp;

returnstmt      : RETURNFUNCTKN exp SEMICOLONTKN { $$ = $2; };
		
%%


int yyerror(char * message)
	
{ fprintf(outputFile,"at line %d: %s\n",g_lineno,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}