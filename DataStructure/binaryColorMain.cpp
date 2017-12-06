#include<stdio.h>
#include<assert.h>

#define MAX_VERTEX 200
enum{RED=1, BLUE};

int initGraph(FILE *fp);
void DFS_Matrix(int, int);
void outputGraph();

int graph[MAX_VERTEX][MAX_VERTEX]; /* �������� ���� ���� ���� ���� ��� �迭 */
int color[MAX_VERTEX]; /* ������ �÷� �� ���� */
int colorable;  /* binary coloring�� �����ϸ� 1, �ƴϸ� 0 */
int vertexCnt, edgeCnt;   /* ���� ������ ���� ���� ���� ���� */
/*----------------------------------------------------------------------------------------
 �Լ��� : main() 
----------------------------------------------------------------------------------------*/
int main()
{
	int i;
	FILE *fp;        /* �׷��� ���� ���� ������ ���������� */

	fp=fopen("d:\\data\\binaryColor.txt", "rt");
	assert(fp!=NULL);

	while(initGraph(fp))
	{
		outputGraph();
		for(i=0; i<vertexCnt; ++i)
			color[i] = 0;   /* ������ color ������ ������ �迭 �ʱ�ȭ */
		colorable = 1;     /* binary coloring�� �������� �ʱ�ȭ */
		DFS_Matrix(0,RED);  /* 0�� ����, RED color�� ���̿켱 Ž�� ���� */
		
		if(colorable == 0)
			printf("Not BinaryColorable.\n\n");
		else
			printf("BinaryColorable.\n\n");
	}
	fclose(fp);
}
/*--------------------------------------------------------------------------------------
  �Լ��� �� ���: initGraph() - ���������Ͽ��� �׷����� ������ ���� ������ �Է� �޾�
                                �׷����� �ʱ�ȭ�ϴ� �Լ�
  �������� : fp - �׷��� ������ �����ϰ� �ִ� ������ ���� ������
  ���ϰ�: �׷��� �� ��Ʈ�� ���������� �ʱ�ȭ �ϸ� 1����, �����ϸ� 0 ����
--------------------------------------------------------------------------------------*/
int initGraph(FILE *fp)
{
	int vertex1, vertex2;  /* �������� �Է��� ���� ���� */
	int i,j;       /* iterator */

	fscanf(fp, "%d %d\n", &vertexCnt, &edgeCnt);  /* ������ ������ ������ �б� */

	if(vertexCnt==0 && edgeCnt==0) 
		return 0;  /* �׷��� ������ �б⸦ �����ϸ� false ���� */

	/* ������ ������ ���� ���� ��� ���� �ʱ�ȭ */
	for(i=0; i<vertexCnt; ++i)
		for(j=0; j<vertexCnt; ++j)
				graph[i][j] = 0;


	/* ������ �׷��������� ��Ī��(Symmetry) ����� �ʱ�ȭ ǥ�� */
	for(i=0; i<edgeCnt; ++i)
	{
		fscanf(fp, "%d %d\n", &vertex1, &vertex2);
		//printf("%d %d\n", vertex1, vertex2);
		graph[vertex1][vertex2] = graph[vertex2][vertex1] = 1;
	}
	return 1;  /* ���������� �׷��� �����͸� �о����� true ���� */
}
/*--------------------------------------------------------------------------------------
  �Լ��� �� ���: outputGraph() - �׷������� ������ ������ ���踦 ���� ��� ���·� ��� ��
  ���ϰ�: ����
--------------------------------------------------------------------------------------*/
void outputGraph()
{
	int i,j;         /* iterator */

	/* ������ ���ι��� ��� */
	printf("   ");
	for(i=0; i<vertexCnt; ++i)
		printf("%3d",i);

	printf("\n");

	for(i=0; i<vertexCnt; ++i)
	{
		printf("%3d",  i);
		for(j=0; j<vertexCnt; j++)
				printf("%3d", graph[i][j]);
		printf("\n");
	}
}
/*--------------------------------------------------------------------------------------
  �Լ��� �� ���: DFS_Matrix() - DFS�� Ž���Ͽ� coloring�� �������� �˻�
  �������� : vNum - ���� ��ȣ
             col - �÷� ��
  ���ϰ�: ����
--------------------------------------------------------------------------------------*/
void DFS_Matrix(int vNum, int col)
{
	int i;

	color[vNum] = col;
	
	for(i=0; i < vertexCnt && colorable; ++i)
	{
		if(graph[vNum][i] == 0) continue;
		if(color[i] == 0)  /* ���� �Ǿ��ְ� color�� üũ�Ǿ����� ������ */
			DFS_Matrix(i,  (col==RED)?BLUE:RED );
		else      /* ����Ǿ��ְ� color�� üũ�Ǿ� ������ */
			if(color[i] == col)  /* ���� ������ �÷��� ���� ���� �÷��̸� �÷��� �Ұ� */
			{
				colorable = 0;
				return;
			}
	}
}
