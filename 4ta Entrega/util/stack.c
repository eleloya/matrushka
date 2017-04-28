#define STACK_MAX 1024

struct stack {
	int data[STACK_MAX];
	int size;
};

typedef struct stack stack;
void stackInit(stack *s);
int stackTop(stack *s);
void stackPush(stack *s, int data);
int stackPop(stack *s);

void stackInit(stack *s){
	s->size=0;
}

int stackTop(stack *s){
	if(s->size==0){
		fprintf(stderr, "Error: stack empty\n");
		return -1;
	}
	
	return s->data[(s->size - 1)];
}

void stackPush(stack *s, int data){
	if (s->size < STACK_MAX)
		s->data[s->size++] = data;
	else
		fprintf(stderr, "Error: stack full\n");
}

//pops an element from the stack
//it returns the element to the caller.
int stackPop(stack *s){
	if (s->size == 0){
		fprintf(stderr, "Error: stack empty\n");
		return -1;
	}
	
	//printf("Debug stackPop() s->size = %d\r\n", s->size);
	//printf("Debug stackPop() s->data = %d\r\n\r\n", s->data[s->size - 1]);

	return s->data[--s->size];
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