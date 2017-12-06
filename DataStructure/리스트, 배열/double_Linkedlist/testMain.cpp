#include <stdio.h>
#include "datatype.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <Windows.h>

void myDelete(LinkedList *lp);
void mySearch(LinkedList *lp);
int input_menu(char *msg);
void sort_node(LinkedList *lp);
void input_node(LinkedList *lp);
void print_menu(void);
char input_sort(char *msg);
void multiSearch(LinkedList *lp);
void multiDelete(LinkedList *lp);
int main()
{
	Person temp = {"",0};
	Person ary[10] = { { "강성혁", 24 }, { "정승주", 45 }, { "노규연", 21 }, { "홍길동", 50 }, { "뭐라구", 80 },
	{ "한승철", 45 }, { "지용선", 32 }, { "노지연", 17 }, { "이채원", 51 }, { "김옥지", 64 } };
	LinkedList list;
	create(&list);
	int i;
	for (i = 0; i < sizeof(ary) / sizeof(ary[0]); i++)
	{
		appendFromTail(&list, &ary[i]); // 링크드리스트를 관리하는 구조체 시작주소, 배열의 시작주소
		//head로 해도됨ㅋ
	}
	while (1)
	{	
		fflush(stdin);
		print_menu();
		int input = input_menu("메뉴를 입력하세요 : ");
		switch (input)
		{
		case 1: input_node(&list); break;
		case 2: display(&list, printPerson); break;
		case 3:	mySearch(&list); break;
		case 4: myDelete(&list); break;
		case 5: sort_node(&list); break;
		case 6: multiSearch(&list); break;
		case 7: multiDelete(&list); break;
		case 8: destroy(&list); 
				exit(0);// 데이터 소멸시키기
				break;
		default:
			break;
		}
	}
}
void print_menu(void)
{
	printf("\n");
	printf("1. 추가하기\n");
	printf("2. 출력하기\n");
	printf("3. 검색하기\n");
	printf("4. 삭제하기 \n");
	printf("5. 정렬하기 \n");
	printf("6. 다중검색 \n");
	printf("7. 다중삭제 \n");
	printf("8. 종료(데이터삭제 포함)\n");
}
void multiDelete(LinkedList *lp)
{
	DataType people = { "", 0 };

	while (1)
	{
		printf("다중 삭제할 이름을 입력하세요(주메뉴:'끝') : ");
		fflush(stdin);
		scanf_s("%s", people.name, sizeof(people.name));
		fflush(stdin);
		if (strcmp(people.name, "끝") == 0)
		{
			break;
		}
		deleteDuplicate(lp, &people, comparePersonName);
	}
}
void multiSearch(LinkedList *lp)
{
	
	Node **p;
	DataType people = { "", 0 };
	while (1)
	{
		
		int cnt = 0;
		fflush(stdin);
		printf("검색할 사람의 이름을 입력하시오(종료 = '끝') : ");
		scanf_s("%s", people.name, sizeof(people.name));
		if (strcmp(people.name, "끝") == 0)
		{
			break;
		}
		p = searchDuplicate(lp, &cnt, &people, comparePersonName);
		if (cnt != 0)
		{
			for (int i = 0; i < cnt; i++)
				printPerson(&(p[i])->data);
		}
		else
		{
			printf("그런 사람 없음!\n");
		}
			free(p);
	}
}
void input_node(LinkedList *lp)
{
	DataType tmp;
	while (1){
		char select[10];
		printf("\n헤드노드 앞에 추가(H) / 테일노드 뒤에 추가(T) / 종료(끝) : ");
		scanf("%s", select);
		if (strcmp(select, "H") == 0 || strcmp(select, "T") == 0){
			printf("# 입력할 사람의 이름 입력 : ");
			scanf("%s", &tmp.name);
			printf("# 입력할 사람의 나이 입력 : ");
			scanf("%d", &tmp.age);
		}

		if (strcmp(select, "H") == 0)
		{
			appendFromHead(lp, &tmp);
		}
		else if (strcmp(select, "T") == 0)
		{
			appendFromTail(lp, &tmp);
		}
		else if (strcmp(select, "끝") == 0)
		{
			break;
		}
	}
}
void sort_node(LinkedList *lp)
{
	char choice = input_sort("이름순(N), 나이순(A) : " );
	if (choice == 'N')
	{
		sortList(lp, comparePersonName); // 이름 순으로 정렬
	}
	else if (choice == 'A')
	{
		sortList(lp, comparePersonAge); // 나이 순으로 정렬
	}
}
char input_sort(char *msg)
{
	char select;
	int count;

	while (1){
		printf("%s", msg);
		count = scanf_s("%c", &select, sizeof(char));
		fflush(stdin);
		if (count == 1 && select == 'A' || select == 'N'){
			return select;
		}
		else
			printf("잘못입력하셨습니다.\n");
	}
}

int input_menu(char *msg)
{
	int num;
	int count;

	while (1){
		printf("%s", msg);
		count = scanf_s("%d", &num, sizeof(int));
		fflush(stdin);
		if (count == 1 && num >= 1 && num <= 8){
			return num;
		}
		else
			printf("잘못입력하셨습니다.\n");
	}
}
void myDelete(LinkedList *lp)
{
	Node *res; //검색결과 저장변수
	Person temp = { "", 0 };
	while (1){
		printf("삭제할 사람의 이름 입력(메뉴로 돌아가려면 '끝') : ");
		scanf_s("%s", temp.name, sizeof(temp.name));
		if (strcmp(temp.name, "끝") == 0)
		{
			return;
		}
		res = searchUnique(lp, &temp, comparePersonName);
		if (res != NULL) deleteNode(lp, res);
		else printf("그런 사람 없음!\n");
	}
}
void mySearch(LinkedList *lp)
{
	Node *res; //검색결과 저장변수
	Person temp = { "", 0 };
	while (1){
		printf("검색할 사람의 이름 입력(메뉴로 돌아가려면 '끝') : ");
		scanf_s("%s", temp.name, sizeof(temp.name));
		if (strcmp(temp.name, "끝") == 0)
		{
			printf("종료됩니다. \n");
			return;
		}
		res = searchUnique(lp, &temp, comparePersonName);
		if (res != NULL) printPerson(&res->data);
		else printf("그런 사람 없음!\n");
	}
}