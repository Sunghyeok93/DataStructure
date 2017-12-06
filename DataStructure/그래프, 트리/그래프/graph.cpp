#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

int check[MAX_VERTAX];


//데이터 파일에서 그래프의 정점과 간선 정보를 입력받아 그래프를 초기화 하는 함수
// gm - 그래프 정보 구조체의 주소, fileName - 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
void initGraph(GraphMatrix *gm, char *fileName)
{
	char str[3];
	FILE *fp;
	
	fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		printf("파일오픈 에러!\n");
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

//그래프내의 정점과 간선의 관계를 인접 행렬 형태로 출력함
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

//여러개의 연결 요소로 구성된 그래프를 깊이 우선 탐색하기 위한 함수(재귀)
//DFS_recursive()함수를 호출하여 처리(이 함수 자체는 재귀 안함)
void DFS_Matrix(GraphMatrix *gm)
{
	for (int i = 0; i < gm->vertexCnt; i++)//정점의 방문상태정보를 저장할 check배열 초기화
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

//연결되어 있는 하나의 그래프내의 모든 정점을 재귀호출 기법으로 방문하는 함수
//gm - 그래프 정보 구조체의 주소, vnum - 방문하고자 하는 정점번호
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

//방문한 정점의 처리
//vnum - 방문하고자 하는 정점번호
void visit(int vNum)
{
	printf("%3c", 'A' + vNum);
}

//여러개의 연결 요소로 구성된 그래프를 '깊이 우선' 탐색하기 위한 함수(비 재귀판)
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

//여러개의 연결 요소로 구성된 그래프를 '너비 우선' 탐색하기 위한 함수(비 재귀판)
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

//인접 행렬법으로 표기되 그래프 내의 연결요소별로 정점들을 출력하고 연결 요소의 개수를 리턴하는 함수
//리턴 - 그래프내의 연결 요소의 개수
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
			printf("연결 요소 %d : ", count + 1);
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


//데이터 파일에서 그래프의 정점과 간선정보를 입력받아 그래프를 인접 리스트법으로 초기화 하는 함수
void initGraph_List(GraphList *g, char *fileName)
{
	FILE *fp;
	char str[3];
	fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		printf("파일 오픈 실패");
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

//그래프 내의 정점과 간선의 관계를 인접리스트 형태로 출력
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

//두 정점의 관계를 리스트에 등록함
//g - 그래프 정보 구조체의 주소, vNum1 - 첫번째 정점의 번호, vNum2 - 두번째 정점의 번호
//정점 등록이 성공하면 true, 실패하면 false 리턴
int addNode(GraphList *g, int vNum1, int vNum2)
{
	return 0;
}

//그래프 내의 정점 노드 모두 삭제
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


