#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
/*--------------------------------------------------------------------------------------
  함수명및기능 : initStack() -  링크드리스트로 관리되는 스택 생성 함수
  전달인자 : sPtr - 스택관리 구조체의 주소
  리턴값 : 없음
--------------------------------------------------------------------------------------*/
void initStack(Stack *sPtr)
{
	sPtr->head = (Snode *)malloc(sizeof(Snode)); //헤드 노드 생성
	assert(sPtr->head!=NULL);
	sPtr->tail = (Snode *)malloc(sizeof(Snode)); //테일 노드 생성
	assert(sPtr->tail!=NULL);
	/*헤드노드가 테일노드를, 테일노드가 헤드노드를 가리키게 함*/
	sPtr->head->next=sPtr->tail;
	sPtr->tail->next=sPtr->tail;
	sPtr->cur = NULL;
	return ;
}
/*--------------------------------------------------------------------------------------
  함수명및기능 : push() - 스택에 데이터 하나를 저장함
  전달인자 : sPtr - 스택구조체의 주소
           inData - 스택에 저장할 데이터
  리턴값 : 성공적으로 저장하면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int push(Stack *sPtr, DataType inData) /* stack에 데이터 저장하기 */
{
	sPtr->cur = (Snode *)malloc(sizeof(Snode)); //새로운 노드 생성
	if(sPtr->cur==NULL)  // 메모리 할당 실패하면 push실패
	{
		return FALSE;
	}
	//노드를 헤드노드 바로 뒤에 노드 추가
	sPtr->cur->next=sPtr->head->next;
	sPtr->head->next=sPtr->cur;
	sPtr->cur->data = inData; //데이터 복사
	return TRUE;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능 : pop() - 스택에서 데이터 하나를 꺼냄
  전달인자 : sPtr - 스택구조체의 주소
             popData - 꺼낸 데이터를 저장할 기억공간의 주소
  리턴값 : 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int pop(Stack *sPtr, DataType *popData)
{
	if(sPtr->head->next == sPtr->tail)  // stack이 비어있으면 pop실패
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
  함수명및기능 : printStack() - 스택의 모든 데이터를 출력 함
  전달인자 : sPtr - 스택구조체의 주소
             print -  DataType의 내용을 출력하는 출력 보조 함수
  리턴값 : 없음
--------------------------------------------------------------------------------------*/
void printStack(Stack *sPtr, void(*print)(DataType *))
{
	if(isStackEmpty(sPtr)==TRUE) 
	{
		printf("Stack이 비어있습니다!!\n");
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
  함수명및기능 : destroyStack() - 스택 소멸 함수
  전달인자 : sPtr - 스택구조체의 주소
  리턴값 : 없음
--------------------------------------------------------------------------------------*/
void destroyStack(Stack *sPtr)
{
	while(sPtr->head->next != sPtr->tail) //맨 뒤의 노드까지 가면서
	{
		sPtr->cur = sPtr->head->next;
		sPtr->head->next = sPtr->head->next->next;
		free(sPtr->cur);
	}
	free(sPtr->head); // 헤드노드 삭제
	free(sPtr->tail); // 테일노드 삭제
	sPtr->head = sPtr->cur = sPtr->tail = NULL; //모든 포인터를 NULL로 초기화

	return ;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: getStackTop() - 스택내의 최상단의 값을 읽어오는 함수(pop하지는 않음)
  전달인자: sPtr - 스택구조체의 주소
            getData - 꺼낸 데이터를 저장할 기억공간의 주소
  리턴값: 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int getStackTop(Stack *sPtr, DataType *getData)
{
	if(isStackEmpty(sPtr))  // stack이 비어있으면 pop실패
	{
		return FALSE;
	}
	*getData = sPtr->head->next->data;
	return TRUE;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: isStackEmpty() - 스택이 비어있는가 검사
  전달인자: sPtr - 스택구조체의 주소
  리턴값: 비어있으면 TRUE 리턴, 비어있지 않으면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int isStackEmpty(Stack *sPtr)
{
	if(sPtr->head->next == sPtr->tail) 
		return TRUE;
	else 
		return FALSE;
}
