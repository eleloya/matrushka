/*
Jose Luis Loya
A01111663
*/
#include <stdio.h>
#include <string.h>

//Hashes work better if the size is prime
#define SYMBOL_TABLE_SIZE 2131

int g_intcount = 0;
int g_doublecount = 0;
int g_booleancount = 0;
int g_stringcount = 0;

struct symbol{
    char *value; //identifierName
		char *typeName;
		char *contextName;
		char *symbolKind;
		int memoryLocation;
		int number;
};

//Auxiliary funcion
char* concat(char *a,char *b)
{
    char *result = malloc(strlen(a)+strlen(b)+1); //+1 for the zero-terminator
		if(NULL==result){
			printf("Error allocating memory for string concat");
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
	keyString = concat(value,"_");
	keyString = concat(keyString,contextName);
	
	len = strlen(keyString);	
	for(i = 0; i < len; i++){
		key += ((key << 5) + key) + keyString[i];
	}	
	free(keyString);	
	return key;
}

unsigned int hash(char *value, char *contextName, int i){	
    return (hash_key(value, contextName) + i) % SYMBOL_TABLE_SIZE;
}

unsigned int locate(struct symbol hashtable[], char *identifierName, char *contextName){
    unsigned int i,key;
    for (i=0; i< SYMBOL_TABLE_SIZE ; i++){
        key = hash(identifierName, contextName, i);
        if (NULL == hashtable[key].value || strcmp(hashtable[key].value, identifierName) ==0)
					break;
    }
	return key;
}

int member(struct symbol hashtable[], char *identifierName, char *contextName){
	unsigned int b = locate(hashtable, identifierName, contextName);
	
	if (NULL == hashtable[b].value)
		return 0;
	else
		return (strcmp(hashtable[b].value, identifierName)==0);
}

char * memberKind(struct symbol hashtable[], char *identifierName, char *contextName){
	unsigned int b = locate(hashtable, identifierName, contextName);
	
	if (NULL == hashtable[b].value)
		return NULL;
	else
		return hashtable[b].symbolKind;
}


char * memberType(struct symbol hashtable[], char *identifierName, char *contextName){
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

int memberNumber(struct symbol hashtable[], char *identifierName, char *contextName){
	unsigned int b = locate(hashtable, identifierName, contextName);	
	if (NULL == hashtable[b].value){
		 b = locate(hashtable, identifierName, "global");
  }		
	
	if (NULL == hashtable[b].value){
		return -1;
	}else{
		return hashtable[b].number;
	}
}

int generateAddress(char *typeName){
	//TO-DO Check for NULLS on symbolKind
	
	//Check for boundaries. If it overlaps stop execution
	
	int offset = 0;
	if(strcmp(typeName,"int")==0){
		offset = 1000 + (4*g_intcount++);
	}
	if(strcmp(typeName,"double")==0){
		offset = 2000 + (8*g_doublecount++);
	}
	if(strcmp(typeName,"boolean")==0){
		offset = 3000 + (8*g_booleancount++);	
	}
	if(strcmp(typeName,"string")==0){
		offset = 4000 + (140*g_stringcount++); // Just like twitter :p
	}
	
	return offset;
}

int insert(struct symbol hashtable[], char *typeName, char *identifierName, char *contextName, char *symbolKind){
	unsigned int key;	
	int address = generateAddress(typeName);
	key = locate(hashtable, identifierName, contextName);
	int numero = 1;
	//Lo que podria hacer es. checar cuantos existen que tengan ya ese contexto.
	//Y eso guardalo como number
	
	
	//Checamos si existen elementos pasados con el mismo contexto
	for(int i=0;i<SYMBOL_TABLE_SIZE;i++){
		if(NULL != hashtable[i].value){
			if(strcmp(hashtable[i].contextName,contextName)==0){
				numero++;
			}
		}
	}
	
	if (NULL == hashtable[key].value){
		hashtable[key].value = strdup(identifierName);
		hashtable[key].contextName = strdup(contextName);
		hashtable[key].typeName = strdup(typeName);
		hashtable[key].symbolKind =  strdup(symbolKind);
		hashtable[key].memoryLocation = address;
		hashtable[key].number = numero;
		return 0;
	}	
	return 1;
}


void init_hash_table(struct symbol hashtable[]){
	unsigned int key;
	
	for (key=0; key < SYMBOL_TABLE_SIZE; key++)
		hashtable[key].value = NULL;
}
