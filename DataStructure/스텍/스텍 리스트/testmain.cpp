#include"stack.h"
#include<stdio.h>
#include "datatype.h"

int menu(char**, int);
void myFlush();
void input(Stack *);
void myDelete(Stack *);
void getTop(Stack *);

int main(void)
{
	Stack stk;
	char *menuList[] = { "입력하기", "삭제하기", "전체출력하기","최상단 값 찾기", "종료\n" };
	int menuCnt;
	int menuNum;

	initStack(&stk);
	menuCnt = sizeof(menuList) / sizeof(menuList[0]);

	while (1)
	{
		menuNum = menu(menuList, menuCnt);
		if (menuNum == menuCnt)
		{
			break;
		}
		switch (menuNum)
		{
		case 1:
		{
			input(&stk);break;
		}
		case 2:
		{
			myDelete(&stk); break;
		}
		case 3: printStack(&stk, printInt); break;
		case 4: getTop(&stk); break;
		case 5: return 0;
		}
	}
	destroyStack(&stk);
	return 0;
}

void getTop(Stack *sPtr)
{
	DataType getData;
	int res;
	res = getStackTop(sPtr, &getData);
	if (res == 1)
	{
		printf("최상단 값 : %d\n", getData);
	}
	else
	{
		printf("최상단 값 구하기 실패 \n");
	}
}
//input - 스택에 데이터를 반복적으로 입력함, sptr - 스택의 주소
void input(Stack *sPtr)
{
	int data;

	while (1)
	{
		printf("push할 정수형 데이터를 입력하시오(문자나 EOF입력시 종료) :");
		if (scanf("%d", &data) != 1)
		{
			myFlush();
			break;
		}
		push(sPtr, data);
	}
}

//mydelete - 스택의 데이터를 반복적으로 꺼냄,  sptr - 스택의 주소
void myDelete(Stack *sPtr)
{
	int cnt; //pop할 횟수를 입력받아 저장할 변수
	int popData; //pop한 데이터를 저장할 변수
	int res; // pop()함수의 리턴값을 저장할 변수

	printf("Stack에서 데이터를 pop할 횟수를 입력하시오 : ");
	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		res = pop(sPtr, &popData);
		if (res == 1)
		{
			printf("pop 데이터 : %5d\n", popData);
		}
		else
		{
			printf("pop 실패");
		}
	}
}


//menu - 메뉴를 출력하고 메뉴번호를 입력받아 리턴함
//menulist - 메뉴 출력할 문자열. menucnt - 메뉴개수
int menu(char **menuList, int menuCnt)
{
	int menuNum = 0;
	int res;
	printf("\n");
	for (int i = 0; i < menuCnt; i++)
	{
		printf("%d. %s\n", i + 1, menuList[i]);
	}
	while (menuNum<1 || menuNum>menuCnt)//범위내의 번호가 입력될때까지 반복
	{
		printf("# 메뉴번호를 입력하세요 : ");
		res = scanf("%d", &menuNum);
		if (res != 1)
		{
			myFlush();
		}
	}
	return menuNum;
}

//myflush - 입력버퍼지우기
void myFlush()
{
	while (getchar() != '\n')
	{
		;
	}
}

void printInt(DataType *p)
{
	printf("%3d", *p);
}