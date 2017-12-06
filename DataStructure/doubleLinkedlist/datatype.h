 #pragma once
typedef struct _person
{
	char name[20];
	int age;
}Person;

typedef  Person DataType;     // 노드내의 데이터 영역의 형명 재지정 

//-------------------------------------
//   Person 구조체 보조 함수
//-------------------------------------
int comparePersonName(DataType *p1, DataType *p2);  // Person 구조체의 name멤버로 비교하는 함수
int comparePersonAge(DataType *p1, DataType *p2);   // Person 구조체의 age멤버로 비교하는 함수
void printPerson(DataType *p);  // Person 구조체의 모든 멤버를 출력하는 함수 
