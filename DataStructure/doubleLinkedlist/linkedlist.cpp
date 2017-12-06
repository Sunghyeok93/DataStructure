#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedlist.h"
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: create() - ��ũ�帮��Ʈ �ʱ�ȭ
��������:  lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void create(LinkedList * lp)
{
	lp->head = (Node *)malloc(sizeof(Node)); //��� ��� ����
	assert(lp->head!=NULL);
	lp->tail = (Node *)malloc(sizeof(Node)); //���� ��� ����
	assert(lp->tail!=NULL);
	/*head node�� tail node�� ���� ��*/
	lp->head->prev=lp->head;
	lp->head->next=lp->tail;
	lp->tail->prev=lp->head;
	lp->tail->next=lp->tail;
	lp->cur=NULL; //cur�� NULL pointer�� �ʱ�ȭ
	lp->length=0; //������ ����� ������ 0���� �ʱ�ȭ

	return ;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: makeNode() - �� ��� ���� �Լ�
��������:  dataPtr - �� ��忡 ������ ������ ������ �ּ�
prev - �� ����� �� ����� �ּ�
next - �� ����� �� ����� �ּ�
���ϰ�: ������ ����� �ּ�
--------------------------------------------------------------------------------------*/
Node * makeNode(DataType *dataPtr, Node *prev, Node *next)
{
	Node *np;
	np = (Node *)malloc(sizeof(Node)); //���ο� ��� ����
	assert(np!=NULL);
	np->prev = prev;
	np->next = next;
	np->data = *dataPtr;
	if(prev != NULL) 
		prev->next = np;
	if(next != NULL)
		next->prev = np;
	return np;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: appendFromHead() - ����� �ڿ� �� ��� �߰�(���� ����)
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
dataPtr - �� ��忡 ������ ������ ������ �ּ�
���ϰ�: �߰��� ����� �ּ�
--------------------------------------------------------------------------------------*/
Node * appendFromHead(LinkedList *lp, DataType *dataPtr)  
{
	lp->cur = makeNode(dataPtr, lp->head, lp->head->next);  //���ο� ��� ����
	assert(lp->cur!=NULL);
	lp->length++; //�����Ͱ��� 1 ����

	return lp->cur;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: appendFromTail() - ���ϳ�� �տ� �� ��� �߰�(���� ����)
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
dataPtr - �� ��忡 ������ ������ ������ �ּ�
���ϰ�: �߰��� ����� �ּ�
--------------------------------------------------------------------------------------*/
Node * appendFromTail(LinkedList *lp, DataType *dataPtr) 
{
	lp->cur = makeNode(dataPtr, lp->tail->prev, lp->tail);  //���ο� ��� ����
	assert(lp->cur!=NULL);
	lp->length++; //�����Ͱ��� 1 ����

	return lp->cur;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: display() - ����Ʈ���� ��� ������ ��� ���
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
print - ��� �� data���� ����� ���� �����Լ��� �����ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void display(LinkedList *lp, void (*print)(DataType *))     
{
	lp->cur = lp->head->next;

	while(lp->cur != lp->tail)
	{
		print(&lp->cur->data);
		lp->cur = lp->cur->next;
	}
	return;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: searchUnique() - ���޵� �����Ϳ� ��ġ�ϴ� ��� �˻� �Լ�
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
dataPtr - �˻��� �����Ͱ� ����� ������ �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���ϰ�: ã�� ����� �ּ� ����/���� �� NULL pointer ����
--------------------------------------------------------------------------------------*/
Node * searchUnique(LinkedList *lp, DataType *dataPtr, int (*compare)(DataType *,DataType *))
{
	lp->cur=lp->head->next;  // ù ������ ��带 ����Ű�� �ϰ�
	while(lp->cur!=lp->tail) // �� �� ������ �˻�
	{
		if(compare(&lp->cur->data, dataPtr)==0) //�����Ͱ� ������ ���� ��ġ ����
		{
			return lp->cur;
		}
		lp->cur=lp->cur->next; //��ġ�� �������� �ű�
	}
	return NULL; //�����Ͱ� ������ NULL ����
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: searchDuplicate() - ���޵� �����Ϳ� ��ġ�ϴ� ��� ��带 ���� �˻��ϴ� �Լ�
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
searchCnt - ã�� ����� ������ ������ ������ �ּ�
dataPtr - �˻��� �����Ͱ� ����� ������ �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���ϰ�: ã�� ����� �ּҸ�Ϲ迭�� ���� �ּ� ����/���� �� NULL pointer ����
--------------------------------------------------------------------------------------*/
Node ** searchDuplicate(LinkedList *lp, int *searchCnt,  DataType *dataPtr, int (*compare)(DataType *, DataType *)) // dataPtr�� ��ġ�ϴ� ����� �ּҸ� ��� �ִ� Node *�迭�� �����ּ� ����/���� �� NULL pointer ����
{
	Node **searchPtr;
	int i=0;  
	*searchCnt = 0; // ã�� ����� ������ count�� ������ 0���� �ʱ�ȭ

	lp->cur=lp->head->next;  // ù ������ ��带 ����Ű�� �ϰ�
	while(lp->cur!=lp->tail) // �� �� ������ �˻�
	{
		if(compare(&lp->cur->data, dataPtr)==0) // ã������
		{
			++*searchCnt;  // �ش� ��带 ã�� �� ���� count�� ����
		}
		lp->cur=lp->cur->next; // ��ġ�� �������� �ű�
	}

	if(*searchCnt == 0) // ã�� ��尡 �Ѱǵ� ������
		return NULL; //�����Ͱ� ������ NULL ����

	searchPtr = (Node **)malloc(sizeof(Node *) * *searchCnt);

	lp->cur=lp->head->next;  // ù ������ ��带 ����Ű�� �ϰ�
	while(lp->cur!=lp->tail) // �� �� ������ �˻�
	{
		if(compare(&lp->cur->data, dataPtr)==0) // ã������
		{
			searchPtr[i]=lp->cur;  // ã�� ����� �ּҸ� �迭�� ����
			i++;
		}
		lp->cur=lp->cur->next; //��ġ�� �������� �ű�
	}
	return searchPtr;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: deleteNode() - ����Ʈ������ target ��� ����
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
target - ������ ����� �����ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void deleteNode(LinkedList *lp, Node *target)
{
	if(target==NULL) 
		return;
	//������ �������� ��,�� ��带 �����Ŵ
	target->prev->next=target->next; 
	target->next->prev=target->prev;
	free(target);       // target��� ����
	lp->length--;       // ������ ���� 1 ����
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: destroy() - ����Ʈ������ ��� ��� ����(head, tail ��� ����)
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void destroy(LinkedList *lp)
{ 
	while(lp->head->next != lp->tail) // ������ ��尡 �ִٸ� ����
	{
		deleteNode(lp,lp->head->next); // head ��� �ٷ� �� ��带 ����
	}
	free(lp->head); // head ��� ����
	free(lp->tail); // tail ��� ����
	lp->head = lp->cur = lp->tail = NULL; //��� �����͸� NULL�� �ʱ�ȭ
	lp->length = 0; //�����Ͱ��� 0���� �ʱ�ȭ
	return ;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: sortList() - ����Ʈ���� ��带 �����Լ��� ���ش�� �����ϴ� �Լ�
��������: lp - ��ũ�帮��Ʈ ���� ����ü�� �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void sortList(LinkedList *lp, int (*compare)(DataType *, DataType *))  // ��� ����
{
	Node *tp;
	Node *target;
	DataType temp;  // swap�� �ӽú��� 

	lp->cur=lp->head->next;  // ù ������ ��带 ����Ű�� �ϰ�
	while(lp->cur!=lp->tail) // �� �� ������ �˻�
	{
		target = lp->cur;
		tp=lp->cur->next; // cur�� ���� ��带 ����Ű�� ��
		while(tp!=lp->tail)
		{
			if(compare(&target->data, &tp->data) > 0)
			{
				target = tp;
			}
			tp=tp->next;
		}
		temp = lp->cur->data;
		lp->cur->data = target->data;
		target->data = temp;

		lp->cur=lp->cur->next;
	}
	return;
}
