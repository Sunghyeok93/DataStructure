#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedlist.h"
/*--------------------------------------------------------------------------------------
함수명 및 기능: create() - 링크드리스트 초기화
전달인자:  lp - 링크드리스트 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void create(LinkedList * lp)
{
	lp->head = (Node *)malloc(sizeof(Node)); //헤드 노드 생성
	assert(lp->head!=NULL);
	lp->tail = (Node *)malloc(sizeof(Node)); //테일 노드 생성
	assert(lp->tail!=NULL);
	/*head node와 tail node를 연결 함*/
	lp->head->prev=lp->head;
	lp->head->next=lp->tail;
	lp->tail->prev=lp->head;
	lp->tail->next=lp->tail;
	lp->cur=NULL; //cur가 NULL pointer로 초기화
	lp->length=0; //데이터 노드의 개수를 0으로 초기화

	return ;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: makeNode() - 새 노드 생성 함수
전달인자:  dataPtr - 새 노드에 저장할 데이터 영역의 주소
prev - 새 노드의 앞 노드의 주소
next - 새 노드의 뒷 노드의 주소
리턴값: 생성된 노드의 주소
--------------------------------------------------------------------------------------*/
Node * makeNode(DataType *dataPtr, Node *prev, Node *next)
{
	Node *np;
	np = (Node *)malloc(sizeof(Node)); //새로운 노드 생성
	assert(np!=NULL);
	np->prev = prev;
	np->next = next;
	np->data = *dataPtr;
	if(prev != NULL) 
		prev->next = np;
	if(next != NULL)
		next->prev = np;
	return np;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: appendFromHead() - 헤드노드 뒤에 새 노드 추가(역순 저장)
전달인자: lp - 링크드리스트 정보 구조체의 주소
dataPtr - 새 노드에 저장할 데이터 영역의 주소
리턴값: 추가한 노드의 주소
--------------------------------------------------------------------------------------*/
Node * appendFromHead(LinkedList *lp, DataType *dataPtr)  
{
	lp->cur = makeNode(dataPtr, lp->head, lp->head->next);  //새로운 노드 생성
	assert(lp->cur!=NULL);
	lp->length++; //데이터개수 1 증가

	return lp->cur;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: appendFromTail() - 테일노드 앞에 새 노드 추가(정순 저장)
전달인자: lp - 링크드리스트 정보 구조체의 주소
dataPtr - 새 노드에 저장할 데이터 영역의 주소
리턴값: 추가한 노드의 주소
--------------------------------------------------------------------------------------*/
Node * appendFromTail(LinkedList *lp, DataType *dataPtr) 
{
	lp->cur = makeNode(dataPtr, lp->tail->prev, lp->tail);  //새로운 노드 생성
	assert(lp->cur!=NULL);
	lp->length++; //데이터개수 1 증가

	return lp->cur;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: display() - 리스트내의 모드 데이터 노드 출력
전달인자: lp - 링크드리스트 정보 구조체의 주소
print - 노드 내 data영역 출력을 위한 보조함수의 시작주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void display(LinkedList *lp, void (*print)(DataType *))     
{
	lp->cur = lp->head->next;

	while(lp->cur != lp->tail)
	{
		print(&lp->cur->data);
		lp->cur = lp->cur->next;
	}
	return;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: searchUnique() - 전달된 데이터와 일치하는 노드 검색 함수
전달인자: lp - 링크드리스트 정보 구조체의 주소
dataPtr - 검색할 데이터가 저장된 영역의 주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴값: 찾은 노드의 주소 리턴/없을 시 NULL pointer 리턴
--------------------------------------------------------------------------------------*/
Node * searchUnique(LinkedList *lp, DataType *dataPtr, int (*compare)(DataType *,DataType *))
{
	lp->cur=lp->head->next;  // 첫 데이터 노드를 가리키게 하고
	while(lp->cur!=lp->tail) // 맨 뒷 노드까지 검색
	{
		if(compare(&lp->cur->data, dataPtr)==0) //데이터가 있으면 현재 위치 리턴
		{
			return lp->cur;
		}
		lp->cur=lp->cur->next; //위치를 다음노드로 옮김
	}
	return NULL; //데이터가 없으면 NULL 리턴
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: searchDuplicate() - 전달된 데이터와 일치하는 모든 노드를 다중 검색하는 함수
전달인자: lp - 링크드리스트 정보 구조체의 주소
searchCnt - 찾은 노드의 개수를 저장할 영역의 주소
dataPtr - 검색할 데이터가 저장된 영역의 주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴값: 찾은 노드의 주소목록배열의 시작 주소 리턴/없을 시 NULL pointer 리턴
--------------------------------------------------------------------------------------*/
Node ** searchDuplicate(LinkedList *lp, int *searchCnt,  DataType *dataPtr, int (*compare)(DataType *, DataType *)) // dataPtr과 일치하는 노드의 주소를 담고 있는 Node *배열의 시작주소 리턴/없을 시 NULL pointer 리턴
{
	Node **searchPtr;
	int i=0;  
	*searchCnt = 0; // 찾은 노드의 개수를 count할 변수를 0으로 초기화

	lp->cur=lp->head->next;  // 첫 데이터 노드를 가리키게 하고
	while(lp->cur!=lp->tail) // 맨 뒷 노드까지 검색
	{
		if(compare(&lp->cur->data, dataPtr)==0) // 찾았으면
		{
			++*searchCnt;  // 해당 노드를 찾을 때 마다 count값 증가
		}
		lp->cur=lp->cur->next; // 위치를 다음노드로 옮김
	}

	if(*searchCnt == 0) // 찾는 노드가 한건도 없으면
		return NULL; //데이터가 없으면 NULL 리턴

	searchPtr = (Node **)malloc(sizeof(Node *) * *searchCnt);

	lp->cur=lp->head->next;  // 첫 데이터 노드를 가리키게 하고
	while(lp->cur!=lp->tail) // 맨 뒷 노드까지 검색
	{
		if(compare(&lp->cur->data, dataPtr)==0) // 찾았으면
		{
			searchPtr[i]=lp->cur;  // 찾은 노드의 주소를 배열에 저장
			i++;
		}
		lp->cur=lp->cur->next; //위치를 다음노드로 옮김
	}
	return searchPtr;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: deleteNode() - 리스트내에서 target 노드 삭제
전달인자: lp - 링크드리스트 정보 구조체의 주소
target - 삭제할 노드의 시작주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void deleteNode(LinkedList *lp, Node *target)
{
	if(target==NULL) 
		return;
	//삭제할 데이터의 앞,뒤 노드를 연결시킴
	target->prev->next=target->next; 
	target->next->prev=target->prev;
	free(target);       // target노드 삭제
	lp->length--;       // 데이터 개수 1 감소
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: destroy() - 리스트내에서 모든 노드 삭제(head, tail 노드 포함)
전달인자: lp - 링크드리스트 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void destroy(LinkedList *lp)
{ 
	while(lp->head->next != lp->tail) // 데이터 노드가 있다면 해제
	{
		deleteNode(lp,lp->head->next); // head 노드 바로 뒷 노드를 삭제
	}
	free(lp->head); // head 노드 삭제
	free(lp->tail); // tail 노드 삭제
	lp->head = lp->cur = lp->tail = NULL; //모든 포인터를 NULL로 초기화
	lp->length = 0; //데이터개수 0으로 초기화
	return ;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: sortList() - 리스트내의 노드를 보조함수의 기준대로 정렬하는 함수
전달인자: lp - 링크드리스트 정보 구조체의 주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void sortList(LinkedList *lp, int (*compare)(DataType *, DataType *))  // 노드 정렬
{
	Node *tp;
	Node *target;
	DataType temp;  // swap용 임시변수 

	lp->cur=lp->head->next;  // 첫 데이터 노드를 가리키게 하고
	while(lp->cur!=lp->tail) // 맨 뒷 노드까지 검색
	{
		target = lp->cur;
		tp=lp->cur->next; // cur의 다음 노드를 가리키게 함
		while(tp!=lp->tail)
		{
			if(compare(&target->data, &tp->data) > 0)
			{
				target = tp;
			}
			tp=tp->next;
		}
		temp = lp->cur->data;
		lp->cur->data = target->data;
		target->data = temp;

		lp->cur=lp->cur->next;
	}
	return;
}
