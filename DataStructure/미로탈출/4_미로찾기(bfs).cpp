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


int map[MAX_SIZE + 1][MAX_SIZE  + 1];  /* �̷� ������ ������ �迭(0��, 0�� ��� ����) */
int row, col;     /* map�� ����(row), ����(colum)�� ũ�� ���� ���� */
RC  start, goal;  /* �̷��� ������ǥ, ������ǥ ���� */

 /*-------------------------------------------------------------------------------------
	   �Լ��� �� ���  main() : �׷����� �����ϰ� BFS Ž���� �ǽ��Ѵ�.
 ------------------------------------------------------------------------------------*/
int main()
{
	char *fileName[] = { "d:\\data\\�̷�ã��1.txt" , "d:\\data\\�̷�ã��2.txt","d:\\data\\�̷�ã��3.txt" };
	int res;
	for (int i = 0; i < sizeof(fileName) / sizeof(fileName[0]); ++i) {
		if (dataLoad(fileName[i]) == FALSE) return 0;
		res = solve();
		if (res > 0) {
			printf("�ִ� �Ÿ� : %d\n\n", res);
		}
		else {
			printf("������ �� �����ϴ�.\n\n");
		}
		
		output();
		NL;
		printf("===================================================================\n\n");
	}
	PAUSE;
	return 0;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  dataLoad() : ������ ���Ͽ��� �˻��� �����͸� �Է� �޾� map�� �����ϴ� �Լ�
��������        char *fileName : �̷� ������ ����� ������ ���ϸ�
���ϰ�          ���� �бⰡ �����ϸ� TRUE ����, �����ϸ� FALSE ����
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
				map[i][j] = -2;  /* goal�� ���ڸ� . ���� ���� */
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
�Լ��� �� ���  output() : �̷� ���� ����Լ�
��������        ����
���ϰ�          ����
--------------------------------------------------------------------------------------*/
void output()
{
	int i, j;
	printf("** �̷���� **\n");
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
�Լ��� �� ���  solve() : BFS������� �ִܰŸ� ���ϴ� �Լ�
��������        ����
���ϰ�          �ִܰŸ� ��
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
�Լ��� �� ���  inRange() : row, colum�� ���ռ� �Ǻ� �Լ�
��������        int r : �� �� / int c : �� ��
���ϰ�          ������ �����̸� TRUE ����, �������� �����̸� FALSE ����
--------------------------------------------------------------------------------------*/
int inRange(int r, int c)
{
	return (0<r && r <= row) && (0<c && c <= col);
}

