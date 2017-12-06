#include "stack.h"
#include <stdio.h>

int menu(char **, int);
void myFlush();
void input(Stack *);
void myDelete(Stack *);

int main()
{
	Stack stk;     /* 스택 생성*/
	char *menuList[] = { "입력하기", "삭제하기", "출력하기", "종료" }; /* 메뉴 리스트*/
	int menuCnt;   /* 메뉴 개수저장 변수*/
	int menuNum;   /* 메뉴 번호저장 변수*/

	initStack(&stk); /* 스택초기화*/
	menuCnt = sizeof(menuList) / sizeof(menuList[0]);  /* 메뉴 개수 계산하기*/

	while(1){
		menuNum = menu(menuList, menuCnt);
		if (menuNum == menuCnt){  /* 종료 메뉴 선택시 반복문 탈출하기*/
			break;
		}
		switch (menuNum){
			case 1: input(&stk);  break;
			case 2: myDelete(&stk); break;
			case 3: printStack(&stk, printInt); /* stack내의 모든 데이터 출력하기*/
		}
	}
	destroyStack(&stk);
	return 0;
}
/*--------------------------------------------------------------------------------------
  함수명및기능: input() - 스택에 데이터를 반복적으로 입력 함
  전달인자: sPtr - 스택의주소
  리턴값: 없음
  --------------------------------------------------------------------------------------*/
void input(Stack *sPtr)
{
	int data;

	while (1){
		printf("Push할 정수형 데이터를 입력하시오(문자나 EOF입력시 종료) : ");
		if (scanf("%d", &data) != 1){ /* 문자나 EOF가 입력되면 while문을 빠져나감*/
			myFlush();
			break;
		}
		if (!push(sPtr, data)){
			printf("push 실패!\n");
		}
	}
}
/*--------------------------------------------------------------------------------------
  함수명및기능: myDelete() - 스택의 데이터를 반복적으로 꺼냄
  전달인자: sPtr – 스택의 주소
  리턴값: 없음
  --------------------------------------------------------------------------------------*/
void myDelete(Stack *sPtr)
{
	int i;
	int cnt;  /* pop할 횟수를 입력 받아 저장할 변수*/
	int popData; /* pop한 데이터를 저장할 변수*/
	int res;     /* pop() 함수의 리턴값을 저장할변 수*/

	printf("Stack에서 데이터를 pop할 횟수를 입력하시오: ");
	scanf("%d", &cnt);
	for (i = 0; i < cnt; i++){
		res = pop(sPtr, &popData);
		if (res == 1){  /* 성공적으로 pop 작업을 수행했으면*/
		
			printf("pop 데이터: %5d\n", popData);
		}
		else
			printf("pop 실패!\n");
	}
}
/*--------------------------------------------------------------------------------------
  함수명및기능: menu() – 메뉴를 출력하고 메뉴번호를 입력 받아 리턴함
  전달인자: menuLIst – 메뉴 출력할 문자열
  menuCnt  - 메뉴 개수
  리턴값: 선택된 메뉴 번호
  --------------------------------------------------------------------------------------*/
int menu(char **menuList, int menuCnt)
{
	int i;
	int menuNum = 0; /* 입력된 메뉴 번호 저장 변수*/
	int res;       /* scanf()함수의 리턴값 저장 변수*/
	for (i = 0; i < menuCnt; i++){
		printf("%d. %s\n", i + 1, menuList[i]);
	}
	while (menuNum<1 || menuNum>menuCnt){  /* 범위 내의 번호가 입력될 때 까지 반복*/
		printf("# 메뉴번호를 입력하세요 : ");
		res = scanf("%d", &menuNum);
		if (res == 0){  /* 정수가 입력되지 않았으면*/
			myFlush();  /* 입력 버퍼 비우기*/
		}
	}
	return menuNum;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: myFlush() – 입력 버퍼 지우기
  전달인자: 없음
  리턴값: 없음
  --------------------------------------------------------------------------------------*/
void myFlush()
{
	while (getchar() != '\n'){
		;
	}
}


//-------------------------------------
//   int type 보조 함수
//-------------------------------------
/*--------------------------------------------------------------------------------------
  함수명 및 기능: printInt() – 전달인자로 넘겨진 int값을 정해진 format으로 출력 함
  전달인자: p - 출력할 정수의 주소
  리턴값: 없음
  --------------------------------------------------------------------------------------*/
void printInt(DataType *p)
{
	printf("%4d", *p);
}