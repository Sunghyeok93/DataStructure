#pragma once
#pragma warning(disable : 4996)

#include <string.h>
#include <malloc.h>
#include <stdio.h>

typedef struct _person
{
	char *name;   // 성명 저장 변수
	int  age;  // 나이 저장 변수
	char phoneNumber[16]; // 핸드폰 번호 저장 배열
}Person;

void personMemCpy(void *p1, void *p2); // p2가 가리키는 구조체의 모든 멤버를 p1이 가리키는 구조체로 복사
void personFree(void *p);  // 구조체 멤버 중 포인터 멤버에 동적메모리 할당이 되어있는 경우 그 메모리를 해제함
void personPrint(void *p);  // 구조체 멤버의 값을  한줄에 출력해 줌
int personNameCompare(void *p1, void *p2);  // 성명을 비교하여 p1이 가리키는 성명이 크면 1, 같으면 0, 작으면 1 리턴
int personAgeCompare(void *p1, void *p2);   // 나이를 비교하여 p1이 가리키는 나이가 크면 1, 같으면 0, 작으면 1 리턴
int personCompare(void *p1, void *p2);      // 성명과 나이가 정확하게 같으면 0, 둘중 하나라도 다르면 -1 리턴