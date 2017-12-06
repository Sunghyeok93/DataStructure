#pragma once
#pragma warning (disable : 4996)
#include "datatype.h"

typedef struct _node Node;

struct _node{
	Node *prev;
	DataType data;
	Node *next;
};

typedef struct _linkedList{
	Node *head;
	Node *cur;
	Node *tail;
	int length;
}LinkedList;


// 링크드리스트 초기화
void create(LinkedList *ip); 

// 새 노드 생성 함수
Node * makeNode(DataType *dataPtr, Node *prev, Node *next); 

// 헤드노드 뒤에 새 노드 추가(역순 저장)
Node * appendFromHead(LinkedList *lp, DataType *dataPtr); 

// 테일노드 앞에 새 노드 추가(정순 저장)
Node * appendFromTail(LinkedList *ip, DataType *dataPtr); 

// 리스트 내의 모든 데이터 노드 출력
void display(LinkedList *lp, void (*print)(DataType *)); 

// target노드 삭제
void deleteNode(LinkedList *lp, Node *target); 

// dataPtr과 일치하는 노드의 주소 리턴/없을 시 NULL pointer 리턴
Node * searchUnique(LinkedList *lp, DataType *dataPtr, int (*compare)(DataType *, DataType *)); 

// dataPtr과 일치하는 노드의 주소를 담고 있는 Node *배열의 시작주소 리턴/없을 시 NULL pointer 리턴
Node ** searchDuplicate(LinkedList *lp, int *searchCnt, DataType *dataPtr, int (*compare)(DataType *, DataType *)); 

// 노드 정렬
void sortList(LinkedList *lp, int (*compare)(DataType *, DataType *));

// 리스트 내의 모든 노드를 삭제
void destroy(LinkedList *lp);

void deleteDuplicate(LinkedList *lp, DataType *dataPtr, int(*compare)(DataType*, DataType *));