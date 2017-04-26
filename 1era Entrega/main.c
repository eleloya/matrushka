#include "common.h"
#include "lex.yy.c"

FILE * inputFile;
FILE * outputFile;

int main(int argc, char * argv[] ){ 
  char filename[256]; //The name of the file containing the source code
  if (argc != 2){ 
			fprintf(stderr,"Invalid command\n");
		 	fprintf(stderr,"Usage: %s source.mka\n",argv[0]);
      exit(1);
  }else{
  		strcpy(filename,argv[1]) ;
  		inputFile = fopen(filename,"r");
  		if (inputFile==NULL){ 
				fprintf(stderr,"Error trying to open '%s'\n",filename);
    		exit(1);
  		}
	}
  outputFile = stdout;
  
	fprintf(outputFile,"\nCompiling: %s\n",filename);
	
	fprintf(outputFile,"\n   ###################");
	fprintf(outputFile,"\n        SCANNER       ");
	fprintf(outputFile,"\n   ###################\n\n");
	
	//while (nextToken()!=ENDFILETKN);
	parse();
	
	// free resources
  fclose(inputFile);
	return 0;
}