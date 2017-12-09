#include <stdio.h>
#include <stdlib.h>

//typedef enum { false, true } bool;
#define INFINITY 1000000
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph ReadG(); /* details omitted */

void ShortestDist(MGraph Graph, int dist[], int count[], Vertex S);
void AddCount(MGraph Graph, int dist[], int count[], Vertex S);

int main()
{
	int dist[MaxVertexNum], count[MaxVertexNum];
	Vertex S, V;
	MGraph G = (MGraph)malloc(sizeof(struct GNode));

	int a, b, c;
	scanf("%d %d", &a, &b);
	G->Ne = b;
	G->Nv = a;
	for (a = 0; a < G->Nv; a++)
	{
		for (b = 0; b < G->Nv; b++)
		{
			G->G[a][b] = 0;
		}
	}
	for (V = 0; V < G->Ne; V++)
	{
		scanf("%d %d %d", &a, &b, &c);
		G->G[a][b] = c;
	}

	scanf("%d", &S);
	ShortestDist(G, dist, count, S);

	for (V = 0; V<G->Nv; V++)
		printf("%d ", dist[V]);
	printf("\n");
	for (V = 0; V<G->Nv; V++)
		printf("%d ", count[V]);
	printf("\n");

	/*for (a = 0; a < G->Nv; a++)
	{
	for (b = 0; b < G->Nv; b++)
	{
	if (G->G[a][b] > 0)
	printf("%d\t", G->G[a][b]);
	else
	printf(" \t");
	}
	printf("\n");
	}*/
	system("pause");

	return 0;
}
void AddCount(MGraph Graph, int dist[], int count[], Vertex S)
{
	static int Added[MaxVertexNum][MaxVertexNum] = {};
	static int Q[MaxVertexNum] = {};
	static int Front = 0;
	static int Rear = 0;
	if (Front > Rear)return;
	if (Rear > MaxVertexNum)return;
	if (!Rear)	Q[Rear++] = S;

	int j;
	for (j = 0; j < Graph->Nv; j++)
	{
		if (Graph->G[S][j] > 0 && Graph->G[S][j]<INFINITY)
		{
			if (dist[j] == dist[S] + Graph->G[S][j])
			{
				if (!Added[S][j])
				{
					count[j] += count[S];
					//printf("add %d from %d to %d\n", count[S], S, j);
					Q[Rear++] = j;
					Added[S][j] = 1;

				}
			}
		}
	}
	AddCount(Graph, dist, count, Q[++Front]);
}
void ShortestDist(MGraph Graph, int dist[], int path[], Vertex S)
{
	int count[MaxVertexNum] = {};
	if (Graph->Nv > MaxVertexNum)return;
	Vertex  Q[MaxVertexNum];
	int Known[MaxVertexNum];
	int i;
	int j;
	int k;
	for (i = 0; i < Graph->Nv; i++)
	{
		Q[i] = INFINITY;
		dist[i] = -1;
		count[i] = 0;
		Known[i] = 0;
		path[i] = -1;
	}
	int Front = 0;
	int Rear = 0;
	Q[Rear++] = S;
	dist[S] = 0;
	count[S] = 1;
	Known[S] = 1;

	for (i = 0; i < Graph->Nv; i++)
	{
		for (j = 0; j < Graph->Nv; j++)
		{
			if (Graph->G[j][i] && Graph->G[j][i]<INFINITY)break;
		}
		if (j == Graph->Nv&&i != S)
		{
			for (k = 0; k < Graph->Nv; k++)Graph->G[i][k] = 0;
		}
	}
	//不成功的尝试
	/*for (i = 0; i < Graph->Nv; i++)
	{
		printf("%d\t", Q[i]);
	}
	printf("\n");

	while (Front != Rear)
	{
		for (i = 0; i < MaxVertexNum; i++)
		{
			if (Graph->G[Q[Front]][i] > 0 && Graph->G[Q[Front]][i] < INFINITY)
			{
				if (Known[i])continue;
				if (dist[Q[Front]] + Graph->G[Q[Front]][i] < dist[i])
				{
					dist[i] = Graph->G[Q[Front]][i] + dist[Q[Front]];
					count[i] = count[Q[Front]];
				}
				else if (dist[Q[Front]] + Graph->G[Q[Front]][i] == dist[i])
				{
					count[i] += count[Q[Front]];
				}
				for (j = 0; j<Rear; j++)
				{
					if (Q[j] == i)
					{
						break;
					}
					else
					{
						Q[Rear++] = i;
						Known[i] = 1;
					}
				}
			}
		}
		Front++;
	}*/
	//实现一次dijkstra算法
	int flag = 0;
	while (1)
	{
		if (flag)
		{
			for (i = 0; i < Graph->Nv; i++)
			{
				if (!Known[i])break;//get smallest unknown
			}
			if (i == Graph->Nv)break;//not a vertex
		}
		else
		{
			i = S;
			flag = 1;
		}

		Known[i] = 1;
		for (j = 0; j < Graph->Nv; j++)
		{
			if (Graph->G[i][j] > 0 && Graph->G[i][j]<INFINITY)//each adjsentvertex
			{
				//if (!Known[j])
				{
					if (dist[j] > dist[i] + Graph->G[i][j] || dist[j]<0)
					{
						dist[j] = dist[i] + Graph->G[i][j];
					}
				}

			}
		}
	}
	AddCount(Graph, dist, count, S);
	for (i = 0; i < Graph->Nv; i++)
	{
		for (j = 0; j < Graph->Nv; j++)
		{
			if (Graph->G[i][j] > 0 && Graph->G[i][j] < INFINITY)
			{
				if ((path[j]>=0&& count[i] < count[path[j]]) || path[j] < 0)path[j] = i;
			}
		}
	}
	return;
}

/*
void ShortestDist(MGraph Graph, int dist[], int path[], Vertex S)
{
	int Known[MaxVertexNum];
	int count[MaxVertexNum];
	int i;

	for (i = 0; i < Graph->Nv; i++) {
		dist[i] = Graph->G[S][i];
		if (dist[i] != INFINITY)
		{
			count[i] = 1;
		}
		else count[i] = 0;
		Known[i] = 0;
		path[i] = S;
	}
	Known[S] = 1;
	dist[S] = 0;
	count[S] = 1;
	path[S] = -1;
	while (1) {
		int MinDist = INFINITY;
		int v = -1;
		for (i = 0; i < Graph->Nv; i++)
		{
			if (!Known[i] && dist[i] < MinDist)
			{
				MinDist = dist[i];
				v = i;
			}
		}
		if (v == -1)break;
		Known[v] = 1;
		for (i = 0; i < Graph->Nv; i++)
		{
			if (!Known[i] && dist[v] + Graph->G[v][i] < dist[i])
			{
				dist[i] = dist[v] + Graph->G[v][i];
				count[i] = count[v];
				path[i] = v;
			}
			else if (dist[v] + Graph->G[v][i] == dist[i])
			{
				count[i] += count[v];
				if(count[v]<count[path[i]])path[i] = v;
			}
		}
	}
	for (i = 0; i < Graph->Nv; i++)
	{
		if (dist[i] == INFINITY)
		{
			dist[i] = -1;
			path[i] = -1;
		}
	}
	return;
}
*/