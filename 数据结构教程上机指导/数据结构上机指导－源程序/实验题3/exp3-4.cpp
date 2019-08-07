//文件名:exp3-4.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 5
typedef char ElemType;
typedef struct qnode
{
	ElemType data;
	struct qnode *next;
} QNode;
typedef struct
{
	QNode *front;
	QNode *rear;
} LiQueue;
extern void InitQueue(LiQueue *&q);
extern void DestroyQueue(LiQueue *&q);
extern bool QueueEmpty(LiQueue *q);
extern void enQueue(LiQueue *&q,ElemType e);
extern bool deQueue(LiQueue *&q,ElemType &e);
void main()
{
	ElemType e;
	LiQueue *q;
	printf("链队的基本运算如下:\n");
	printf("  (1)初始化链队q\n");
	InitQueue(q);
	printf("  (2)依次进链队元素a,b,c\n");
	enQueue(q,'a');
	enQueue(q,'b');
	enQueue(q,'c');
	printf("  (3)链队为%s\n",(QueueEmpty(q)?"空":"非空"));
	if (deQueue(q,e)==0) 
		printf("\t提示:队空,不能出队\n");
	else
		printf("  (4)出队一个元素%c\n",e);
	printf("  (5)依次进链队元素d,e,f\n");
	enQueue(q,'d');
	enQueue(q,'e');
	enQueue(q,'f');
	printf("  (6)出链队序列:");
	while (!QueueEmpty(q))
	{	deQueue(q,e);
		printf("%c ",e);
	}
	printf("\n");
	printf("  (7)释放链队\n");
	DestroyQueue(q);
}
