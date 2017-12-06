#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//initStack() - ��ũ�帮��Ʈ�� �����Ǵ� ���� �����Լ�
//sPtr - ���ð��� ����ü�� �ּ�
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
//push()- ���ÿ� ������ �ϳ��� ������
//sptr - ���ñ���ü�� �ּ�
//indata - ���ÿ� ������ ������
//�����ϸ� true, �����ϸ� false ����
int push(Stack *sPtr, DataType indata)
{
	Snode * new_snode = (Snode *)calloc(1, sizeof(Snode));
	if (new_snode == NULL)
	{
		printf("make node ����\n");
		return false;
	}
	new_snode->data = indata;
	new_snode->next = sPtr->head->next;
	sPtr->head->next = new_snode;
	return 1;
}
//pop() - ���ÿ��� �����͸� �ϳ� ����
//�����ϸ� Ʈ��, �����ϸ� false����
int pop(Stack *sPtr, DataType *popData)
{
	if (isStackEmpty(sPtr) == 1)
	{
		printf("������ ����ֽ��ϴ�.");
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

//printstack() - ������ ��� �����͸� �����
//print - datatype�� ������ ����ϴ� �����Լ�
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
	printf("�����޸� �Ҵ� ���� �� ����˴ϴ�. \n");
}
int getStackTop(Stack *sPtr, DataType *getData)
{
	sPtr->cur = sPtr->head->next;
	*getData = sPtr->cur->data;
	if (getData->age != NULL)return 1;
	else return 0;
}
//isstackempty() - ������ ����ִ°� �˻�.
//���������true �ƴϸ�false
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