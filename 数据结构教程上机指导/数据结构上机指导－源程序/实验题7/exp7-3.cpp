//文件名:exp7-3.cpp
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
extern void CreateBTNode(BTNode *&b,char *str);  //在algo7-1.cpp文件中
extern void DispBTNode(BTNode *b);
extern void DestroyBTNode(BTNode *&b);
void AllPath(BTNode *b)
{
	struct snode
	{
	   BTNode *node;			//存放当前节点指针
	   int parent;				//存放双亲节点在队列中的位置
	} Qu[MaxSize];				//定义顺序队列
	int front,rear,p;			//定义队头和队尾指针
    front=rear=-1;				//置队列为空队列
	rear++;
    Qu[rear].node=b;			//根节点指针进入队列
	Qu[rear].parent=-1;			//根节点没有双亲节点
    while (front<rear)			//队列不为空
    {
		front++;
		b=Qu[front].node;		//队头出队列
		if (b->lchild==NULL && b->rchild==NULL)	//*b为叶子节点
		{
			printf("   %c到根节点逆路径:",b->data);
			p=front;
			while (Qu[p].parent!=-1)
			{
				printf("%c ",Qu[p].node->data);
				p=Qu[p].parent;
			}
			printf("%c\n",Qu[p].node->data);
		}
		if (b->lchild!=NULL)		//左孩子入队列
		{
			rear++;
			Qu[rear].node=b->lchild;
			Qu[rear].parent=front;
		}
		if (b->rchild!=NULL)		//右孩子入队列
		{
			rear++;
			Qu[rear].node=b->rchild;
			Qu[rear].parent=front;
		}
	} 
}
void AllPath1(BTNode *b,ElemType path[],int pathlen)
{
	int i;
	if (b!=NULL)
	{
		if (b->lchild==NULL && b->rchild==NULL)	//*b为叶子节点
		{
			printf("   %c到根节点逆路径: %c ",b->data,b->data);
			for (i=pathlen-1;i>=0;i--)
				printf("%c ",path[i]);
			printf("\n");
		}
		else
		{
			path[pathlen]=b->data;				//将当前节点放入路径中
			pathlen++;							//路径长度增1
			AllPath1(b->lchild,path,pathlen);	//递归扫描左子树
			AllPath1(b->rchild,path,pathlen);	//递归扫描右子树
			pathlen--;							//恢复环境
		}
	}
}
void LongPath(BTNode *b,ElemType path[],int pathlen,ElemType longpath[],int &longpathlen)
{
	int i;
	if (b==NULL)
	{
		if (pathlen>longpathlen)	//若当前路径更长,将路径保存在longpath中
		{
			for (i=pathlen-1;i>=0;i--)
				longpath[i]=path[i];
			longpathlen=pathlen;
		}
	}
	else	
	{
		path[pathlen]=b->data;					//将当前节点放入路径中
		pathlen++;								//路径长度增1
		LongPath(b->lchild,path,pathlen,longpath,longpathlen);	//递归扫描左子树
		LongPath(b->rchild,path,pathlen,longpath,longpathlen);	//递归扫描右子树
		pathlen--;								//恢复环境
	}
}
void DispLeaf(BTNode *b)
{
    	if (b!=NULL) 
	{	if (b->lchild==NULL && b->rchild==NULL) 
			printf("%c ",b->data);
    	else
    	{	
			DispLeaf(b->lchild);
			DispLeaf(b->rchild);
		}
	}
}
void main()
{
	BTNode *b;
	ElemType path[MaxSize],longpath[MaxSize];
	int i,longpathlen=0;
	CreateBTNode(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"); 
	printf("二叉树b:");DispBTNode(b);printf("\n");
	printf("b的叶子节点:");DispLeaf(b);printf("\n");
	printf("AllPath:\n");AllPath(b);
	printf("AllPath1:\n");AllPath1(b,path,0);
	LongPath(b,path,0,longpath,longpathlen);
	printf("第一条最长逆路径长度:%d\n",longpathlen);
	printf("第一条最长逆路径:");
	for (i=longpathlen-1;i>=0;i--)
		printf("%c ",longpath[i]);
	printf("\n");
	DestroyBTNode(b);
}