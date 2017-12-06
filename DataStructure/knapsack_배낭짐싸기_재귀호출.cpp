#pragma warning(disable: 4996)
#include <stdio.h>
#include <assert.h>
#define MAX_CNT 100
int weight[MAX_CNT+1];  // ������ ���Ը� �����ϴ� �迭(0���� ��� ����)
int value[MAX_CNT+1];   // ���Ǻ� ��ġ�� �����ϴ� �迭 (0���� ��� ����)
int n;                  // ������ ���� ���庯��
int totWeight;          // �賶�� ���� ������ �� ���� ���� ����
void fileLoad(char * fileName);
int knapsack(int itemNum, int remainWeight);

int main()
{
	fileLoad("d:\\data\\knapsack3.txt");
	printf("�ִ� ��ġ : %d\n\n", knapsack(1,totWeight));	
	return 0;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: fineLoad() - ���Ͽ��� ������ ����(����, ��ġ)�� �Է� �޾� �ʱ�ȭ�ϴ� �Լ�
�������� : fileName - ������ ������ �����ϰ� �ִ� ���ϸ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void fileLoad(char * fileName)
{	
	FILE *fp;
	int i; /* iterator */
	fp=fopen(fileName, "rt");
	assert(fp != NULL);

	fscanf(fp, "%d %d\n", &n, &totWeight);  /* ������ ������ �賶�� ���尡���� �ִ빫�� �Է� */

	for(i=1; i<=n; ++i)
	{
		fscanf(fp, "%d %d\n", &weight[i], &value[i]); /* ������ ���Կ� ��ġ �Է� */
	}
	fclose(fp);
	return;
}
/*------------------------------------------------------------------
�Լ��� �� ���: knapsack() - �ش��ϴ� ��ȣ�� ������ ���� ���� ���� ���� ��� �� �� ū ��ġ�� �����ϴ� ����Լ�
�������� : itemNum - ������ ��ȣ
           remainWeight - ���� ����
���ϰ�: �ش繰���� ���� ����� ��ġ�� ���� ���� ����� ��ġ �� ū ��
------------------------------------------------------------------*/
int knapsack(int itemNum, int remainWeight)
{
	int res1, res2;
	if(itemNum == n+1)  // ������ ������ �ʰ� ������
		return 0;
	else if(remainWeight<weight[itemNum])  // ���� ���԰�  ���� ����(itemNum)�� ���Ժ��� ������ ���� ������ ���� �� �ִ��� Ȯ���Ϸ� ��
		return knapsack(itemNum+1,remainWeight);
	else   // ���� ����(itemNum)�� ���� ���� ���� �ִ� ��츦 ȣ�� ��
	{
		res1 = knapsack(itemNum+1, remainWeight);
		res2 = knapsack(itemNum+1, remainWeight-weight[itemNum])+value[itemNum];
		return (res1>res2)?res1:res2; // ���� ����(itemNum)�� ���� ���� ���� �ִ� ��� �� ��ġ�� �� ū ��츦 ���� ��
	}
}
