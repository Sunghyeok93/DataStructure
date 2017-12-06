#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedlist.h"

/* ------------------------------------------------
�Լ��� �� ��� : create() - ��ũ�帮��Ʈ �ʱ�ȭ
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
���ϰ� : ����
-------------------------------------------------*/
void create(LinkedList *lp)
{
	lp -> head = (Node *)calloc(1, sizeof(Node)); // Head Node ����
	lp -> tail = (Node *)calloc(1, sizeof(Node)); // Tail Node ����
	lp -> head -> next = lp -> tail; // 1�� ��(head.next -> tail) ����
	lp -> tail -> prev = lp -> head; // 2�� ��(tail.prev -> head) ����
	lp -> head -> prev = lp -> head; // 3�� ��(head.prev -> �ڱ��ڽ�) ����
	lp -> tail -> next = lp -> tail; // 4�� ��(tail.next -> �ڱ��ڽ�) ����
	lp -> cur = NULL;
	lp -> length = 0;
	return ;
}

/* ------------------------------------------------
�Լ��� �� ��� : makeNode() - �� ��� ���� �Լ�
�������� : dataPtr - �� ��忡 ������ ������ ������ �ּ�
		   prev - �� ����� �� ����� �ּ�
		   next - �� ����� �� ����� �ּ�
���ϰ� : ������ ����� �ּ�
-------------------------------------------------*/
Node * makeNode(DataType *dataPtr, Node *prev, Node *next)
{
	Node *np;
	np = (Node *)calloc(1, sizeof(Node));
	if (np == NULL)
	{
		printf("make node ����\n");
		return np;
	}
	np->prev = prev;
	np->next = next;
	np->prev->next = np;
	np->next->prev = np;
	
	np->data = *dataPtr;
	return np;//��������
}

/* -----------------------------------------------------------------------
�Լ��� �� ��� : appendFromHead() - ��� ��� �ڿ� �� ��� �߰�(���� ����)
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   dataPtr - �� ��忡 ������ ������ ������ �ּ�
���ϰ� : �߰��� ����� �ּ�
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
�Լ��� �� ��� : appendFromTail() - ���ϳ�� �տ� �� ��� �߰�(���� ����)
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   dataPtr - 
���ϰ� : �߰��� ����� �ּ�
--------------------------------------------------------------------------*/
Node * appendFromTail(LinkedList *lp, DataType *dataPtr)
{
	lp->cur = makeNode(dataPtr, lp->tail->prev, lp->tail);
	if (lp->cur != NULL)
	{
		lp->length++;
	}
	return lp->cur; //�����ϸ� �� ����� �ּ�, �����ϸ� NULL pointer
}

/* -----------------------------------------------------------------------
�Լ��� �� ��� : display() - ����Ʈ ���� ��� ������ ��� ���
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   print - ��� �� data���� ����� ���� �����Լ��� �����ּ�
���ϰ� : ����
-------------------------------------------------------------------------*/
void display(LinkedList *lp, void (*print)(DataType *))
{
	//��� �̵��ڵ� �ſ� �߿�!!!!!!!
	lp->cur = lp->head->next;//ù node�� ����Ű�� ��.
	printf("\n");
	while (lp->cur != lp->tail)
	{
		print(&lp->cur->data);
		lp->cur = lp->cur->next;//���� ���� �̵�
	}
	return ;
}

/* -----------------------------------------------------------------------
�Լ��� �� ��� : searchUnique() - ���޵� �����Ϳ� ��ġ�ϴ� ��� �˻� �Լ�
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   dataPtr - �˻��� �����Ͱ� ����� ������ �ּ�
		   compare - data ���� �񱳸� ���� �����Լ��� �����ּ�
���ϰ� : ã�� ����� �ּ� ����/���� �� NULL pointer ����
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
�Լ��� �� ��� : searchDuplicate() - ���޵� �����Ϳ� ��ġ�ϴ� ��� ��带 ���� �˻��ϴ� �Լ�
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   searchCnt - ã�� ����� ������ ������ ������ �ּ�
		   dataPtr - �˻��� �����Ͱ� ����� ������ �ּ�
		   compare - data ���� �� ���� �����Լ��� ���� �ּ�
���ϰ� : ã�� ����� �ּҸ�Ϲ迭�� ���� �ּ� ����/���� �� NULL pointer ����
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
�Լ��� �� ��� : deleteNode() - ����Ʈ������ target ��� ���� 
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   target - ������ ����� ���� �ּ�
���ϰ� : ����
-------------------------------------------------------------------------*/
void deleteNode(LinkedList *lp, Node *target)
{
	
	target->prev->next = target->next;
	target->next->prev = target->prev;
	free(target);

	return ;
}

/* -----------------------------------------------------------------------
�Լ��� �� ��� : deleteNode() - ����Ʈ������ target ��� ���� 
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   target - ������ ����� ���� �ּ�
���ϰ� : ����
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
	printf("�����Ҵ�޸𸮰� �����Ǿ����ϴ�.\n");
	return;
}

/* -----------------------------------------------------------------------
�Լ��� �� ��� : destroy() - ����Ʈ ������ ��� ��� ����(head, tail, ��� ����)
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
���ϰ� : ����
-------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------
�Լ��� �� ��� : sortList()-����Ʈ ���� ��带 �����Լ��� ���ش�� �����ϴ� �Լ�
�������� : lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
		   compare - data�����񱳸� ���� �����Լ��� ���� �ּ�
���� ��  : ����
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