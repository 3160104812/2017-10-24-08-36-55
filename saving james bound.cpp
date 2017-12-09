#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MaxVertexNum 100
struct Coordinate
{
	int x;
	int y;
}Vertex[MaxVertexNum + 1];//CurrentPositionom 1~101

int VertexNum;
int JumpRange;

int Visited[MaxVertexNum + 1] = {};
int Path[MaxVertexNum + 1] = { -1 };

int DirectlyToBank(int a)
{
	if (Vertex[a].x >= 50 - JumpRange || Vertex[a].y >= 50 - JumpRange || Vertex[a].x <= -50 + JumpRange || Vertex[a].y <= -50 + JumpRange)return 1;
	else return 0;
}
int InRange(int a, int b)
{
	if (pow(Vertex[a].x - Vertex[b].x, 2) + pow(Vertex[a].y - Vertex[b].y, 2) <= pow(JumpRange, 2))return 1;
	return 0;
}
int FirstJump(int a)
{
	if (pow(Vertex[a].x, 2) + pow(Vertex[a].y, 2) <= pow(JumpRange + 7.5, 2))return pow(Vertex[a].x, 2) + pow(Vertex[a].y, 2);
	return 0;
}

void Jump()
{
	int step = 2;
	int firststep[MaxVertexNum + 1];
	int queue[MaxVertexNum + 1] = { -1 };
	int Front = 0;
	int Rear = 0;
	int stack[MaxVertexNum + 1];
	int Top = 0;
	int i;
	int MinFS = 10E8;
	for (i = 0; i < VertexNum; i++)
	{
		firststep[i] = FirstJump(i);
	}
	int Last;
	int min = 0;
	while (1)
	{
		for (i = 0; i < VertexNum; i++)
		{
			if (MinFS > firststep[i] && !Visited[i] && firststep[i])
			{
				MinFS = firststep[i];
				min = i;
			}
		}
		if (MinFS == 10E8)break;
		Visited[min] = 1;
		MinFS = 10E8;
		queue[Rear] = min;
		Last = Rear++;
	}
	for (int i = 0; i < MaxVertexNum; i++)
	{
		Visited[i] = 0;
	}
	int Tail = 0;
	while (Front != Rear)
	{
		int CurrentPosition = queue[Front++];
		if (DirectlyToBank(CurrentPosition))
		{
			printf("%d\n", step + 1);
			for (int i = 0; i < step; i++)
			{
				stack[Top++] = CurrentPosition;
				CurrentPosition = Path[CurrentPosition];
			}
			for (int i = Top - 1; i >= 0; i--)
			{
				printf("%d %d\n", Vertex[stack[i]].x, Vertex[stack[i]].y);
			}
			Top = 0;
			return;
		}
		for (int i = 0; i < VertexNum; i++)
		{
			if (!Visited[i] && InRange(CurrentPosition, i))
			{
				queue[Rear++] = i;
				Path[i] = CurrentPosition;
				Visited[i] = 1;
				Tail = i;
			}
		}
		if (Last == CurrentPosition)
		{
			step++;
			Last = Tail;
		}
	}
	printf("0\n");
	return;
}

int main()
{
	scanf("%d %d", &VertexNum, &JumpRange);
	for (int i = 1; i < VertexNum; i++)
	{
		scanf("%d %d", &Vertex[i].x, &Vertex[i].y);
	}
	if (JumpRange > 42.5)
	{
		printf("1\n");
		return 0;
	}
	Jump();
	system("pause");
	return 0;
}