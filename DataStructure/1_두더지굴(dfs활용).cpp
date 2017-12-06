#pragma warning(disable:4996)
#include<stdio.h>
#include<assert.h>
#include<windows.h>
#define TRUE (1)
#define FALSE (0)
#define NL printf("\n")
#define PAUSE system("pause")

typedef struct tunnel_info {
	int number;  /* �� ��ȣ */
	int size;    /* �� ũ�� */
}TunnelInfo;

#define MAX_SIZE 30
int dataLoad(char *);
void solve();
void output();
void dfs(int row, int col, int tNum);
void sort(int start, int end);

int map[MAX_SIZE + 1][MAX_SIZE + 1];  /* �δ��� ���� ���� ����(0��, 0�� ��� ����) */
TunnelInfo tunnelInfo[MAX_SIZE * 2 + 1];    /* �δ��� ���� ũ�� ����(2�� �� ���ĺ��� ���) */
int n;  /* map�� ����(row), ����(colum)�� ũ�� ���� ���� */
int tunnelNumber;  /* �δ����� ��ȣ */
/*-------------------------------------------------------------------------------------
�Լ��� �� ���  main() : �׷����� �����ϰ� DFS Ž���� �ǽ��Ѵ�.
------------------------------------------------------------------------------------*/
int main()
{
	char *fileName[] = { "d:\\data\\�δ�����1.txt" , "d:\\data\\�δ�����2.txt", "d:\\data\\�δ�����3.txt" };
	for (int i = 0; i < sizeof(fileName) / sizeof(fileName[0]); ++i) {
		tunnelNumber = 1; /* �δ����� ��ȣ(1�� �ͳ��� ������ �ǹ��ϹǷ� 2�� ���� ���) */
		if (dataLoad(fileName[i]) == FALSE) return 0;
		solve();
		output();
		NL;
		printf("===================================================================\n\n");
	}
	PAUSE;
	return 0;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  dataLoad() : ������ ���Ͽ��� �˻��� �����͸� �Է� �޾� map�� �����ϴ� �Լ�
��������        char *fileName : �δ��� ���� ������ ����� ������ ���ϸ�
���ϰ�          ���� �бⰡ �����ϸ� TRUE ����, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
int dataLoad(char *fileName)
{
	FILE *fp;

	int i, j; /* iterator */
	fp = fopen(fileName, "rt");
	if (fp == NULL) {
		printf("file open error!!!\n");
		PAUSE;
		return FALSE;
	}
	if (fscanf(fp, "%d", &n) != 1) return FALSE;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			if (fscanf(fp, "%d", &map[i][j]) != 1) return FALSE;
		}
	}
	fclose(fp);
	return TRUE;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  initTunnelInfo() : ���� ������ ������ ����ü �ʱ�ȭ �Լ�
��������        ����
���ϰ�          ����
--------------------------------------------------------------------------------------*/
void initTunnelInfo()
{
	int i;
	for (i = 0; i <= MAX_SIZE*2; ++i) {
		tunnelInfo[i].number = i;
		tunnelInfo[i].size = 0;  /* extern���� ����� �迭�� ����̹Ƿ� ���ص� �� */
	}
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  solve() : �δ��� ���� ����, ũ�⸦ ����ϴ� �Լ�(���ȣ�� ������ dfs�� �̿��� Ǯ��)
��������        ����
���ϰ�          ����
--------------------------------------------------------------------------------------*/
void solve()
{
	int i, j;
	initTunnelInfo();
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			if (map[i][j] == 1) {  /* �ͳ��� �߰ߵǸ� */
				++tunnelNumber;
				dfs(i, j, tunnelNumber);  /* ���̿켱Ž�� ���� */
			}
		}
	}
	return;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  inRange() : row, colum�� ���ռ� �Ǻ� �Լ�
��������        int row : �� ��
                int col : �� ��
���ϰ�          ������ �����̸� TRUE ����, �������� �����̸� FALSE ����
--------------------------------------------------------------------------------------*/
int inRange(int row, int col)
{
	return (0<row && row<=n) && (0<col && col<=n);
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  dfs() : row, col�� ���� �δ��� ������ dfs������� �˻��ϴ� �Լ� 
��������        int row : �� ��   /  int col : �� ��
                int tNum : �δ��� �� ��ȣ(2���� ����)
���ϰ�          ����
--------------------------------------------------------------------------------------*/
void dfs(int row, int col, int tNum)
{
	if (inRange(row, col) == FALSE) return;
	if (map[row][col] != 1) return;
	map[row][col] = tNum; /* üũ�� �δ����� ������ �ٲ� */
	++tunnelInfo[tNum].size;  /* �δ������� ũ�� ���� */
	dfs(row - 1, col, tNum);
	dfs(row + 1, col, tNum);
	dfs(row, col - 1, tNum);
	dfs(row, col + 1, tNum);
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  output() : �δ��� ���� ���¿� ũ������� ��Ʈ�� �δ��� ���� ���� ����Լ�
��������        ����
���ϰ�          ����
--------------------------------------------------------------------------------------*/
void output()
{
	int i, j;
	printf("** �δ��� �� ���� : %d��\n", tunnelNumber-1);
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			printf("%3d", map[i][j]);
		}
		NL;
	}
	NL;
	
	sort(2, tunnelNumber);
	printf("** �δ��� �� ũ������� ��� **\n");
	for (i = 2; i <= tunnelNumber; ++i) {
		printf("size of tunnel %d : %d\n", tunnelInfo[i].number, tunnelInfo[i].size);
	}

}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���  sort() : �δ��� ���� ������ �����ϰ� �ִ� �迭�� ���� ũ�⸦ �������� 
                         �������� ��Ʈ�ϴ� �Լ�
��������        int start : ��Ʈ�� ������ ���� index ��
                int end : ��Ʈ�� ������ �� index ��
���ϰ�          ����
--------------------------------------------------------------------------------------*/
void sort(int start, int end)
{
	int i, j;
	int max;
	TunnelInfo temp;
	for (i = start; i < end; ++i) {
		max = i;
		for (j = i + 1; j <= end; ++j) {
			if (tunnelInfo[max].size < tunnelInfo[j].size)
				max = j;
		}
		temp = tunnelInfo[i];
		tunnelInfo[i] = tunnelInfo[max];
		tunnelInfo[max] = temp;
	}
}