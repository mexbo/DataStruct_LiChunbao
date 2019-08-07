//文件名:exp2-5.cpp
#include <stdio.h>
typedef char ElemType;
typedef struct DNode	//定义循环双链表结点类型
{	
	ElemType data;
	struct DNode *prior,*next;
} DLinkList;
extern void InitList(DLinkList *&L);		//以下均为外部函数
extern void DestroyList(DLinkList *&L);
extern bool ListEmpty(DLinkList *L);
extern int ListLength(DLinkList *L);
extern void DispList(DLinkList *L);
extern bool GetElem(DLinkList *L,int i,ElemType &e);
extern int LocateElem(DLinkList *L,ElemType e);
extern bool ListInsert(DLinkList *&L,int i,ElemType e);
extern bool ListDelete(DLinkList *&L,int i,ElemType &e);
void main()
{
	DLinkList *h;
	ElemType e;
	printf("循环双链表的基本运算如下:\n");
	printf("  (1)初始化循环双链表h\n");
	InitList(h);
	printf("  (2)依次采用尾插法插入a,b,c,d,e元素\n");
	ListInsert(h,1,'a');
	ListInsert(h,2,'b');
	ListInsert(h,3,'c');
	ListInsert(h,4,'d');
	ListInsert(h,5,'e');
	printf("  (3)输出循环双链表h:");
	DispList(h);
	printf("  (4)循环双链表h长度=%d\n",ListLength(h));
	printf("  (5)循环双链表h为%s\n",(ListEmpty(h)?"空":"非空"));
	GetElem(h,3,e);
	printf("  (6)循环双链表h的第3个元素=%c\n",e);
	printf("  (7)元素a的位置=%d\n",LocateElem(h,'a'));
	printf("  (8)在第4个元素位置上插入f元素\n");
	ListInsert(h,4,'f');
	printf("  (9)输出循环双链表h:");
	DispList(h);
	printf("  (10)删除h的第3个元素\n");
    	ListDelete(h,3,e);
	printf("  (11)输出循环双链表h:");
	DispList(h);
	printf("  (12)释放循环双链表h\n");
	DestroyList(h);
}
