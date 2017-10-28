#include<stdio.h>
#include<stdlib.h>

void Father(int M, int N)
{
  int sum = 1;
  //count
  //initially 1
  
  int num;//number
  int Father;
  int n;//read
  int i,j;

  int f[M+1];//father array
  int d[M+1];//depth array
  int notleaf[M];
  int p = 0;//not_leaf array
  
  for(i = 0;i<M;i++)
  {
  	notleaf[i] = 0;
  }//initialization
  
  int depthleavescount[M];//depth's leaves counting
  for(i = 1;i<=M;i++)
  {
  	depthleavescount[i] = 0;
  //printf("depthleavescount[%d] = %d\n",i,depthleavescount[i]);
  }//initialization
	  
  
  
  
  int havechild = 0;
  int maxdepth = 1;
  
  f[0] = 0;//root
  f[1] = 0;//root
  
  d[0] = 0;//root
  d[1] = 1;//root
  
  while(sum < M)
  {
    scanf("%d",&Father);
    notleaf[p] = Father;
    p++;
    scanf("%d",&num );
    for(i=0;i<num;i++)
    {
      scanf("%d",&n);
      f[n] = Father;
    }
    sum += num;
  }//create father chain
  //printf("f[%d] = %d\n",n,f[n]);
  for(i = 1;i<=M;i++)
  {
  	d[i]=countfather(f,i);
  	if(d[i]>=d[i-1])maxdepth = d[i];
  }//find depth
  //printf("maxd=%d\n",maxdepth);
  for(i = 1;i<=M;i++)
  {
  	for(j = 0;j<p;j++)
  	{
  		havechild = (notleaf[j] == i) ;
  		if(havechild)break;
	  }
	 // printf("havechild[%d] = %d\n",i,havechild);
	  if(!havechild)
	  {
	  	depthleavescount[d[i]]++;
	 // 	printf("d[%d] = %d\ndepthleavescount[%d] = %d\n",i,d[i],d[i],depthleavescount[d[i]]);
	  }
	  else
	  {
	  	havechild = 0;
	 // 	printf("d[%d] = %d\ndepthleavescount[%d] = %d\n",i,d[i],d[i],depthleavescount[d[i]]);
	  } 
  }
  
  for(i = 1;i<=maxdepth;i++)
  {
  	printf("%d",depthleavescount[i]);
  	if(i!=maxdepth)printf(" ");
  	else printf("\n");
  }
}
int countfather(int* f,int n)
{
	static int depth = 1;
	int temp;
	if(n == 1)
	{
		temp = depth;
		depth = 1;
		return temp;
	}
	else
	{
		depth++;
		countfather(f,f[n]);
		
	}
}
int main()
{
  int M,N;
  int father;
  while(1)
  {
    scanf("%d %d",&M,&N);
    if(!M)break;
    Father(M,N);
  }
  return 0;
}
