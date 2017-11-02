int depth(BinTree T)
{
  int ld;
  int rd;
  if(!T)return 0;
  else
  {
    ld=depth(T->Left);
    rd=depth(T->Right);
    if(ld<rd)return --ld;
    else return --rd;
  }
}
void In(BinTree T,int* inorder)
{
  static int i =0;
  if(T)
  {
    In(T->Left,inorder);
    inorder[i++]=T->Key;
    In(T->Right,inorder);
  }
}

int check(BinTree T,int* array)
{
  /*if(!T->Left&&!T->Right)return 1;
  if(T->Left)
  {
    if(T->Left->Key>T->Key)return 0;
  }
  if(T->Right)
  {
    if(T->Right->Key<T->Key)return 0;
  }
  if(T->Left->Key>T->Key||T->Right->Key<T->Key)return 0;
  return check(T->Left)&&check(T->Right);*/
  int i;
  for(i=0;array[i];i++)
  {
    if(array[i+1]&&array[i]>array[i+1])return 0;
  }
  return 1;
}

int CheckBST ( BinTree T, int K )
{
  //check
  int inorder[100]={0};
  In(T,inorder);//inorder traversal
  if(check(T,inorder))
  {
    int i=0;
    //if(!inorder[1])return inorder[0];
    for(i=0;inorder[i]!=0;i++)
    {

    }//lenth
    return inorder[i-K];
  }
  else
  {
    return depth(T);
  }
}