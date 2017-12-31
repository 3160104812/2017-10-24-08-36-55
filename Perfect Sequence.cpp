#include<stdio.h>
#include<stdlib.h>
#define maxN 1e5
#define maxp 1e9
int comp(const void*a, const void*b)
{
	return *(int*)a - *(int*)b;
}
int calc(int *array, int N, int p)
{
	int i = 0;
	int j = N - 1;
	while (array[i] * p < array[j]&&i<=j)
	{
		while (array[i + 1] == array[i])i++;
		while (array[j - 1] == array[j])j--;
		if ((array[i + 1] - array[i])*p >= array[j] - array[j - 1])
			i++;
		else
			j--;
	}
	return j - i + 1;
}
int main()
{
	int* array = (int*)malloc(sizeof(int)*maxN);
	int N;
	int p;
	scanf("%d%d", &N, &p);
	if (N > maxN || p > maxp)return 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", array + i);
	}
	qsort(array, N, sizeof(int), comp);
	printf("%d", calc(array, N, p));
	system("pause");
}