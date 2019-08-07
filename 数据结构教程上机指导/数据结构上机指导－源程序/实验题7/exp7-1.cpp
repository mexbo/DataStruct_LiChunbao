//文件名:exp7-1.cpp
#include <stdio.h>
typedef char ElemType;
typedef struct node
{
	ElemType data;				//数据元素
	struct node *lchild;		//指向左孩子
	struct node *rchild;		//指向右孩子
} BTNode;
extern void CreateBTNode(BTNode *&b,char *str);
extern BTNode *FindNode(BTNode *b,ElemType x);
extern BTNode *LchildNode(BTNode *p);
extern BTNode *RchildNode(BTNode *p);
extern int BTNodeDepth(BTNode *b);
extern void DispBTNode(BTNode *b);
extern int BTWidth(BTNode *b);
extern int Nodes(BTNode *b);
extern int LeafNodes(BTNode *b);
extern void DestroyBTNode(BTNode *&b);
void main()
{	BTNode *b,*p,*lp,*rp;;
	CreateBTNode(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("二叉树的基本运算如下:\n");
	printf("  (1)输出二叉树:");DispBTNode(b);printf("\n");
	printf("  (2)H节点:");
	p=FindNode(b,'H');
	if (p!=NULL)
	{	lp=LchildNode(p);
		if (lp!=NULL) 
			printf("左孩子为%c ",lp->data);
		else
			printf("无左孩子 ");
		rp=RchildNode(p);
		if (rp!=NULL)
			printf("右孩子为%c",rp->data);
		else
			printf("无右孩子 ");
	}
	printf("\n");
	printf("  (3)二叉树b的深度:%d\n",BTNodeDepth(b));
	printf("  (4)二叉树b的宽度:%d\n",BTWidth(b));
	printf("  (5)二叉树b的节点个数:%d\n",Nodes(b));
	printf("  (6)二叉树b的叶子节点个数:%d\n",LeafNodes(b));
	printf("  (7)释放二叉树b\n");
	DestroyBTNode(b);
}
