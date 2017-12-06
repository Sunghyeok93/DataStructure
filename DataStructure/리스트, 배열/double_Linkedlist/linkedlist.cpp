#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedlist.h"

/* ------------------------------------------------
함수명 및 기능 : create() - 링크드리스트 초기화
전달인자 : lp - 링크드리스트 정보 구조체의 주소
리턴값 : 없음
-------------------------------------------------*/
void create(LinkedList *lp)
{
	lp -> head = (Node *)calloc(1, sizeof(Node)); // Head Node 생성
	lp -> tail = (Node *)calloc(1, sizeof(Node)); // Tail Node 생성
	lp -> head -> next = lp -> tail; // 1번 선(head.next -> tail) 연결
	lp -> tail -> prev = lp -> head; // 2번 선(tail.prev -> head) 연결
	lp -> head -> prev = lp -> head; // 3번 선(head.prev -> 자기자신) 연결
	lp -> tail -> next = lp -> tail; // 4번 선(tail.next -> 자기자신) 연결
	lp -> cur = NULL;
	lp -> length = 0;
	return ;
}

/* ------------------------------------------------
함수명 및 기능 : makeNode() - 새 노드 생성 함수
전달인자 : dataPtr - 새 노드에 저장할 데이터 영역의 주소
		   prev - 새 노드의 앞 노드의 주소
		   next - 새 노드의 뒷 노드의 주소
리턴값 : 생성된 노드의 주소
-------------------------------------------------*/
Node * makeNode(DataType *dataPtr, Node *prev, Node *next)
{
	Node *np;
	np = (Node *)calloc(1, sizeof(Node));
	if (np == NULL)
	{
		printf("make node 실패\n");
		return np;
	}
	np->prev = prev;
	np->next = next;
	np->prev->next = np;
	np->next->prev = np;
	
	np->data = *dataPtr;
	return np;//성공수행
}

/* -----------------------------------------------------------------------
함수명 및 기능 : appendFromHead() - 헤드 노드 뒤에 새 노드 추가(역순 저장)
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   dataPtr - 새 노드에 저장할 데이터 영역의 주소
리턴값 : 추가한 노드의 주소
-------------------------------------------------------------------------*/
Node * appendFromHead(LinkedList *lp, DataType *dataPtr)
{
	lp->cur = makeNode(dataPtr, lp->head, lp->head->next);
	if (lp->cur != NULL)
	{
		lp->length++;
	}
	return lp->cur;
}

/* -----------------------------------------------------------------------
함수명 및 기능 : appendFromTail() - 테일노드 앞에 새 노드 추가(정순 저장)
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   dataPtr - 
리턴값 : 추가한 노드의 주소
--------------------------------------------------------------------------*/
Node * appendFromTail(LinkedList *lp, DataType *dataPtr)
{
	lp->cur = makeNode(dataPtr, lp->tail->prev, lp->tail);
	if (lp->cur != NULL)
	{
		lp->length++;
	}
	return lp->cur; //성공하면 새 노드의 주소, 실패하면 NULL pointer
}

/* -----------------------------------------------------------------------
함수명 및 기능 : display() - 리스트 내의 모든 데이터 노드 출력
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   print - 노드 내 data영역 출력을 위한 보조함수의 시작주소
리턴값 : 없음
-------------------------------------------------------------------------*/
void display(LinkedList *lp, void (*print)(DataType *))
{
	//노드 이동코드 매우 중요!!!!!!!
	lp->cur = lp->head->next;//첫 node를 가리키게 함.
	printf("\n");
	while (lp->cur != lp->tail)
	{
		print(&lp->cur->data);
		lp->cur = lp->cur->next;//다음 노드로 이동
	}
	return ;
}

/* -----------------------------------------------------------------------
함수명 및 기능 : searchUnique() - 전달된 데이터와 일치하는 노드 검색 함수
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   dataPtr - 검색할 데이터가 저장된 영역의 주소
		   compare - data 영역 비교를 위한 보조함수의 시작주소
리턴값 : 찾은 노드의 주소 리턴/없을 시 NULL pointer 리턴
-------------------------------------------------------------------------*/

