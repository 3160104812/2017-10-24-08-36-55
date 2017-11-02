#include <stdio.h>
#include <stdlib.h>
#define RED           0    // red node  ;key<0
#define BLACK         1    // black node ;key>0
#define ElementType   int
#define MAXSIZE 30 //maxsize
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType  Element;
    int color;
    Tree  Left;
    Tree  Right;
    Tree  Parent;
};
void insert(Tree* T,int key,int color)
{
  Tree temp = (Tree)malloc(sizeof(struct TreeNode));
  temp->color=color;
  temp->Element=key;
  temp->Right=temp->Left=NULL;
  Tree ptr;//moving pointer
  Tree ptr_p;//following ptr,save its parent address
  ptr=*T;//ptr is pointing at root node
  if(!ptr)
  {
      temp->Parent=NULL;
      *T=temp;
      return;//when the tree is initially empty
  }
  while(ptr)
  {
      ptr_p=ptr;
      if(key>ptr->Element)
      {
          ptr=ptr->Right;
      }
      else
      {
          ptr=ptr->Left;
      }
  }//move to the deepest level to find a reasonable position
  temp->Parent=ptr_p;//tail it here
  if(key>ptr_p->Element)
  {
      ptr_p->Right=temp;//assign the parent pointer
  }
  else
  {
      ptr_p->Left=temp;
  }
  return;
}
void buildtree(Tree* T,int* key,int*color,int max)
{
  int i=0;
  while(i<max)
  {
	  insert(T,key[i],color[i]);
      i++;
  } return; 
}
int check(Tree T)
{
  
  // (1) Every node is either red or black.
  //needless to check
  // (2) The root is black.
  if(!T)//begin at the root,an empty tree is rbtree
  {
    return 1;
  }//NULL is rbtree
  if(T->color != BLACK)
  {
    return 0;
  }//check whether the root is black

  // (4) If a node is red, then both its children are black.
  // (5) For each node, all simple paths from the node to descendant leaves 
  //     contain the same number of black nodes.
  
  /*
  	dudes:
  	can you please show that these two expression is equal to each other:
  	
  	1.For each node, all simple paths from the node to descendant leaves 
       contain the same number of black nodes.
       
  	2.From the root node,the paths to each leaf(NULL) contain the same 
	  number of black nodes.
	  
	I used 2nd line and passed PTA test while the given statement is in
	1st form. 
  	
  */
  int blackCount = 1;
  //this value is used to later measure the number of passing-by black nodes
  Tree ptr = T;
  while(ptr->Left)
  {
    if(ptr->Left->color == BLACK)
    {
      blackCount++;
    }
    ptr = ptr->Left;
  }//go down an arbitrary path from root to leaf(here is the last one before NULL but doesn't matter)
  //and count the BLACK quantity

  return furthercheck(T,blackCount,0);//enter further check for (4)&(5)
}

int furthercheck(Tree T,int blackCount,int blacknum)
{
  if(!T)//begin at the root,an empty tree is rbtree((3)NULL is BLACK)
  {
    return (blacknum==blackCount);
	//check leaves along the path
	//actually it is ( blacknum+1(comming from leaf itself) ==blackCount + 1)
  }
  // (4) If a node is red, then both its children are black.
  
  if(T->color == RED&&(T->Left||T->Right))//(4)
  {
    if(T->Left->color == RED||T->Right->color==RED)
    {
    return 0;
	}
    
  }
  if(T->color == BLACK)
  {
    blacknum++;
  }
    // (5) For each node, all simple paths from the node to descendant leaves 
  //     contain the same number of black nodes.
  if(!T->Left && !T->Right)//T == NULL's parent
  {
    if(blacknum!=blackCount)//actually it is ( blacknum+1(leaf itself) !=blackCount + 1)
    {
	  return 0;
    }
    else 
	{
		return 1;
	}
  }
//recursion further check
  return furthercheck(T->Left, blackCount, blacknum) && furthercheck(T->Right, blackCount, blacknum);
}
//void print(Tree T)
//{
//	printf("(%d,%d)\t",T->Element,T->color);
//	if(T->Left)print(T->Left);
//	if(T->Right)print(T->Right);
//	return;
//}
int main(void)
{
  int K;//the total number of cases
  scanf("%d",&K);
  if(K>=MAXSIZE || K<=0)return 0; 
  while(K--)
  {
    int N;//the total number of nodes in the binary tree
    scanf("%d",&N);
    if(N>=MAXSIZE||N<=0)return 0; 
    int key[N];
    int color[N];
    int i;
    Tree T = NULL;
    for(i=0;i<N;i++)
    {
      scanf("%d",&key[i]);
      color[i] = (key[i]>0);//key>0--BLACK;key<0--RED
      if(!color[i])key[i]*=-1;//ABS()
    }
	buildtree(&T,key,color,N);
	//!!!
	//here we use T's address so we dont need "return x"
	
	
//this is a function to test structre of the tree	
//	print(T);

//check()will return 1 or 0
    if(check(T))printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
//sample data
//1 9 7 -2 1 5 -4 -11 8 14 -15
//1 9 11 -2 1 -7 5 -4 8 14 -15
//1 8 10 -7 5 -6 8 15 -11 17

