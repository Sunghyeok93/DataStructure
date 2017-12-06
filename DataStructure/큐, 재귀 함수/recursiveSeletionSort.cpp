#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void iteratorSelectionSort(int *ary, int n);
void recursiveSelectionSort(int *ary, int n);
void initArray(int *ary, int n);
void printArray(int *ary, int n);
void swap(int *data, int a, int b);

int main(void)
{
	int numberArray[10], arySize;
	arySize = sizeof(numberArray) / sizeof(numberArray[0]);
	srand((unsigned int)time(NULL));

	initArray(numberArray, arySize);
	iteratorSelectionSort(numberArray, arySize);
	printArray(numberArray, arySize);

	initArray(numberArray, arySize);
	recursiveSelectionSort(numberArray, arySize);
	printArray(numberArray, arySize);

	return 0;
}
void iteratorSelectionSort(int *ary, int n)
{
	int target;
	for (int i = 0; i < n - 1; i++)
	{
		target = i;
		for (int j = i + 1; j < n; j++)
		{
			if (ary[target] > ary[j])
			{
				target = j;
			}
		}
		swap(ary, i, target);
	}
}
void recursiveSelectionSort(int *ary, int n)
{
	if (n == 1) return;
	int largest = 0;
	for (int i = 1; i < n; i++)
	{
		if (ary[largest] < ary[i])
		{
			largest = i;
		}
	}
	int t = ary[largest];
	ary[largest] = ary[n - 1];
	ary[n - 1] = t;
	recursiveSelectionSort(ary, n - 1);
}

void initArray(int *ary, int n)
{
	for (int i = 0; i < n; i++)
	{
		ary[i] = rand() % 20 + 1;
	}
}
void printArray(int *ary, int n)
{
	printf("배열 내용 : ");
	for (int i = 0; i < n; i++)
	{
		printf("%4d", ary[i]);
	}
	printf("\n");
}
void swap(int *data, int a, int b)
{
	int t = data[a];
	data[a] = data[b];
	data[b] = t;
}