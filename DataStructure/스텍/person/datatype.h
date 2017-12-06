#pragma once
typedef struct _person
{
	char name[20];
	int age;
}Person;

typedef Person DataType;



//int type 보조함수
void printPerson(DataType *p);