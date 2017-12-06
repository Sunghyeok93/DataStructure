#include <stdio.h>
void quickSort(int *ary, int size);
int binarySearch(int *ary, int leftIndex, int rightIndex, int key);
int rbinarySearch(int *ary, int leftIndex, int rightIndex, int key);
void output(int *ary, int size);
int main()
{
	int ary[]={11,3,25,7,19,10,13,35,8,19};
	int size;        // 배열요소개수 저장
	int key;         // 찾을 숫자 저장
	int index;      // 검색된 데이터의 인덱스
	int res;        // scanf()함수의 리턴값 저장
	size = sizeof(ary)/sizeof(ary[0]);
	quickSort(ary, size);
	output(ary, size);

	while(1)
	{
		printf("검색할 숫자 입력(문자입력 시 종료) : ");
		res = scanf("%d", &key);
		if(res != 1) {break;}   // 문자입력 시 종료
		if( ( index = rbinarySearch(ary, 0, size-1, key) ) != -1)
		{
			printf("%d는 %d번방 데이터입니다.\n", key, index);
		}
		else
		{
			printf("%d는 존재하지 않습니다.\n", key);
		}
	}
	return 0;
}
/*---------------------------------------------------------------------
함수명 및 기능 : binarySearch() - 이분 검색 함수
전달인자: ary - 검색할 데이터 배열의 시작주소
leftIndex - 검색 구간의 좌측 인덱스
rightIndex - 검색 구간의 우측 인덱스
key - 검색할 데이터
리턴값: 검색 성공 시 - 찾은 숫자의 index / 검색 실패 시 - -1 리턴
--------------------------------------------------------------------*/
int binarySearch(int *ary, int leftIndex, int rightIndex, int key)
{
	int midIndex;  // 중간위치값의 인덱스
	//while(rightIndex >= leftIndex)
	//while(1)
	{
		midIndex = (leftIndex+rightIndex) / 2; 
		if(key == ary[midIndex])
			return midIndex;  // 찾은 데이터의 index값을 리턴
		else if( key < ary[midIndex])
			rightIndex = midIndex-1;
		else
			leftIndex = midIndex+1;
		//if(rightIndex<leftIndex) 
		//	break;
	}

	return -1;  // 못찾았으면 -1 리턴
}
//-----------------------------------------------------------------------------
int rbinarySearch(int *ary, int leftIndex, int rightIndex, int key)
{
	int midIndex;  // 중간위치값의 인덱스

	if(leftIndex >rightIndex) 
		return -1;
	midIndex = (leftIndex+rightIndex) / 2;
	if(key == ary[midIndex])
		return midIndex;  // 찾은 데이터의 index값을 리턴
	
	if( key < ary[midIndex])
		return rbinarySearch(ary,leftIndex, midIndex-1, key);
	else
		return rbinarySearch(ary, midIndex+1, rightIndex, key);
}
/*--------------------------------------------------------------------
함수명 및 기능 : quickSort() - 퀵 정렬 함수
전달인자: ary - 정렬할 데이터 배열의 시작주소
size - 소트할 데이터의 개수
리턴값: 없음
--------------------------------------------------------------------*/
void quickSort(int *ary, int size)
{
	int pivot, temp;
	int i, j;

	if(size <= 1) return;// 구간값이 1이하이면 sort가 완료된 것 이므로 return

	pivot = ary[size-1];         // 구간의 가장 우측값을 pivot으로 정함
	i = -1;        // i는 좌측에서 부터 검색할 위치 저장
	j = size-1;    // j는 우측에서 부터 검색할 위치 저장

	while(1)       // 분할 작업
	{
		while(ary[++i] < pivot);  // 좌측으로부터 pivot보다 큰 값 위치 찾기
		while(j>0 && ary[--j] > pivot ); // 우측으로부터 pivot보다 작은 값 위치 찾기
		if(i >= j ) break; //i가 j보다 크거나 같아지면 분할이 끝이므로 while문 탈출
		// 아니면 i와 j번 방의 값 swap
		temp = ary[i];
		ary[i] = ary[j];
		ary[j] = temp;
	}
	// 분할이 끝났으면 i번 방의 값과 pivot위치의 값 swap
	temp = ary[i];
	ary[i] = ary[size-1];    // 여기서 pivot변수의 값과 바꾸지 않도록 주의
	ary[size-1] = temp;

	quickSort(ary, i);             // 좌측 소구간에 대한 퀵 정렬 재귀 호출
	quickSort(ary+i+1, size-i-1);  // 우측 소구간에 대한 퀵 정렬 재귀 호출
}

/*------------------------------------------------------------------------
함수명 및 기능 : output() - 배열의 모든 원소 출력하기
전달인자: ary - 정렬할 데이터 배열의 시작주소
size - 데이터의 개수
리턴값: 없음
------------------------------------------------------------------------*/
void output(int *ary, int size)
{
	for(int i=0; i<size;i++)
	{
		printf(" %d ", ary[i]);
	}
	printf("\n");
}
