#include "doubleLinkedList.h"
#include <stddef.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void create(LinkedList *list)
{
	list->head=(Node *)calloc(1, sizeof(Node)); // 헤드노드 할당
	assert(list->tail!=NULL);

	list->tail=(Node *)calloc(1, sizeof(Node)); // 테일노드 할당
	assert(list->tail!=NULL);

	list->head->prev=list->head;
	list->head->next=list->tail;

	list->tail->prev=list->head;
	list->tail->next=list->tail;

	list->length=0;
	list->cur=NULL;
}
//tail노드 앞에 데이터 추가

Node *appendFromTail(LinkedList *list,void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	list->cur=(Node *)calloc(1,sizeof(Node)+size);
	if(list->cur==NULL)
	{
		return NULL;
	}
	myMemCpy(list->cur+1,item);

	list->cur->prev=list->tail->prev;
    list->cur->next=list->tail;
	list->tail->prev->next=list->cur;
	list->tail->prev=list->cur;

	list->length++;
	return list->cur;
}


//특정 데이터 추출


void  getAt(Node *index, void *getData, void (*myMemCpy)(void *, void *))
{
	myMemCpy(getData, index+1);
}

void display(LinkedList *list, void (*dataPrint)(void *))
{	 
	int i;
	if(list->length==0) return;
	list->cur=list->head->next;
	for(i=0;i<list->length;i++){
		dataPrint(list->cur+1);
		list->cur=list->cur->next;
	}
}

Node *linearSearchUnique(LinkedList *list,void *key,int (*compare)(void *, void *))
{
	int i;
	int res;
	list->cur=list->head->next;				//첫 노드 연결
	for(i=0;i<list->length;i++){
		res = compare(list->cur+1,key);
		
		if(res==0){return list->cur;}  // 찾으면 찾은 노드의 주소 리턴
		list->cur=list->cur->next;
	}
	return NULL; // 못찾으면 NULL pointer 리턴
}

Node **linearSearchDuplicate(LinkedList *list,void *key,int *searchNodeCount,int (*compare)(void *, void *))
{
	int i,j=0;
	int res;
	Node **searchNodePtr;
	*searchNodeCount = 0;
	list->cur=list->head->next;

	for(i=0;i<list->length;i++){
		res = compare(list->cur+1,key);	
		if(res==0){(*searchNodeCount)++;}
		list->cur=list->cur->next;
	}
	
	list->cur=list->head->next;
	searchNodePtr=(Node **)calloc((*searchNodeCount), sizeof(Node *));
	assert(searchNodePtr!=NULL);
	for(i=0;i<list->length;i++){
		res = compare(list->cur+1,key);
		if(res==0){
			searchNodePtr[j]=list->cur;
			j++;}
		list->cur=list->cur->next;	
	}
	return searchNodePtr;
}

void sort(LinkedList *list, size_t size, int (*compare)(void *, void *),  void (*myMemCpy)(void *, void *), void (*dataFree)(void *))
{
	Node *temp;
	void *temp2;
	int res,i,j;
	
	temp2 = calloc(1, size);
	

	list->cur=list->head->next;	
		
	for(i=0;i<list->length-1;i++){
		temp=list->cur->next;
		for(j=i+1;j<list->length;j++){
			res = compare(list->cur+1,temp+1);
			if(res==1){
				myMemCpy(temp2,temp+1);
				myMemCpy(temp+1,list->cur+1);
				myMemCpy(list->cur+1,temp2);		
			}
			temp=temp->next;
		}
		list->cur=list->cur->next;
	}

	dataFree(temp2);	
	free(temp2);
}

Node *nodeDelete(LinkedList *list, Node *index, void (*dataFree)(void *))
{
	if(index==NULL) return NULL;
	index->prev->next = index->next;
	dataFree(index+1);
	index->next->prev=index->prev;
	free(index);
	list->length--;
	return index;
}

void destroy(LinkedList *list, void (*dataFree)(void *))
{
	int n;
	n=list->length;
	for(int i=0;i<n;i++){
		list->cur=list->head->next;
		nodeDelete(list,list->cur,dataFree);		
	}
	free(list->head);
	free(list->tail);
	list->length=0;
	list->cur=NULL;
	list->head=NULL;
	list->tail=NULL;
}

Node *insertAfter(LinkedList *list, Node *index, void *item, size_t size, void (*myMemCpy)(void *, void *))
{
	list->cur = (Node *)calloc(1, sizeof(Node)+size);
	if(list->cur==NULL)  // 동적메모리 할당 실패시 NULL pointer 리턴
	{
		return NULL;
	}
	list->cur->prev = index;
	list->cur->next = index->next;
	index->next->prev = list->cur;
	index->next = list->cur;
	myMemCpy(list->cur+1,item);
	list->length++;
	return list->cur;  // node insert성공하면 성공적으로 insert한 노드의 주소 리턴
}