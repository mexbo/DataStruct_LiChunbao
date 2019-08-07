//文件名:algo7-1.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;				//数据元素
	struct node *lchild;		//指向左孩子
	struct node *rchild;		//指向右孩子
} BTNode;
void CreateBTNode(BTNode *&b,char *str)		//由str串创建二叉链
{
	BTNode *St[MaxSize],*p=NULL;
	int top=-1,k,j=0;  
	char ch;
	b=NULL;				//建立的二叉树初始时为空
	ch=str[j];
	while (ch!='\0')	//str未扫描完时循环
	{
   	   	switch(ch) 
		{
		case '(':top++;St[top]=p;k=1; break;		//为左节点
		case ')':top--;break;
		case ',':k=2; break;                      	//为右节点
		default:p=(BTNode *)malloc(sizeof(BTNode));
			p->data=ch;p->lchild=p->rchild=NULL;
		         	if (b==NULL)                    //p指向二叉树的根节点
						b=p;
					else  							//已建立二叉树根节点
					{	
						switch(k) 
						{
						case 1:St[top]->lchild=p;break;
						case 2:St[top]->rchild=p;break;
						}
					}
		}
		j++;
		ch=str[j];
	}
}
BTNode *FindNode(BTNode *b,ElemType x)	//返回data域为x的节点指针
{
	BTNode *p;
	if (b==NULL)
	     return NULL;
	else if (b->data==x)
	     return b;
	else
	{	
		p=FindNode(b->lchild,x);
		if (p!=NULL) 
			return p;
		else 
			return FindNode(b->rchild,x);
	}
}
BTNode *LchildNode(BTNode *p)	//返回*p节点的左孩子节点指针
{
    return p->lchild;
}
BTNode *RchildNode(BTNode *p)	//返回*p节点的右孩子节点指针
{
    return p->rchild;
}
int BTNodeDepth(BTNode *b)	//求二叉树b的深度
{
   	int lchilddep,rchilddep;
   	if (b==NULL) 
		return(0); 							//空树的高度为0
   	else  
	{	
		lchilddep=BTNodeDepth(b->lchild);	//求左子树的高度为lchilddep
	  	rchilddep=BTNodeDepth(b->rchild);	//求右子树的高度为rchilddep
		return (lchilddep>rchilddep)? (lchilddep+1):(rchilddep+1);
   	}
}
void DispBTNode(BTNode *b)	//以括号表示法输出二叉树
{
	if (b!=NULL)
	{
		printf("%c",b->data);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{
			printf("(");
			DispBTNode(b->lchild);
			if (b->rchild!=NULL) printf(",");
			DispBTNode(b->rchild);
			printf(")");
		}
	}
}
int BTWidth(BTNode *b)  //求二叉树b的宽度
{
	struct 
	{
		int lno;		//节点的层次编号
		BTNode *p;		//节点指针
	} Qu[MaxSize];		//定义顺序非循环队列
	int front,rear;							//定义队首和队尾指针
	int lnum,max,i,n;
	front=rear=0;							//置队列为空队
    if (b!=NULL) 
	{
		rear++;	
		Qu[rear].p=b;						//根节点指针入队
		Qu[rear].lno=1;						//根节点的层次编号为1
		while (rear!=front)					//队列不为空
		{
			front++;
			b=Qu[front].p;					//队头出队
			lnum=Qu[front].lno;
			if (b->lchild!=NULL)			//左孩子入队
			{
				rear++;
				Qu[rear].p=b->lchild;
				Qu[rear].lno=lnum+1;
			}
			if (b->rchild!=NULL)			//右孩子入队
			{
				rear++;
				Qu[rear].p=b->rchild;
				Qu[rear].lno=lnum+1;
			}
		}
		max=0;lnum=1;i=1;
		while (i<=rear)
		{
			n=0;
			while (i<=rear && Qu[i].lno==lnum) 
			{
				n++;i++;
			}
			lnum=Qu[i].lno;
			if (n>max) max=n;
		}
		return max;
	}
	else
		return 0;
}
int Nodes(BTNode *b)	//求二叉树b的节点个数
{
	int num1,num2;
    if (b==NULL) 
		return 0;
    else if (b->lchild==NULL && b->rchild==NULL) 
		return 1;
    else
    {
        num1=Nodes(b->lchild);
        num2=Nodes(b->rchild);
        return (num1+num2+1);
	}
}
int LeafNodes(BTNode *b)	//求二叉树b的叶子节点个数
{
	int num1,num2;
    if (b==NULL) 
		return 0;
    else if (b->lchild==NULL && b->rchild==NULL) 
		return 1;
    else
    {
        num1=LeafNodes(b->lchild);
        num2=LeafNodes(b->rchild);
        return (num1+num2);
	}
}
void DestroyBTNode(BTNode *&b)
{
	if (b!=NULL)
	{
		DestroyBTNode(b->lchild);
		DestroyBTNode(b->rchild);
		free(b);
	}
}

