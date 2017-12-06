#pragma once
#include "dataType.h"

typedef struct _node Node;
typedef struct _node
{
	DataType data;
	Node *left;
	Node *right;
}Node;

typedef struct _tree
{
	Node *root;
	int nodeCnt;
}Tree;

//트리 관리 구조체를 초기화하는 함수
void initTree(Tree *tr);

//새노드를 만들어 새노드의 주소를 리턴하는 함수
Node * makeNode(DataType *data, Node*, Node *);

//노드를 삽입하는 함수
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *));

//중위순회(정렬순서로 출력)
void inorderTraverse(Node *np, void(*print)(DataType*));

//전위순회
void preorderTraverse(Node *np, void(*print)(DataType*));

//후위순회
void postorderTraverse(Node *np, void(*print)(DataType*));

//data에 해당하는 노드검색 / 찾은 노드의 주소 리턴, 못찾으면 NULL 리턴
Node * searchNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *));

//data에 해당하는 노드 삭제 / 삭제한 노드의 parent의 주소 리턴
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *));

//tree내의 모든 노드 삭제(tree소멸)
void destroyTree(Tree *tr, void(*print)(DataType *));

//postorder(후위 순회)방식의 노드 삭제 재귀호출 함수
void postorderDelete(Node *np, void(*print)(DataType *));