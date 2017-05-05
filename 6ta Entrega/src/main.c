#include "lex.yy.c"

FILE * inputFile;
FILE * outputFile;

/*
Funcion de entrada al compilador
Realmente solo coordinada el input y el output del compilador
El codigo del compilador se encuentra en yacc.y
*/
int main(int argc, char * argv[] ){ 
	char filename[256]; //The name of the file containing the source code
	char target[256];   //The name of the file containing the intermediate code
	if (argc != 3){ 
		printf("Invalid command\n");
	 	printf("Usage: %s source.mka target.bab\n",argv[0]);
	  exit(1);
	}else{
		strcpy(filename,argv[1]);
		strcpy(target,argv[2]);
		inputFile = fopen(filename,"r");
		outputFile = fopen(target,"w");
		if (outputFile==NULL){ 
			printf("Error trying to open '%s'\n",target);
			exit(1);
		}
		if (inputFile==NULL){ 
			printf("Error trying to open '%s'\n",filename);
			exit(1);
		}
	}
	
	printf("\n###################################################");
	printf("\n        COMPILING %s      ", filename);
	printf("\n###################################################\n\n");	

	yyin = inputFile;
	yyout = outputFile;

	yyparse();	

	fclose(inputFile);
	fclose(outputFile);
	
	printf("To execute:\n");
	printf("./mvm.py %s\n", target);
	return 0;
}