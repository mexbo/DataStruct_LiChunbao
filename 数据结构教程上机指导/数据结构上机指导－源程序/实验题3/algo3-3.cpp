//文件名:algo3-3.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 5
typedef char ElemType;
typedef struct 
{
	ElemType data[MaxSize];
	int front,rear;		//队首和队尾指针
} SqQueue;
void InitQueue(SqQueue *&q)	//初始化队列
{	q=(SqQueue *)malloc (sizeof(SqQueue));
	q->front=q->rear=0;
}
void DestroyQueue(SqQueue *&q)	//销毁队列
{
	free(q);
}
bool QueueEmpty(SqQueue *q)	//判断队列空
{
	return(q->front==q->rear);
}
bool enQueue(SqQueue *&q,ElemType e)	//进队
{
	if ((q->rear+1)%MaxSize==q->front)	//队满上溢出
		return false;
	q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=e;
	return true;
}
bool deQueue(SqQueue *&q,ElemType &e)	//出队
{
	if (q->front==q->rear)		//队空下溢出
		return false;
	q->front=(q->front+1)%MaxSize;
	e=q->data[q->front];
	return true;
}

