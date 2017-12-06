#include <stdio.h>
#include <string.h>
#include "datatype.h"


// Person 구조체의 name 멤버로 비교하는 함수
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

// Person 구조체의 age 멤버로 비교하는 함수
int comparePersonAge(DataType *p1, DataType *p2)
{
	if(p1->age > p2->age)
		return 1;
	else if(p1->age == p2->age)
		return 0;
	else
		return -1;
}

// Person 구조체의 모든 멤버를 출력하는 함수
void printPerson(DataType *p)
{
	printf(" %s : %d세 \n", p->name, p->age);
	return ;
}