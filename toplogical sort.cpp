#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;
	PtrToAdjVNode Next;
};

typedef struct Vnode {
	PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;



bool TopSort(LGraph Graph, Vertex TopOrder[])
{
	//1.calculate Indegree
	int Indegree[MaxVertexNum];
	int i;
	for (i = 0; i < MaxVertexNum; i++)
	{
		Indegree[i] = 0;
	}

	PtrToAdjVNode ptr;//for moving

	for (i = 0; i < Graph->Nv; i++)
	{
		ptr = Graph->G[i].FirstEdge;
		while (ptr)
		{
			Indegree[ptr->AdjV]++;
			ptr = ptr->Next;
		}
	}
	//calculate done

	//2.topsort
	int Q[MaxVertexNum] = {};
	int front = 0;/*queue front,dequeue sequence*/
	int rear = 0;/*queue rear,enqueue sequence*/
	int  Counter = 0;

	for (i = 0; i < Graph->Nv; i++)
	{
		if (Indegree[i] == 0)
		{
			Q[rear++] = i;
		}
	}/*enqueue those indegree==0*/

	int TopNum[MaxVertexNum] = {};

	while (front != rear)/*not empty*/
	{
		TopNum[Q[front]] = Counter++; /* assign next */
		PtrToAdjVNode ptr;
		ptr = Graph->G[Q[front]].FirstEdge;
		while (ptr)
		{
			if (!--Indegree[ptr->AdjV])
			{
				Q[rear++] = ptr->AdjV;
			}
			ptr = ptr->Next;
		}
		front++;
	}
	if (Counter != Graph->Nv)
	{
		return false;
	}
	else
	{
		for (i = 0; i < Graph->Nv; i++)
		{
			TopOrder[TopNum[i]] = i;
		}
		return true;
	}
}