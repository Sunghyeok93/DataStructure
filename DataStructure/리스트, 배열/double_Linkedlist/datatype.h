#pragma once
typedef struct _person
{
	char name[20];
	int age;
}Person;

typedef Person DataType;

// ---------------------------
//   Person ����ü ���� �Լ�
// ---------------------------

// Person ����ü�� name ����� ���ϴ� �Լ�
int comparePersonName(DataType *p1, DataType *p2);

// Person ����ü�� age ����� ���ϴ� �Լ�
int comparePersonAge(DataType *p1, DataType *p2); 

// Person ����ü�� ��� ����� ����ϴ� �Լ�
void printPerson(DataType *p); 
