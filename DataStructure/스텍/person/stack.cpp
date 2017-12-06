#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//initStack() - 링크드리스트로 관리되는 스택 생성함수
//sPtr - 스택관리 구조체의 주소
void initStack(Stack *sPtr)
{
	sPtr->head = (Snode *)calloc(1, sizeof(Snode));
	assert(sPtr->head != NULL);
	sPtr->tail = (Snode *)calloc(1, sizeof(Snode));
	assert(sPtr->tail != NULL);

	sPtr->head->next = sPtr->tail;
	sPtr->tail->next = sPtr->tail;
	sPtr->cur = NULL;
	return;
}
//push()- 스택에 데이터 하나를 저장함
//sptr - 스택구조체의 주소
//indata - 스택에 저장할 데이터
//성공하면 true, 실패하면 false 리턴
int push(Stack *sPtr, DataType indata)
{
	Snode * new_snode = (Snode *)calloc(1, sizeof(Snode));
	if (new_snode == NULL)
	{
		printf("make node 실패\n");
		return false;
	}
	new_snode->data = indata;
	new_snode->next = sPtr->head->next;
	sPtr->head->next = new_snode;
	return 1;
}
//pop() - 스택에서 데이터를 하나 꺼냄
//성공하면 트루, 실패하면 false리턴
int pop(Stack *sPtr, DataType *popData)
{
	if (isStackEmpty(sPtr) == 1)
	{
		printf("스택이 비어있습니다.");
		return false;
	}
	else
	{
		sPtr->cur = sPtr->head->next;
		*popData = sPtr->cur->data;
		sPtr->head->next = sPtr->cur->next;
		free(sPtr->cur);
		return true;
	}
}

//printstack() - 스택의 모든 데이터를 출력함
//print - datatype의 내용을 출력하는 보조함수
void printStack(Stack *sPtr, void(*print)(DataType *))
{
	sPtr->cur = sPtr->head->next;
	printf("\n");
	while (sPtr->cur != sPtr->tail)
	{
		print(&sPtr->cur->data);
		sPtr->cur = sPtr->cur->next;
	}
}


void destroyStack(Stack *sPtr)
{
	Snode * tp;
	sPtr->cur = sPtr->head->next;
	while (sPtr->cur != sPtr->tail)
	{
		tp = sPtr->cur->next;
		free(sPtr->cur);
		sPtr->cur = tp;
	}
	free(sPtr->head);
	free(sPtr->tail);
	printf("동적메모리 할당 해제 및 종료됩니다. \n");
}
int getStackTop(Stack *sPtr, DataType *getData)
{
	sPtr->cur = sPtr->head->next;
	*getData = sPtr->cur->data;
	if (getData->age != NULL)return 1;
	else return 0;
}
//isstackempty() - 스택이 비어있는가 검사.
//비어있으면true 아니면false
int isStackEmpty(Stack *sPtr)
{
	if (sPtr->head->next == sPtr->tail)
	{
		return true;
	}
	else
	{
		return false;
	}
}