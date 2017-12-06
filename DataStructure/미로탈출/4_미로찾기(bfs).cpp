#pragma warning(disable:4996)
#include<stdio.h>
#include<assert.h>
#include<windows.h>
#include<conio.h>
#include "queue.h"
//#define TRUE (1)
//#define FALSE (0)
#define NL printf("\n")
#define PAUSE system("pause")

#define MAX_SIZE 100
int dataLoad(char *);
int solve();
void output();
int inRange(int r, int c);


int map[MAX_SIZE + 1][MAX_SIZE  + 1];  /* 미로 지도를 저장할 배열(0행, 0열 사용 안함) */
int row, col;     /* map의 가로(row), 세로(colum)의 크기 저장 변수 */
RC  start, goal;  /* 미로의 시작좌표, 골인좌표 저장 */

 /*-------------------------------------------------------------------------------------
	   함수명 및 기능  main() : 그래프를 구현하고 BFS 탐색을 실시한다.
 ------------------------------------------------------------------------------------*/
int main()
{
	char *fileName[] = { "d:\\data\\미로찾기1.txt" , "d:\\data\\미로찾기2.txt","d:\\data\\미로찾기3.txt" };
	int res;
	for (int i = 0; i < sizeof(fileName) / sizeof(fileName[0]); ++i) {
		if (dataLoad(fileName[i]) == FALSE) return 0;
		res = solve();
		if (res > 0) {
			printf("최단 거리 : %d\n\n", res);
		}
		else {
			printf("도달할 수 없습니다.\n\n");
		}
		
		output();
		NL;
		printf("===================================================================\n\n");
	}
	PAUSE;
	return 0;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능  dataLoad() : 데이터 파일에서 검사할 데이터를 입력 받아 map에 저장하는 함수
전달인자        char *fileName : 미로 정보가 저장된 데이터 파일명
리턴값          파일 읽기가 성공하면 TRUE 리턴, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int dataLoad(char *fileName)
{
	FILE *fp;
	int i,j; /* iterator */
	char ch;
	fp = fopen(fileName, "rt");
	if (fp == NULL) {
		printf("file open error!!!\n");
		PAUSE;
		return FALSE;
	}
	if (fscanf(fp, "%d %d\n", &row, &col) != 2) return FALSE;
	for (i = 1; i <= row; ++i) {
		for (j = 1; j <= col; ++j) {
			ch = fgetc(fp);
			if (ch == '#') map[i][j] = -1;
			else if (ch == '.') map[i][j] = -2;
			else if (ch == 's') { 
				map[i][j] = 0;
				start.row = i; start.col = j; 
			}
			else if (ch == 'g') {
				map[i][j] = -2;  /* goal의 문자를 . 으로 변경 */
				goal.row = i;
				goal.col = j;
			}
		}
		fgetc(fp);
	}
	fclose(fp);
	return TRUE;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능  output() : 미로 상태 출력함수
전달인자        없음
리턴값          없음
--------------------------------------------------------------------------------------*/
void output()
{
	int i, j;
	printf("** 미로출력 **\n");
	for (i = 1; i <= row; ++i) {
		for (j = 1; j <= col; ++j) {
			if(map[i][j]==-1)	printf("  #");        
			else if (map[i][j] == -2) printf("  .");  
			else if(map[i][j] == 0) printf("  S");
			else printf("%3d", map[i][j]);
		}
		NL;
	}
	NL;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능  solve() : BFS방식으로 최단거리 구하는 함수
전달인자        없음
리턴값          최단거리 값
--------------------------------------------------------------------------------------*/
int solve()
{
	Queue que;
	RC rc, tRc;
	RC rcxy[4] = { {-1,0},{1,0},{0,-1},{0,1} };
	int tY, tX;

	initQueue(&que, MAX_SIZE);
	enqueue(&que, start);

	while (!isQueueEmpty(&que)) {
		dequeue(&que, &rc);
		if (rc.row == goal.row && rc.col == goal.col) break;
		for (int i = 0; i < 4; ++i) {
			tY = rc.row + rcxy[i].row;
			tX = rc.col + rcxy[i].col;
			if (inRange(tY, tX) && map[tY][tX] == -2) {
				map[tY][tX] = map[rc.row][rc.col] + 1;
				tRc.row = tY;
				tRc.col = tX;
				enqueue(&que, tRc);
			}
		}
	}
	return map[goal.row][goal.col];
}
/*--------------------------------------------------------------------------------------
함수명 및 기능  inRange() : row, colum의 적합성 판별 함수
전달인자        int r : 행 값 / int c : 열 값
리턴값          적합한 범위이면 TRUE 리턴, 부적합한 범위이면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int inRange(int r, int c)
{
	return (0<r && r <= row) && (0<c && c <= col);
}

