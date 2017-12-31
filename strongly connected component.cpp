#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 15  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
	Vertex Vert;
	PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
	int NumOfVertices;
	int NumOfEdges;
	PtrToVNode *Array;
};
PtrToVNode insert(PtrToVNode p, int x)
{
	p->Next = (PtrToVNode)malloc(sizeof(struct VNode));
	p = p->Next;
	p->Vert = x;
	p->Next = NULL;
	return p;
}
Graph ReadG()
{
	int i, j, m, n, x, y;
	scanf("%d%d", &m, &n);
	Graph p = (Graph)malloc(sizeof(struct GNode));
	PtrToVNode *rear = (PtrToVNode*)malloc(m * sizeof(struct VNode));
	p->Array = (PtrToVNode*)malloc(m * sizeof(struct VNode));
	p->NumOfVertices = m;
	p->NumOfEdges = n;
	for (i = 0; i<m; i++) {
		rear[i] = p->Array[i] = (PtrToVNode)malloc(sizeof(struct VNode));
		p->Array[i]->Next = NULL;
	}
	for (i = 0; i<n; i++) {
		scanf("%d%d", &x, &y);
		rear[x] = insert(rear[x], y);
	}
	for (i = 0; i<m; i++) {
		PtrToVNode tmp = p->Array[i];
		p->Array[i] = p->Array[i]->Next;
		tmp->Next = NULL;
		free(tmp);
	}
	return p;
}

void PrintV(Vertex V)
{
	printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void(*visit)(Vertex V));

int main()
{
	Graph G = ReadG();

	StronglyConnectedComponents(G, PrintV);
	return 0;
}


void DFS(Graph G, int* Low, int* Num, int* Stack, int* Instack, int* Visited, int v)
{
	static int top = -1;
	static int count = 1;
	PtrToVNode ptr = G->Array[v];
	Stack[++top] = v;
	Instack[v] = 1;
	Low[v] = Num[v] = count++;
	while (ptr != NULL)
	{
		if (Visited[ptr->Vert])
		{
			ptr = ptr->Next;
			continue;
		}
		if (Num[ptr->Vert] == 0)
		{
			int u = ptr->Vert;
			DFS(G, Low, Num, Stack, Instack, Visited, u);
			if (Low[u] < Low[v])
				Low[v] = Low[u];
		}
		else
		{
			if (Instack[ptr->Vert])
			{
				if (Num[ptr->Vert] < Low[v])
				{
					Low[v] = Num[ptr->Vert];
				}
			}
		}
		ptr = ptr->Next;
	}
	if (Num[v] == Low[v])
	{
		do {
			Instack[Stack[top]] = 0;
			Visited[Stack[top]] = 1;
			PrintV(Stack[top]);
			top--;
		} while (Stack[top + 1] != v);
		printf("\n");
		//printf("%d\n", Stack[top]);
		//Visited[Stack[top--]] = 1;
		for (int i = 0; i < G->NumOfVertices; i++)
		{
			if (!Num[i])
				DFS(G, Low, Num, Stack, Instack, Visited, i);
		}
	}
	
	return;
}
void StronglyConnectedComponents(Graph G, void(*visit)(Vertex V))
{
	int Low[MaxVertices] = {};
	int Num[MaxVertices] = {};
	int Instack[MaxVertices] = {};
	int Stack[MaxVertices] = {};
	int Visited[MaxVertices] = {};
	DFS(G, Low, Num, Stack, Instack, Visited, G->NumOfVertices - 1);
	system("pause");
}