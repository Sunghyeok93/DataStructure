#include <stdio.h>
#include <stdlib.h>

void cal_ary(int(*A)[4], int(*B)[4], int(*C)[4]);
void print_ary(int(*A)[4], int(*B)[4], int(*C)[4]);

int main(void)
{
	int A[4][4] = { { 0, 1, 2, 3 }, { 1, -2, 1, 2 }, { 2, 5, -3, 2 }, { 0, -3, 1, 4 } };
	int B[4][4] = { { 1, -1, 2, 0 }, { 1, -1, 1, 2 }, { -1, 0, 3, 1 }, { 2, -1, 2, 8 } };
	int C[4][4] = { 0 };
	
	cal_ary(A, B, C);
	print_ary(A, B, C);
}

void cal_ary(int(*A)[4], int(*B)[4], int(*C)[4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				C[i][j] += (A[i][k] * B[k][j]);
			}
		}
	}
}

void print_ary(int(*A)[4], int(*B)[4], int(*C)[4])
{
	printf("  [Matrix A]     [Matrix B]     [Matrix C]");
	
	for (int i = 0; i < 4; i++)
	{
		printf("\n");
		for (int j = 0; j < 4; j++)
		{
			printf("%3d", A[i][j]);
		}
		printf("   ");
		for (int j = 0; j < 4; j++)
		{
			printf("%3d", B[i][j]);
		}
		printf("   ");
		for (int j = 0; j < 4; j++)
		{
			printf("%3d", C[i][j]);
		}
	}
	printf("\n");
}
