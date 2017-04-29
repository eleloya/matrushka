#define STACK_MAX 1024

struct stack {
	char * data[STACK_MAX];
	int size;
};

typedef struct stack stack;
void stackInit(stack *s);
char * stackTop(stack *s);
void stackPush(stack *s, char *data);
char * stackPop(stack *s);

void stackInit(stack *s){
	s->size=0;
	for(int i=0;i<STACK_MAX;i++){
		s->data[i] = NULL;
	}
}

void printStringStack(stack *s){
	for(int i=0;i<s->size;i++){
		printf("\t|%10s|","----------");
		printf("\t|%10s|",s->data[i]);
		printf("\t|%10s|","----------");
		
	}
}

char * stackTop(stack *s){
	if(s->size==0){
		fprintf(stderr, "Error: stack empty\n");
		return NULL;
	}
	
	return s->data[(s->size - 1)];
}

//REWORK / TO-DO
//Move this to int. Return 0 on fullstack.
void stackPush(stack *s, char *data){
	int i;
	if (s->size < (STACK_MAX-1)){
		i = s->size++;
		if(s->data[i]!=NULL){
			free(s->data[i]);
		}
		s->data[i] = strdup(data);
	}else
		fprintf(stderr, "Error: stack full\n");
}

//pops an element from the stack
//it returns the element to the caller.
char * stackPop(stack *s){
	if (s->size == 0){
		fprintf(stderr, "Error: stack empty\n");
		return NULL;
	}
	
	char *result = strdup(s->data[--s->size]);
	//printf("POPPED: %s\n", result);
	return result;
}