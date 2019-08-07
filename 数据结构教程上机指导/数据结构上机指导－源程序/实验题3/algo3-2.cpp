//文件名:algo3-2.cpp
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct linknode
{
	ElemType data;				//数据域
	struct linknode *next;		//指针域
} LiStack;
void InitStack(LiStack *&s)		//初始化栈s
{	s=(LiStack *)malloc(sizeof(LiStack));
	s->next=NULL;
}
void DestroyStack(LiStack *&s)	//销毁栈
{	LiStack *p=s,*q=s->next;
	while (q!=NULL)
	{	free(p);
		p=q;
		q=p->next;
	}
	free(p);	//此时p指向尾节点,释放其空间
}
bool StackEmpty(LiStack *s)	//判断栈是否为空
{
	return(s->next==NULL);
}
void Push(LiStack *&s,ElemType e)	//进栈
{	LiStack *p;
	p=(LiStack *)malloc(sizeof(LiStack));
	p->data=e;				//新建元素e对应的节点*p
	p->next=s->next;		//插入*p节点作为开始节点
	s->next=p;
}
bool Pop(LiStack *&s,ElemType &e)	//出栈
{	LiStack *p;
	if (s->next==NULL)		//栈空的情况
		return false;
	p=s->next;				//p指向开始节点
	e=p->data;
	s->next=p->next;		//删除*p节点
	free(p);				//释放*p节点
	return true;
}
bool GetTop(LiStack *s,ElemType &e)	//取栈顶元素
{	if (s->next==NULL)		//栈空的情况
		return false;
	e=s->next->data;
	return true;
}
