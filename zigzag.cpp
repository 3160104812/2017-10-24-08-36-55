#include <stdio.h>
#include <stdlib.h>
#define Max 30
/*8
12 11 20 17 1 15 8 5
12 20 17 11 15 8 5 1
*/
struct TreeNode
{
	struct TreeNode* left;
	struct TreeNode* right;
	int value;
	int flag;
};
int inorder[Max];
int postorder[Max];
int zigzag[Max][2] = {};
int top = 0;
struct TreeNode* transform(int*inorder, int*postorder, int n, int level)
{
	int i;
	if (!n)return NULL;
	for (i = 0; i<n; i++)
	{
		if (inorder[i] == *(postorder + n - 1))
			break;
	}
	struct TreeNode* preorder = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	preorder->value = *(postorder + n - 1);
	preorder->flag = level;
	preorder->left = transform(inorder, postorder, i, (level + 1) % 2);
	preorder->right = transform(inorder + i + 1, postorder + i, n - i - 1, (level + 1) % 2);
	return preorder;
}
void level_order(struct TreeNode* T)
{
	struct TreeNode* queue[Max];
	int front = -1;
	int rear = 0;
	if (!T)return;
	queue[rear] = T;
	while (front != rear)
	{
		front++;
		{
			zigzag[top][0] = queue[front]->value;
			zigzag[top][1] = queue[front]->flag;
			top++;
		}
		if (queue[front]->left)
		{
			rear++;
			queue[rear] = queue[front]->left;
		}
		if (queue[front]->right)
		{
			rear++;
			queue[rear] = queue[front]->right;
		}
	}
	return;
}
int main()
{
	int n;
	scanf("%d", &n);
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%d", inorder + i);
		}
		for (int i = 0; i < n; i++)
		{
			scanf("%d", postorder + i);
		}

	}
	struct TreeNode*T = transform(inorder, postorder, n, 0);
	level_order(T);
	for (int i = 0; i < n; i++)
	{
		if (zigzag[i][1])
		{
			if (i != 0)
				printf(" ");
			printf("%d", zigzag[i][0]);
		}

		else
		{
			int ti;
			for (ti = i; zigzag[ti][1] == 0 && ti<n; ti++);
			ti--;
			for (int tti = ti; zigzag[tti][1] == 0 && tti >= i; tti--)
			{
				if (ti != 0)
					printf(" ");
				printf("%d", zigzag[tti][0]);
			}
			i = ti;
		}
	}
	system("pause");
	return 0;
}