#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//intiStack - ������ ũ���� ������ �����ϴ� �Լ�
//sPtr - ������ �ּ�
//sSize - ������ ũ��
void initStack(Stack *sPtr, int sSize)
{
	sPtr->sSize = sSize;
	sPtr->stack = (int *)calloc(sizeof(sSize), sizeof(int));
	sPtr->top = -1;
}

//clearStack() - ���� �ʱ�ȭ�Լ�(��絥���� ���� ����)
//sPtr - ������ �ּ�
void clearStack(Stack *sPtr)
{
	for (int i = 0; i < sPtr->sSize; i++)
	{
		sPtr->stack[i] = 0;
	}
}

//push() - ���ÿ� ������ �ϳ��� ������
//sPtr - ������ �ּ�
//inData - ���ÿ� ������ ������
//���������� �����ϸ� 1, �����ϸ� 0 ����
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

//pop() - ���ÿ��� ������ �ϳ��� ����
//sPtr - ������ �ּ�
//popData - ���� �����͸� ������ �������� �ּ�
// ���������� ������ 1, �����ϸ� 0 ����
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


//printStack() - ������ ��� �����͸� �����
//sPtr - ������ �ּ�
void printStack(const Stack *sPtr)
{
	
	for (int i = sPtr->top; i > -1; i--)
	{
		printf("%5d\n", sPtr->stack[i]);
	}
}

//destroy() - ���� �Ҹ� �Լ�
//sPtr - ������ �ּ�
void destroyStack(Stack *sPtr)
{
	free(sPtr->stack);
	sPtr->sSize = 0;
	sPtr->top = -1;
	sPtr->stack = NULL;

	int* a = (int*)malloc()
}