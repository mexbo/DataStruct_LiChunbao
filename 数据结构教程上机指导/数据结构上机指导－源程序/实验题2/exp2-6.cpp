//文件名:exp2-6.cpp
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct LNode	//定义单链表结点类型
{
	ElemType data;
    struct LNode *next;
} LinkList;
extern void DispList(LinkList *L);
extern void DestroyList(LinkList *&L);
void CreateListR(LinkList *&L,ElemType a[],int n) //尾插法建表
{
	LinkList *s,*r;int i;
	L=(LinkList *)malloc(sizeof(LinkList));	//创建头结点
	L->next=NULL;
	r=L;						//r始终指向终端结点,开始时指向头结点
	for (i=0;i<n;i++)
	{
		s=(LinkList *)malloc(sizeof(LinkList));//创建新结点
		s->data=a[i];
		r->next=s;				//将*s插入*r之后
		r=s;
	}
	r->next=NULL;				//终端结点next域置为NULL
}
void sort(LinkList *&L)		//单链表元素递增排序
{
	LinkList *p,*pre,*q;
	p=L->next->next;		//p指向L的第2个数据节点
	L->next->next=NULL;		//构造只含一个数据节点的有序表
	while (p!=NULL)
	{	q=p->next;			//q保存*p节点后继节点的指针
		pre=L;				//从有序表开头进行比较,pre指向插入*p的前驱节点
		while (pre->next!=NULL && pre->next->data<p->data)
			pre=pre->next;	//在有序表中找插入*p的前驱节点*pre
		p->next=pre->next;	//将*pre之后插入*p
		pre->next=p;
		p=q;				//扫描原单链表余下的节点
	}
}

void Union(LinkList *ha,LinkList *hb,LinkList *&hc)  //求两有序集合的并
{
	LinkList *pa=ha->next,*pb=hb->next,*s,*tc;
	hc=(LinkList *)malloc(sizeof(LinkList));	//创建头结点
	tc=hc;
	while (pa!=NULL && pb!=NULL)
	{
		if (pa->data<pb->data)
		{
			s=(LinkList *)malloc(sizeof(LinkList));	//复制结点
			s->data=pa->data;
			tc->next=s;tc=s;
			pa=pa->next;
		}
		else if (pa->data>pb->data)
		{
			s=(LinkList *)malloc(sizeof(LinkList));	//复制结点
			s->data=pb->data;
			tc->next=s;tc=s;
			pb=pb->next;
		}
		else
		{
			s=(LinkList *)malloc(sizeof(LinkList));	//复制结点
			s->data=pa->data;
			tc->next=s;tc=s;
			pa=pa->next;	//重复的元素只复制一个
			pb=pb->next;
		}
	}
	if (pb!=NULL) pa=pb;	//复制余下的结点
	while (pa!=NULL)
	{
		s=(LinkList *)malloc(sizeof(LinkList));	//复制结点
		s->data=pa->data;
		tc->next=s;tc=s;
		pa=pa->next;
	}
	tc->next=NULL;
}
void InterSect(LinkList *ha,LinkList *hb,LinkList *&hc)	//求两有序集合的差
{
   LinkList *pa=ha->next,*pb,*s,*tc;
   hc=(LinkList *)malloc(sizeof(LinkList));
   tc=hc;
   while (pa!=NULL)
   {
	   pb=hb->next;
	   while (pb!=NULL && pb->data<pa->data)  
		   pb=pb->next; 
	   if (pb!=NULL && pb->data==pa->data)			//若pa结点值在B中
	   {
		   s=(LinkList *)malloc(sizeof(LinkList));	//复制结点
		   s->data=pa->data;
		   tc->next=s;tc=s;
	   }
	   pa=pa->next;
   }
   tc->next=NULL;
}
void Subs(LinkList *ha,LinkList *hb,LinkList *&hc)	//求两有序集合的差
{
   LinkList *pa=ha->next,*pb,*s,*tc;
   hc=(LinkList *)malloc(sizeof(LinkList));
   tc=hc;
   while (pa!=NULL)
   {
	   pb=hb->next;
	   while (pb!=NULL && pb->data<pa->data)  
		   pb=pb->next; 
	   if (!(pb!=NULL && pb->data==pa->data))		//若pa结点值不在B中
	   {
		   s=(LinkList *)malloc(sizeof(LinkList));	//复制结点
		   s->data=pa->data;
		   tc->next=s;tc=s;
	   }
	   pa=pa->next;
   }
   tc->next=NULL;
}
void main()
{
	LinkList *ha,*hb,*hc;
	ElemType a[]={'c','a','e','h'};
	ElemType b[]={'f','h','b','g','d','a'};
	printf("集合的运算如下:\n");
	CreateListR(ha,a,4);
	CreateListR(hb,b,6);
	printf("  原 集 合A: ");DispList(ha);
	printf("  原 集 合B: ");DispList(hb);
	sort(ha);
	sort(hb);
	printf("  有序集合A: ");DispList(ha);
	printf("  有序集合B: ");DispList(hb);
	Union(ha,hb,hc);
	printf("  集合的并C: ");DispList(hc);
	InterSect(ha,hb,hc);
	printf("  集合的交C: ");DispList(hc);
	Subs(ha,hb,hc);
	printf("  集合的差C: ");DispList(hc);
	DestroyList(ha);
	DestroyList(hb);
	DestroyList(hc);
}

