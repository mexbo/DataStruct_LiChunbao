//文件名:exp7-7.cpp
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;				//数据元素
	struct node *lchild;		//指向左孩子
	struct node *rchild;		//指向右孩子
} BTNode;
extern void DispBTNode(BTNode *b);	 //在algo7-1.cpp文件中
extern void DestroyBTNode(BTNode *&b);
BTNode *CRTree(char s[],int i,int j)
{
	BTNode *p;
	int k,plus=0,posi;
	if (i==j)
	{
		p=(BTNode *)malloc(sizeof(BTNode));
		p->data=s[i];
		p->lchild=NULL;
		p->rchild=NULL;
		return p;
	}
	//以下为i!=j的情况
	for (k=i;k<=j;k++)
		if (s[k]=='+' || s[k]=='-')
		{
			plus++;
			posi=k;              //最后一个+或-的位置
		}
	if (plus==0)                 //没有+或-的情况
		for (k=i;k<=j;k++)
			if (s[k]=='*' || s[k]=='/')
			{
				plus++;
				posi=k;
			}
   if (plus!=0)
   {
		p=(BTNode *)malloc(sizeof(BTNode));
		p->data=s[posi];
		p->lchild=CRTree(s,i,posi-1);
		p->rchild=CRTree(s,posi+1,j);
		return p;
	}
   else       //若没有任何运算符，返回NULL
	   return NULL;
}
double Comp(BTNode *b)
{
	double v1,v2;
	if (b==NULL) return 0;
	if (b->lchild==NULL && b->rchild==NULL)
		return b->data-'0';    //叶子节点直接返回节点值
	v1=Comp(b->lchild);
	v2=Comp(b->rchild);
	switch(b->data)
	{
	case '+':
		return v1+v2;
	case '-':
		return v1-v2;
	case '*':
		return v1*v2;
	case '/':
		if (v2!=0)
			return v1/v2;
		else
			abort();

	}
}
void main()
{
	BTNode *b;
	char s[MaxSize]="1+2*3-4/5";
    printf("代数表达式%s\n",s);
	b=CRTree(s,0,strlen(s)-1);
	printf("对应二叉树:");
	DispBTNode(b);
	printf("\n表达式的值:%g\n",Comp(b));
	DestroyBTNode(b);
}
