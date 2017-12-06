#pragma warning(disable: 4996)
#include <stdio.h>
#include <assert.h>
#define MAX_CNT 100
int weight[MAX_CNT+1];  // ������ ���Ը� �����ϴ� �迭(0���� ��� ����)
int value[MAX_CNT+1];   // ���Ǻ� ��ġ�� �����ϴ� �迭 (0���� ��� ����)
int n;                  // ������ ���� ���庯��
int totWeight;          // �賶�� ���� ������ �� ���� ���� ����
void fileLoad(char * fileName);
int knapsack(void);
int makePermutaionTable(int (*indexAry)[4]) ;
/*---------------------------------------------------------------------------------------
   main()
 ---------------------------------------------------------------------------------------*/
int main()
{
	fileLoad("d:\\data\\knapsack1.txt");
	printf("�ִ� ��ġ : %d\n\n", knapsack());	
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

	fscanf(fp, "%d %d\n", &n, &totWeight);  // ������ ������ �賶�� ���尡���� �ִ� ���� �Է� 

	for(i=1; i<=n; ++i)
	{
		fscanf(fp, "%d %d\n", &weight[i], &value[i]); // ���Ǻ� ���Կ� ��ġ �Է�
	}
	fclose(fp);
	return;
}
/*------------------------------------------------------------------
�Լ��� �� ���: knapsack() - ���濡 ���� ū ��ġ�� �����ϴ� ��츦 ã�Ƴ��� �Լ� 
�������� : ����
���ϰ�: ������ ���� ��ü �߿� �� ���Ը� ����� �ִ� ��ġ�� ���� ��
------------------------------------------------------------------*/
int knapsack(void)
{
	int indexAry[24][4] = {0};
	int cnt;
	int i, j;
	int maxValue=0; // �ִ� ��ġ ���� ���� 
	int sumValue;
	int sumWeight;  

	cnt=makePermutaionTable(indexAry);

	for(i=0; i<cnt; i++)
	{
		printf("cnt : %3d = ", i+1);
	    printf("[ %d %d %d %d ]\n", indexAry[i][0], indexAry[i][1], indexAry[i][2], indexAry[i][3]);
		sumValue = sumWeight = 0;
		for(j=0; j<n; ++j) // 4���� ������ 
		{
			sumWeight += weight[indexAry[i][j]];
			if(totWeight<sumWeight)   // ���� ���԰� �� ���Ը� �ʰ��ϸ�
			{
				sumWeight -= weight[indexAry[i][j]]; // �� ������ ���Ը� ���ְ� for�� Ż��
				break;
			}
			sumValue += value[indexAry[i][j]]; // ���� ������ �賶�� ������ ��ġ�� ���� ��
		}
		//for(int k=0; k<j; ++k)  // �� ���� ���Ϸ� ���õ� ������ ������ ��ȣ(�ε���)�� ����, ��ġ�� ����ϱ�
		//{
		//	printf(" %d(w:%d,v:%d)", indexAry[i][k], weight[indexAry[i][k]], value[indexAry[i][k]]);
		//}
		//printf("  totWeight=%d,  totValue=%d\n", sumWeight, sumValue); // �� ���� ���Ϸ� ���õ� ������ �� ���Կ� ��ġ ���
		if(sumValue > maxValue)  // �̹� ������ �� ��ġ�� ������ ���� ū ��ġ���� ũ��  
			maxValue = sumValue;  // �̹� ������ �� ��ġ�� maxValue�� ���� ��
	}
	return  maxValue; // ���� ��ü �߿� �� ���Ը� ����� �ִ� ��ġ�� ���� ��
}
/*------------------------------------------------------------------
�Լ��� �� ���: makePermutaionTable() - index 4���� ������ ���� indexAry�� �����ϴ� �Լ�
�������� : ���� ������ ���� ���� �迭�� �����ּ�
���ϰ�: ������ ����
------------------------------------------------------------------*/
int makePermutaionTable(int (*indexAry)[4]) 
{
	int i, j, k, l;  // iterator
	int cnt=0;  // ������ ���� ���� ����
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
								++cnt;  // ������ ���� ī��Ʈ
							}

						}
					}
				}
			}
		}
	}
	return cnt;
}