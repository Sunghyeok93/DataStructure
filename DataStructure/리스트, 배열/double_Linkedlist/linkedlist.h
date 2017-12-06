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


// ��ũ�帮��Ʈ �ʱ�ȭ
void create(LinkedList *ip); 

// �� ��� ���� �Լ�
Node * makeNode(DataType *dataPtr, Node *prev, Node *next); 

// ����� �ڿ� �� ��� �߰�(���� ����)
Node * appendFromHead(LinkedList *lp, DataType *dataPtr); 

// ���ϳ�� �տ� �� ��� �߰�(���� ����)
Node * appendFromTail(LinkedList *ip, DataType *dataPtr); 

// ����Ʈ ���� ��� ������ ��� ���
void display(LinkedList *lp, void (*print)(DataType *)); 

// target��� ����
void deleteNode(LinkedList *lp, Node *target); 

// dataPtr�� ��ġ�ϴ� ����� �ּ� ����/���� �� NULL pointer ����
Node * searchUnique(LinkedList *lp, DataType *dataPtr, int (*compare)(DataType *, DataType *)); 

// dataPtr�� ��ġ�ϴ� ����� �ּҸ� ��� �ִ� Node *�迭�� �����ּ� ����/���� �� NULL pointer ����
Node ** searchDuplicate(LinkedList *lp, int *searchCnt, DataType *dataPtr, int (*compare)(DataType *, DataType *)); 

// ��� ����
void sortList(LinkedList *lp, int (*compare)(DataType *, DataType *));

// ����Ʈ ���� ��� ��带 ����
void destroy(LinkedList *lp);

void deleteDuplicate(LinkedList *lp, DataType *dataPtr, int(*compare)(DataType*, DataType *));