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
	Person ary[10] = { { "������", 24 }, { "������", 45 }, { "��Կ�", 21 }, { "ȫ�浿", 50 }, { "����", 80 },
	{ "�ѽ�ö", 45 }, { "���뼱", 32 }, { "������", 17 }, { "��ä��", 51 }, { "�����", 64 } };
	LinkedList list;
	create(&list);
	int i;
	for (i = 0; i < sizeof(ary) / sizeof(ary[0]); i++)
	{
		appendFromTail(&list, &ary[i]); // ��ũ�帮��Ʈ�� �����ϴ� ����ü �����ּ�, �迭�� �����ּ�
		//head�� �ص��ʤ�
	}
	while (1)
	{	
		fflush(stdin);
		print_menu();
		int input = input_menu("�޴��� �Է��ϼ��� : ");
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
				exit(0);// ������ �Ҹ��Ű��
				break;
		default:
			break;
		}
	}
}
void print_menu(void)
{
	printf("\n");
	printf("1. �߰��ϱ�\n");
	printf("2. ����ϱ�\n");
	printf("3. �˻��ϱ�\n");
	printf("4. �����ϱ� \n");
	printf("5. �����ϱ� \n");
	printf("6. ���߰˻� \n");
	printf("7. ���߻��� \n");
	printf("8. ����(�����ͻ��� ����)\n");
}
void multiDelete(LinkedList *lp)
{
	DataType people = { "", 0 };

	while (1)
	{
		printf("���� ������ �̸��� �Է��ϼ���(�ָ޴�:'��') : ");
		fflush(stdin);
		scanf_s("%s", people.name, sizeof(people.name));
		fflush(stdin);
		if (strcmp(people.name, "��") == 0)
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
		printf("�˻��� ����� �̸��� �Է��Ͻÿ�(���� = '��') : ");
		scanf_s("%s", people.name, sizeof(people.name));
		if (strcmp(people.name, "��") == 0)
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
			printf("�׷� ��� ����!\n");
		}
			free(p);
	}
}
void input_node(LinkedList *lp)
{
	DataType tmp;
	while (1){
		char select[10];
		printf("\n����� �տ� �߰�(H) / ���ϳ�� �ڿ� �߰�(T) / ����(��) : ");
		scanf("%s", select);
		if (strcmp(select, "H") == 0 || strcmp(select, "T") == 0){
			printf("# �Է��� ����� �̸� �Է� : ");
			scanf("%s", &tmp.name);
			printf("# �Է��� ����� ���� �Է� : ");
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
		else if (strcmp(select, "��") == 0)
		{
			break;
		}
	}
}
void sort_node(LinkedList *lp)
{
	char choice = input_sort("�̸���(N), ���̼�(A) : " );
	if (choice == 'N')
	{
		sortList(lp, comparePersonName); // �̸� ������ ����
	}
	else if (choice == 'A')
	{
		sortList(lp, comparePersonAge); // ���� ������ ����
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
			printf("�߸��Է��ϼ̽��ϴ�.\n");
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
			printf("�߸��Է��ϼ̽��ϴ�.\n");
	}
}
void myDelete(LinkedList *lp)
{
	Node *res; //�˻���� ���庯��
	Person temp = { "", 0 };
	while (1){
		printf("������ ����� �̸� �Է�(�޴��� ���ư����� '��') : ");
		scanf_s("%s", temp.name, sizeof(temp.name));
		if (strcmp(temp.name, "��") == 0)
		{
			return;
		}
		res = searchUnique(lp, &temp, comparePersonName);
		if (res != NULL) deleteNode(lp, res);
		else printf("�׷� ��� ����!\n");
	}
}
void mySearch(LinkedList *lp)
{
	Node *res; //�˻���� ���庯��
	Person temp = { "", 0 };
	while (1){
		printf("�˻��� ����� �̸� �Է�(�޴��� ���ư����� '��') : ");
		scanf_s("%s", temp.name, sizeof(temp.name));
		if (strcmp(temp.name, "��") == 0)
		{
			printf("����˴ϴ�. \n");
			return;
		}
		res = searchUnique(lp, &temp, comparePersonName);
		if (res != NULL) printPerson(&res->data);
		else printf("�׷� ��� ����!\n");
	}
}