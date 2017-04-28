#define STACK_MAX 1024

struct stringStack {
	char * data[STACK_MAX];
	int size;
};

typedef struct stringStack stringStack;
void stringStackInit(stringStack *s);
char * stringStackTop(stringStack *s);
void stringStackPush(stringStack *s, char *data);
char * stringStackPop(stringStack *s);

void stringStackInit(stringStack *s){
	s->size=0;
	for(int i=0;i<STACK_MAX;i++){
		s->data[i] = NULL;
	}
}

void printStringStack(stringStack *s){
	for(int i=0;i<s->size;i++){
		printf("\t|%10s|","----------");
		printf("\t|%10s|",s->data[i]);
		printf("\t|%10s|","----------");
		
	}
}

char * stringStackTop(stringStack *s){
	if(s->size==0){
		fprintf(stderr, "Error: stack empty\n");
		return NULL;
	}
	
	return s->data[(s->size - 1)];
}

void stringStackPush(stringStack *s, char * data){
	int indexs;
	if (s->size < STACK_MAX){
		indexs = s->size++;
		if(s->data[indexs]!=NULL){
			free(s->data[indexs]);
		}
		s->data[indexs] = strdup(data);
	}else
		fprintf(stderr, "Error: stack full\n");
}

//pops an element from the stack
//it returns the element to the caller.
char * stringStackPop(stringStack *s){
	if (s->size == 0){
		fprintf(stderr, "Error: stack empty\n");
		return NULL;
	}
	
	//printf("Debug stackPop() s->size = %d\r\n", s->size);
	//printf("Debug stackPop() s->data = %d\r\n\r\n", s->data[s->size - 1]);
	char *result = strdup(s->data[--s->size]);
	return result;
}

/*
int main(){
	stack platos;
	
	stackInit(&platos);
	stackPush(&platos,2);
	stackPush(&platos,3);
	stackPush(&platos,5);
	stackPop(&platos);
	stackPop(&platos);
	stackPop(&platos);
	stackPop(&platos);
	
	return 0;
}
*/