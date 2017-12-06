
#include "person.h"


void personMemCpy(void *p1, void *p2)
{
	personFree(p1);  // name멤버의 메모리 해제
	if (((Person *)p2)->name != NULL)
	{
		((Person *)p1)->name = (char *)calloc(strlen(((Person *)p2)->name) + 1, sizeof(char));
		strcpy(((Person *)p1)->name, ((Person *)p2)->name);
	}


	((Person *)p1)->age = ((Person *)p2)->age;

	strcpy(((Person *)p1)->phoneNumber, ((Person *)p2)->phoneNumber);

}


void personFree(void *p) // Person구조체의 멤버에 속해있는 부가 메모리 해제하기
{
	if (((Person *)p)->name != NULL)
		free(((Person *)p)->name);
	((Person *)p)->name = NULL;  // 메모리 해제 후 name멤버를 NULL 포인터로 변경해놓음
}

void personPrint(void *p)
{
	printf("성명 : %s / 나이 : %d\n", ((Person *)p)->name, ((Person *)p)->age);
}

int personNameCompare(void *p1, void *p2)
{
	return strcmp(((Person *)p1)->name, ((Person *)p2)->name);
}

int personAgeCompare(void *p1, void *p2)
{
	if (((Person *)p1)->age > ((Person *)p2)->age)
	{
		return 1;
	}
	else if (((Person *)p1)->age == ((Person *)p2)->age)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int personPhoneNumberCompare(void *p1, void *p2)
{
	return strcmp(((Person *)p1)->phoneNumber, ((Person *)p2)->phoneNumber);
}

int personCompare(void *p1, void *p2)
{
	int res1, res2, res3;

	res1 = personNameCompare(p1, p2);
	res2 = personAgeCompare(p1, p2);
	res3 = personPhoneNumberCompare(p1, p2);
	if (res1 == 0 && res2 == 0 && res3)
	{
		return 0;  // 모든 멤버가 동일하면 0 리턴
	}
	else
	{
		return -1;  // 모든 멤버가 일치하지 않으면 -1 리턴
	}
}
