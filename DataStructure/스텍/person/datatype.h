#pragma once
typedef struct _person
{
	char name[20];
	int age;
}Person;

typedef Person DataType;



//int type �����Լ�
void printPerson(DataType *p);