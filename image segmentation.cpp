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
int parent[N];//����ÿ�������һ�����
			  //int s[N];

struct edge {
	int x;
	int y;
	int z;
}ed[N]; //ÿ���ߵ������Լ���Ȩ


int b[N];//
int fa[N], s[N];
int count[N];

int initial() {//��ʼ��count��parent���飬count��ÿ����ĸ�Ϊ��־������˿��ڵĽ��������ʼ��Ϊ1
	int i;
	for (i = 0; i<N; i++) {
		count[i] = 1;
		parent[i] = -1;
	}
	return 0;
}

void initials(int n, int m) {//��ʼ��s���飬ǰ����ed�����Ѿ�����Ȩ��С���󱣴��ˡ���ʼ��ʱ�ڴ�ÿ������������С�ı�Ȩ
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

void sort(int m) {//��ed���鰴��С��������
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

int Find(int x)     //����һ���������������ڵĿ�ĸ�
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
		if (p == q) continue;//���������ͬ������ͬһ�����ڣ�����Ҫ���뵱ǰ���۵ı�
		if (p<q) {
			int temp;
			temp = p;
			p = q;
			q = temp;
		}
		if (s[p] + c / count[p] < ed[i].z) continue;
		if (s[q] + c / count[q] < ed[i].z) continue;//������Ŀ�еĹ�ʽ����˱�Ϊ��������ı�
		parent[p] = q;//��������£���p���������㲢��q
		Find(p);//�ô˺�����Ŀ�������¼���
		s[q] = ed[i].z;//���¿��ڵ���С������������
	}
	for (int i = 0; i<n; i++) {//��ʼ�����������б߻�δ������
		known[i] = 0;
	}
	int i;
	while (save != n) {//save��¼�Ѿ���ӡ��������
		for (i = 0; i<n; i++) {//�������ͬ��һ��������\n��Ϊ����
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
