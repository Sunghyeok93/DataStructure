#pragma once
#pragma warning(disable:4996) /* VS2005 이상에서 발생하는 콘솔 함수 경고 제거 */
#include "datatype.h"

typedef struct _node Node;    // 구조체 노드 형명재지정

struct _node{         // 데이터를 보관할 노드(자기참조 구조체)
	Node *prev;               // 앞 노드를 가리키는 멤버
	DataType data;            // 데이터 저장 멤버
	Node *next;               // 뒷 노드를 가리키는 멤버
};

typedef struct _linkedList{   // 리스트 관리 구조체
	Node *head;               // 헤드포인터 (헤드노드 가리킴)
	Node *cur;                // 특정 작업 시 노드를 가리키기 위한 포인터
	Node *tail;               // 테일포인터 (테일노드 가리킴)
	int length;               // 실제 데이터노드의 갯수
}LinkedList;

//-------------------------------------------------------------------------------------------
//                                 링크드리스트 관리 함수 
//-------------------------------------------------------------------------------------------
void create(LinkedList *lp);   // 링크드리스트 초기화
Node * makeNode(DataType *dataPtr, Node *prev, Node *next);
Node * appendFromHead(LinkedList *lp, DataType *dataPtr);      // 헤드노드 뒤에 새 노드 추가(역순 저장)
Node * appendFromTail(LinkedList *lp, DataType *dataPtr);      // 테일노드 앞에 새 노드 추가(정순 저장)
void display(LinkedList *lp, void (*print)(DataType *));       // 리스트내의 모드 데이터 노드 출력
void deleteNode(LinkedList *lp, Node *target);                // target노드 삭제
Node * searchUnique(LinkedList *lp, DataType *dataPtr, int (*compare)(DataType *,DataType *)); // dataPtr과 일치하는 노드의 주소 리턴/없을 시 NULL pointer 리턴
Node ** searchDuplicate(LinkedList *lp, int *searchCnt,  DataType *dataPtr, int (*compare)(DataType *, DataType *)); // dataPtr과 일치하는 노드의 주소를 담고 있는 Node *배열의 시작주소 리턴/없을 시 NULL pointer 리턴
void sortList(LinkedList *lp, int (*compare)(DataType *, DataType *));  // 노드 정렬
void destroy(LinkedList *lp);                                   // 리스트내의 모든 노드를 삭제
