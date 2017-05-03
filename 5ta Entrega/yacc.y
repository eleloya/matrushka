%{
#include "util/string_stack.c"
#include "util/int_stack.c"
#include "util/hash.c"
#define YYPARSER 
#define YYSTYPE char *
#define VERBOSE 0	
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
	if(strcmp(operand1,"boolean")==0 && strcmp(operand2,"boolean")){
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
	if(response_local==0 && response_global==0){
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
	
	if(response_global){
		offset = memberNumber(SymbolTable, operand, "global");	
		sprintf(offset_string, "%d", offset);
		operand = concat("(",concat("\%GLOBALS",concat("+",concat(offset_string,")"))));
	}else{
		offset = memberNumber(SymbolTable, operand, PRG_GetScope());	
		sprintf(offset_string, "%d", offset);
		operand = concat("(",concat("\%STACK",concat("+",concat(offset_string,")"))));
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
		printf("LINE: %-4d  CALL: EXP_PushOperator(NULL)\t", g_lineno);
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

void IR_AddEXP(char *operator, char *operandA, char *operandB, char *resultado){
	if(VERBOSE)
		printf("LINE: %-4d IR_AddEXP(%s,%s,%s,%s)\n", g_lineno, operator,operandA,operandB, resultado);
	
	// IADD OPA OPB T1
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
	
	if(response_global){
		offset = memberNumber(SymbolTable, identifier, "global");	
		sprintf(offset_string, "%d", offset);
		identifier = concat("(",concat("\%GLOBALS",concat("+",concat(offset_string,")"))));
	}else{
		offset = memberNumber(SymbolTable, identifier, PRG_GetScope());	
		sprintf(offset_string, "%d", offset);
		identifier = concat("(",concat("\%STACK",concat("+",concat(offset_string,")"))));
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
	sprintf(jmp_address, " %d", program_counter+1);
	
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
	
	PRG_SaveSymbol(getTypeFromSymbol(PRG_GetScope(), PRG_GetScope()), temporal_variable, PRG_GetScope(), "tmp"); 
	
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
	IR_AddEXP(operator,operand1,operand2,temporal_variable);
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

/*
		
$ para absolutos
% para direcciones

Funciones Auxiliares:
-> Funcion que me regrese el numero de variables locales (var,param,temp) de una funcion.
-> Funcion que me regrese el numero de parametros de una funcion

Atributos para el grammar de funcion:
-> "Generar label" donde empieza la funcion.
	+ Cambiar la direccion de memoria de la funcion hacia la ubicación en IRCode de la funcion
-> "Generar retorno" al acabar la funcion.

Atributos para llamadas de funciones:
-> Al principio. Verificar que exista. 
-> Al principio. Generar ERA tamaño (segun # de variables)
-> Checar semantica de parametros.
	-> (a) Tenemos una lista no ordenada de parametros de la funcion
	-> Recibimos siempre parametro por parametro.
	-> Podemos generar un stack de tiposParametr desde (a)
	-> Hacer pop de un parametro (esta en operandsStack y typeStack). 
	   -> Buscar un elemento en tiposParametro del mismo tipo y eliminarlo.
	-> Si no se encuentra alguno tipo de tiposParametro: typemismatch.
-> Igual que el anterior. En cada parametro:
	-> Generar "PARAMETRO, Argumento, Parametro K"
-> Donde acaban los parametros.
	-> Si el numero de elementos en tiposParametro es distinto a cero: insufficient parameters.
-> Al acabar el function name. Generar un "GOSUB, nombre-proc, dir-de-inicio"


*/
%%
	//TO-DO pasar las dos funciones de al final para el final de main.c
	//que pedo con los programas sin secerto.. checar si se awita el shift reduce
	//remplazar esa funcion de al final con una seccion de los tamaños del ERA:
program   		: secrets { PRG_Initialize(); } vardeclarations functions eraupdate { DBG_PrintSymbolTable(SymbolTable); DBG_PrintIRCode(); }
				| secrets { PRG_Initialize(); } functions eraupdate
eraupdate       : { PRG_ERAUpdate(); }
										

secrets			: secrets secret
				| secret

secret			: CIPHERTKN STRINGVALTKN COMMATKN STRINGVALTKN SEMICOLONTKN

functions       : functions function
				| function;

function		: FUNCTKN type OPENBLOCKTKN IDTKN { IR_MakeFUNCTION($4); PRG_SetScope($4); PRG_SaveSymbol($2, $4, "global", "func");  } LEFTPTKN params RIGHTPTKN OPENBLOCKTKN funcbody { IR_MakeFUNCTIONEND(); } ENDFUNCTKN;

funcbody		: /* empty */ | vardeclarations blockstmts
				| blockstmts

params			: /* empty */ | paramlist;

paramlist       : paramlist COMMATKN param 
				| param;

param           : type IDTKN { PRG_SaveSymbol($1, $2, PRG_GetScope(), "param"); };

						
vardeclarations : vardeclarations vardeclaration SEMICOLONTKN;
				| vardeclaration SEMICOLONTKN;

vardeclaration  : type IDTKN { PRG_SaveSymbol($1, $2, PRG_GetScope(), "var"); }
				| type IDTKN LEFTBTKN INTVALTKN RIGHTBTKN; // NOT YET

type   			: INTTKN | DOUBLETKN | STRINGTKN | BOOLTKN;


blockstmts      : blockstmts blockstmt;
				| blockstmt;

blockstmt       : assignstmt SEMICOLONTKN | returnstmt SEMICOLONTKN | ifstmt | iterstmt | iostmt SEMICOLONTKN | callstmt SEMICOLONTKN;

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
			
expstmt         : expstmt compoperator {  EXP_PushOperator($2); } exp { IR_MakeEXP(); } 
				| exp;

compoperator    : LTTKN | LTETKN | GTTKN | GTETKN | EQUALTKN | NOTEQUALTKN | ORTKN | ANDTKN;

exp             : exp additiveoperator { EXP_PushOperator($2); } term { IR_MakeEXP();} 
				| term;
additiveoperator: MINUSTKN | PLUSTKN;

term    		: term TIMESTKN { EXP_PushOperator($2); }  factor  { IR_MakeEXP();}
				| term DIVTKN { EXP_PushOperator($2); } factor  { IR_MakeEXP();}
				| factor

values          : INTVALTKN 
				| DOUBLEVALTKN  
				| STRINGVALTKN   
				| TRUETKN  
				| FALSETKN;

factor			: LEFTPTKN { /* fake bottom */ } exp { /* fake bottom */ } RIGHTPTKN
				| var  { EXP_PushOperand($1, "var"); }
				| values { EXP_PushOperand($1, "const"); }
				| callstmt {  IR_MakeCALL($1); };

callstmt        : IDTKN { IR_MakeERA($1);} LEFTPTKN args RIGHTPTKN  { PRG_GetSymbol($1, "global", "func"); };

// Me falta la semantica de variables
args            : /* empty */ | arglist
arglist         : arglist COMMATKN exp {IR_MakeSTACKPUSH(); } | exp {IR_MakeSTACKPUSH(); };

returnstmt      : RETURNFUNCTKN expstmt { IR_MakeRETURN(); };
		
%%


int yyerror(char * message)
	
{ fprintf(outputFile,"at line %d: %s\n",g_lineno,message);
  //fprintf(outputFile,"token: %d\n\n", yychar);
  return 1;
}