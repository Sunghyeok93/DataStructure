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
	Queue que; //ť����
	char *menuList[] = { "�Է��ϱ�", "�����ϱ�", "����ϱ�", "����" };
	int menuCnt; //�޴����� ���� ����
	int menuNum; //�޴� ��ȣ ���� ����

	intitQueue(&que, 5);//ũ�Ⱑ 5�� ť ���� �� �ʱ�ȭ

	menuCnt = sizeof(menuList) / sizeof(menuList[0]);

	while (1)
	{
		menuNum = menu(menuList, menuCnt);
		if (menuNum == menuCnt) //����޴� ���ý� �ݺ��� Ż���ϱ�
		{
			break;
		}
		switch (menuNum)
		{
		case 1: input(&que); break;
		case 2: myDelete(&que); break;
		case 3: printQueue(&que, printInt); break;//ť���� ��� ������ ���
		}
	}
	destroyQueue(&que);
	return 0;
}

//input - ť�� �����͸� �ݺ������� �Է���, qptr - ť�� �ּ�
void input(Queue *qPtr)
{
	DataType data;

	while (1)
	{
		printf("Put�� ������ �����͸� �Է��Ͻÿ�(���ڳ� EOF�� �Է� �� ����) :");
		
		if (scanf("%d", &data) != 1)
		{
			myFlush();
			break;
		}
		if (!enqueue(qPtr, data))
		{
			printf("put(enqueue) ���� !\n");
		}
	}
}

//mydelete - ������ �����͸� �ݺ������� ����,  qptr - ť�� �ּ�
void myDelete(Queue *qPtr)
{
	int cnt; //get�� Ƚ���� �Է¹޾� ������ ����
	DataType getData; //get�� �����͸� ������ ����
	int res; // get()�Լ��� ���ϰ��� ������ ����

	printf("Queue���� �����͸� get�� Ƚ���� �Է��Ͻÿ� : ");
	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		res = dequeue(qPtr, &getData);
		if (res == 1)
		{
			printf("get ������ : %5d\n", getData);
		}
		else
		{
			printf("get(dequeue) ����\n");
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
			continue;
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

void printInt(DataType *p)
{
	printf("%4d", *p);
}