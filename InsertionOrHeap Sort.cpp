#include<stdio.h>
#include<stdlib.h>
#define MaxNum 100
int source[MaxNum];
int result[MaxNum];
int Insert[MaxNum];
int Heap[MaxNum];
int N;
void ini()
{
	scanf("%d", &N);
	for (int i = 0; i < MaxNum; i++)
	{
		source[i] = -1;
		Insert[i] = -1;
		Heap[i] = -1;
		result[i] = -1;
	}
	for (int i = 0; i < N; i++)
	{
		scanf("%d", source + i);
		Insert[i] = Heap[i] = source[i];
	}
	for (int i = 0; i < N; i++)
	{
		scanf("%d", result + i);
	}
	return;
}
int comp(int*a, int*b)
{
	for (int i=0; i < N; i++)
	{
		if (a[i] != b[i])return 0;
	}
	return 1;
}
void Insertion(int* a,int step)
{
	int j;
	int P = step;
	int tmp;

	tmp = a[P]; 
	for (j = P; j > 0 && a[j - 1] > tmp; j--)
		a[j] = a[j - 1];
	a[j] = tmp; 
	return;
}
void PercDown(int a[], int p, int n)
{
	int i, Child;

	int tmp = a[p];
	for (i = p; (i * 2 + 1) < n; i = Child) {
		Child = i * 2 + 1;
		if ((Child != n - 1) && (a[Child] < a[Child + 1]))
			Child++;
		if (tmp >= a[Child]) break;
			a[i] = a[Child];
	}
	a[i] = tmp;
}
void buildheap(int*a)
{
	for (int i = N/2-1; i >=0; i--)
	{
		PercDown(a, i, N);
	}
}
void HeapSort(int*a)
{
	for ( int i = N - 1; i > 0; i--) {
		int tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		PercDown(a, 0, i);
		if (comp(Heap, result))
		{
			printf("Heap Sort\n");
			int tmp = a[0];
			a[0] = a[i-1];
			a[i-1] = tmp;
			PercDown(a, 0, i-1);
			for (int i = 0; i < N - 1; i++)
			{
				printf("%d ", Heap[i]);
			}
			printf("%d\n", Heap[N - 1]);
			return;
		}
	}
}
int main()
{
	ini();
	for (int i = 1; i < N; i++)
	{
		Insertion(Insert, i);
		if (comp(Insert, result))
		{
			printf("Insertion Sort\n");
			Insertion(Insert, i + 1);
			for (int i = 0; i < N-1; i++)
			{
				printf("%d ", Insert[i]);
			}
			printf("%d\n", Insert[N - 1]);
			system("pause");
			return 0;
		}
	}
	
	buildheap(Heap);
	HeapSort(Heap);
	system("pause");
	return 0;
}