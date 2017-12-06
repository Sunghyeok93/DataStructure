#pragma warning(disable: 4996)
#include <stdio.h>
#include <assert.h>
#define MAX_CNT 100
int weight[MAX_CNT+1];  // 물건의 무게를 저장하는 배열(0번방 사용 안함)
int value[MAX_CNT+1];   // 물건별 가치를 저장하는 배열 (0번방 사용 안함)
int n;                  // 물건의 개수 저장변수
int totWeight;          // 배낭에 저장 가능한 총 무게 저장 변수
void fileLoad(char * fileName);
int knapsack(void);
int makePermutaionTable(int (*indexAry)[4]) ;
/*---------------------------------------------------------------------------------------
   main()
 ---------------------------------------------------------------------------------------*/
int main()
{
	fileLoad("d:\\data\\knapsack1.txt");
	printf("최대 가치 : %d\n\n", knapsack());	
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

	fscanf(fp, "%d %d\n", &n, &totWeight);  // 물건의 개수와 배낭에 저장가능한 최대 무게 입력 

	for(i=1; i<=n; ++i)
	{
		fscanf(fp, "%d %d\n", &weight[i], &value[i]); // 물건별 무게와 가치 입력
	}
	fclose(fp);
	return;
}
/*------------------------------------------------------------------
함수명 및 기능: knapsack() - 가방에 가장 큰 가치로 저장하는 경우를 찾아내는 함수 
전달인자 : 없음
리턴값: 물건의 순열 전체 중에 총 무게를 고려한 최대 가치를 리턴 함
------------------------------------------------------------------*/
int knapsack(void)
{
	int indexAry[24][4] = {0};
	int cnt;
	int i, j;
	int maxValue=0; // 최대 가치 저장 변수 
	int sumValue;
	int sumWeight;  

	cnt=makePermutaionTable(indexAry);

	for(i=0; i<cnt; i++)
	{
		printf("cnt : %3d = ", i+1);
	    printf("[ %d %d %d %d ]\n", indexAry[i][0], indexAry[i][1], indexAry[i][2], indexAry[i][3]);
		sumValue = sumWeight = 0;
		for(j=0; j<n; ++j) // 4개의 물건중 
		{
			sumWeight += weight[indexAry[i][j]];
			if(totWeight<sumWeight)   // 누적 무게가 총 무게를 초과하면
			{
				sumWeight -= weight[indexAry[i][j]]; // 현 물건의 무게를 빼주고 for문 탈출
				break;
			}
			sumValue += value[indexAry[i][j]]; // 현재 물건을 배낭에 넣으면 가치도 누적 함
		}
		//for(int k=0; k<j; ++k)  // 총 무게 이하로 선택된 각각의 물건의 번호(인덱스)와 무게, 가치를 출력하기
		//{
		//	printf(" %d(w:%d,v:%d)", indexAry[i][k], weight[indexAry[i][k]], value[indexAry[i][k]]);
		//}
		//printf("  totWeight=%d,  totValue=%d\n", sumWeight, sumValue); // 총 무게 이하로 선택된 물건의 총 무게와 가치 출력
		if(sumValue > maxValue)  // 이번 순열의 총 가치가 기존의 가장 큰 가치보다 크면  
			maxValue = sumValue;  // 이번 순열의 총 가치로 maxValue를 갱신 함
	}
	return  maxValue; // 순열 전체 중에 총 무게를 고려한 최대 가치를 리턴 함
}
/*------------------------------------------------------------------
함수명 및 기능: makePermutaionTable() - index 4개의 순열을 만들어서 indexAry에 저장하는 함수
전달인자 : 만들어낸 순열의 정보 저장 배열의 시작주소
리턴값: 순열의 개수
------------------------------------------------------------------*/
int makePermutaionTable(int (*indexAry)[4]) 
{
	int i, j, k, l;  // iterator
	int cnt=0;  // 순열의 개수 저장 변수
	for(i=1; i<=n; ++i)
	{
		for(j=1;j<=n; ++j)
		{
			if(j!=i)
			{
				for(k=1; k<=n; ++k)
				{
					if(k!=i && k!=j)
					{
						for(l=1; l<=n; ++l)
						{
							if(l!=i && l!=j && l!=k)
							{
								indexAry[cnt][0]=i;
								indexAry[cnt][1]=j;
								indexAry[cnt][2]=k;
								indexAry[cnt][3]=l;
								++cnt;  // 순열의 개수 카운트
							}

						}
					}
				}
			}
		}
	}
	return cnt;
}