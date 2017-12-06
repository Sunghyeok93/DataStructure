#include <stdio.h>
#include <string.h>
#include "datatype.h"


// Person ����ü�� name ����� ���ϴ� �Լ�
int comparePersonName(DataType *p1, DataType *p2)
{
	int num = strcmp(p1->name, p2->name);
	if(num > 0)
		return 1;
	else if(num == 0)
		return 0;
	else
		return -1;
}

// Person ����ü�� age ����� ���ϴ� �Լ�
int comparePersonAge(DataType *p1, DataType *p2)
{
	if(p1->age > p2->age)
		return 1;
	else if(p1->age == p2->age)
		return 0;
	else
		return -1;
}

// Person ����ü�� ��� ����� ����ϴ� �Լ�
void printPerson(DataType *p)
{
	printf(" %s : %d�� \n", p->name, p->age);
	return ;
}