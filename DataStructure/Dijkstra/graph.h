#pragma once

#define MAX_VERTEX 100
#define WEIGHT_MAX 1000 /* 실제 사용되는 가중치보다 월등히 높게 책정, INT_MAX는 사용하면 안 됨*/
#define NEWL printf("\n")

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

