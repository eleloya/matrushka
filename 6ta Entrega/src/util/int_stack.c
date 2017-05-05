#include <stdio.h>

#define INT_STACK_MAX 1024

struct int_stack {
	int data[INT_STACK_MAX];
	int size;
};

typedef struct int_stack int_stack;

void int_stackInit(int_stack *s){
	s->size=0;
}

int int_stackTop(int_stack *s){
	if(s->size==0){
		fprintf(stderr, "Error: int_stack empty\n");
		return -1;
	}
	
	return s->data[(s->size - 1)];
}

void int_stackPush(int_stack *s, int data){
	if (s->size < INT_STACK_MAX)
		s->data[s->size++] = data;
	else
		fprintf(stderr, "Error: int_stack full\n");
}


int int_stackPop(int_stack *s){
	if (s->size == 0){
		fprintf(stderr, "Error: int_stack empty\n");
		return -1;
	}

	return s->data[--s->size];
}
