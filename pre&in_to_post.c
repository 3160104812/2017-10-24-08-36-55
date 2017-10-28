#include <stdio.h>
#include <stdlib.h>

void build(int* preorder,int* inorder,int N)
{
  char str[4];

  int top_preorder = 0;//top of pre stack
  int top_inorder = 0;//top of in stack

  int stack[N];
  int top = 0;
  
  int n = 2*N;

  while(n--)
  {
    scanf("%s",str);
  	if(!strcmp(str, "Push"))
    {
        scanf("%d",&preorder[top_preorder++]);
        stack[top++] = preorder[top_preorder - 1];
    }
    else if(!strcmp(str, "Pop"))
    {
        inorder[top_inorder++] = stack[--top];
        stack[top] = 0;
    }
  }
}
void postorder(int* preorder,int* inorder,int n)
{
  int i;
  if(!n)return;
  for(i = 0;i<n;i++)
  {
    if(inorder[i] == *preorder)
    break;
  }//get i which is location of root
  postorder(preorder+1,inorder,i);
  postorder(preorder+i+1,inorder+i+1,n-i-1);
  if(*preorder != 1)printf("%d ",*preorder);
  else printf("%d",*preorder);
}

int main()
{
  int N;
  scanf("%d",&N);
  
  int i;

  int preorder[N];
  int inorder[N];
  build(preorder,inorder,N);
  
  
  postorder(preorder,inorder,N);
  //printf("test");//check extra space
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxTree 30 /* maximum number of nodes in a tree */
/*typedef int ElementType; 

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
    Tree  Father;
};

Tree BuildTree(int N)
{
    char str[4];
    int num = 0;
    int i = 0;

    scanf("%s",str); 
    i++; 
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T -> Father = NULL;
    T -> Left = NULL;
    T -> Right = NULL;         
    if(!strcmp(str, "Push"))
    {
        scanf("%d",&num);
        if( num > N )return NULL;
        T ->Element = num;
    }

    Tree ret = (Tree)malloc(sizeof(struct TreeNode));
    ret = T;
    

    while(i < 2 * N)
    {
        scanf("%s",str); 
         
        if(!strcmp(str, "Push"))
        {
            
            i ++;
            scanf("%d",&num);
            Tree temp = (Tree)malloc(sizeof(struct TreeNode));
            temp ->Element = num;
            temp->Left = NULL;
            temp->Right = NULL;
            if(T->Left == NULL)
            {
                temp->Father = T;
                T->Left = temp;
                T = temp;
            }
            else if(T->Right == NULL) 
            {
                temp->Father = T;
                T->Right = temp;
                T = temp;
            }  
        }
        else if(!strcmp(str, "Pop"))
        {
            i ++;
            T = T->Father;
            continue;
        }
    }

    return ret;
}

void PrintNode( Tree NodePtr )
{
    printf("%d", NodePtr->Element);
    return;
}

void Postorder(Tree T, int N){
    if(T==NULL)
        return;
    Postorder(T->Left,N);
    Postorder(T->Right,N);
    PrintNode(T);
    if(T->Element!=N)printf(" ");
}



int main()
{
    int N;
    Tree T = NULL;
    scanf("%d", &N);
    if (N > MaxTree)return 0;
    T = BuildTree(N);
    Postorder(T, N);
    return 0;
}
*/ 
