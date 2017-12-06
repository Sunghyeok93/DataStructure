#include<stdio.h>
#include<assert.h>
#include "graph.h"

/*--------------------------------------------------------------------------------------
  함수명 및 기능: initGraph() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 '
                                그래프를 초기화하는 함수
  전달인자:  gm : 그래프 정보 구조체의 주소
             fileName : 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void initGraph(GraphMatrix *gm, char *fileName)
{
	char vertex[3];  /* 간선정보 입력을 위한 공간 "AB" 형태의 데이터 저장 char 배열 */
	int i,j,k;       /* iterator */
	FILE *fp;        /* 그래프 정보 저장 파일의 파일포인터 */
	int weight;      /* 가중치 저장 변수 */

	fp=fopen(fileName, "rt");
	assert(fp!=NULL);
	fscanf(fp, "%d %d\n", &gm->vertexCnt, &gm->edgeCnt);  /* 정점과 간선의 개수를 읽기 */

	/* 정점의 개수에 맞춰 인접 행렬 영역 초기화 */
	for(i=0; i<gm->vertexCnt; ++i)
		for(j=0; j<gm->vertexCnt; ++j)
				gm->graph[i][j] = WEIGHT_MAX;

	/* 무방향 그래프에서의 반사정(Reflexive) 표기 */
	for(i=0; i<gm->vertexCnt;++i)
		gm->graph[i][i] = 0;	
	
	/* 무방향 그래프에서의 대칭성(Symmetry) 고려한 초기화 표기 */
	for(k=0; k<gm->edgeCnt; ++k)
	{
		fscanf(fp, "%s %d\n",vertex, &weight);
		i=vertex[0]-'A';   /* 정점의 이름을 숫자화  'B'-'A' => 1의 형식으로 변환*/
		j=vertex[1]-'A';   /* 정점의 이름을 숫자화 */
		gm->graph[i][j] = gm->graph[j][i] = weight;
	}
	fclose(fp);
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: outputGraph() - 그래프내의 정점과 간선의 관계를 인접 행렬 형태로 출력 함
  전달인자:  gm : 그래프 정보 구조체의 주소
  리턴값: 없음
--------------------------------------------------------------------------------------*/
void outputGraph(GraphMatrix *gm)
{
	int i,j;         /* iterator */
	printf("   ");
	/* 정점명 가로방향 출력 */
	for(i=0; i<gm->vertexCnt; ++i)
		printf("%3c", 'A' + i);

	NEWL;

	for(i=0; i<gm->vertexCnt; ++i)
	{
		printf("%3c", 'A' + i);
		for(j=0; j<gm->vertexCnt; j++)
			if(gm->graph[i][j]==WEIGHT_MAX)
				printf("%3s", "∞");
			else
				printf("%3d", gm->graph[i][j]);
		NEWL;
	}
	NEWL;
	printf("    ∞ : %d값으로 계산됨\n\n", WEIGHT_MAX);
}
