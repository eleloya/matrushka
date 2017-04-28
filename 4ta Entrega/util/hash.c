/*
Jose Luis Loya
A01111663
*/
#include <stdio.h>
#include <string.h>

//Hashes work better if the size is prime
#define HASH_TABLE_SIZE 2131

struct hashrecord{
    char *value; //identifierName
		char *typeName;
		char *contextName;
		char *symbolKind;
};

//Auxiliary funcion
char* concat(char *a,char *b)
{
    char *result = malloc(strlen(a)+strlen(b)+1); //+1 for the zero-terminator
		if(NULL==result){
			printf("Error allocating memory in hashing");
			exit(1);
		}
    strcpy(result, a);
    strcat(result, b);
    return result;
}

// El hash_key es una combinación del identifier y su contexto.
// No se ocupa su clase ni su tipo. Dado que no puede haber distintos objetos con el mismo nombre en el mismo contexto
unsigned long hash_key(char *value,char *contextName){
	unsigned long key = 5381;
	char *keyString;
	int len;
	int i;	
	keyString = concat(value,contextName);
	
	len = strlen(keyString);	
	for(i = 0; i < len; i++){
		key += ((key << 5) + key) + keyString[i];
	}	
	free(keyString);	
	return key;
}

unsigned int hash(char *value, char *contextName, int i){	
    return (hash_key(value, contextName) + i) % HASH_TABLE_SIZE;
}

unsigned int locate(struct hashrecord hashtable[], char *identifierName, char *contextName){
    unsigned int i,key;
    for (i=0; i< HASH_TABLE_SIZE ; i++){
        key = hash(identifierName, contextName, i);
        if (NULL == hashtable[key].value || strcmp(hashtable[key].value, identifierName) ==0)
					break;
    }
	return key;
}

int member(struct hashrecord hashtable[], char *identifierName, char *contextName){
	unsigned int b = locate(hashtable, identifierName, contextName);
	
	if (NULL == hashtable[b].value)
		return 0;
	else
		return (strcmp(hashtable[b].value, identifierName)==0);
}

char * memberKind(struct hashrecord hashtable[], char *identifierName, char *contextName){
	unsigned int b = locate(hashtable, identifierName, contextName);
	
	if (NULL == hashtable[b].value)
		return NULL;
	else
		return hashtable[b].symbolKind;
}


char * memberType(struct hashrecord hashtable[], char *identifierName, char *contextName){
	unsigned int b = locate(hashtable, identifierName, contextName);	
	if (NULL == hashtable[b].value){
		 b = locate(hashtable, identifierName, "global");
  }		
	
	if (NULL == hashtable[b].value){
		return NULL;
	}else{
		return hashtable[b].typeName;
	}
}

int insert(struct hashrecord hashtable[], char *typeName, char *identifierName, char *contextName, char *symbolKind){
	unsigned int key;	
	key = locate(hashtable, identifierName, contextName);
	if (NULL == hashtable[key].value){
		hashtable[key].value = strdup(identifierName);
		hashtable[key].contextName = strdup(contextName);
		hashtable[key].typeName = strdup(typeName);
		hashtable[key].symbolKind =  strdup(symbolKind);
		return 0;
	}	
	return 1;
}

void print_hash_table(struct hashrecord hashtable[]){
	printf("\nSYMBOL TABLE\n");
	printf("%15s  %10s  ------  -----  ----\n","----------","----------");
	printf("%15s  %-10s  type    kind   key\n","identifier", "context");
	printf("%15s  %10s  ------  -----  ----\n","----------","----------");
	
  for (int i=0; i< HASH_TABLE_SIZE ; i++){
      if (NULL != hashtable[i].value)
				printf("%15s  %10s  %6s  %5s  %d\n", hashtable[i].value, hashtable[i].contextName, hashtable[i].typeName, hashtable[i].symbolKind, i);
  }
}

void init_hash_table(struct hashrecord hashtable[]){
	unsigned int key;
	
	for (key=0; key < HASH_TABLE_SIZE; key++)
		hashtable[key].value = NULL;
}
