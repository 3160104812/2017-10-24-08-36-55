#include<stdio.h>
#include<stdlib.h>
//typedef int Vertex;
typedef int DistType;
#define NotAVertex -1
#define MaxVertexNum 100
#define Infinity 10000

typedef struct TableEntry{
	int			Known;
	DistType	Dist;
	int			Path;
}Table[MaxVertexNum];
Table T;
void InitializeTable()
{
	int i;
	for (i = 0; i < MaxVertexNum; i++)
	{
		T[i].Known = T[i].Path = 0;
		T[i].Dist = 0;
	}
	T[0].Known = 1;
	T[0].Path = -1;
	T[0].Dist = 0;
	return;
}


int AdjacentMatrix[MaxVertexNum][MaxVertexNum] = {};
int Indegree[MaxVertexNum];

int TopNum[MaxVertexNum] = {};
int TopOrder[MaxVertexNum] = {};

void InitializeMatrix()
{
	int i, j;
	for ( i = 0; i < MaxVertexNum; i++)
	{
		for ( j = 0; j < MaxVertexNum; j++)
		{
			/*if (i != j)*/AdjacentMatrix[i][j] = Infinity;
		}
	}
	return;
}
void InputEdge(int EdgeNum)
{
	int i;
	int From;
	int To;
	int Weight;
	for ( i = 0; i < EdgeNum; i++)
	{
		scanf("%d %d %d", &From, &To, &Weight);
		//if (!Weight)continue;
		AdjacentMatrix[From][To] = Weight;
		Indegree[To]++;
	}
}
int TopSort(int VertexNum)
{
	int Q[MaxVertexNum] = {};
	int front = 0;
	int rear = 0;
	int Counter = 0;
	int i, j;
	for (i = 0; i < VertexNum; i++)
	{
		if (Indegree[i] == 0)
		{
			Q[rear++] = i;
		}
	}
	while (front != rear)
	{
		TopNum[Q[front]] = Counter++;
		for (i = 0; i < VertexNum; i++)
		{
			if (/*AdjacentMatrix[Q[front]][i] > 0&& */AdjacentMatrix[Q[front]][i] != Infinity)
			{
				if (!--Indegree[i])
				{
					Q[rear++] = i;
				}
			}
		}
		front++;
	}
	if (Counter != VertexNum)
	{
		printf("Impossible\n");
		return 0;
	}
	else
	{
		for (i = 0; i < VertexNum; i++)
		{
			TopOrder[TopNum[i]] = i;
		}
		return 1;
	}
}
int CriticalPath(int VertexNum)
{
	int i, j;
	for (i = 0; i < VertexNum; i++)
	{
		for (j = 0; j < VertexNum; j++)
		{
			if (/*AdjacentMatrix[TopOrder[i]][j] &&*/ AdjacentMatrix[TopOrder[i]][j] != Infinity)
			{
				T[j].Dist = T[j].Dist > (T[TopOrder[i]].Dist + AdjacentMatrix[TopOrder[i]][j] )? T[j].Dist : (T[TopOrder[i]].Dist + AdjacentMatrix[TopOrder[i]][j]);
			}
		}
	}
	/*for (i = 0; i < VertexNum; i++)
	{
		printf("dist[%d]=%d\n", i, T[i].Dist);
	}*/
	return(T[TopOrder[VertexNum-1]].Dist);
}
int main()
{
	InitializeMatrix();
	InitializeTable();
	int Vertexs;
	int Edges;
	scanf("%d %d", &Vertexs, &Edges);
	InputEdge(Edges);
	int i, j;
	for (i = 0; i < Vertexs; i++)
	{
		for (j = 0; j < Vertexs; j++)
		{
			if (AdjacentMatrix[i][j] != Infinity)printf("%d ", AdjacentMatrix[i][j]);
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	if(TopSort(Vertexs))printf("%d", CriticalPath(Vertexs));
	system("pause");
	return 0;

}