//文件名:exp8-3.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList(MGraph,ALGraph *&);	//以下外部函数在algo8-1.cpp中
extern void DispAdj(ALGraph *);
int visited[MAXV];
void DFSALL(ALGraph *G,int v,int path[],int d)  
{
	ArcNode *p;
	visited[v]=1;                   //置已访问标记
	path[d]=v;
	d++;
	if (d==G->n)					//如果已访问所有顶点，则输出访问序列
	{
		for (int k=0;k<d;k++)
			printf("%2d",path[k]);
		printf("\n");
	}
	p=G->adjlist[v].firstarc;      	//p指向顶点v的第一条弧的弧头结点
	while (p!=NULL) 
	{
		if (visited[p->adjvex]==0)	//若p->adjvex顶点未访问,递归访问它
			DFSALL(G,p->adjvex,path,d);    
		p=p->nextarc;              	//p指向顶点v的下一条弧的弧头结点
	}
	visited[v]=0;
}
void DFS(ALGraph *G,int v)
{	ArcNode *p;
	visited[v]=1;						//置已访问标记
	printf("%d  ",v);					//输出被访问顶点的编号
	p=G->adjlist[v].firstarc;			//p指向顶点v的第一个边节点
	while (p!=NULL)
	{	if (visited[p->adjvex]==0)		//若p->adjvex顶点未访问,递归访问它
			DFS(G,p->adjvex);
		p=p->nextarc;					//p指向顶点v的下一个边节点
	}
	visited[v]=0;
}
void main()
{
	int path[MAXV],i,j,v=1;
	MGraph g;
	ALGraph *G;
	g.n=5;g.e=8;
	int A[MAXV][MAXV]={
		{0,1,0,1,1},
		{1,0,1,1,0},
		{0,1,0,1,1},
		{1,1,1,0,1},
		{1,0,1,1,0}};	
	for (i=0;i<g.n;i++)				//建立《教程》中图8.1(a)的邻接矩阵
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	MatToList(g,G);
	for (i=0;i<g.n;i++) 			//visited数组置初值
		visited[i]=0;
	printf("图G的邻接表:\n");DispAdj(G);	//输出邻接表
	printf("从顶点%d出发的所有深度优先序列:\n",v);
	DFSALL(G,v,path,0);
	printf("\n");
}
