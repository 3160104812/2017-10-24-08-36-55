#include<stdio.h>
#include<stdlib.h>
#define Max 1e5
int count = 0;
void swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
	return;
}
int search(int* a, int num)
{
	static int first = 1;
	for (int i = first; i<num; i++)
		if (a[i] != i)
			return first = i;
	return 0;
}
void calc(int *a,int num)
{
	while (true)
	{
		if (a[0])
			swap(a, a+a[0]);
		else
		{
			int temp;
			temp = search(a, num);
			if (!temp) break;
			swap(a, a+temp);
		}
		count++;
	}
	return;
}
int main()
{
	int num;
	int data;
	scanf("%d", &num);
	if (num > Max)
		return 0;
	int* array = (int *)malloc(sizeof(int)*num);
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &data);
		array[data] = i;
	}
	calc(array, num);
	printf("%d\n", count);
	system("pause");
	return 0;
}