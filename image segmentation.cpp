//
//  main.c
//  image
//
//  Created by mac on 2017/12/4.
//  Copyright ? 2017mac. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


#define N  200 


int m, n, c;
int parent[N];//储存每个点的上一个结点
			  //int s[N];

struct edge {
	int x;
	int y;
	int z;
}ed[N]; //每个边的两端以及边权


int b[N];//
int fa[N], s[N];
int count[N];

int initial() {//初始化count与parent数组，count以每个块的根为标志，保存此块内的结点数。初始化为1
	int i;
	for (i = 0; i<N; i++) {
		count[i] = 1;
		parent[i] = -1;
	}
	return 0;
}

void initials(int n, int m) {//初始化s数组，前提是ed数组已经按边权从小到大保存了。初始化时内存每个点相连的最小的边权
	int i;
	int *known=(int *)malloc(sizeof(int)*n);
	for (i = 0; i<n; i++) {
		known[i] = 0;
	}
	for (i = 1; i <= m; i++) {
		if (known[ed[i].x] == 0) {
			s[ed[i].x] = ed[i].z;
			known[ed[i].x] = 1;
		}
	}
}

void sort(int m) {//将ed数组按从小到大排列
	int temp;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m - i; j++) {
			if (ed[j].z > ed[j + 1].z) {
				temp = ed[j].z;
				ed[j].z = ed[j + 1].z;
				ed[j + 1].z = temp;

				temp = ed[j].x;
				ed[j].x = ed[j + 1].x;
				ed[j + 1].x = temp;

				temp = ed[j].y;
				ed[j].y = ed[j + 1].y;
				ed[j + 1].y = temp;
			}
		}
	}
}

int Find(int x)     //输入一个数，返回它所在的块的根
{
	int d;
	for (d = x; parent[d] >= 0; d = parent[d]);
	count[parent[x]] += count[x];
	if (x != d)
		count[x] = 0;
	return d;
}

int main() {
	initial();
	int x, y, z;
	int save = 0;
	int root = 0;
	int known[N];
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		ed[i].x = x;
		ed[i].y = y;
		ed[i].z = z;
	}
	sort(m);
	initials(n, m);
	for (int i = 1; i <= m; i++) {
		int p = Find(ed[i].x), q = Find(ed[i].y);
		if (p == q) continue;//若两点根相同，则在同一个块内，不需要加入当前讨论的边
		if (p<q) {
			int temp;
			temp = p;
			p = q;
			q = temp;
		}
		if (s[p] + c / count[p] < ed[i].z) continue;
		if (s[q] + c / count[q] < ed[i].z) continue;//满足题目中的公式，则此边为连接两块的边
		parent[p] = q;//其余情况下，将p及其下属点并入q
		Find(p);//用此函数的目的是重新计数
		s[q] = ed[i].z;//更新块内的最小生成树的最大边
	}
	for (int i = 0; i<n; i++) {//初始化，代表所有边还未被访问
		known[i] = 0;
	}
	int i;
	while (save != n) {//save记录已经打印的数字数
		for (i = 0; i<n; i++) {//输出根相同的一组数，以\n作为结束
			if (known[Find(i)] == 0) {
				root = Find(i);
				break;
			}
		}
		known[Find(i)] = 1;
		for (i = 0; i<n; i++) {
			if (Find(i) == root) {
				printf("%d ", i);
				save++;
			}
		}
		printf("\n");
	}
	return 0;
}
