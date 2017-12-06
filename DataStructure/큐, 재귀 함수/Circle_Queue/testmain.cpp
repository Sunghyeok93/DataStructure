#include <string.h>
#include "queue.h"
#include <stdio.h>
#include "datatype.h"

int menu(char**, int);
void myFlush();
void input(Queue *);
void myDelete(Queue *);


int main(void)
{
	Queue que; //큐생성
	char *menuList[] = { "입력하기", "삭제하기", "출력하기", "종료" };
	int menuCnt; //메뉴개수 저장 변수
	int menuNum; //메뉴 번호 저장 변수

	intitQueue(&que, 5);//크기가 5인 큐 생성 및 초기화

	menuCnt = sizeof(menuList) / sizeof(menuList[0]);

	while (1)
	{
		menuNum = menu(menuList, menuCnt);
		if (menuNum == menuCnt) //종료메뉴 선택시 반복문 탈출하기
		{
			break;
		}
		switch (menuNum)
		{
		case 1: input(&que); break;
		case 2: myDelete(&que); break;
		case 3: printQueue(&que, printInt); break;//큐내의 모든 데이터 출력
		}
	}
	destroyQueue(&que);
	return 0;
}

//input - 큐에 데이터를 반복적으로 입력함, qptr - 큐의 주소
void input(Queue *qPtr)
{
	DataType data;

	while (1)
	{
		printf("Put할 정수형 데이터를 입력하시오(문자나 EOF가 입력 시 종료) :");
		
		if (scanf("%d", &data) != 1)
		{
			myFlush();
			break;
		}
		if (!enqueue(qPtr, data))
		{
			printf("put(enqueue) 실패 !\n");
		}
	}
}

//mydelete - 스택의 데이터를 반복적으로 꺼냄,  qptr - 큐의 주소
void myDelete(Queue *qPtr)
{
	int cnt; //get할 횟수를 입력받아 저장할 변수
	DataType getData; //get한 데이터를 저장할 변수
	int res; // get()함수의 리턴값을 저장할 변수

	printf("Queue에서 데이터를 get할 횟수를 입력하시오 : ");
	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		res = dequeue(qPtr, &getData);
		if (res == 1)
		{
			printf("get 데이터 : %5d\n", getData);
		}
		else
		{
			printf("get(dequeue) 실패\n");
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
			continue;
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
	printf("%4d", *p);
}