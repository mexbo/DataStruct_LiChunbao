//文件名:algo8-2.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
int visited[MAXV];						//全局数组
void DFS(ALGraph *G,int v) 
{
	ArcNode *p;
	visited[v]=1;                   	//置已访问标记
	printf("%3d",v); 					//输出被访问顶点的编号
	p=G->adjlist[v].firstarc;      		//p指向顶点v的第一条弧的弧头结点
	while (p!=NULL) 
	{	
		if (visited[p->adjvex]==0)		//若p->adjvex顶点未访问,递归访问它
			DFS(G,p->adjvex);    
		p=p->nextarc;              		//p指向顶点v的下一条弧的弧头结点
	}
}
void DFS1(ALGraph *G,int v)   //非递归深度优先算法
{
	ArcNode *p;
	ArcNode *St[MAXV];
	int top=-1,w,i;
    for (i=0;i<G->n;i++) 
		visited[i]=0;		//顶点访问标志均置成0
	printf("%3d",v);        //访问顶点v
	visited[v]=1;
	top++;                  //将顶点v的第一个相邻顶点进栈
	St[top]=G->adjlist[v].firstarc;
	while (top>-1)          //栈不空循环
	{
		p=St[top]; top--;   //出栈一个顶点作为当前顶点
		while (p!=NULL)     //查找当前顶点的第一个未访问的顶点
		{
			w=p->adjvex;
			if (visited[w]==0)
			{
				printf("%3d",w); //访问w
				visited[w]=1;
				top++;           //将顶点w的第一个顶点进栈
				St[top]=G->adjlist[w].firstarc;
				break;           //退出循环
			}
			p=p->nextarc;        //找下一个相邻顶点
		}
	}
	printf("\n");
}

void BFS(ALGraph *G,int v)  
{
	ArcNode *p;
	int queue[MAXV],front=0,rear=0;			//定义循环队列并初始化
	int visited[MAXV];            			//定义存放结点的访问标志的数组
	int w,i;
	for (i=0;i<G->n;i++) visited[i]=0;		//访问标志数组初始化
	printf("%3d",v); 						//输出被访问顶点的编号
	visited[v]=1;              				//置已访问标记
	rear=(rear+1)%MAXV;
	queue[rear]=v;             				//v进队
	while (front!=rear)       				//若队列不空时循环
	{	
		front=(front+1)%MAXV;
		w=queue[front];       				//出队并赋给w
		p=G->adjlist[w].firstarc; 			//找与顶点w邻接的第一个顶点
		while (p!=NULL) 
		{	
			if (visited[p->adjvex]==0) 		//若当前邻接顶点未被访问
			{	
				printf("%3d",p->adjvex);  	//访问相邻顶点
				visited[p->adjvex]=1;		//置该顶点已被访问的标志
				rear=(rear+1)%MAXV;			//该顶点进队
				queue[rear]=p->adjvex; 		
           	}
           	p=p->nextarc;              		//找下一个邻接顶点
		}
	}
	printf("\n");
}
