//文件名:exp8-5.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList(MGraph,ALGraph *&);	//以下外部函数在algo8-1.cpp中
extern void DispAdj(ALGraph *);
int visited[MAXV];							//全局数组
void PathAll1(ALGraph *G,int u,int v,int path[],int i)
//输出图G中从顶点u到v的所有简单路径
{
	ArcNode *p;
	int j,n;
	visited[u]=1;
	p=G->adjlist[u].firstarc;  			//p指向顶点m的第一条边
	while (p!=NULL)
	{
		n=p->adjvex;					//n为m的邻接顶点
		if (n==v)
		{
			path[i+1]=v;
			for (j=0;j<=i+1;j++)
				printf("%3d",path[j]);
			printf("\n");
		}
		else if (visited[n]==0 ) 		//若该顶点未标记访问,则递归访问之
		{
			path[i+1]=n;
			PathAll1(G,n,v,path,i+1);
		}
		p=p->nextarc;					//找u的下一个邻接顶点
	}
	visited[u]=0;
}
void PathAll2(ALGraph *G,int u,int v,int l,int path[],int d)
//输出图G中从顶点u到v的长度为l的所有简单路径,d是到当前为止已走过的路径长度,调用时初值为-1
{
	int m,i;
	ArcNode *p;
	visited[u]=1;
	d++;							//路径长度增1
	path[d]=u;						//将当前顶点添加到路径中
	if (u==v && d==l)				//输出一条路径
	{
		for (i=0;i<=d;i++)
			printf("%3d",path[i]);
		printf("\n");
	}
	p=G->adjlist[u].firstarc;  		//p指向顶点u的第一条边
	while (p!=NULL)
	{
		m=p->adjvex;				//m为u的邻接顶点
		if (visited[m]==0)			//若该顶点未标记访问,则递归访问之
			PathAll2(G,m,v,l,path,d);
		p=p->nextarc;				//找u的下一个邻接顶点
	}
	visited[u]=0;					//取消访问标记,以使该顶点可重新使用
}
int ShortPath(ALGraph *G,int u,int v,int path[])
//求顶点u到顶点v(u≠v)的最短路径
{
	struct 
	{
		int vno;						//当前顶点编号
		int level;						//当前顶点的层次
		int parent;						//当前顶点的当一个节点编号
	} qu[MAXV];							//定义顺序非循环队列
	int front=-1,rear=-1,k,lev,i,j;
	ArcNode *p;
	visited[u]=1;
	rear++;								//顶点u已访问,将其入队
	qu[rear].vno=u;
	qu[rear].level=0;
	qu[rear].parent=-1;
	while (front<rear)					//队非空则执行
	{
		front++;
		k=qu[front].vno;				//出队
		lev=qu[front].level;
		if (k==v) 
		{
			i=0;
			j=front;
			while (j!=-1)
			{
				path[lev-i]=qu[j].vno;	//将最短路径存入path中
				j=qu[j].parent;
				i++;
			}
			return lev;					//找到顶点v,返回
		}
		p=G->adjlist[k].firstarc;		//取k的边表头指针           
		while (p!=NULL)                 //依次搜索巧的邻接点
		{
			if (visited[p->adjvex]==0)  //若未访问过
			{
				visited[p->adjvex]=1;
				rear++;
				qu[rear].vno=p->adjvex;	//访问过的邻接点入队
				qu[rear].level=lev+1;
				qu[rear].parent=front;
			}
			p=p->nextarc;				//找顶点i的下一邻接点
		}
	}
	return -1;     //如果未找到顶点j,返回一特殊值-1
}
void main()
{ 
	int i,j;
	int u=5,v=2,d=3;
	int path[MAXV];
	MGraph g;
	ALGraph *G;
	int A[MAXV][6]={
		{0,1,0,1,0,0},
		{0,0,1,0,0,0},
		{1,0,0,0,0,1},
		{0,0,1,0,0,1},
		{0,0,0,1,0,0},
		{1,1,0,1,1,0}};
	g.n=6;g.e=10;
	for (i=0;i<g.n;i++)		//建立图9.10的邻接矩阵
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);					//图G的邻接矩阵转换成邻接表
	printf("图G的邻接表:\n");
	DispAdj(G);
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("从顶点%d到%d的所有路径:\n",u,v);
	path[0]=u;visited[u]=1;
	PathAll1(G,u,v,path,0);
	printf("从顶点%d到%d的所有长度为%d路径:\n",u,v,d);
	PathAll2(G,u,v,d,path,-1);printf("\n");
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("从顶点%d到%d的最短路径:\n",u,v);
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	j=ShortPath(G,u,v,path);
	for (i=0;i<=j;i++)
		printf("%3d",path[i]);
	printf("\n");
}