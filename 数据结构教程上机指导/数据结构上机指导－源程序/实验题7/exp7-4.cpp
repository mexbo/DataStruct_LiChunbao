//文件名:exp7-4.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef char ElemType;
typedef struct node 
{
	ElemType data;				//数据元素
	struct node *lchild;		//指向左孩子
	struct node *rchild;		//指向右孩子
} BTNode;
extern void DispBTNode(BTNode *b);
extern void DestroyBTNode(BTNode *&b);
BTNode *CreateBT1(char *pre,char *in,int n)
{
	BTNode *s;
	char *p;
	int k;
	if (n<=0) return NULL;
	s=(BTNode *)malloc(sizeof(BTNode));		//创建二叉树节点*s
	s->data=*pre;
	for (p=in;p<in+n;p++)		//在中序序列中找等于*ppos的位置k
		if (*p==*pre)
			break;
	k=p-in;
	s->lchild=CreateBT1(pre+1,in,k);
	s->rchild=CreateBT1(pre+k+1,p+1,n-k-1);
	return s;
}
BTNode *CreateBT2(char *post,char *in,int n,int m)
{
	BTNode *s;
	char *p,*q,*maxp;
	int maxpost,maxin,k;
	if (n<=0) return NULL;
	maxpost=-1;
	for (p=in;p<in+n;p++)			//求in中全部字符中在post中最右边的那个字符
		for (q=post;q<post+m;q++)	//在in中用maxp指向这个字符,用maxin标识它在in中的下标
			if (*p==*q)
			{
				k=q-post;
				if (k>maxpost) 
				{
					maxpost=k;
					maxp=p;
					maxin=p-in;
				}
			}
	s=(BTNode *)malloc(sizeof(BTNode));		//创建二叉树节点*s
	s->data=post[maxpost];
	s->lchild=CreateBT2(post,in,maxin,m);
	s->rchild=CreateBT2(post,maxp+1,n-maxin-1,m);
	return s;
}
void DispBTNode1(BTNode *b)  //以凹入表表示法输出一棵二叉树
{
	BTNode *St[MaxSize],*p;
	int level[MaxSize][2],top=-1,n,i,width=4;
	char type;
	if (b!=NULL)
	{
		top++;
		St[top]=b;						//根节点入栈
		level[top][0]=width;
		level[top][1]=2;				//2表示是根
		while (top>-1)
		{
			p=St[top];					//退栈并凹入显示该节点值
			n=level[top][0];
			switch(level[top][1])
			{
			case 0:type='L';break;		//左节点之后输出(L)
			case 1:type='R';break;		//右节点之后输出(R)
			case 2:type='B';break;		//根节点之后前输出(B)
			}
			for (i=1;i<=n;i++)			//其中n为显示场宽,字符以右对齐显示
				printf(" ");
			printf("%c(%c)",p->data,type);
			for (i=n+1;i<=MaxWidth;i+=2)
				printf("--");
			printf("\n");
			top--;
			if (p->rchild!=NULL)
			{							//将右子树根节点入栈
				top++;
				St[top]=p->rchild;
				level[top][0]=n+width;	//显示场宽增width
				level[top][1]=1;		//1表示是右子树
			}
			if (p->lchild!=NULL)
			{							//将左子树根节点入栈
				top++;
				St[top]=p->lchild;
				level[top][0]=n+width;  //显示场宽增width
				level[top][1]=0;        //0表示是左子树
			}
		}
	}
}

void main()
{
	BTNode *b;
	ElemType pre[]="ABDEHJKLMNCFGI";
	ElemType in[]="DBJHLKMNEAFCGI";
	ElemType post[]="DJLNMKHEBFIGCA";
	b=CreateBT1(pre,in,14);
	printf("先序序列:%s\n",pre);
	printf("中序序列:%s\n",in);
	printf("构造一棵二叉树b:\n");
	printf("  括号表示法:");DispBTNode(b);printf("\n");
	printf("  凹入表示法:\n");DispBTNode1(b);printf("\n\n");
	printf("中序序列:%s\n",in);
	printf("后序序列:%s\n",post);
	b=CreateBT2(post,in,14,14);
	printf("构造一棵二叉树b:\n");
	printf(" 括号表示法:");DispBTNode(b);printf("\n");
	printf(" 凹入表示法:\n");DispBTNode1(b);printf("\n");
	DestroyBTNode(b);
}
