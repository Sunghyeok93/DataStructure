#pragma once
typedef struct _stack{
	int *stack;
	int sSize;
	int top;
}Stack;

void initStack(Stack *, int);
void clearStack(Stack *);
int push(Stack*, int);
int pop(Stack*, int*);
void printStack(const Stack*);
void destroyStack(Stack *);