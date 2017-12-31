#include<stdio.h>
#include<stdlib.h>

#define Max 1e5
int* array;
int count = 0;


void swap(int x,int y)
{
	int tmp = array[x];
	array[x] = array[y];
	array[y] = tmp;
	count++;
	return;
}
void swapsort(int*a,int num)
{
	int z_pos;//locate 0
	int s_pos;
	while (1)
	{
		for (int i = 0; i < num; i++)
		{
			if (!a[i])
			{
				z_pos = i;
				break;
			}
		}//find 0
		if (!z_pos)//0 at a[0]
		{
			int flag=0;
			for (int i = num - 1; i > 0; i--)
			{
				if (a[i] != i)
				{
					s_pos = i;
					flag = 1;
					break;
				}
			}
			if (!flag)return;
			else swap(z_pos, s_pos);
		}
		else
		{
			for (int i = 0; i < num; i++)
			{
				if (a[i]==z_pos)
				{
					s_pos = i;
					break;
				}
			}//find s_pos
			swap(z_pos, s_pos);
		}
	}
}
int main()
{
	int num;
	scanf("%d", &num);
	if (num > Max)
		return 0;
	array = (int *)malloc(sizeof(int)*num);
	for (int i = 0; i < num; i++)
		scanf("%d", array + i);
	swapsort(array,num);
	printf("%d\n", count);
	system("pause");
	return 0;
}