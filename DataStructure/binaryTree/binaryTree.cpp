#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "binaryTree.h"

/* -------------------------------------------------------------------------------------
�Լ��� : initTree - Ʈ�� ���� ����ü�� �ʱ�ȭ �ϴ� �Լ�
�������� : tr - Tree ����ü�� �ּ�
���� �� : ����
--------------------------------------------------------------------------------------*/
void initTree(Tree *tr)
{
	tr->root = NULL;
	tr->nodeCnt = 0;
}
/* --------------------------------------------------------------------------------------
�Լ��� : makeNode - �� ��带 ����� �� ����� �ּҸ� �����ϴ� �Լ�
�������� : data - �� ��忡 ����� ��(������)
left - �� ����� left ��� ��
right - �� ����� right ��� ��
���� �� : �� ����� �ּ� / �޸� �Ҵ� ���� �� NULL pointer 
---------------------------------------------------------------------------------------*/
Node * makeNode(DataType *data, Node * left, Node *right)
{
	Node *np;
	np = (Node *)malloc(sizeof(Node));
	if (np != NULL) {
		np->data = *data;
		np->left = left;
		np->right = right;
	}
	return np;
}

/* --------------------------------------------------------------------------------------
�Լ��� : addNode - ��带 �����ϴ� �Լ�
�������� : tr - Tree ����ü�� �ּ�
data - �� ��忡 ����� ������ ���� ������ �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : �� ����� �ּ� / �޸� �Ҵ� ���� �� NULL pointer
---------------------------------------------------------------------------------------*/
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node *np;
	Node *parent; 
	Node *son;

	np = makeNode(data, NULL, NULL);
	assert(np != NULL);

	if (tr->root != NULL) {  // root��� ���� ��ġ�� ��带 �߰��� ���(�� ��°���� ������ ��� �߰� ��)
		son = tr->root;
		/*if (compare(data, &parent->data) > 0)
		son = tr->root->right;
		else
		son = tr->root->left;*/

		while (son != NULL) {  // ��带 �߰��� ������ ��带 ã�� ���� �ݺ�
			parent = son;
			if (compare(data, &son->data) > 0)
				son = son->right;
			else
				son = son->left;
		}
		if (compare(&np->data, &parent->data) < 0)
			parent->left = np;
		else
			parent->right = np;
	}
	else { // root��� ��ġ�� ��带 �߰��� ���
		tr->root = np;
	}
	tr->nodeCnt++;
	return np;	
}
/* --------------------------------------------------------------------------------------
�Լ��� : inorderTraverse - ������ȸ(���� ������ ���)
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void inorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np != NULL) {
		inorderTraverse(np->left, print);
		print(&np->data);
		inorderTraverse(np->right, print);
	}
}

/* --------------------------------------------------------------------------------------
�Լ��� : preorderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void preorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np != NULL) {
		print(&np->data);
		preorderTraverse(np->left, print);
		preorderTraverse(np->right, print);
	}
}
/* --------------------------------------------------------------------------------------
�Լ��� : postorderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void postorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np != NULL) {
		postorderTraverse(np->left, print);
		postorderTraverse(np->right, print);
		print(&np->data);
	}
}
/* --------------------------------------------------------------------------------------
�Լ��� : searchNode - data�� �ش��ϴ� ��� �˻�
�������� : tr - Tree ����ü�� �ּ�
data - �˻��� ������ ���� ������ �����ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : ã�� ����� �ּ� / ��ã���� NULL pointer
---------------------------------------------------------------------------------------*/
Node * searchNode(Tree *tr, DataType  *data, int(*compare)(DataType *, DataType *))
{
	Node *sp;
	sp = tr->root;
	while (sp != NULL) {
		if (compare(data, &sp->data) == 0)  // ã������!
			return sp;
		else if (compare(data, &sp->data) < 0)
			sp = sp->left;
		else
			sp = sp->right;
	}
	return NULL;
}

/* --------------------------------------------------------------------------------------
�Լ��� : deleteNode - data�� �ش��ϴ� ��� ����
�������� : tr - Tree ����ü�� �ּ�
data - ������ �������� �����ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : ������ ����� parent ����� �ּ� / ��ã����(���� ���� ��) NULL pointer
---------------------------------------------------------------------------------------*/
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node *parent;  // ������ ����� �θ���
	Node *son;     // ������ ����� �ڽĳ븩�� �� ����� �ּ� ����
	Node *del;     // ������ ���

	parent = del = tr->root;

	while (del != NULL) {
		if (compare(data, &del->data) == 0)  // ã������!
			break;
		parent = del;
		if (compare(data, &del->data) < 0)
			del = del->left;
		else
			del = del->right;
	}
	if(del == NULL) return NULL; // ���� ���� �� NULL ����

	// ����1 : ������ ����� ������ �ڽ��� ���� ���-������ ����� ���� �ڽ��� son����
	if (del->right == NULL)
		son = del->left;
	// ����2 : ������ ����� ������ �ڽ��� ���� �ڽ��� ���� ���-������ ����� ������ �ڽ��� son����
	else if (del->right->left == NULL) {
		son = del->right;
		son->left = del->left;
	}
	// ����3 : �׿� ��� ���-������ ����� ������ ����Ʈ������ ������ �����Ϳ� ���� ����� ���� ã��
	else {
		Node *temp;
		temp = del->right;
		while (temp->left->left != NULL) temp = temp->left;// ������ �����Ϳ� ���� ����� ���� ã�� ���� �̵�
		son = temp->left;// ������ �����Ϳ� ���� ����� ����� �ּҸ� son�� ����
		temp->left = son->right;// son�� del�� �ڸ��� �ö󰡰� �Ǹ� ������ son�� ������ �ڽ��� temp�� left�� ����
		// ������ ����� ����, ������ Node�� �ּҸ� son�� ����
		son->left = del->left;
		son->right = del->right;
	}
	// ������ ��� ��� �ڽ�(son) ������ �� ��带 ��ġ��Ŵ
	if (del == tr->root)
		tr->root = son;
	else if (son->data < parent->data)
		parent->left = son;
	else 
		parent->right = son;

	free(del);  // ��� ����
	--tr->nodeCnt;
	return parent;

}
/* --------------------------------------------------------------------------------------
�Լ��� : destroyTree - tree ���� ��� ��� ����(tree �Ҹ�)
�������� : tr - Tree ����ü�� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void destroyTree(Tree * tr, void(*print)(DataType *))
{
	postorderDelete(tr->root, print);  // ������ ���� ��ȸ �ϸ� ����
	tr->root = NULL;
	tr->nodeCnt = 0;
}

/* --------------------------------------------------------------------------------------
�Լ��� : postorderDelete - postorder(���� ��ȸ)����� ��� ����(���ȣ�� �Լ�)
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void postorderDelete(Node *np, void(*print)(DataType *))
{
	if (np != NULL)
	{
		postorderTraverse(np->left, print);
		postorderTraverse(np->right, print);
		print(&np->data);
		free(np);  // ��� ����
	}
	printf("\n\n");
}
