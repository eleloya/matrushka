#include "lex.yy.c"

FILE * inputFile;
FILE * outputFile;

int main(int argc, char * argv[] ){ 
	char *resultado;
	char filename[256]; //The name of the file containing the source code
	char target[256]; //The name of the file containing the intermediate code
	if (argc != 3){ 
		printf("Invalid command\n");
	 	printf("Usage: %s source.mka target.bab\n",argv[0]);
	  exit(1);
	}else{
		strcpy(filename,argv[1]) ;
		strcpy(target,argv[2]) ;
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
	
	printf("\n###################");
	printf("\n     COMPILING       ");
	printf("\n###################\n\n");	

	yyin = inputFile;
	yyout = outputFile;

	yyparse();	

	fclose(inputFile);
	fclose(outputFile);
	return 0;
}