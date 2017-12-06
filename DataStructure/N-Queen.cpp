#pragma warning(disable: 4996)
#include <stdio.h>
#define CHECK (1)
#define MAX_CNT 15
int columnChk[MAX_CNT+1];             // column üũ �迭 (0���� ��� ����)
int incDiagonalLineChk[MAX_CNT*2+1];  // ������ �����ϴ� �밢�� üũ �迭 (0���� ��� ����)
int decDiagonalLineChk[MAX_CNT*2+1];  // ������ �����ϴ� �밢�� üũ �迭 (0���� ��� ����)
int placementCnt;                     // ���� ���ݸ��ϰ� ��ġ ������ ����� �� ī��Ʈ ����
int n;                                // queen�� ��(���� ��,���� ��) ���庯��

void nQueen(int row);

int main()
{
	while(1)  // ���� ������ 1~MAX_CNT �� ������ �ƴϸ� ���Է�
	{
		printf("���� ������ �Է� �Ͻÿ� : ");
		scanf("%d", &n);
		if(n>0 && n<=MAX_CNT) 
			break;
	}
	nQueen(1);
	printf("��ġ ������ ����� �� : %d\n\n", placementCnt);	
	return 0;
}
/*------------------------------------------------------------------
  �Լ��� �� ���: nQueen() - n���� queen�� ��ġ�ϱ� ���� ���ȣ�� �Լ�
  �������� : row - ü������ ���ȣ(0���� ��� ����)
  ���ϰ�: ����
------------------------------------------------------------------*/
void nQueen(int row)
{
	int i;
	/* n�� 4�϶� ��ǥ����
	(1,1)  (1,2)  (1,3)  (1,4)
	(2,1)  (2,2)  (2,3)  (2,4)
	(3,1)  (3,2)  (3,3)  (3,4)
	(4,1)  (4,2)  (4,3)  (4,4)
	(1,1) �밢���� incDiagonalLineChk[2] �濡 üũ <<== (��+��) = 1+1 = 2����
	(2,1) (1,2) �밢���� incDiagonalLineChk[3] �濡 üũ
	(3,1) (2,2) (1,3) �밢���� incDiagonalLineChk[4] �濡 üũ
	(4,1) (3,2) (2,3) (1,4) �밢���� incDiagonalLineChk[5] �濡 üũ ...
	(1,4) �밢���� decDiagonalLineChk[1] �濡 üũ <== n+(��-��) = 4+(1-4) = 1����
	(1,3) (2,4) �밢���� decDiagonalLineChk[2] �濡 üũ 
	(1,2) (2,3) (3,4) �밢���� decDiagonalLineChk[3] �濡 üũ
	(1,1) (2,2) (3,3) (4,4) �밢���� decDiagonalLineChk[4] �濡 üũ ...  */
	
	/* for(int j=1;j<=n;++j)
		printf("%4d", columnChk[j]);
	printf("\n"); */

	if(row>n) // �ప�� n�� �ʰ��ϸ� ���� ���� ���ݸ��ϰ� ��ġ�ϴ� �۾��� 1ȸ ���� ���̹Ƿ�  
	{
		placementCnt++;   // ��ġ ī��Ʈ�� ������Ű��
		return;           // backtrack
	}
	

	for(i=1; i<=n; ++i)
	{
		if(!columnChk[i] && !incDiagonalLineChk[row+i] && !decDiagonalLineChk[n+(row-i)])
		{
			columnChk[i] = incDiagonalLineChk[row+i] = decDiagonalLineChk[n+(row-i)] = CHECK; // �� ��ġ
			nQueen(row+1);  // ���� ���� �����ϹǷ� ���� ���� �˻��ϱ� ���� ���ȣ�� ��
			columnChk[i] = incDiagonalLineChk[row+i] = decDiagonalLineChk[n+(row-i)] = 0; // backtrack �� üũ�ߴ� ���� ���� 
		}
	}
	return;
}
/* ������ 

  n= 1  ��ġ���� ��� = 1
  n= 2  ��ġ���� ��� = 0
  n= 3  ��ġ���� ��� = 0
  n= 4  ��ġ���� ��� = 2
  n= 5  ��ġ���� ��� = 10
  n= 6  ��ġ���� ��� = 4
  n= 7  ��ġ���� ��� = 40
  n= 8  ��ġ���� ��� = 92
  n= 9  ��ġ���� ��� = 352
  n=10  ��ġ���� ��� = 724
  n=11  ��ġ���� ��� = 2680
  n=12  ��ġ���� ��� = 14200
  n=13  ��ġ���� ��� = 73712
  n=14  ��ġ���� ��� = 365596
  n=15  ��ġ���� ��� = 2279184
  
*/