//文件名:exp8-2.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList1(MGraph,ALGraph *&);	//以下外部函数在algo8-1.cpp中
extern void DispAdj1(ALGraph *G);
extern void DFS(ALGraph *G,int v);			//以下外部函数在algo8-2.cpp中
extern void DFS1(ALGraph *G,int v);
extern void DFS2(ALGraph *G,int v);
extern void BFS(ALGraph *G,int v);
void main()
{
	int i,j;
	MGraph g;
	ALGraph *G;
	int A[MAXV][6]={
		{0,5,INF,7,INF,INF},
		{INF,0,4,INF,INF,INF},
		{8,INF,0,INF,INF,9},
		{INF,INF,5,0,INF,6},
		{INF,INF,INF,5,0,INF},
		{3,INF,INF,INF,1,0}};
	g.n=6;g.e=10;			//建立图8.1中有向带标图G的邻接矩阵
	for (i=0;i<g.n;i++)	
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList1(g,G);					//图G的邻接矩阵转换成邻接表
	printf("图G的邻接表:\n");
	DispAdj1(G);
	printf("从顶点0开始的DFS(递归算法):\n");
	DFS(G,0);printf("\n");
	printf("从顶点0开始的DFS(非递归算法):\n");
	DFS1(G,0);
	printf("从顶点0开始的BFS(非递归算法):\n");
	BFS(G,0);printf("\n");
}
