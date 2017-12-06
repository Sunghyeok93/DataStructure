#pragma once
#pragma warning(disable:4996)
#include "datatype.h"

enum {FALSE, TRUE};

typedef struct _queue
{
	DataType *queue;
	int qSize;
	int front, rear;
}Queue;

// ť���� �� �ʱ�ȭ �Լ�
void intitQueue(Queue * qPtr, int size); 

//ť�� ������ �ϳ��� ������
int enqueue(Queue * qPtr, DataType inData);

//ť���� ������ �ϳ��� ����
int dequeue(Queue * qPtr, DataType * getData);

//ť ���� ��� �����͸� ���(dequeue�� �ٸ�)
void printQueue(const Queue * qPtr, void(*print)(DataType *));

//ť �Ҹ� �Լ�
void destroyQueue(Queue * qPtr);

//ť�� ����ִ°� �˻�
int isQueueEmpty(const Queue *qPtr);

int isQueueFull(const Queue * qPtr);