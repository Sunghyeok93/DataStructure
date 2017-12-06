#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "queue.h"

// 큐생성 및 초기화 함수
//qPtr- 큐 구조체 주소, size - 큐의 크기
void intitQueue(Queue * qPtr, int size)
{
	qPtr->qSize = size;
	qPtr->front = 0;
	qPtr->rear = 0;
	qPtr->queue = (DataType *)calloc(sizeof(DataType), qPtr->qSize);
}

//큐에 데이터 하나를 저장함
//qPtr-큐 구조체 주소, indata - 큐에 저장할 데이터, 성공 true, 실패 false 리턴
int enqueue(Queue * qPtr, DataType inData)
{
	if (isQueueFull(qPtr) == 1)
	{
		printf("큐가 가득 찼습니다.\n");
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


//큐에서 데이터 하나를 꺼냄
//qPtr - 큐 구조체의 주소, getdata - 꺼낸 데이터를 저장할 기억공간의 주소, 성공 true, 실패 false 리턴
int dequeue(Queue * qPtr, DataType * getData)
{
	if (isQueueEmpty(qPtr) == 1)
	{
		printf("큐가 비었습니다.");
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

//큐 내의 모든 데이터를 출력(dequeue와 다름)
//qPtr - 큐 구조체 주소, print - datatype의 내용을 출력하는 출력보조함수
void printQueue(const Queue * qPtr, void(*print)(DataType *))
{
	//front값이 rear값보다 작을수도 있으니 아래와 같은 코드!
	//대소비교로 하면 닶없음
	for (int i = qPtr->front; i != qPtr->rear; i=(i+1)%qPtr->qSize)
	{
		print(&(qPtr->queue[i]));
	}
	return;
}

//큐 소멸 함수
//qPtr- 큐 구조체 주소
void destroyQueue(Queue * qPtr)
{
	free(qPtr->queue);
	qPtr->queue = NULL;
	qPtr->front = 0;
	qPtr->qSize = 0;
	qPtr->rear = 0;
}

//큐가 비어있는가 검사
//qPtr - 큐 구조체 주소, 비어있으면  true, 아니면 false 리턴
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

//큐가 꽉찼는지 검사
//찼으면 true, 아니면 false 리턴
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