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

//Ʈ�� ���� ����ü�� �ʱ�ȭ�ϴ� �Լ�
void initTree(Tree *tr);

//����带 ����� ������� �ּҸ� �����ϴ� �Լ�
Node * makeNode(DataType *data, Node*, Node *);

//��带 �����ϴ� �Լ�
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *));

//������ȸ(���ļ����� ���)
void inorderTraverse(Node *np, void(*print)(DataType*));

//������ȸ
void preorderTraverse(Node *np, void(*print)(DataType*));

//������ȸ
void postorderTraverse(Node *np, void(*print)(DataType*));

//data�� �ش��ϴ� ���˻� / ã�� ����� �ּ� ����, ��ã���� NULL ����
Node * searchNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *));

//data�� �ش��ϴ� ��� ���� / ������ ����� parent�� �ּ� ����
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *));

//tree���� ��� ��� ����(tree�Ҹ�)
void destroyTree(Tree *tr, void(*print)(DataType *));

//postorder(���� ��ȸ)����� ��� ���� ���ȣ�� �Լ�
void postorderDelete(Node *np, void(*print)(DataType *));