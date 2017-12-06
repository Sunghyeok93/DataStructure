#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

int check[MAX_VERTAX];


//������ ���Ͽ��� �׷����� ������ ���� ������ �Է¹޾� �׷����� �ʱ�ȭ �ϴ� �Լ�
// gm - �׷��� ���� ����ü�� �ּ�, fileName - �׷����� ���� �� ���� ������ ����� ������ ���ϸ�
void initGraph(GraphMatrix *gm, char *fileName)
{
	char str[3];
	FILE *fp;
	
	fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		printf("���Ͽ��� ����!\n");
		return;
	}
	
	fscanf(fp, "%d", &gm->vertexCnt);
	fscanf(fp, "%d", &gm->edgeCnt);
	
	for (int i = 0; i < MAX_VERTAX; i++)
	{
		for (int j=0; j < MAX_VERTAX; j++)
		{
			gm->graph[i][j] = 0;
		}
	
	}
	
	for (int i = 0; i < gm->edgeCnt; i++)
	{
		fscanf(fp, "%s", str);
		gm->graph[str[0] - 'A'][str[1] - 'A'] = 1;
		gm->graph[str[1] - 'A'][str[0] - 'A'] = 1;
	}
}

//�׷������� ������ ������ ���踦 ���� ��� ���·� �����
void outputGraph(GraphMatrix *gm)
{
	int A = 65;
	printf(" ");
	for (int i = 0; i < 17; i++)
	{
		printf("%2c", 65 + i);
	}
	printf("\n");
	for (int i = 0; i < gm->vertexCnt; i++)
	{
		printf("%c", A + i);
		for (int j = 0; j < gm->vertexCnt; j++)
		{
			printf("%2d", gm->graph[i][j]);
		}
		printf("\n");
	}
}

//�������� ���� ��ҷ� ������ �׷����� ���� �켱 Ž���ϱ� ���� �Լ�(���)
//DFS_recursive()�Լ��� ȣ���Ͽ� ó��(�� �Լ� ��ü�� ��� ����)
void DFS_Matrix(GraphMatrix *gm)
{
	for (int i = 0; i < gm->vertexCnt; i++)//������ �湮���������� ������ check�迭 �ʱ�ȭ
	{
		check[i] = 0;
	}
	for (int i = 0; i < gm->vertexCnt; i++)
	{
		if (check[i] == 0)
		{
			DFS_recursive(gm, i);
		}
	}
}

//����Ǿ� �ִ� �ϳ��� �׷������� ��� ������ ���ȣ�� ������� �湮�ϴ� �Լ�
//gm - �׷��� ���� ����ü�� �ּ�, vnum - �湮�ϰ��� �ϴ� ������ȣ
void DFS_recursive(GraphMatrix *gm, int vNum)
{
	check[vNum] = 1;
	visit(vNum);
	for (int i = 0; i < gm->vertexCnt; i++)
	{
		if (gm->graph[vNum][i] != 0)
		{
			if (check[i] == 0)
			{
				DFS_recursive(gm, i);
				check[i] = 1;
			}
		}
	}
	return;
}

//�湮�� ������ ó��
//vnum - �湮�ϰ��� �ϴ� ������ȣ
void visit(int vNum)
{
	printf("%3c", 'A' + vNum);
}

//�������� ���� ��ҷ� ������ �׷����� '���� �켱' Ž���ϱ� ���� �Լ�(�� �����)
void nrDFS_Matrix(GraphMatrix *gm)
{
	int i, j;
	int popData;
	Stack stack;
	initStack(&stack);
	
	for (i = 0; i < gm->vertexCnt; i++)
	{
		check[i] = 0;
	}
	for (i = 0; i < gm->vertexCnt; i++)
	{
		if (check[i] == 0)
		{
			push(&stack, i);
			check[i] = 1;
			while (!isStackEmpty(&stack))
			{
				pop(&stack, &popData);
				visit(popData);
				for (j = 0; j < gm->vertexCnt; j++)
				{
					if (gm->graph[popData][j] != 0)
					{
						if (check[j] == 0)
						{
							push(&stack, j);
							check[j] = 1;
						}
					}
				}
			}
		}
	}
	destroyStack(&stack);
	return;
}

