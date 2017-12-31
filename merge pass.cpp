#include <stdio.h>
#include<stdlib.h>

#define ElementType int
#define MAXN 100

void merge_pass(ElementType list[], ElementType sorted[], int N, int length);

void output(ElementType list[], int N)
{
	int i;
	for (i = 0; i<N; i++) printf("%d ", list[i]);
	printf("\n");
}

void  merge_sort(ElementType list[], int N)
{
	ElementType extra[MAXN];  /* the extra space required */
	int  length = 1;  /* current length of sublist being merged */
	while (length < N) {
		merge_pass(list, extra, N, length); /* merge list into extra */
		output(extra, N);
		length *= 2;
		merge_pass(extra, list, N, length); /* merge extra back to list */
		output(list, N);
		length *= 2;
	}
}


int main()
{
	int N, i;
	ElementType A[MAXN];

	scanf("%d", &N);
	for (i = 0; i<N; i++) scanf("%d", &A[i]);
	merge_sort(A, N);
	output(A, N);
	system("pause");
	return 0;
}
/*

10
8 7 9 2 3 5 1 6 4 0

*/
void merge_pass(ElementType list[], ElementType sorted[], int N, int length)
{
	
	int left = 0;
	int right = (left + length) > N ? N : (left + length);
	int top = 0;
	while (left < right)
	{
		int cl = left;
		int cr = right;
		while (left < cl + length&&left < N&&right < cr + length&&right < N)
		{
			
			if (list[left]<list[right])
			{
				sorted[top++] = list[left++];
			}
			else
			{
				sorted[top++] = list[right++];
			}
		}
		while (left < cl + length&&left < N)
			sorted[top++] = list[left++];
		while (right < cr + length&&right < N)
			sorted[top++] = list[right++];
		
		left = (cl + 2 * length) < N ? (cl + 2 * length) : N;
		right = (cr + 2 * length) < N ? (cr + 2 * length) : N;
	}
}