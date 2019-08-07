//文件名:algo2-2.cpp
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct LNode	//定义单链表结点类型
{
	ElemType data;
    struct LNode *next;
} LinkList;
void InitList(LinkList *&L)		//初始化线性表
{
	L=(LinkList *)malloc(sizeof(LinkList));  	//创建头结点
	L->next=NULL;
}
void DestroyList(LinkList *&L)	//销毁线性表
{
	LinkList *p=L,*q=p->next;
	while (q!=NULL)
	{
		free(p);
		p=q;
		q=p->next;
	}
	free(p);
}
bool ListEmpty(LinkList *L)	//判线性表是否为空表
{
	return(L->next==NULL);
}
int ListLength(LinkList *L)	//求线性表的长度
{
	LinkList *p=L;int i=0;
	while (p->next!=NULL)
	{
		i++;
		p=p->next;
	}
	return(i);
}
void DispList(LinkList *L)	//输出线性表
{
	LinkList *p=L->next;
	while (p!=NULL)
	{
		printf("%c ",p->data);
		p=p->next;
	}
	printf("\n");
}
bool GetElem(LinkList *L,int i,ElemType &e)	//求线性表中某个数据元素值
{
	int j=0;
	LinkList *p=L;			//p指向头节点,j置为0(即头节点的序号为0)
	while (j<i && p!=NULL)	//找第i个节点
	{	j++;
		p=p->next;
	}
	if (p==NULL)			//不存在第i个数据节点,返回0
		return false;
	else					//存在第i个数据节点,返回1
	{	e=p->data;
		return true;
	}
}
int LocateElem(LinkList *L,ElemType e)	//按元素值查找
{	int i=1;
	LinkList *p=L->next;		//p指向开始节点,i置为1(即开始节点的序号为1)
	while (p!=NULL && p->data!=e)	//查找data值为e的节点,其序号为i
	{	p=p->next;
		i++;
	}
	if (p==NULL)				//不存在元素值为e的节点,返回0
		return(0);
	else						//存在元素值为e的节点,返回其逻辑序号i
		return(i);
}
bool ListInsert(LinkList *&L,int i,ElemType e)	//插入数据元素
{
	int j=0;
	LinkList *p=L,*s;			//p指向头节点,j置为0(即头节点的序号为0)
	while (j<i-1 && p!=NULL)	//查找第i-1个节点
	{	j++;
		p=p->next;
	}
	if (p==NULL)			//未找到第i-1个节点,返回false
		return false;
	else					//找到第i-1个节点*p,插入新节点并返回1
	{	s=(LinkList *)malloc(sizeof(LinkList));
		s->data=e;			//创建新节点*s,其data域置为e
		s->next=p->next;	//将*s插入到*p之后
		p->next=s;
		return true;
	}
}
bool ListDelete(LinkList *&L,int i,ElemType &e)	//删除数据元素
{
	int j=0;
	LinkList *p=L,*q;			//p指向头节点,j置为0(即头节点的序号为0)
	while (j<i-1 && p!=NULL)	//查找第i-1个节点
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//未找到第i-1个节点,返回false
		return false;
	else						//找到第i-1个节点*p
	{	q=p->next;				//q指向第i个节点
		if (q==NULL)			//若不存在第i个节点,返回false
			return false;
		e=q->data;
		p->next=q->next;		//从单链表中删除*q节点
		free(q);				//释放*q节点
		return true;			//返回true表示成功删除第i个节点
	}
}
