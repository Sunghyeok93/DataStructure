#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "queue.h"

// ť���� �� �ʱ�ȭ �Լ�
//qPtr- ť ����ü �ּ�, size - ť�� ũ��
void intitQueue(Queue * qPtr, int size)
{
	qPtr->qSize = size;
	qPtr->front = 0;
	qPtr->rear = 0;
	qPtr->queue = (DataType *)calloc(sizeof(DataType), qPtr->qSize);
}

//ť�� ������ �ϳ��� ������
//qPtr-ť ����ü �ּ�, indata - ť�� ������ ������, ���� true, ���� false ����
int enqueue(Queue * qPtr, DataType inData)
{
	if (isQueueFull(qPtr) == 1)
	{
		printf("ť�� ���� á���ϴ�.\n");
		return FALSE;
	}
	else
	{
		qPtr->queue[qPtr->rear] = inData;
		(qPtr->rear)++;
		qPtr->rear = (qPtr->rear) % qPtr->qSize;
		return TRUE;
	}
	
}


//ť���� ������ �ϳ��� ����
//qPtr - ť ����ü�� �ּ�, getdata - ���� �����͸� ������ �������� �ּ�, ���� true, ���� false ����
int dequeue(Queue * qPtr, DataType * getData)
{
	if (isQueueEmpty(qPtr) == 1)
	{
		printf("ť�� ������ϴ�.");
		return FALSE;
	}
	else
	{
		*getData = qPtr->queue[qPtr->front];
		(qPtr->front)++;
		qPtr->front = (qPtr->front) % qPtr->qSize;
		return TRUE;
	}
}

//ť ���� ��� �����͸� ���(dequeue�� �ٸ�)
//qPtr - ť ����ü �ּ�, print - datatype�� ������ ����ϴ� ��º����Լ�
void printQueue(const Queue * qPtr, void(*print)(DataType *))
{
	//front���� rear������ �������� ������ �Ʒ��� ���� �ڵ�!
	//��Һ񱳷� �ϸ� ������
	for (int i = qPtr->front; i != qPtr->rear; i=(i+1)%qPtr->qSize)
	{
		print(&(qPtr->queue[i]));
	}
	return;
}

//ť �Ҹ� �Լ�
//qPtr- ť ����ü �ּ�
void destroyQueue(Queue * qPtr)
{
	free(qPtr->queue);
	qPtr->queue = NULL;
	qPtr->front = 0;
	qPtr->qSize = 0;
	qPtr->rear = 0;
}

//ť�� ����ִ°� �˻�
//qPtr - ť ����ü �ּ�, ���������  true, �ƴϸ� false ����
int isQueueEmpty(const Queue *qPtr)
{
	if (qPtr->rear == qPtr->front)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
} 

//ť�� ��á���� �˻�
//á���� true, �ƴϸ� false ����
int isQueueFull(const Queue * qPtr)
{
	if (((qPtr->rear)+1)%qPtr->qSize == qPtr->front)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}