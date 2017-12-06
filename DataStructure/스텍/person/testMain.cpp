#include <string.h>
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
	char *menuList[] = { "�Է��ϱ�", "�����ϱ�", "��ü����ϱ�", "�ֻ�� �� ã��", "����\n" };
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
				  input(&stk); break;
		}
		case 2:
		{
				  myDelete(&stk); break;
		}
		case 3: printStack(&stk, printPerson); break;
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
		printf("�ֻ�� : %s : %d��\n", getData.name, getData.age);
	}
	else
	{
		printf("�ֻ�� �� ���ϱ� ���� \n");
	}
}
//input - ���ÿ� �����͸� �ݺ������� �Է���, sptr - ������ �ּ�
void input(Stack *sPtr)
{
	DataType data;

	while (1)
	{
		printf("push�� �̸��� �Է��Ͻÿ�('��'�Է½� ����) :");
		scanf("%s", &data.name);
		if (strcmp(data.name, "��") == 0)
		{
			break;
		}
		printf("push�� ���̸� �Է��Ͻÿ� :");
		scanf("%d", &data.age);
		printf("push�Ϸ�\n");
		push(sPtr, data);
	}
}

//mydelete - ������ �����͸� �ݺ������� ����,  sptr - ������ �ּ�
void myDelete(Stack *sPtr)
{
	int cnt; //pop�� Ƚ���� �Է¹޾� ������ ����
	DataType popData; //pop�� �����͸� ������ ����
	int res; // pop()�Լ��� ���ϰ��� ������ ����

	printf("Stack���� �����͸� pop�� Ƚ���� �Է��Ͻÿ� : ");
	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		res = pop(sPtr, &popData);
		if (res == 1)
		{
			printf("pop ������ : %5d\n", popData);
		}
		else
		{
			printf("pop ����");
		}
	}
}


//menu - �޴��� ����ϰ� �޴���ȣ�� �Է¹޾� ������
//menulist - �޴� ����� ���ڿ�. menucnt - �޴�����
int menu(char **menuList, int menuCnt)
{
	int menuNum = 0;
	int res;
	printf("\n");
	for (int i = 0; i < menuCnt; i++)
	{
		printf("%d. %s\n", i + 1, menuList[i]);
	}
	while (menuNum<1 || menuNum>menuCnt)//�������� ��ȣ�� �Էµɶ����� �ݺ�
	{
		printf("# �޴���ȣ�� �Է��ϼ��� : ");
		res = scanf("%d", &menuNum);
		if (res != 1)
		{
			myFlush();
		}
	}
	return menuNum;
}

//myflush - �Է¹��������
void myFlush()
{
	while (getchar() != '\n')
	{
		;
	}
}

