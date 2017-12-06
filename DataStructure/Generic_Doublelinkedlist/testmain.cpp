// 일반화된 링크드 리스트 만들기 (동적메모리할당 이용_Person구조체)

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
	LinkedList list;  // double LinkedList를 관리하는 LinkedList 구조체 변수 선언
	char *menuList[] = { "입력하기", "출력하기", "검색하기", "삭제하기","종료"};
	int menuSize;  // 메뉴의 개수 저장 변수
	char mNum;  // 선택된 메뉴번호 저장 변수

	menuSize = sizeof(menuList)/sizeof(menuList[0]); // 메뉴 개수 계산

	create(&list); // 비어있는 double LinkedList 생성

	while(1){
		mNum=menu(menuList, menuSize); // 입력된 메뉴의 번호를 mNum에 리턴받음
		if(mNum==menuSize) {break;}  // 마지막 종료하기 메뉴가 입력되었으면 무한반복문을 탈출한다.
		switch(mNum){
			case 1 : input(&list); break;
			case 2 : sort(&list, sizeof(Person), personNameCompare, personMemCpy, personFree);
				     listDisplay(&list); 
					 break;
			case 3 : search(&list); break;
			case 4 : fun_delete(&list); break;
		}
	}
       
	destroy(&list, personFree); // 헤드노드부터 테일노드까지 모든 노드 삭제하기
	
	return 0;
}
//--------------------------------------------------------------------------
void input(LinkedList *list)
{
	Person pa;    // 구조체 임시변수
	char tname[100];
	
	while(1)
	{
		printf("성명 입력(엔터만 입력하면 종료) : ");
		gets(tname);
		if(tname[0]==NULL) {break;}  // 그냥 엔터치면 종료
		pa.name = (char *) calloc(strlen(tname) + 1, sizeof(char));
		strcpy(pa.name, tname);
		printf("나이 입력 : ");
		scanf("%d", &pa.age);
		fflush(stdin);
		appendFromTail(list, &pa, sizeof(Person), personMemCpy);
		free(pa.name);
	}
}
//--------------------------------------------------------------------------
void listDisplay(LinkedList *list)
{
	Person pa={NULL, 0};   // 하나의 데이터값을 저장해올 구조체 변수, 반드시 NULL로 초기화-메모리 해제 대비
	int i=0;     // 출력할 데이터 번호 저장 변수

	if(list->length==0) 
	{
		printf("출력할 데이터가 하나도 없습니다.\n");
		getch();
		return;
	}
	list->cur = list->head->next;  // 출력할 첫 노드 지정하기
	while(list->cur != list->tail)  // tail node 전 노드까지만 출력하기
	{
		getAt(list->cur, &pa, personMemCpy); // 데이터 하나 읽어오기
		printf("%d. ", ++i);
		personPrint(&pa);  // 읽어온 데이터 출력하기
		list->cur = list->cur->next; // 다음 노드로 이동하기
		if(i%10==0)    // 10명씩 출력 후 잠시 멈춤
		{
			getch();
		}
	}
	if(i%10!=0) //i가 10으로 나누어 떨어질 경우 앞에서 출력했으므로 다시 출력하지 않음
	{
		getch();
	}
	personFree(&pa);
	return;
}
//--------------------------------------------------------------------------
void search(LinkedList *list)
{
	char *menuList[] = { "성명 검색", "나이 검색", "성명+나이 검색", "검색 종료" };
	int menuSize;  // 메뉴의 개수 저장 변수
	int mNum;  // 선택된 메뉴번호 저장 변수

	if(list->length==0) 
	{
		printf("출력할 데이터가 하나도 없습니다.\n");
		getch();
		return;
	}

	while(1)
	{
		menuSize = sizeof(menuList)/sizeof(menuList[0]); // 메뉴 개수 계산

		mNum=menu(menuList, menuSize); // 입력된 메뉴의 번호를 mNum에 리턴받음
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
	Person pa={NULL,0};   // 임시 구조체 변수
	char tname[100];
	Node *res;   // 검색된 노드의 시작주소 저장 변수
	printf("찾을 성명 입력 : ");
	gets(tname);  
	pa.name = (char *) calloc(strlen(tname) + 1, sizeof(char));
	strcpy(pa.name, tname);
	res=linearSearchUnique(list, &pa, personNameCompare);
	if(res==NULL)
	{
		printf("찾는 사람이 없습니다.\n");
	}
	else
	{
		personPrint(res+1); // res+1을 하면 res가 가리키는 노드 뒤에 붙어있는 Person 구조체 영역의 주소가 계산되어 나옴
	}
	free(pa.name);
}
//--------------------------------------------------------------------------
void searchAge(LinkedList *list, int(*cmp)(void *, void *))
{
	Person pa;   // 임시 구조체 변수
	Node *res;   // 검색된 노드의 시작주소 저장 변수
	printf("찾을 나이 입력 : ");
	scanf("%d", &pa.age);
	fflush(stdin);
	pa.name=NULL;
	res=linearSearchUnique(list, &pa, personAgeCompare);
	if(res==NULL)
	{
		printf("찾는 사람이 없습니다.\n");
	}
	else
	{
		personPrint(res+1);
	}
}
//--------------------------------------------------------------------------
void searchNameAge(LinkedList *list, int(*cmp)(void *, void *))
{
	Person pa;   // 임시 구조체 변수
	Node *res;   // 검색된 노드의 시작주소 저장 변수
	char tname[100];
	printf("찾을 성명 입력 : ");
	scanf("%s", tname);
	printf("찾을 나이 입력 : ");
	scanf("%d", &pa.age);
	fflush(stdin);
	pa.name = (char *) calloc(strlen(tname)+1, sizeof(char));
	strcpy(pa.name, tname);
	res=linearSearchUnique(list, &pa, personCompare);
	if(res==NULL)
	{
		printf("찾는 사람이 없습니다.\n");
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
	Person pa;   // 임시 구조체 변수
	Node *res;   // 검색된 노드의 시작주소 저장 변수
	char tname[100];

	while(1)
	{
		printf("삭제할 성명 입력 : ");
		gets(tname);
		if(tname[0]==NULL) {break;}  // 그냥 엔터치면 종료
		pa.name = (char *) calloc(strlen(tname)+1, sizeof(char));
		strcpy(pa.name, tname);
		res=linearSearchUnique(list, &pa, personNameCompare);
		if(res==NULL)
		{
			printf("찾는 사람이 없습니다.\n");
		}
		else
		{
			nodeDelete(list, res, personFree); // 찾은 노드 삭제
			printf("[%s]가 삭제되었습니다.\n", pa.name);
		}
		free(pa.name);
	}
}
//--------------------------------------------------------------------------
int menu(char ** menu_list, int mSize)
 {
	int num=0, i;
	system("cls");
	for(i=0; i<mSize; i++){  // 메뉴 문자열을 출력하는 반복문
		gotoxy(30,5+i*2); 	printf("%2d. %s",i+1, menu_list[i]);
	}
	while(num<1 || num>mSize){  //입력한 메뉴번호가 유효한 번호가 아니면 다시 입력
		gotoxy(25,17);printf("* Select menu No. : _\b");
		scanf("%d", &num);
		fflush(stdin); // 입력한 문자들중 맨앞의 한문자만 사용하기 위해 버퍼내의 나머지 문자 모두 지움.
	}
	return(num);
 }
 //--------------------------------------------------------------------------
 void gotoxy(int x, int y) 
 { 
	COORD Pos = {x - 1, y - 1}; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); 
 }