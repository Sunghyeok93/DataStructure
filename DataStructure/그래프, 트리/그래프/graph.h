#pragma once
#pragma warning(disable:4996)
#define MAX_VERTAX 100
#define NEWL printf("\n");

extern int check[];//선언부분이라 첨자 생략 가능

typedef struct
{
	int graph[MAX_VERTAX][MAX_VERTAX];
	int vertexCnt;
	int edgeCnt;
}GraphMatrix;

typedef struct _node
{
	int vertex;
	struct _node *next;
}Node;

typedef struct
{
	Node *graph[MAX_VERTAX]; // 인접 리스트 표기 배열 - node 포인터 배열
	int vertexCnt;
	int edgeCnt;
}GraphList;

//데이터 파일에서 그래프의 정점과 간선 정보를 입력받아 그래프를 초기화 하는 함수
void initGraph(GraphMatrix *gm, char *fileName);

//그래프내의 정점과 간선의 관계를 인접 행렬 형태로 출력함
void outputGraph(GraphMatrix *gm);

//여러개의 연결 요소로 구성된 그래프를 깊이 우선 탐색하기 위한 함수(재귀)
//DFS_recursive()함수를 호출하여 처리(이 함수 자체는 재귀 안함)
void DFS_Matrix(GraphMatrix *gm);

//연결되어 있는 하나의 그래프내의 모든 정점을 재귀호출 기법으로 방문하는 함수
void DFS_recursive(GraphMatrix *gm, int vNum);

//방문한 정점의 처리
void visit(int vNum);

//여러개의 연결 요소로 구성된 그래프를 '깊이 우선' 탐색하기 위한 함수(비 재귀판)
void nrDFS_Matrix(GraphMatrix *gm);

//여러개의 연결 요소로 구성된 그래프를 '너비 우선' 탐색하기 위한 함수(비 재귀판)
void BFS_Matrix(GraphMatrix *gm);

//인접 행렬법으로 표기되 그래프 내의 연결요소별로 정점들을 출력하고 연결 요소의 개수를 리턴하는 함수
int countGraphComponents(GraphMatrix *gm);

//데이터 파일에서 그래프의 정점과 간선정보를 입력받아 그래프를 인접 리스트법으로 초기화 하는 함수
void initGraph_List(GraphList *g, char *fileName);

//그래프 내의 정점과 간선의 관계를 인접리스트 형태로 출력
void outputGraph_List(GraphList *g);

//두 정점의 관계를 리스트에 등록함
int addNode(GraphList *g, int vNum1, int vNum2);

//그래프 내의 정점 노드 모두 삭제
void destroyGraph_List(GraphList *g);