#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
// 1.build tree with struct array
// 2.sort input numbers
// 3.inorder traversal and push numbers
// 4.levelorder output
typedef struct TreeNode *Tree;
struct TreeNode {
    int   key;
    Tree  Left;
    Tree  Right;
};
void Sort(int* input,int N)
{
	if(N>1){
        int i=0,j;
        for(j=1;j<N;j++)
            if(input[j]<input[0])
            {
            	int temp = 0;
            	temp=input[j];
            	input[j]=input[++i];
            	input[i]=temp;
			}
        int tmp = 0;
            	tmp=input[0];
            	input[0]=input[i];
            	input[i]=tmp;
        Sort(input,i);
        Sort(input+i+1,N-i-1);
    }
	
     
     
     return;
}
//inorder
void In (Tree T,int* inorder_push)
{
  static int i =0;
  if(T)
  {
    In(T->Left, inorder_push);
    T->key = inorder_push[i++];
    In(T->Right, inorder_push);
  }
}
void Level_order(Tree T,int MaxTree)
{
  Tree queue[MaxTree];
  int front = -1;
  int rear = 0;
  int i=0;
  if (!T)
    return;
  queue[rear] = T;
  while (front != rear)
  {
    front++;
    printf("%d",queue[front]->key);
    if(i<MaxTree-1)
    {
      printf(" ");
      i++;
    }
    if (queue[front]->Left)
    {
      rear++;
      queue[rear] = queue[front]->Left;
    }
    if (queue[front]->Right)
    {
      rear++;
      queue[rear] = queue[front]->Right;
    }
  }
}
int main()
{
  int N;
  scanf("%d",&N);
  if(N>MAXSIZE)return 0;
  //buildtree
  int left_index;
  int right_index;
  struct TreeNode T[N];
  int i=0;
  for(i=0;i<N;i++)
  {
    scanf("%d %d",&left_index,&right_index);
    if(left_index!=-1)T[i].Left=&T[left_index];
    else T[i].Left=NULL;
    if(right_index!=-1)T[i].Right=&T[right_index];
    else T[i].Right=NULL;
  }
  //input
  int input[N];
  for(i=0;i<N;i++)
  {
    scanf("%d",&input[i]);
  }
  
  Sort(input,N);
    
  //inorder traversal
  In(T,input);
  //levelorder
  Level_order(T, N);
  return 0;
}

/*

9
1 6
2 3
-1 -1
-1 4
5 -1
-1 -1
7 -1
-1 8
-1 -1
73 45 11 58 82 25 67 38 42

*/
