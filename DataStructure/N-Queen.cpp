#pragma warning(disable: 4996)
#include <stdio.h>
#define CHECK (1)
#define MAX_CNT 15
int columnChk[MAX_CNT+1];             // column 체크 배열 (0번방 사용 안함)
int incDiagonalLineChk[MAX_CNT*2+1];  // 각도가 증가하는 대각선 체크 배열 (0번방 사용 안함)
int decDiagonalLineChk[MAX_CNT*2+1];  // 각도가 감소하는 대각선 체크 배열 (0번방 사용 안함)
int placementCnt;                     // 서로 공격못하게 배치 가능한 경우의 수 카운트 변수
int n;                                // queen의 수(또한 행,열의 수) 저장변수

void nQueen(int row);

int main()
{
	while(1)  // 퀸의 개수가 1~MAX_CNT 개 범위가 아니면 재입력
	{
		printf("퀸의 개수를 입력 하시오 : ");
		scanf("%d", &n);
		if(n>0 && n<=MAX_CNT) 
			break;
	}
	nQueen(1);
	printf("배치 가능한 경우의 수 : %d\n\n", placementCnt);	
	return 0;
}
/*------------------------------------------------------------------
  함수명 및 기능: nQueen() - n개의 queen을 배치하기 위한 재귀호출 함수
  전달인자 : row - 체스판의 행번호(0행은 사용 안함)
  리턴값: 없음
------------------------------------------------------------------*/
void nQueen(int row)
{
	int i;
	/* n이 4일때 좌표계산법
	(1,1)  (1,2)  (1,3)  (1,4)
	(2,1)  (2,2)  (2,3)  (2,4)
	(3,1)  (3,2)  (3,3)  (3,4)
	(4,1)  (4,2)  (4,3)  (4,4)
	(1,1) 대각선은 incDiagonalLineChk[2] 방에 체크 <<== (행+열) = 1+1 = 2번방
	(2,1) (1,2) 대각선은 incDiagonalLineChk[3] 방에 체크
	(3,1) (2,2) (1,3) 대각선은 incDiagonalLineChk[4] 방에 체크
	(4,1) (3,2) (2,3) (1,4) 대각선은 incDiagonalLineChk[5] 방에 체크 ...
	(1,4) 대각선은 decDiagonalLineChk[1] 방에 체크 <== n+(행-열) = 4+(1-4) = 1번방
	(1,3) (2,4) 대각선은 decDiagonalLineChk[2] 방에 체크 
	(1,2) (2,3) (3,4) 대각선은 decDiagonalLineChk[3] 방에 체크
	(1,1) (2,2) (3,3) (4,4) 대각선은 decDiagonalLineChk[4] 방에 체크 ...  */
	
	/* for(int j=1;j<=n;++j)
		printf("%4d", columnChk[j]);
	printf("\n"); */

	if(row>n) // 행값이 n을 초과하면 퀸을 서로 공격못하게 배치하는 작업이 1회 끝난 것이므로  
	{
		placementCnt++;   // 배치 카운트를 증가시키고
		return;           // backtrack
	}
	

	for(i=1; i<=n; ++i)
	{
		if(!columnChk[i] && !incDiagonalLineChk[row+i] && !decDiagonalLineChk[n+(row-i)])
		{
			columnChk[i] = incDiagonalLineChk[row+i] = decDiagonalLineChk[n+(row-i)] = CHECK; // 퀸 배치
			nQueen(row+1);  // 현재 행이 가능하므로 다음 행을 검사하기 위해 재귀호출 함
			columnChk[i] = incDiagonalLineChk[row+i] = decDiagonalLineChk[n+(row-i)] = 0; // backtrack 후 체크했던 내용 삭제 
		}
	}
	return;
}
/* 실행결과 

  n= 1  배치가능 경우 = 1
  n= 2  배치가능 경우 = 0
  n= 3  배치가능 경우 = 0
  n= 4  배치가능 경우 = 2
  n= 5  배치가능 경우 = 10
  n= 6  배치가능 경우 = 4
  n= 7  배치가능 경우 = 40
  n= 8  배치가능 경우 = 92
  n= 9  배치가능 경우 = 352
  n=10  배치가능 경우 = 724
  n=11  배치가능 경우 = 2680
  n=12  배치가능 경우 = 14200
  n=13  배치가능 경우 = 73712
  n=14  배치가능 경우 = 365596
  n=15  배치가능 경우 = 2279184
  
*/