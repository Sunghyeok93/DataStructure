#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

int check[MAX_VERTEX];  /* 방문된 정점은 1로 미방문 정점은 0으로 저장 */
/*--------------------------------------------------------------------------------------
  함수명 및 기능: initGraph() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 '
                                그래프를 인접 행렬법으로 초기화하는 함수
  전달인자:  gm - 그래프 정보 구조체의 주소
             fileName - 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void initGraph(GraphMatrix *gm, char *fileName)
{
	char vertex[3];  /* 간선정보 입력을 위한 공간 "AB" 형태의 데이터 저장 char 배열 */
	int i,j,k;       /* iterator */
	FILE *fp;        /* 그래프 정보 저장 파일의 파일포인터 */

	fp=fopen(fileName, "rt");
	assert(fp!=NULL);
	fscanf(fp, "%d %d\n", &gm->vertexCnt, &gm->edgeCnt);  /* 정점과 간선의 개수를 읽기 */

	/* 정점의 개수에 맞춰 인접 행렬 영역 초기화 */
	for(i=0; i<gm->vertexCnt; ++i)
		for(j=0; j<gm->vertexCnt; ++j)
				gm->graph[i][j] = 0;

	/* 무방향 그래프에서의 반사정(Reflexive) 표기 */
	//for(i=0; i<gm->vertexCnt;++i)
	//	gm->graph[i][i] = 1;	
	
	/* 무방향 그래프에서의 대칭성(Symmetry) 고려한 초기화 표기 */
	for(k=0; k<gm->edgeCnt; ++k)
	{
		fscanf(fp, "%s\n",vertex);
		i=vertex[0]-'A';   /* 정점의 이름을 숫자화  'B'-'A' => 1의 형식으로 변환*/
		j=vertex[1]-'A';   /* 정점의 이름을 숫자화 */
		gm->graph[i][j] = gm->graph[j][i] = 1;
	}
	fclose(fp);
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: outputGraph() - 그래프내의 정점과 간선의 관계를 인접 행렬 형태로 출력
  전달인자:  gm : 그래프 정보 구조체의 주소
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void outputGraph(GraphMatrix *gm)
{
	int i,j;         /* iterator */

	/* 정점명 가로방향 출력 */
	printf("   ");
	for(i=0; i<gm->vertexCnt; ++i)
		printf("%3c", 'A' + i);

	NEWL;  // 개행 매크로 

	for(i=0; i<gm->vertexCnt; ++i)
	{
		printf("%3c", 'A' + i);
		for(j=0; j<gm->vertexCnt; j++)
				printf("%3d", gm->graph[i][j]);
		NEWL;
	}
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: DFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색
                                   하기 위한 함수(재귀판)
  전달인자:  gm : 그래프 정보 구조체의 주소
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void DFS_Matrix(GraphMatrix *gm)
{
	int i;
	for(i=0; i<gm->vertexCnt; ++i)  /* 정점의 방문상태 정보를 저장할 check배열 초기화 */
		check[i] = 0;
	for(i=0; i<gm->vertexCnt; ++i)
		if(check[i] == 0) 
			DFS_recursive(gm, i);
	return;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: DFS_recursive() - 연결되어있는 하나의 그래프 내의 모든 정점을 
                                    재귀호출기법으로 방문하는 함수
  전달인자:  gm : 그래프 정보 구조체의 주소
             vNum : 방문하고자 하는 정점 번호
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void DFS_recursive(GraphMatrix *gm, int vNum)
{
	int i;
	check[vNum] = 1;  /* 방문한 정점 표시를 위해 1 저장 */
	visit(vNum);   /* 방문에 따른 처리 */
	for(i=0; i<gm->vertexCnt; ++i) 
	{
		if(gm->graph[vNum][i] != 0)  /* 연결된 정점이 있으면 */
			if(check[i] == 0)   /* 또한 방문한 적이 없는 정점이면 */
				DFS_recursive(gm, i); /* 재귀 호출을 통해 정점 방문을 한다 */
	}
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: visit() - 방문된 정점을 처리하는 함수(이 함수에서는 방문된 정점을 출력 함)
  전달인자: vNum : 방문하고자 하는 정점 번호
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void visit(int vNum)
{
	printf("%3c", 'A'+vNum);
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: nrDFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색
                                   하기 위한 함수(비 재귀판)
  전달인자:  gm : 그래프 정보 구조체의 주소
  리턴값: 없음    
--------------------------------------------------------------------------------------*/
void nrDFS_Matrix(GraphMatrix *gm)
{
	int i, j;
	int popData;  /* pop한 데이터 저장 */
	Stack stack;
	initStack(&stack);  /* 비재귀 처리를 위해 사용될 스택 초기화 */

	for(i=0; i<gm->vertexCnt; ++i)  /* 정점의 방문상태 정보를 저장할 check배열 초기화 */
		check[i] = 0;

	for(i=0; i<gm->vertexCnt; ++i)  /* 순차적으로 정점을 방문함 */
	{
		if(check[i] == 0)           /* 방문하지 않은 정점을 발견 하면 */
		{	
			push(&stack, i);
			check[i] = 1;     /* 방문상태를 1로 변경 */
			while( !isStackEmpty(&stack) )  /* 스택이 비면 한 연결 요소에 대한 순회가 끝난것을 의미함 */
			{
				pop(&stack, &popData);
				visit(popData);   /* 정점 방문 */
				
				for(j=0; j<gm->vertexCnt; ++j)
					if(gm->graph[popData][j] != 0)  /* (!!)pop한 정점과 연결된 j정점이 있고 */
						if(check[j] == 0)  /* j정점이 스택에 들어있지 않으면 */
						{
							push(&stack, j);  /* j정점을 스택에 저장하고 */
							check[j] = 1;     /* 방문상태를 1로 변경 */
						}
			}
		}
	}
	destroyStack(&stack);
	return;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: nrBFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 너비 우선 탐색
                                   하기 위한 함수(비 재귀판)
  전달인자:  gm : 그래프 정보 구조체의 주소
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void BFS_Matrix(GraphMatrix *gm)
{
	int i, j;
	int getData;  /* dequeue(get)한 데이터 저장 */
	Queue queue;
	initQueue(&queue, MAX_VERTEX);  /* 큐 초기화 */

	for(i=0; i<gm->vertexCnt; ++i)  /* 정점의 방문상태 정보를 저장할 check배열 초기화 */
		check[i] = 0;

	for(i=0; i<gm->vertexCnt; ++i)  /* 순차적으로 정점을 방문함 */
	{
		if(check[i] == 0)           /* 방문하지 않은 정점을 발견 하면 */
		{	
			enqueue(&queue, i);
			check[i] = 1;     /* 방문상태를 1로 변경 */
			while( !isQueueEmpty(&queue) )  /* 스택이 비면 한 연결 요소에 대한 순회가 끝난것을 의미함 */
			{
				dequeue(&queue, &getData);
				visit(getData);   /* 정점 방문 */
				
				for(j=0; j<gm->vertexCnt; ++j)
					if(gm->graph[getData][j] != 0)  /* (!!)pop한 정점과 연결된 j정점이 있고 */
						if(check[j] == 0)  /* j정점이 스택에 들어있지 않으면 */
						{
							enqueue(&queue, j);  /* j정점을 스택에 저장하고 */
							check[j] = 1;     /* 방문상태를 1로 변경 */
						}
			}
		}
	}
	destroyQueue(&queue);
	return;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: countGraphComponents() - 인접 행렬법으로 표기되 그래프 내의 연결 요소별로 
                                           정점들을 출력하고 연결 요소의 개수 리턴
  전달인자:  gm : 그래프 정보 구조체의 주소
  리턴값: 그래프내의 연결 요소의 개수
--------------------------------------------------------------------------------------*/
int countGraphComponents(GraphMatrix *gm)
{
	int componetsCount=0;  /* 그래프 내의 연결 요소 카운트 변수 */
	int i, j;
	int popData;  /* pop한 데이터 저장 */
	Stack stack;
	initStack(&stack);  /* 비재귀 처리를 위해 사용될 스택 초기화 */

	for(i=0; i<gm->vertexCnt; ++i)  /* 정점의 방문상태 정보를 저장할 check배열 초기화 */
		check[i] = 0;

	for(i=0; i<gm->vertexCnt; ++i)  /* 순차적으로 정점을 방문함 */
	{
		if(check[i] == 0)           /* 방문하지 않은 정점을 발견 하면 */
		{	
			++componetsCount;  /* 방문하지 않은 정점을 발견되면 연결 요소 카운트를 증가 시킴 */
			printf("\n연결 요소 %d : ", componetsCount);
			push(&stack, i);
			check[i] = 1;     /* 방문상태를 1로 변경 */
			while( !isStackEmpty(&stack) )  /* 스택이 비면 한 연결 요소에 대한 순회가 끝난것을 의미함 */
			{
				pop(&stack, &popData);
				visit(popData);   /* 정점 방문 */
				
				for(j=0; j<gm->vertexCnt; ++j)
					if(gm->graph[popData][j] != 0)  /* (!!)pop한 정점과 연결된 j정점이 있고 */
						if(check[j] == 0)  /* j정점이 스택에 들어있지 않으면 */
						{
							push(&stack, j);  /* j정점을 스택에 저장하고 */
							check[j] = 1;     /* 방문상태를 1로 변경 */
						}
			}
		}
	}
	destroyStack(&stack);
	return componetsCount;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: initGraph_L() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 '
                                 그래프를 인접 리스트법으로 초기화하는 함수
  전달인자:  g : 그래프 정보 구조체의 주소
             fileName : 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void initGraph_List(GraphList *g, char *fileName)
{
	char vertex[3];  /* 간선정보 입력을 위한 공간 "AB" 형태의 데이터 저장 char 배열 */
	int i,j,k;       /* iterator */
	FILE *fp;        /* 그래프 정보 저장 파일의 파일포인터 */

	fp=fopen(fileName, "rt");
	assert(fp!=NULL);
	fscanf(fp, "%d %d\n", &g->vertexCnt, &g->edgeCnt);  /* 정점과 간선의 개수를 읽기 */

	/* 정점의 개수에 맞춰 인접 리스트 영역 초기화 */
	for(i=0; i<g->vertexCnt; ++i)
		g->graph[i] = NULL;

	/* 무방향 그래프에서의 대칭성(Symmetry) 고려한 초기화 표기 */
	for(k=0; k<g->edgeCnt; ++k)
	{
		fscanf(fp, "%s\n",vertex);
		i=vertex[0]-'A';   /* 정점의 이름을 숫자화  'B'-'A' => 1의 형식으로 변환*/
		j=vertex[1]-'A';   /* 정점의 이름을 숫자화 */
		assert( addNode(g, i, j) != FALSE);
	}
	fclose(fp);
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: addNode() - 두 정점의 관계를 리스트에 등록함
  전달인자:  g - 그래프 정보 구조체의 주소
			 vNum1 - 첫번째 정점의 번호
			 vNum2 - 두번째 정점이 번호
  리턴값: 정점 등록이 성공하면 TRUE 리턴, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int addNode(GraphList *g, int vNum1, int vNum2)
{
	Node *newNode;
	newNode = (Node *) malloc(sizeof(Node));  /* 새 간선 정보 노드 생성 */
	if(newNode == NULL) return FALSE;
	newNode->next = g->graph[vNum1];   
	newNode->vertex = vNum2;
	g->graph[vNum1] = newNode;   /* 새로운 간선 정보 노드를 인접 리스트에 추가 */

	/* 무방향 그래프에서의 대칭성(Symmetry) 고려하여 역 방향에 간선도 추가로 초기화 */
	newNode = (Node *) malloc(sizeof(Node));  /* 새 간선 정보 노드 생성 */
	if(newNode == NULL) 
	{
		free(g->graph[vNum1]);
		return FALSE;
	}
	newNode->next = g->graph[vNum2];   
	newNode->vertex = vNum1;
	g->graph[vNum2] = newNode;   /* 새로운 간선 정보 노드를 인접 리스트에 추가 */
	return TRUE;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: outputGraph_L() - 그래프내의 정점과 간선의 관계를 인접 리스트 형태로 출력
  전달인자:  g : 그래프 정보 구조체의 주소
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void outputGraph_List(GraphList *g)
{
	int i;         /* iterator */
	Node *now;
	for(i=0; i<g->vertexCnt; ++i)
	{
		printf("%3c : ", 'A' + i);
		for(now = g->graph[i]; now != NULL; now = now->next)
			printf("%3c -> ", 'A' + now->vertex);
		printf("\b\b\b    ");
		NEWL;
	}
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: destroyGraph_L() - 그래프내의 정점 노드 모두 삭제
  전달인자:  g : 그래프 정보 구조체의 주소
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void destroyGraph_List(GraphList *g)
{
	int i;         /* iterator */
	Node *now, *next;
	for(i=0; i<g->vertexCnt; ++i)
	{
		now = g->graph[i];
		while(now != NULL)
		{
			next = now->next;
			free(now);
			now=next;
		}	
	}
}