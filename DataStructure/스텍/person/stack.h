#pragma once
#pragma warning(disable:4996)
#include "datatype.h"
enum { FALSE, TRUE };

typedef struct _stacknode Snode;

struct _stacknode
{
	DataType data;
	Snode *next;
};

typedef struct _stack
{
	Snode *head;
	Snode *tail;
	Snode *cur;
}Stack;

void initStack(Stack *sPtr);
int push(Stack *sPtr, DataType indata);
int pop(Stack *sPtr, DataType *popData);
void printStack(Stack *sPtr, void(*print)(DataType *));
void destroyStack(Stack *sPtr);
int getStackTop(Stack *sPtr, DataType *getData);
int isStackEmpty(Stack *sPtr);