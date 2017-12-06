#pragma once
#pragma warning(disable:4996)
//#include "datatype.h"
#define MAX_VERTEX 100
#define NEWL printf("\n")

extern int check[];
/*----------------------------------------------
       GraphMatrix 처리 구조체 및 활용 함수
-----------------------------------------------*/
typedef struct 
{
	int graph[MAX_VERTEX][MAX_VERTEX]; /* 인접 행렬법 표기 배열 - 2차원 배열 */
	int vertexCnt;    /* 정점 개수 */
	int edgeCnt;      /* 간선 개수 */
}GraphMatrix;

void initGraph(GraphMatrix *gm, char *fileName); /*데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 그래프를 초기화하는 함수 */
void outputGraph(GraphMatrix *gm); /* 그래프내의 정점과 간선의 관계를 인접 행렬 형태로 출력 함 */
void DFS_Matrix(GraphMatrix *gm); /* 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색하기 위한 함수(재귀판) - DFS_recursive()함수를 호출하여 처리(이 함수 자체는 재귀하지 않음) */
void DFS_recursive(GraphMatrix *gm, int vNum); /* 연결되어있는 하나의 그래트내의 모든 정점을 재귀호출기법으로 방문하는 함수 */
void visit(int vNum);   /* 방문한 정점의 처리 */
void nrDFS_Matrix(GraphMatrix *gm); /* 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색하기 위한 함수(비 재귀판) */
void BFS_Matrix(GraphMatrix *gm); /* 여러 개의 연결 요소로 구성된 그래프를 너비 우선 탐색하기 위한 함수(비 재귀판) */
int countGraphComponents(GraphMatrix *gm); /* 인접 행렬법으로 표기되 그래프 내의 연결 요소별로 정점들을 출력하고 연결 요소의 개수를 리턴하는 함수 */

/*---------------------------------------------
        GraphList 처리 구조체 및 활용 함수
----------------------------------------------*/
typedef struct _node
{
	int vertex;
	struct _node *next;
}Node;

typedef struct 
{
	Node *graph[MAX_VERTEX];  /* 인접 리스트 표기 배열 - Node 포인터 배열 */
	int vertexCnt;    /* 정점 개수 */
	int edgeCnt;      /* 간선 개수 */
}GraphList;

void initGraph_List(GraphList *g, char *fileName); /* 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 그래프를 인접 리스트법으로 초기화하는 함수 */
void outputGraph_List(GraphList *g); /* 그래프내의 정점과 간선의 관계를 인접 리스트 형태로 출력 */
int addNode(GraphList *g, int vNum1, int vNum2); /* 두 정점의 관계를 리스트에 등록함 */
void destroyGraph_List(GraphList *g); /* 그래프내의 정점 노드 모두 삭제 */
