#include<stdio.h>
#include <malloc.h>
#include <assert.h>
#include "binaryTree.h"

//Ʈ�� ���� ����ü�� �ʱ�ȭ�ϴ� �Լ�
//tr - Tree����ü�� �ּ�
void initTree(Tree *tr)
{
	tr->root = NULL;
	tr->nodeCnt = 0;
}

//����带 ����� ������� �ּҸ� �����ϴ� �Լ�
//data - ����忡 ����� ������, left - �� ����� left��� ��, right - ������� right �����
//���� - ������� �ּ�, �޸� �Ҵ� ���н� null pointer
Node * makeNode(DataType *data, Node* left, Node * right)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (node != NULL)
	{
		node->data = *data;
		node->left = left;
		node->right = right;
	}
	return node;
}

//��带 �����ϴ� �Լ�
//tr - Ʈ�� ����ü�� �ּ�, data - ����忡 ����� ������ ���� ������ �ּ�
//compare - data���� �񱳸� ���� �����Լ��� �����ּ�
//���� - ������� �ּ� / �޸� �Ҵ� ���н� null pointer
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	tr->nodeCnt++;
	//data���� �� ��尡 �߰��� ��ġ�� ã�� ��
	Node *parent, *son, *np;
	//tree���� ������ ���� �����ϸ鼭 �߰��Ұ�(�ߺ������ʹ� ���°����� ����)
	// : ���� �ڽĳ���� �� < �θ� ����� �� < ������ �ڽ� ����� ��
	//makenode()�Լ��� �̿��Ͽ� ����带 ������ �� tree�� �߰�
	np = makeNode(data, NULL, NULL);
	if (np == NULL)
	{
		return NULL;
	}
	if (tr->root != NULL)
	{
		son = tr->root;
		parent = tr->root;
		while (son != NULL)
		{
			parent = son;
			if (np->data > son->data)
			{
				son = son->right;
			}
			else
			{
				son = son->left;
			}
		}
		if (np->data > parent->data)
		{
			parent->right = np;
		}
		else
		{
			parent->left = np;
		}
	}
	else{
		tr->root = np;
	}
	return np;
}

//������ȸ(���ļ����� ���)
//np - �湮�� ����� �ּ�
//print - data������ ����ϴ� �����Լ��� �ּ�
void inorderTraverse(Node *np, void(*print)(DataType*))
{
	//���� subtree �湮
	//�ش� ��� �湮
	//������ subtree�湮
	//����Լ�ȣ���
	if (np == NULL)
	{
		return;
	}
	
	inorderTraverse(np->left, print);
	print(&np->data);
	inorderTraverse(np->right, print);
}

//������ȸ
void preorderTraverse(Node *np, void(*print)(DataType*))
{
	//�ش���湮
	//���� subtree�湮
	//������ subtree�湮
	//���
	if (np == NULL)
	{
		return;
	}

	
	print(&np->data); 
	preorderTraverse(np->left, print);
	preorderTraverse(np->right, print);
}

//������ȸ
void postorderTraverse(Node *np, void(*print)(DataType*))
{
	
	//���� subtree�湮
	//������ subtree�湮
	//�ش���湮
	//���
	if (np == NULL)
	{
		return;
	}

	postorderTraverse(np->left, print);
	postorderTraverse(np->right, print);
	print(&np->data);
}


//data�� �ش��ϴ� ���˻� / ã�� ����� �ּ� ����, ��ã���� NULL ����
Node * searchNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node * np;
	np = tr->root;
	if (tr->root == NULL) return NULL;
	int tmp;
	while (np != NULL)
	{
		tmp = compare(&np->data, data);
		if (tmp == 1)
		{
			np = np->left;
		}
		else if (tmp == -1)
		{
			np = np->right;
		}
		else if (tmp == 0)
		{
			return np;
		}
	}
	return NULL;
	

}

//data�� �ش��ϴ� ��� ���� / ������ ����� parent�� �ּ� ����
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node * parent, *child, *del;
	Node * temp;
	parent = tr->root;
	child = tr->root;
	while (child->data != *data)
	{
		parent = child;
		if (compare(&child->data, data) > 0)
			child = child->left;
		else if (compare(&child->data, data) < 0)
			child = child->right;

		if (child == NULL)
			return NULL;
	}

	del = child; // ������ ��带 del�� ����

	if (del->right == NULL) // ���� 1 ������ ����� ������ �ڽ��� ���� ���
	{
		child = del->left; //������ ����� ���� �ڽ��� child ����
		if (parent->data > child->data) //del���� ���踦 ���� child�� ����
			parent->left = child;
		else
			parent->right = child;
		tr->nodeCnt--;
		return del;
	}
	else if (del->right->left == NULL)// ���� 2 ������ ����� ������ �ڽ��� �����ڽ��� ���� ���
	{
		child = del->right; // ������ ����� ������ �ڽ��� child ����
		if (child->left == NULL)
		{
			child->left = del->left; // ������ ����� �����ڽ��� ������ ����� �����ڽĿ� �������ν� Ʈ�� ����
			if (parent->data > child->data)
				parent->left = child;
			else
				parent->right = child;
			tr->nodeCnt--;
			return del;
		}
	}
	else // ���� 3
	{
		temp = del->right;
		child = temp->left;
		while (child->left != NULL) // ���� �� ������ ã�ư�
		{
			temp = child;
			child = child->left;
		}

		if (child->right != NULL) // ������ ��尡 ���̾ƴϸ� temp���ʿ� ������ ��带 ���δ�
			temp->left = child;
		else // ������ ��尡 ���̸� temp ������ ���� ��
			temp->left = NULL;

		if (*data != tr->root->data) // ������ ������ ��Ʈ�����Ͱ� �ƴҶ�
		{
			if (parent->data > child->data)
				parent->left = child;
			else
				parent->right = child;

		}
		else // ������ ������ ��Ʈ�������϶�
		{
			tr->root = child; // child�� ��Ʈ�� �ְ� ������ �������
			child->left = del->left;
			child->right = del->right;
		}

		tr->nodeCnt--;
		return del;

	}
}

//tree���� ��� ��� ����(tree�Ҹ�)
void destroyTree(Tree *tr, void(*print)(DataType *))
{
	postorderDelete(tr->root, print);
	tr->nodeCnt = 0;
	printf("\n");
}

//postorder(���� ��ȸ)����� ��� ���� ���ȣ�� �Լ�
void postorderDelete(Node *np, void(*print)(DataType *))
{
	if (np == NULL)
		return;

	postorderDelete(np->left, print);
	postorderDelete(np->right, print);
	print(&np->data);
	free(np);
}