// �Ϲ�ȭ�� ��ũ�� ����Ʈ ����� (�����޸��Ҵ� �̿�_Person����ü)

#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
#include<windows.h>
#include "doubleLinkedList.h"
#include "person.h"

int  menu(char**, int);
void input(LinkedList *);
void listDisplay(LinkedList *);
void search(LinkedList *);
void searchName(LinkedList *, int(*)(void *, void *));
void searchAge(LinkedList *, int(*)(void *, void *));
void searchNameAge(LinkedList *list, int(*cmp)(void *, void *));
void fun_delete(LinkedList *);
void gotoxy(int, int);

int main()
{
	LinkedList list;  // double LinkedList�� �����ϴ� LinkedList ����ü ���� ����
	char *menuList[] = { "�Է��ϱ�", "����ϱ�", "�˻��ϱ�", "�����ϱ�","����"};
	int menuSize;  // �޴��� ���� ���� ����
	char mNum;  // ���õ� �޴���ȣ ���� ����

	menuSize = sizeof(menuList)/sizeof(menuList[0]); // �޴� ���� ���

	create(&list); // ����ִ� double LinkedList ����

	while(1){
		mNum=menu(menuList, menuSize); // �Էµ� �޴��� ��ȣ�� mNum�� ���Ϲ���
		if(mNum==menuSize) {break;}  // ������ �����ϱ� �޴��� �ԷµǾ����� ���ѹݺ����� Ż���Ѵ�.
		switch(mNum){
			case 1 : input(&list); break;
			case 2 : sort(&list, sizeof(Person), personNameCompare, personMemCpy, personFree);
				     listDisplay(&list); 
					 break;
			case 3 : search(&list); break;
			case 4 : fun_delete(&list); break;
		}
	}
       
	destroy(&list, personFree); // �������� ���ϳ����� ��� ��� �����ϱ�
	
	return 0;
}
//--------------------------------------------------------------------------
void input(LinkedList *list)
{
	Person pa;    // ����ü �ӽú���
	char tname[100];
	
	while(1)
	{
		printf("���� �Է�(���͸� �Է��ϸ� ����) : ");
		gets(tname);
		if(tname[0]==NULL) {break;}  // �׳� ����ġ�� ����
		pa.name = (char *) calloc(strlen(tname) + 1, sizeof(char));
		strcpy(pa.name, tname);
		printf("���� �Է� : ");
		scanf("%d", &pa.age);
		fflush(stdin);
		appendFromTail(list, &pa, sizeof(Person), personMemCpy);
		free(pa.name);
	}
}
//--------------------------------------------------------------------------
void listDisplay(LinkedList *list)
{
	Person pa={NULL, 0};   // �ϳ��� �����Ͱ��� �����ؿ� ����ü ����, �ݵ�� NULL�� �ʱ�ȭ-�޸� ���� ���
	int i=0;     // ����� ������ ��ȣ ���� ����

	if(list->length==0) 
	{
		printf("����� �����Ͱ� �ϳ��� �����ϴ�.\n");
		getch();
		return;
	}
	list->cur = list->head->next;  // ����� ù ��� �����ϱ�
	while(list->cur != list->tail)  // tail node �� �������� ����ϱ�
	{
		getAt(list->cur, &pa, personMemCpy); // ������ �ϳ� �о����
		printf("%d. ", ++i);
		personPrint(&pa);  // �о�� ������ ����ϱ�
		list->cur = list->cur->next; // ���� ���� �̵��ϱ�
		if(i%10==0)    // 10�� ��� �� ��� ����
		{
			getch();
		}
	}
	if(i%10!=0) //i�� 10���� ������ ������ ��� �տ��� ��������Ƿ� �ٽ� ������� ����
	{
		getch();
	}
	personFree(&pa);
	return;
}
//--------------------------------------------------------------------------
void search(LinkedList *list)
{
	char *menuList[] = { "���� �˻�", "���� �˻�", "����+���� �˻�", "�˻� ����" };
	int menuSize;  // �޴��� ���� ���� ����
	int mNum;  // ���õ� �޴���ȣ ���� ����

	if(list->length==0) 
	{
		printf("����� �����Ͱ� �ϳ��� �����ϴ�.\n");
		getch();
		return;
	}

	while(1)
	{
		menuSize = sizeof(menuList)/sizeof(menuList[0]); // �޴� ���� ���

		mNum=menu(menuList, menuSize); // �Էµ� �޴��� ��ȣ�� mNum�� ���Ϲ���
		if(mNum==menuSize) {break;}
		switch(mNum)
		{
		case 1 : searchName(list, personNameCompare); break;
		case 2 : searchAge(list, personAgeCompare); break;
		case 3 : searchNameAge(list, personCompare); break;
		}
		getch();
	}
}
//--------------------------------------------------------------------------
void searchName(LinkedList *list, int(*cmp)(void *, void *))
{
	Person pa={NULL,0};   // �ӽ� ����ü ����
	char tname[100];
	Node *res;   // �˻��� ����� �����ּ� ���� ����
	printf("ã�� ���� �Է� : ");
	gets(tname);  
	pa.name = (char *) calloc(strlen(tname) + 1, sizeof(char));
	strcpy(pa.name, tname);
	res=linearSearchUnique(list, &pa, personNameCompare);
	if(res==NULL)
	{
		printf("ã�� ����� �����ϴ�.\n");
	}
	else
	{
		personPrint(res+1); // res+1�� �ϸ� res�� ����Ű�� ��� �ڿ� �پ��ִ� Person ����ü ������ �ּҰ� ���Ǿ� ����
	}
	free(pa.name);
}
//--------------------------------------------------------------------------
void searchAge(LinkedList *list, int(*cmp)(void *, void *))
{
	Person pa;   // �ӽ� ����ü ����
	Node *res;   // �˻��� ����� �����ּ� ���� ����
	printf("ã�� ���� �Է� : ");
	scanf("%d", &pa.age);
	fflush(stdin);
	pa.name=NULL;
	res=linearSearchUnique(list, &pa, personAgeCompare);
	if(res==NULL)
	{
		printf("ã�� ����� �����ϴ�.\n");
	}
	else
	{
		personPrint(res+1);
	}
}
//--------------------------------------------------------------------------
void searchNameAge(LinkedList *list, int(*cmp)(void *, void *))
{
	Person pa;   // �ӽ� ����ü ����
	Node *res;   // �˻��� ����� �����ּ� ���� ����
	char tname[100];
	printf("ã�� ���� �Է� : ");
	scanf("%s", tname);
	printf("ã�� ���� �Է� : ");
	scanf("%d", &pa.age);
	fflush(stdin);
	pa.name = (char *) calloc(strlen(tname)+1, sizeof(char));
	strcpy(pa.name, tname);
	res=linearSearchUnique(list, &pa, personCompare);
	if(res==NULL)
	{
		printf("ã�� ����� �����ϴ�.\n");
	}
	else
	{
		personPrint(res+1);
	}
	free(pa.name);
}
//--------------------------------------------------------------------------
void fun_delete(LinkedList *list)
{
	Person pa;   // �ӽ� ����ü ����
	Node *res;   // �˻��� ����� �����ּ� ���� ����
	char tname[100];

	while(1)
	{
		printf("������ ���� �Է� : ");
		gets(tname);
		if(tname[0]==NULL) {break;}  // �׳� ����ġ�� ����
		pa.name = (char *) calloc(strlen(tname)+1, sizeof(char));
		strcpy(pa.name, tname);
		res=linearSearchUnique(list, &pa, personNameCompare);
		if(res==NULL)
		{
			printf("ã�� ����� �����ϴ�.\n");
		}
		else
		{
			nodeDelete(list, res, personFree); // ã�� ��� ����
			printf("[%s]�� �����Ǿ����ϴ�.\n", pa.name);
		}
		free(pa.name);
	}
}
//--------------------------------------------------------------------------
int menu(char ** menu_list, int mSize)
 {
	int num=0, i;
	system("cls");
	for(i=0; i<mSize; i++){  // �޴� ���ڿ��� ����ϴ� �ݺ���
		gotoxy(30,5+i*2); 	printf("%2d. %s",i+1, menu_list[i]);
	}
	while(num<1 || num>mSize){  //�Է��� �޴���ȣ�� ��ȿ�� ��ȣ�� �ƴϸ� �ٽ� �Է�
		gotoxy(25,17);printf("* Select menu No. : _\b");
		scanf("%d", &num);
		fflush(stdin); // �Է��� ���ڵ��� �Ǿ��� �ѹ��ڸ� ����ϱ� ���� ���۳��� ������ ���� ��� ����.
	}
	return(num);
 }
 //--------------------------------------------------------------------------
 void gotoxy(int x, int y) 
 { 
	COORD Pos = {x - 1, y - 1}; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); 
 }