//文件名:excise44.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
int visited[MAXV],path[MAXV];		//全局数组
int V1[MAXV],V2[MAXV],n,m; 
int count=0;
bool Cond(int path[],int d)			//判断条件
{
	int flag1=0,f1,flag2=0,f2,i,j;
	for (i=0;i<n;i++)		//判断路径中是否有必经点
	{
		f1=1;
		for (j=0;j<=d;j++)
			if (path[j]==V1[i])
			{
				f1=0;break;
			}
		flag1+=f1;
	}

	for (i=0;i<m;i++)		//判断路径中是否有必避点
	{
		f2=0;
		for (j=0;j<=d;j++)
			if (path[j]==V2[i])
			{
				f2=1;break;
			}
		flag2+=f2;
	}
	if (flag1==0 && flag2==0)	//满足条件返回true
		return true;
	else						//不满足条件返回false
		return false;
}
void TravPath(ALGraph *G,int vi,int vj,int d)
{
	int v,i;
	ArcNode *p;
	visited[vi]=1;
	d++;
	path[d]=vi;
	if (vi==vj && Cond(path,d))
	{
		printf("  路径%d: ",++count);
		for (i=0;i<d;i++)
			printf("%d->",path[i]);
		printf("%d\n",path[i]);
	}
    p=G->adjlist[vi].firstarc;      //找vi的第一个邻接顶点
	while (p!=NULL)
	{
		v=p->adjvex;                //v为vi的邻接顶点
		if (visited[v]==0)          //若该顶点未标记访问,则递归访问之
			TravPath(G,v,vj,d);
		p=p->nextarc;               //找vi的下一个邻接顶点
	}
	visited[vi]=0;                  //取消访问标记,以使该顶点可重新使用
	d--;
}
void MatToList(MGraph g,ALGraph *&G)
//将邻接矩阵g转换成邻接表G
{
	int i,j;
	ArcNode *p;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	for (i=0;i<g.n;i++)					//给邻接表中所有头节点的指针域置初值
		G->adjlist[i].firstarc=NULL;
	for (i=0;i<g.n;i++)					//检查邻接矩阵中每个元素
		for (j=g.n-1;j>=0;j--)
			if (g.edges[i][j]!=0)		//邻接矩阵的当前元素不为0
			{   
			   	p=(ArcNode *)malloc(sizeof(ArcNode));	//创建一个节点*p
				p->adjvex=j;
				p->nextarc=G->adjlist[i].firstarc;		//将*p链到链表后
				G->adjlist[i].firstarc=p;
			}
	G->n=g.n;G->e=g.e;
}
void DispAdj(ALGraph *G)	//输出邻接表G
{
	int i;
	ArcNode *p;
	for (i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		printf("%3d: ",i);
		while (p!=NULL)
		{
			printf("%3d",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
}
void main()
{ 
	int i,j,u,v;
	MGraph g;
	ALGraph *G;
	int A[MAXV][15]={
		{0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
		{0,1,0,1,0,0,0,1,0,1,0,0,0,0,0},
		{0,0,0,0,1,0,1,0,0,0,1,1,0,0,0},
		{0,1,0,0,0,1,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,1,1,0,0,0,1,0,1,0,0},
		{0,0,0,0,0,0,0,1,0,1,0,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,1,1,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0}};
	g.n=15;g.e=21;
	for (i=0;i<g.n;i++)	
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);
	printf("图G的邻接表:\n");
	DispAdj(G);
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("输入起点和终点:");
	scanf("%d%d",&u,&v);
	printf("输入必经点个数:");
	scanf("%d",&n);
	printf("输入必经点集合:");
	for (i=0;i<n;i++)
		scanf("%d",&V1[i]);
	printf("输入必避点个数:");
	scanf("%d",&m);
	printf("输入必避点集合:");
	for (i=0;i<m;i++)
		scanf("%d",&V2[i]);
	printf("\n所有的探宝路径如下:\n");
    TravPath(G,u,v,-1);
}