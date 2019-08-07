//文件名:exp8-8.cpp
#include <stdio.h>
#include "graph.h"
#define MAXE 100		//最多边数
typedef struct 
{	int u;				//边的起始顶点
    int v;				//边的终止顶点
    int w;				//边的权值		
} Edge;
extern void DispMat1(MGraph);		//外部函数在algo8-1.cpp中
void SortEdge(MGraph g,Edge E[])	//从邻接矩阵产生权值递增的边集
{
	int i,j,k=0;
	Edge temp;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
			if (g.edges[i][j]<INF)
			{
				E[k].u=i;
				E[k].v=j;
				E[k].w=g.edges[i][j];
				k++;
			}
	for (i=1;i<k;i++)	//按权值递增有序进行直接插入排序 
	{
		temp=E[i];
		j=i-1;			//从右向左在有序区E[0..i-1]中找E[i]的插入位置
		while (j>=0 && temp.w<E[j].w) 
		{ 	
			E[j+1]=E[j]; //将权值大于E[i].w的记录后移
			j--;
		}
		E[j+1]=temp;      //在j+1处插入E[i]
	}
}
void Kruskal(Edge E[],int n,int e)
{
	int i,j,m1,m2,sn1,sn2,k;
	int vset[MAXE];
	for (i=0;i<n;i++) vset[i]=i;	//初始化辅助数组
	k=1;                 			//k表示当前构造最小生成树的第几条边,初值为1
	j=0;                 			//E中边的下标,初值为0
	while (k<n)       				//生成的边数小于n时循环
	{	
		m1=E[j].u;m2=E[j].v;        //取一条边的头尾顶点
		sn1=vset[m1];sn2=vset[m2]; 	//分别得到两个顶点所属的集合编号
		if (sn1!=sn2)     			//两顶点属于不同的集合,该边是最小生成树的一条边
		{	
			printf("  (%d,%d):%d\n",m1,m2,E[j].w);
			k++;                    //生成边数增1
			for (i=0;i<n;i++)      	//两个集合统一编号
				if (vset[i]==sn2)  	//集合编号为sn2的改为sn1
				    vset[i]=sn1;
		}
		j++;   						//扫描下一条边
	}
}
void main()
{
	int i,j,u=3;
	MGraph g;
	Edge E[MAXE];
	int A[MAXV][MAXV]={{0,5,8,7,INF,3},
	{5,0,4,INF,INF,INF},
	{8,4,0,5,INF,9},
	{7,INF,5,0,5,INF},
	{INF,INF,INF,5,0,1},
	{3,INF,9,INF,1,0}};
	g.n=6;g.e=10;
	for (i=0;i<g.n;i++)		//建立图8.16的邻接矩阵
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	SortEdge(g,E);
	printf("图G的邻接矩阵:\n");
	DispMat1(g);
	printf("克鲁斯卡尔算法求解结果:\n");
	Kruskal(E,g.n,g.e);
	printf("\n");
}
