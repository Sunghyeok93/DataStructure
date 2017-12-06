#pragma warning(disable: 4996)
#include <stdio.h>
#include <assert.h>
#define MAX_CNT 100
int weight[MAX_CNT+1];  // 물건의 무게를 저장하는 배열(0번방 사용 안함)
int value[MAX_CNT+1];   // 물건별 가치를 저장하는 배열 (0번방 사용 안함)
int n;                  // 물건의 개수 저장변수
int totWeight;          // 배낭에 저장 가능한 총 무게 저장 변수
void fileLoad(char * fileName);
int knapsack(int itemNum, int remainWeight);

int main()
{
	fileLoad("d:\\data\\knapsack3.txt");
	printf("최대 가치 : %d\n\n", knapsack(1,totWeight));	
	return 0;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: fineLoad() - 파일에서 물건의 정보(무게, 가치)를 입력 받아 초기화하는 함수
전달인자 : fileName - 물건의 정보를 저장하고 있는 파일명
리턴값: 없음
--------------------------------------------------------------------------------------*/
void fileLoad(char * fileName)
{	
	FILE *fp;
	int i; /* iterator */
	fp=fopen(fileName, "rt");
	assert(fp != NULL);

	fscanf(fp, "%d %d\n", &n, &totWeight);  /* 물건의 개수와 배낭에 저장가능한 최대무게 입력 */

	for(i=1; i<=n; ++i)
	{
		fscanf(fp, "%d %d\n", &weight[i], &value[i]); /* 물건의 무게와 가치 입력 */
	}
	fclose(fp);
	return;
}
/*------------------------------------------------------------------
함수명 및 기능: knapsack() - 해당하는 번호의 물건을 넣을 경우와 넣지 않을 경우 중 더 큰 가치를 리턴하는 재귀함수
전달인자 : itemNum - 물건의 번호
           remainWeight - 남은 무게
리턴값: 해당물건을 넣은 경우의 가치와 넣지 않은 경우의 가치 중 큰 값
------------------------------------------------------------------*/
int knapsack(int itemNum, int remainWeight)
{
	int res1, res2;
	if(itemNum == n+1)  // 물건의 개수를 초과 했으면
		return 0;
	else if(remainWeight<weight[itemNum])  // 남은 무게가  현재 물건(itemNum)의 무게보다 작으면 다음 물건을 넣을 수 있는지 확인하러 감
		return knapsack(itemNum+1,remainWeight);
	else   // 현재 물건(itemNum)을 넣지 않은 경우와 넣는 경우를 호출 함
	{
		res1 = knapsack(itemNum+1, remainWeight);
		res2 = knapsack(itemNum+1, remainWeight-weight[itemNum])+value[itemNum];
		return (res1>res2)?res1:res2; // 현재 물건(itemNum)을 넣지 않은 경우와 넣는 경우 중 가치가 더 큰 경우를 리턴 함
	}
}
