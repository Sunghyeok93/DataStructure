#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//intiStack - 지정된 크기의 스택을 생성하는 함수
//sPtr - 스택의 주소
//sSize - 스택의 크기
void initStack(Stack *sPtr, int sSize)
{
	sPtr->sSize = sSize;
	sPtr->stack = (int *)calloc(sizeof(sSize), sizeof(int));
	sPtr->top = -1;
}

//clearStack() - 스택 초기화함수(모든데이터 삭제 개념)
//sPtr - 스택의 주소
void clearStack(Stack *sPtr)
{
	for (int i = 0; i < sPtr->sSize; i++)
	{
		sPtr->stack[i] = 0;
	}
}

//push() - 스택에 데이터 하나를 저장함
//sPtr - 스택의 주소
//inData - 스택에 저장할 데이터
//성공적으로 저장하면 1, 실패하면 0 리턴
int push(Stack *sPtr, int inData)
{
	
	if (sPtr->top == sPtr->sSize-1)
	{
		return 0;
	}
	else
	{
		(sPtr->top)++;
		sPtr->stack[sPtr->top] = inData;
		return 1;
	}
}

//pop() - 스택에서 데이터 하나를 꺼냄
//sPtr - 스택의 주소
//popData - 꺼낸 데이터를 저장한 기억공간의 주소
// 성공적으로 꺼내면 1, 실패하면 0 리턴
int pop(Stack *sPtr, int *popData)
{
	if (sPtr->top >= 0 && sPtr->top <= sPtr->sSize-1)
	{
		*popData = sPtr->stack[sPtr->top];
		(sPtr->top)--;
		return 1;
	}
	else
	{
		return 0;
	}
	
}


//printStack() - 스택의 모든 데이터를 출력함
//sPtr - 스택의 주소
void printStack(const Stack *sPtr)
{
	
	for (int i = sPtr->top; i > -1; i--)
	{
		printf("%5d\n", sPtr->stack[i]);
	}
}

//destroy() - 스택 소멸 함수
//sPtr - 스택의 주소
void destroyStack(Stack *sPtr)
{
	free(sPtr->stack);
	sPtr->sSize = 0;
	sPtr->top = -1;
	sPtr->stack = NULL;

	int* a = (int*)malloc()
}