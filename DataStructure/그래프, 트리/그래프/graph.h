#pragma once
#pragma warning(disable:4996)
#define MAX_VERTAX 100
#define NEWL printf("\n");

extern int check[];//����κ��̶� ÷�� ���� ����

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
	Node *graph[MAX_VERTAX]; // ���� ����Ʈ ǥ�� �迭 - node ������ �迭
	int vertexCnt;
	int edgeCnt;
}GraphList;

//������ ���Ͽ��� �׷����� ������ ���� ������ �Է¹޾� �׷����� �ʱ�ȭ �ϴ� �Լ�
void initGraph(GraphMatrix *gm, char *fileName);

//�׷������� ������ ������ ���踦 ���� ��� ���·� �����
void outputGraph(GraphMatrix *gm);

//�������� ���� ��ҷ� ������ �׷����� ���� �켱 Ž���ϱ� ���� �Լ�(���)
//DFS_recursive()�Լ��� ȣ���Ͽ� ó��(�� �Լ� ��ü�� ��� ����)
void DFS_Matrix(GraphMatrix *gm);

//����Ǿ� �ִ� �ϳ��� �׷������� ��� ������ ���ȣ�� ������� �湮�ϴ� �Լ�
void DFS_recursive(GraphMatrix *gm, int vNum);

//�湮�� ������ ó��
void visit(int vNum);

//�������� ���� ��ҷ� ������ �׷����� '���� �켱' Ž���ϱ� ���� �Լ�(�� �����)
void nrDFS_Matrix(GraphMatrix *gm);

//�������� ���� ��ҷ� ������ �׷����� '�ʺ� �켱' Ž���ϱ� ���� �Լ�(�� �����)
void BFS_Matrix(GraphMatrix *gm);

//���� ��Ĺ����� ǥ��� �׷��� ���� �����Һ��� �������� ����ϰ� ���� ����� ������ �����ϴ� �Լ�
int countGraphComponents(GraphMatrix *gm);

//������ ���Ͽ��� �׷����� ������ ���������� �Է¹޾� �׷����� ���� ����Ʈ������ �ʱ�ȭ �ϴ� �Լ�
void initGraph_List(GraphList *g, char *fileName);

//�׷��� ���� ������ ������ ���踦 ��������Ʈ ���·� ���
void outputGraph_List(GraphList *g);

//�� ������ ���踦 ����Ʈ�� �����
int addNode(GraphList *g, int vNum1, int vNum2);

//�׷��� ���� ���� ��� ��� ����
void destroyGraph_List(GraphList *g);