Node * searchUnique(LinkedList * lp, DataType * dataPtr, int(*compare)(DataType *, DataType *))  
{
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail)
	{
		if (!compare(dataPtr, &lp->cur->data))
			return lp->cur;

		lp->cur = lp->cur->next;
	}
	return NULL;
}
/* -----------------------------------------------------------------------
함수명 및 기능 : searchDuplicate() - 전달된 데이터와 일치하는 모든 노드를 다중 검색하는 함수
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   searchCnt - 찾은 노드의 개수를 저장할 영역의 주소
		   dataPtr - 검색할 데이터가 저장된 영역의 주소
		   compare - data 영역 빅를 위한 보조함수의 시작 주소
리턴값 : 찾은 노드의 주소목록배열의 시작 주소 리턴/없을 시 NULL pointer 리턴
-------------------------------------------------------------------------*/
Node ** searchDuplicate(LinkedList *lp, int *searchCnt, DataType *dataPtr, int (*compare)(DataType *, DataType *))
{
	Node **p = NULL;
	int i = 0;
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail)
	{
		if (compare(&lp->cur->data, dataPtr) == 0)
		{
			(*searchCnt)++;
			p = (Node**)realloc(p, sizeof(Node *)* (*searchCnt));
			p[i] = lp->cur;
			i++;
		}
		lp->cur = lp->cur->next;
	}
	return p;
}

void deleteDuplicate(LinkedList *lp, DataType *dataPtr, int(*compare)(DataType*, DataType *))
{
	Node *tp, *target;
	int res = NULL;
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail)
	{
		tp = lp->cur->next;
		if (compare(dataPtr, &(lp->cur->data)) == 0)
		{
			target = lp->cur;
			target->prev->next = lp->cur->next;
			target->next->prev = lp->cur->prev;
			free(target);
			res = 1;
		}
		lp->cur = tp;
	}
	return ;
}
/* -----------------------------------------------------------------------
함수명 및 기능 : deleteNode() - 리스트내에서 target 노드 삭제 
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   target - 삭제할 노드의 시작 주소
리턴값 : 없음
-------------------------------------------------------------------------*/
void deleteNode(LinkedList *lp, Node *target)
{
	
	target->prev->next = target->next;
	target->next->prev = target->prev;
	free(target);

	return ;
}

/* -----------------------------------------------------------------------
함수명 및 기능 : deleteNode() - 리스트내에서 target 노드 삭제 
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   target - 삭제할 노드의 시작 주소
리턴값 : 없음
-------------------------------------------------------------------------*/
void destroy(LinkedList *lp)
{
	Node * tp;
	lp->cur = lp->head->next;
	while (lp->cur != lp->tail->prev)
	{
		tp = lp->cur->next;
		free(lp->cur);
		lp->cur = tp;
	}
	free(lp->head);
	free(lp->tail);
	printf("동적할당메모리가 해제되었습니다.\n");
	return;
}

/* -----------------------------------------------------------------------
함수명 및 기능 : destroy() - 리스트 내에서 모든 노드 삭제(head, tail, 노드 포함)
전달인자 : lp - 링크드리스트 정보 구조체의 주소
리턴값 : 없음
-------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------
함수명 및 기능 : sortList()-리스트 내의 노드를 보조함수의 기준대로 정렬하는 함수
전달인자 : lp - 링크드리스트 정보 구조체의 주소
		   compare - data영역비교를 위한 보조함수의 시작 주소
리턴 값  : 없음
-------------------------------------------------------------------------*/
void sortList(LinkedList *lp, int(*compare)(DataType*, DataType *))
{
	lp->cur = lp->head->next; 
	Node * tmp;
	DataType tp;
	while (lp->cur != lp->tail)
	{
		tmp = lp->cur->next;
		while (tmp != lp->tail)
		{
			if (compare(&lp->cur->data, &tmp->data) == 1)
			{
				tp = lp->cur->data;
				lp->cur->data = tmp->data;
				tmp->data = tp;
			}
			tmp = tmp->next;
		}
		lp->cur = lp->cur->next;
	}
	return;
}