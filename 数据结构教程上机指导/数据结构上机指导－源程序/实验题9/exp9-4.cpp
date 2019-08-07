//文件名:exp9-4.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef int KeyType;					//定义关键字类型
typedef char InfoType;
typedef struct node               		//记录类型
{	
	KeyType key;                  		//关键字项
    InfoType data;               		//其他数据域
    struct node *lchild,*rchild;		//左右孩子指针
} BSTNode;
int path[MaxSize];						//全局变量,用于存放路径
void DispBST(BSTNode *b);				//函数说明
int InsertBST(BSTNode *&p,KeyType k)	//在以*p为根节点的BST中插入一个关键字为k的节点
{
   	if (p==NULL)						//原树为空, 新插入的记录为根节点
	{
		p=(BSTNode *)malloc(sizeof(BSTNode));
		p->key=k;p->lchild=p->rchild=NULL;
		return 1;
	}
	else if (k==p->key) 
		return 0;
	else if (k<p->key) 
		return InsertBST(p->lchild,k);	//插入到*p的左子树中
	else  
		return InsertBST(p->rchild,k);  //插入到*p的右子树中
}
BSTNode *CreatBST(KeyType A[],int n)				
//由数组A中的关键字建立一棵二叉排序树
{
  	BSTNode *bt=NULL;         			//初始时bt为空树
   	int i=0;
   	while (i<n) 
		if (InsertBST(bt,A[i])==1)		//将A[i]插入二叉排序树T中
		{
			printf("    第%d步,插入%d:",i+1,A[i]);
			DispBST(bt);printf("\n");
			i++;
		}
    return bt;               			//返回建立的二叉排序树的根指针
}
void Delete1(BSTNode *p,BSTNode *&r)
//当被删*p节点有左右子树时的删除过程
{
	BSTNode *q;
	if (r->rchild!=NULL)
		Delete1(p,r->rchild);	//递归找最右下节点
	else						//找到了最右下节点*r
	{
		p->key=r->key;			//将*r的关键字值赋给*p
		q=r;					
		r=r->lchild;			//将*r的双亲节点的右孩子节点改为*r的左孩子节点
		free(q);				//释放原*r的空间
	}
}
void Delete(BSTNode *&p)
//从二叉排序树中删除*p节点
{
	BSTNode *q;
	if (p->rchild==NULL)		//*p节点没有右子树的情况
	{
		q=p;p=p->lchild;free(q);
	}
	else if (p->lchild==NULL)	//*p节点没有左子树的情况
	{
		q=p;p=p->rchild;free(q);
	}
	else Delete1(p,p->lchild);	//*p节点既有左子树又有右子树的情况
}
int DeleteBST(BSTNode *&bt,KeyType k)	
//在bt中删除关键字为k的节点
{
	if (bt==NULL) return 0;		//空树删除失败
	else 
	{
		if (k<bt->key) 
			return DeleteBST(bt->lchild,k);		//递归在左子树中删除关键字为k的节点
		else if (k>bt->key) 
			return DeleteBST(bt->rchild,k);		//递归在右子树中删除关键字为k的节点
		else									//k=bt->key的情况
		{
			Delete(bt);		//调用Delete(bt)函数删除*bt节点
			return 1;
		}
	}
}
void SearchBST1(BSTNode *bt,KeyType k,KeyType path[],int i)	
//以非递归方式输出从根节点到查找到的节点的路径
{ 
	int j;
	if (bt==NULL)
		return;
	else if (k==bt->key)	//找到了节点
	{
		path[i+1]=bt->key;	//输出其路径
		for (j=0;j<=i+1;j++)
			printf("%3d",path[j]);
		printf("\n");
	}
	else
	{
		path[i+1]=bt->key;
		if (k<bt->key)
			SearchBST1(bt->lchild,k,path,i+1);  //在左子树中递归查找
		else
			SearchBST1(bt->rchild,k,path,i+1);  //在右子树中递归查找
	}
}
int SearchBST2(BSTNode *bt,KeyType k)	
//以递归方式输出从根节点到查找到的节点的路径
{ 
	if (bt==NULL)
		return 0;
	else if (k==bt->key)
	{
		printf("%3d",bt->key);
		return 1;
	}
	else if (k<bt->key)
		SearchBST2(bt->lchild,k);  //在左子树中递归查找
	else
		SearchBST2(bt->rchild,k);  //在右子树中递归查找
	printf("%3d",bt->key);
}

void DispBST(BSTNode *bt)	
//以括号表示法输出二叉排序树bt
{
	if (bt!=NULL)
	{
		printf("%d",bt->key);
		if (bt->lchild!=NULL || bt->rchild!=NULL)
		{
			printf("(");
			DispBST(bt->lchild);
			if (bt->rchild!=NULL) printf(",");
			DispBST(bt->rchild);
			printf(")");
		}
	}
}
KeyType predt=-32767; //predt为全局变量,保存当前节点中序前趋的值,初值为-∞
int JudgeBST(BSTNode *bt)	//判断bt是否为BST
{
	int b1,b2;
	if (bt==NULL)
		return 1;
	else 
	{
		b1=JudgeBST(bt->lchild);
		if (b1==0 || predt>=bt->key)
			return 0;
		predt=bt->key;
		b2=JudgeBST(bt->rchild);
		return b2;
	}
}
void main()
{
	BSTNode *bt;
	KeyType k=6;
	int a[]={4,9,0,1,8,6,3,5,2,7},n=10;
	printf("创建一棵BST树:");
	printf("\n");
	bt=CreatBST(a,n);
	printf("BST:");DispBST(bt);printf("\n");
	printf("bt%s\n",(JudgeBST(bt)?"是一棵BST":"不是一棵BST"));
	printf("  查找%d关键字(递归,顺序):",k);SearchBST1(bt,k,path,-1);
	printf("查找%d关键字(非递归,逆序):",k);SearchBST2(bt,k);
	printf("\n删除操作:\n");
	printf("   原BST:");DispBST(bt);printf("\n");
	printf("   删除节点4:");
	DeleteBST(bt,4);
	DispBST(bt);printf("\n");
	printf("   删除节点5:");
	DeleteBST(bt,5);
	DispBST(bt);
	printf("\n");
}
