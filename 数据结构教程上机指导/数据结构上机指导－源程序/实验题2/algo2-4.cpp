//文件名:algo2-4.cpp
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct LNode		//定义单链表结点类型
{
	ElemType data;
    struct LNode *next;
} LinkList;
void InitList(LinkList *&L)	//初始化线性表
{
	L=(LinkList *)malloc(sizeof(LinkList));	//创建头结点
	L->next=L;
}
void DestroyList(LinkList *&L)	//销毁线性表
{
	LinkList *p=L,*q=p->next;
	while (q!=L)
	{
		free(p);
		p=q;
		q=p->next;
	}
	free(p);
}
bool ListEmpty(LinkList *L)	//判空表
{
	return(L->next==L);
}
int ListLength(LinkList *L)	//求表长
{
	LinkList *p=L;
	int i=0;
	while (p->next!=L)
	{
		i++;
		p=p->next;
	}
	return(i);
}
void DispList(LinkList *L)	//输出线性表
{
	LinkList *p=L->next;
	while (p!=L)
	{
		printf("%c ",p->data);
		p=p->next;
	}
	printf("\n");
}
bool GetElem(LinkList *L,int i,ElemType &e)	//找指定位置的元素
{
	int j=0;
	LinkList *p;
	if (L->next!=L)		//单链表不为空表时
	{
		if (i==1)
		{
			e=L->next->data;
			return true;
		}
		else			//i不为1时
		{
			p=L->next;
			while (j<i-1 && p!=L)
			{
				j++;
				p=p->next;
			}
			if (p==L)
				return false;
			else
			{
				e=p->data;
				return true;
			}
		}
	}
	else				//空表返回false
		return false;
}
int LocateElem(LinkList *L,ElemType e)	//查找元素位置
{
	LinkList *p=L->next;
	int n=1;
	while (p!=L && p->data!=e)
	{
		p=p->next;
		n++;
	}
	if (p==L)
		return(0);
	else
		return(n);
}
bool ListInsert(LinkList *&L,int i,ElemType e)	//插入元素
{
	int j=0;
	LinkList *p=L,*s;
	if (p->next==L || i==1)		//原单链表为空表或i==1时
	{
		s=(LinkList *)malloc(sizeof(LinkList));	//创建新结点*s
		s->data=e;								
		s->next=p->next;		//将*s插入到*p之后
		p->next=s;
		return true;
	}
	else
	{
		p=L->next;
		while (j<i-2 && p!=L)
		{
			j++;
			p=p->next;
		}
		if (p==L)				//未找到第i-1个结点
			return false;
		else					//找到第i-1个结点*p
		{
			s=(LinkList *)malloc(sizeof(LinkList));	//创建新结点*s
			s->data=e;								
			s->next=p->next;						//将*s插入到*p之后
			p->next=s;
			return true;
		}
	}
}
bool ListDelete(LinkList *&L,int i,ElemType &e)	//删除元素
{
	int j=0;
	LinkList *p=L,*q;
	if (p->next!=L)					//原单链表不为空表时
	{
		if (i==1)					//i==1时
		{
			q=L->next;				//删除第1个结点
			e=q->data;
			L->next=q->next;
			free(q);
			return true;
		}
		else						//i不为1时
		{
			p=L->next;
			while (j<i-2 && p!=L)
			{
				j++;
				p=p->next;
			}
			if (p==L)				//未找到第i-1个结点
				return false;
			else					//找到第i-1个结点*p
			{
				q=p->next;			//q指向要删除的结点
				e=q->data;
				p->next=q->next;	//从单链表中删除*q结点
				free(q);			//释放*q结点
				return true;
			}
		}
	}
	else							//空表返回false
		return false;
}
