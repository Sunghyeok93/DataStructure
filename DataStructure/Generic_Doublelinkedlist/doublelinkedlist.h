#pragma once
#pragma warning(disable : 4996)


typedef struct _node Node;
struct _node{
	Node *prev;  // �� ��带 ����Ű�� ���
	Node *next;  // �� ��带 ����Ű�� ���
};

typedef struct _linkedList{
	Node *head; // head ��带 ����Ű�� ���
	Node *tail; // tail ��带 ����Ű�� ���
	Node *cur;  // �۾��� ����� �Ǵ� ��带 ����Ű�� ���
	int length; // ������ ����� ���� ���� ���
}LinkedList;

// double linkedlist�� �ʱ�ȭ ��Ų��.
void create(LinkedList *linkedList);

// ����� �ڿ� �� ��� �߰�(���� ����) - �߰��� ������� �ּ� ����
// item : �߰��� ������ �ϳ��� �����ϰ� �ִ� ���� �ּ�
// size : �߰��� ������ �ϳ��� ũ��
// myMemCpy : �߰��� �����͸� �����ϴ� ���� �Լ��� �ּ�
Node *appendFromHead(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

// ���ϳ�� �տ� �� ��� �߰�(���� ����) - �߰��� ������� �ּ� ����
Node *appendFromTail(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

// index ��� �ڿ� �� ��� ���� - �߰��� ������� �ּ� ����
Node *insertAfter(LinkedList *linkedList, Node *index, void *item, size_t size, void (*myMemCpy)(void *, void *));

// index ��� �տ� �� ��� ���� - �߰��� ������� �ּ� ����
Node *insertBefore(LinkedList *linkedList, Node *index, void *item, size_t size, void (*myMemCpy)(void *, void *));

// ���޹��� �ּ��� ��� ���� - ������ ����� �ּ� ����
// dataFree : ������ ����� ����Ÿ������ �ΰ� �޸� �ִ� ��� �ΰ� �޸𸮸� ó���ϴ� ���� �Լ��� �ּ� 
Node *nodeDelete(LinkedList *linkedList, Node *index, void (*dataFree)(void *));

// target�� �ش��ϴ� ù��° ������ �˻� - ã�� ����� �ּ� ����, ��ã���� NULL pointer ����
// compare : ã�� ����� ������ ������ ���ϴ� ���� �Լ��� �ּ�
Node *linearSearchUnique(LinkedList *linkedList, void *target,int (*compare)(void *, void *));

// target�� �ش��ϴ� ������ ��� �˻� - ã�� ������ �ּҵ��� ������ �迭�� �����ּ� ����, ��ã���� NULL pointer ����
// searchNodeCount : ã�� ����� ������ ������ ������ ���� �ּ�
Node **linearSearchDuplicate(LinkedList *linkedList, void *target,int *searchNodeCount,int (*compare)(void *, void *));

// index Node�� ������ ������ getData�� ����Ű�� ������ �������ִ� �Լ�
void getAt(Node *index, void *getData, void (*myMemCpy)(void *, void *));

// ����� ������ ������ swap�ϴ� ���·� ��Ʈ�ϴ� �Լ�, ��Ʈ ������ compare�Լ��� ���뿡 ���ؼ� ���� ��
void sort(LinkedList *list, size_t size, int (*compare)(void *, void *),  void (*myMemCpy)(void *, void *), void (*dataFree)(void *));

// ��ũ�帮��Ʈ ���� ��� ��� ����ϱ�
// dataPrint : ����� ������ ������ ������ִ� ���� �Լ��� �ּ�
void display(LinkedList *linkedList, void (*dataPrint)(void *));

// ��ũ�帮��Ʈ ���� ��� ��� �����ϱ�(head node, tail node ����
// dataFree : ������ ����� ����Ÿ������ �ΰ� �޸� �ִ� ��� �ΰ� �޸𸮸� ó���ϴ� ���� �Լ��� �ּ� 
void destroy(LinkedList *linkedList, void (*dataFree)(void *));