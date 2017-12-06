#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : initStack() -  ��ũ�帮��Ʈ�� �����Ǵ� ���� ���� �Լ�
  �������� : sPtr - ���ð��� ����ü�� �ּ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void initStack(Stack *sPtr)
{
	sPtr->head = (Snode *)malloc(sizeof(Snode)); //��� ��� ����
	assert(sPtr->head!=NULL);
	sPtr->tail = (Snode *)malloc(sizeof(Snode)); //���� ��� ����
	assert(sPtr->tail!=NULL);
	/*����尡 ���ϳ�带, ���ϳ�尡 ����带 ����Ű�� ��*/
	sPtr->head->next=sPtr->tail;
	sPtr->tail->next=sPtr->tail;
	sPtr->cur = NULL;
	return ;
}
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : push() - ���ÿ� ������ �ϳ��� ������
  �������� : sPtr - ���ñ���ü�� �ּ�
           inData - ���ÿ� ������ ������
  ���ϰ� : ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int push(Stack *sPtr, DataType inData) /* stack�� ������ �����ϱ� */
{
	sPtr->cur = (Snode *)malloc(sizeof(Snode)); //���ο� ��� ����
	if(sPtr->cur==NULL)  // �޸� �Ҵ� �����ϸ� push����
	{
		return FALSE;
	}
	//��带 ����� �ٷ� �ڿ� ��� �߰�
	sPtr->cur->next=sPtr->head->next;
	sPtr->head->next=sPtr->cur;
	sPtr->cur->data = inData; //������ ����
	return TRUE;
}
/*--------------------------------------------------------------------------------------
  �Լ��� �� ��� : pop() - ���ÿ��� ������ �ϳ��� ����
  �������� : sPtr - ���ñ���ü�� �ּ�
             popData - ���� �����͸� ������ �������� �ּ�
  ���ϰ� : ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int pop(Stack *sPtr, DataType *popData)
{
	if(sPtr->head->next == sPtr->tail)  // stack�� ��������� pop����
	{
		return FALSE;
	}
	*popData = sPtr->head->next->data;
	sPtr->cur = sPtr->head->next;
	sPtr->head->next =  sPtr->head->next->next;
	free(sPtr->cur);
	return TRUE;
}
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : printStack() - ������ ��� �����͸� ��� ��
  �������� : sPtr - ���ñ���ü�� �ּ�
             print -  DataType�� ������ ����ϴ� ��� ���� �Լ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void printStack(Stack *sPtr, void(*print)(DataType *))
{
	if(isStackEmpty(sPtr)==TRUE) 
	{
		printf("Stack�� ����ֽ��ϴ�!!\n");
		return;
	}
	sPtr->cur = sPtr->head->next;
	while(sPtr->cur != sPtr->tail)
	{
		print(&sPtr->cur->data);
		sPtr->cur = sPtr->cur->next;
	}
	printf("\n");
	return;
}
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : destroyStack() - ���� �Ҹ� �Լ�
  �������� : sPtr - ���ñ���ü�� �ּ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void destroyStack(Stack *sPtr)
{
	while(sPtr->head->next != sPtr->tail) //�� ���� ������ ���鼭
	{
		sPtr->cur = sPtr->head->next;
		sPtr->head->next = sPtr->head->next->next;
		free(sPtr->cur);
	}
	free(sPtr->head); // ����� ����
	free(sPtr->tail); // ���ϳ�� ����
	sPtr->head = sPtr->cur = sPtr->tail = NULL; //��� �����͸� NULL�� �ʱ�ȭ

	return ;
}
/*--------------------------------------------------------------------------------------
  �Լ��� �� ���: getStackTop() - ���ó��� �ֻ���� ���� �о���� �Լ�(pop������ ����)
  ��������: sPtr - ���ñ���ü�� �ּ�
            getData - ���� �����͸� ������ �������� �ּ�
  ���ϰ�: ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int getStackTop(Stack *sPtr, DataType *getData)
{
	if(isStackEmpty(sPtr))  // stack�� ��������� pop����
	{
		return FALSE;
	}
	*getData = sPtr->head->next->data;
	return TRUE;
}
/*--------------------------------------------------------------------------------------
  �Լ��� �� ���: isStackEmpty() - ������ ����ִ°� �˻�
  ��������: sPtr - ���ñ���ü�� �ּ�
  ���ϰ�: ��������� TRUE ����, ������� ������ FALSE ����
--------------------------------------------------------------------------------------*/
int isStackEmpty(Stack *sPtr)
{
	if(sPtr->head->next == sPtr->tail) 
		return TRUE;
	else 
		return FALSE;
}
