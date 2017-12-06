#pragma once
#pragma warning(disable:4996)
#include "datatype.h"
enum {FALSE, TRUE};

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

void initStack(Stack *sPtr);  /*  링크드리스트로 관리되는 스택 생성 함수 */
int push(Stack *sPtr, DataType indata); /*  스택에 데이터 하나를 저장함 */
int pop(Stack *sPtr, DataType *popData); /*  스택에서 데이터 하나를 꺼냄 */
void printStack(Stack *sPtr, void (*print)(DataType *) );  /*  스택의 모든 데이터를 출력 함 */
void destroyStack(Stack *sPtr); /*  스택 소멸 함수 */
int getStackTop(Stack *sPtr, DataType *getData);  /*  스택내의 최상단의 값을 읽어오는 함수(pop하지는 않음) */
int isStackEmpty(Stack *sPtr); /* 스택이 비어있는가 검사 */
