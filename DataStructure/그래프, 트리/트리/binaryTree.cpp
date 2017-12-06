#include<stdio.h>
#include <malloc.h>
#include <assert.h>
#include "binaryTree.h"

//트리 관리 구조체를 초기화하는 함수
//tr - Tree구조체의 주소
void initTree(Tree *tr)
{
	tr->root = NULL;
	tr->nodeCnt = 0;
}

//새노드를 만들어 새노드의 주소를 리턴하는 함수
//data - 새노드에 저장될 데이터, left - 새 노드의 left멤버 값, right - 새노드의 right 멤버값
//리턴 - 새노드의 주소, 메모리 할당 실패시 null pointer
Node * makeNode(DataType *data, Node* left, Node * right)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (node != NULL)
	{
		node->data = *data;
		node->left = left;
		node->right = right;
	}
	return node;
}

//노드를 삽입하는 함수
//tr - 트리 구조체의 주소, data - 새노드에 저장될 데이터 저장 공간의 주소
//compare - data영역 비교를 위한 보조함수의 시작주소
//리턴 - 새노드의 주소 / 메모리 할당 실패시 null pointer
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	tr->nodeCnt++;
	//data값의 새 노드가 추가될 위치를 찾은 후
	Node *parent, *son, *np;
	//tree내의 데이터 구조 유지하면서 추가할것(중복데이터는 없는것으로 간주)
	// : 왼쪽 자식노드의 값 < 부모 노드의 값 < 오른쪽 자식 노드의 값
	//makenode()함수를 이용하여 새노드를 생성한 후 tree에 추가
	np = makeNode(data, NULL, NULL);
	if (np == NULL)
	{
		return NULL;
	}
	if (tr->root != NULL)
	{
		son = tr->root;
		parent = tr->root;
		while (son != NULL)
		{
			parent = son;
			if (np->data > son->data)
			{
				son = son->right;
			}
			else
			{
				son = son->left;
			}
		}
		if (np->data > parent->data)
		{
			parent->right = np;
		}
		else
		{
			parent->left = np;
		}
	}
	else{
		tr->root = np;
	}
	return np;
}

//중위순회(정렬순서로 출력)
//np - 방문할 노드의 주소
//print - data영역을 출력하는 보조함수의 주소
void inorderTraverse(Node *np, void(*print)(DataType*))
{
	//왼쪽 subtree 방문
	//해당 노드 방문
	//오른쪽 subtree방문
	//재귀함수호출법
	if (np == NULL)
	{
		return;
	}
	
	inorderTraverse(np->left, print);
	print(&np->data);
	inorderTraverse(np->right, print);
}

//전위순회
void preorderTraverse(Node *np, void(*print)(DataType*))
{
	//해당노드방문
	//왼쪽 subtree방문
	//오른쪽 subtree방문
	//재귀
	if (np == NULL)
	{
		return;
	}

	
	print(&np->data); 
	preorderTraverse(np->left, print);
	preorderTraverse(np->right, print);
}

//후위순회
void postorderTraverse(Node *np, void(*print)(DataType*))
{
	
	//왼쪽 subtree방문
	//오른쪽 subtree방문
	//해당노드방문
	//재귀
	if (np == NULL)
	{
		return;
	}

	postorderTraverse(np->left, print);
	postorderTraverse(np->right, print);
	print(&np->data);
}


//data에 해당하는 노드검색 / 찾은 노드의 주소 리턴, 못찾으면 NULL 리턴
Node * searchNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node * np;
	np = tr->root;
	if (tr->root == NULL) return NULL;
	int tmp;
	while (np != NULL)
	{
		tmp = compare(&np->data, data);
		if (tmp == 1)
		{
			np = np->left;
		}
		else if (tmp == -1)
		{
			np = np->right;
		}
		else if (tmp == 0)
		{
			return np;
		}
	}
	return NULL;
	

}

//data에 해당하는 노드 삭제 / 삭제한 노드의 parent의 주소 리턴
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node * parent, *child, *del;
	Node * temp;
	parent = tr->root;
	child = tr->root;
	while (child->data != *data)
	{
		parent = child;
		if (compare(&child->data, data) > 0)
			child = child->left;
		else if (compare(&child->data, data) < 0)
			child = child->right;

		if (child == NULL)
			return NULL;
	}

	del = child; // 삭제할 노드를 del에 저장

	if (del->right == NULL) // 유형 1 삭제할 노드의 오른쪽 자식이 없는 경우
	{
		child = del->left; //삭제할 노드의 왼쪽 자식이 child 역할
		if (parent->data > child->data) //del과의 관계를 끊고 child와 연결
			parent->left = child;
		else
			parent->right = child;
		tr->nodeCnt--;
		return del;
	}
	else if (del->right->left == NULL)// 유형 2 삭제할 노드의 오른쪽 자식의 왼쪽자식이 없는 경우
	{
		child = del->right; // 삭제할 노드의 오른쪽 자식이 child 역할
		if (child->left == NULL)
		{
			child->left = del->left; // 삭제할 노드의 왼쪽자식을 삭제할 노드의 왼쪽자식에 넣음으로써 트리 유지
			if (parent->data > child->data)
				parent->left = child;
			else
				parent->right = child;
			tr->nodeCnt--;
			return del;
		}
	}
	else // 유형 3
	{
		temp = del->right;
		child = temp->left;
		while (child->left != NULL) // 왼쪽 끝 노드까지 찾아감
		{
			temp = child;
			child = child->left;
		}

		if (child->right != NULL) // 오른쪽 노드가 널이아니면 temp왼쪽에 오른쪽 노드를 붙인다
			temp->left = child;
		else // 오른쪽 노드가 널이면 temp 왼쪽은 이제 널
			temp->left = NULL;

		if (*data != tr->root->data) // 데이터 삭제가 루트데이터가 아닐때
		{
			if (parent->data > child->data)
				parent->left = child;
			else
				parent->right = child;

		}
		else // 데이터 삭제가 루트데이터일때
		{
			tr->root = child; // child를 루트에 넣고 가지를 쳐줘야함
			child->left = del->left;
			child->right = del->right;
		}

		tr->nodeCnt--;
		return del;

	}
}

//tree내의 모든 노드 삭제(tree소멸)
void destroyTree(Tree *tr, void(*print)(DataType *))
{
	postorderDelete(tr->root, print);
	tr->nodeCnt = 0;
	printf("\n");
}

//postorder(후위 순회)방식의 노드 삭제 재귀호출 함수
void postorderDelete(Node *np, void(*print)(DataType *))
{
	if (np == NULL)
		return;

	postorderDelete(np->left, print);
	postorderDelete(np->right, print);
	print(&np->data);
	free(np);
}