//�������� ���� ��ҷ� ������ �׷����� '�ʺ� �켱' Ž���ϱ� ���� �Լ�(�� �����)
void BFS_Matrix(GraphMatrix *gm)
{
	Queue que;
	int getData;
	initQueue(&que, gm->vertexCnt+1);

	for (int i = 0; i < gm->vertexCnt; i++)
		check[i] = 0;

	for (int i = 0; i < gm->vertexCnt; i++)
	{
		if (check[i] == 0)
		{
			enqueue(&que, i);
			check[i] = 1;
		}
		for (int j = i + 1; j < gm->vertexCnt; j++)
		{
			if (gm->graph[i][j] == 1 && check[j] == 0)
			{
				enqueue(&que, j);
				check[j] = 1;
			}
		}
		if (dequeue(&que, &getData) == 1)
			printf("%2c", getData + 'A');
	}
	printf("\n");
	destroyQueue(&que);
}

//���� ��Ĺ����� ǥ��� �׷��� ���� �����Һ��� �������� ����ϰ� ���� ����� ������ �����ϴ� �Լ�
//���� - �׷������� ���� ����� ����
int countGraphComponents(GraphMatrix *gm)
{
	int count = 0;
	int i, j;
	int popData;
	Stack stack;
	initStack(&stack);
	for (i = 0; i < gm->vertexCnt; i++)
	{
		check[i] = 0;
	}
	for (i = 0; i < gm->vertexCnt; i++)
	{
		if (check[i] == 0)
		{
			push(&stack, i);
			check[i] = 1;
			printf("���� ��� %d : ", count + 1);
			while (!isStackEmpty(&stack))
			{
				pop(&stack, &popData);
				visit(popData);
				for (j = 0; j < gm->vertexCnt; j++)
				{
					if (gm->graph[popData][j] != 0)
					{
						if (check[j] == 0)
						{
							push(&stack, j);
							check[j] = 1;
						}
					}
				}
			}
			printf("\n");
			count++;
		}
	}
	destroyStack(&stack);
	return count;
}


//������ ���Ͽ��� �׷����� ������ ���������� �Է¹޾� �׷����� ���� ����Ʈ������ �ʱ�ȭ �ϴ� �Լ�
void initGraph_List(GraphList *g, char *fileName)
{
	FILE *fp;
	char str[3];
	fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		printf("���� ���� ����");
		return;
	}
	fscanf(fp, "%d", &g->vertexCnt);
	fscanf(fp, "%d", &g->edgeCnt);
	
	for (int i = 0; i < g->vertexCnt; i++)
	{
		g->graph[i]= NULL;
	}
	Node * np1;
	Node * np2;
	for (int i = 0; i < g->edgeCnt; i++)
	{
		fscanf(fp, "%s", str);
		np1 = (Node *)calloc(1, sizeof(Node));
		np1->vertex = (int)(str[1] - 'A');
		np1->next = g->graph[str[0] - 'A'];
		g->graph[str[0] - 'A'] = np1;
		
		np2 = (Node *)calloc(1, sizeof(Node));
		np2->vertex = (int)(str[0] - 'A');
		np2->next = g->graph[str[1] - 'A'];
		g->graph[str[1] - 'A'] = np2;
	}
	printf("\n\n");
}

//�׷��� ���� ������ ������ ���踦 ��������Ʈ ���·� ���
void outputGraph_List(GraphList *g)
{
	int A = 65;
	Node * tmp;
	for (int i = 0; i < g->vertexCnt; i++)
	{
		tmp = g->graph[i];
		printf("%c : ", A+i);
		while (tmp !=NULL)
		{
			printf("%c -> ", tmp->vertex + A);
			tmp = tmp->next;
		}
		printf("\b\b\b\b   \n");
	}
	return;
}

//�� ������ ���踦 ����Ʈ�� �����
//g - �׷��� ���� ����ü�� �ּ�, vNum1 - ù��° ������ ��ȣ, vNum2 - �ι�° ������ ��ȣ
//���� ����� �����ϸ� true, �����ϸ� false ����
int addNode(GraphList *g, int vNum1, int vNum2)
{
	return 0;
}

//�׷��� ���� ���� ��� ��� ����
void destroyGraph_List(GraphList *g)
{
	int i;
	Node * now, *next;
	for (i = 0; i < g->vertexCnt; i++)
	{
		now = g->graph[i];
		while (now != NULL)
		{
			next = now->next;
			free(now);
			now = next;
		}
	}
}


