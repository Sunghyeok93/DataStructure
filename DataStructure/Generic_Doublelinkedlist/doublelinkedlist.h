#pragma once
#pragma warning(disable : 4996)


typedef struct _node Node;
struct _node{
	Node *prev;  // 앞 노드를 가리키는 멤버
	Node *next;  // 뒷 노드를 가리키는 멤버
};

typedef struct _linkedList{
	Node *head; // head 노드를 가리키는 멤버
	Node *tail; // tail 노드를 가리키는 멤버
	Node *cur;  // 작업의 대상이 되는 노드를 가리키는 멤버
	int length; // 데이터 노드의 개수 저장 멤버
}LinkedList;

// double linkedlist를 초기화 시킨다.
void create(LinkedList *linkedList);

// 헤드노드 뒤에 새 노드 추가(역순 저장) - 추가한 새노드의 주소 리턴
// item : 추가할 데이터 하나를 저장하고 있는 곳의 주소
// size : 추가할 데이터 하나의 크기
// myMemCpy : 추가할 데이터를 복사하는 보조 함수의 주소
Node *appendFromHead(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

// 테일노드 앞에 새 노드 추가(정순 저장) - 추가한 새노드의 주소 리턴
Node *appendFromTail(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

// index 노드 뒤에 새 노드 삽입 - 추가한 새노드의 주소 리턴
Node *insertAfter(LinkedList *linkedList, Node *index, void *item, size_t size, void (*myMemCpy)(void *, void *));

// index 노드 앞에 새 노드 삽입 - 추가한 새노드의 주소 리턴
Node *insertBefore(LinkedList *linkedList, Node *index, void *item, size_t size, void (*myMemCpy)(void *, void *));

// 전달받은 주소의 노드 삭제 - 삭제한 노드의 주소 리턴
// dataFree : 삭제할 노드의 데이타영역에 부가 메모가 있는 경우 부가 메모리를 처리하는 보조 함수의 주소 
Node *nodeDelete(LinkedList *linkedList, Node *index, void (*dataFree)(void *));

// target에 해당하는 첫번째 데이터 검색 - 찾은 노드의 주소 리턴, 못찾으면 NULL pointer 리턴
// compare : 찾는 노드의 데이터 영역을 비교하는 보조 함수의 주소
Node *linearSearchUnique(LinkedList *linkedList, void *target,int (*compare)(void *, void *));

// target에 해당하는 데이터 모두 검색 - 찾은 노드들의 주소들을 저장한 배열의 시작주소 리턴, 못찾으면 NULL pointer 리턴
// searchNodeCount : 찾은 노드의 개수를 저장할 변수의 시작 주소
Node **linearSearchDuplicate(LinkedList *linkedList, void *target,int *searchNodeCount,int (*compare)(void *, void *));

// index Node의 데이터 영역을 getData가 가리키는 영역에 복사해주는 함수
void getAt(Node *index, void *getData, void (*myMemCpy)(void *, void *));

// 노드의 데이터 영역을 swap하는 형태로 소트하는 함수, 소트 기준은 compare함수의 내용에 의해서 결정 됨
void sort(LinkedList *list, size_t size, int (*compare)(void *, void *),  void (*myMemCpy)(void *, void *), void (*dataFree)(void *));

// 링크드리스트 내의 모든 노드 출력하기
// dataPrint : 노드의 데이터 영역을 출력해주는 보조 함수의 주소
void display(LinkedList *linkedList, void (*dataPrint)(void *));

// 링크드리스트 내의 모든 노드 삭제하기(head node, tail node 포함
// dataFree : 삭제할 노드의 데이타영역에 부가 메모가 있는 경우 부가 메모리를 처리하는 보조 함수의 주소 
void destroy(LinkedList *linkedList, void (*dataFree)(void *));