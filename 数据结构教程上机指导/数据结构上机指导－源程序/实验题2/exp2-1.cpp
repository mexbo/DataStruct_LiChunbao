//文件名:exp2-1.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 50
typedef char ElemType;
typedef struct 
{
	ElemType data[MaxSize];
   	int length;
} SqList;
extern void InitList(SqList *&L);
extern void DestroyList(SqList *L);
extern bool ListEmpty(SqList *L);
extern int ListLength(SqList *L);
extern void DispList(SqList *L);
extern bool GetElem(SqList *L,int i,ElemType &e);
extern int LocateElem(SqList *L, ElemType e);
extern bool ListInsert(SqList *&L,int i,ElemType e);
extern bool ListDelete(SqList *&L,int i,ElemType &e);
void main()
{
	SqList *L;
	ElemType e;
	printf("顺序表的基本运算如下:\n");
	printf("  (1)初始化顺序表L\n");
	InitList(L);
	printf("  (2)依次采用尾插法插入a,b,c,d,e元素\n");
	ListInsert(L,1,'a');
	ListInsert(L,2,'b');
	ListInsert(L,3,'c');
	ListInsert(L,4,'d');
	ListInsert(L,5,'e');
	printf("  (3)输出顺序表L:");
	DispList(L);
	printf("  (4)顺序表L长度=%d\n",ListLength(L));
	printf("  (5)顺序表L为%s\n",(ListEmpty(L)?"空":"非空"));
	GetElem(L,3,e);
	printf("  (6)顺序表L的第3个元素=%c\n",e);
	printf("  (7)元素a的位置=%d\n",LocateElem(L,'a'));
	printf("  (8)在第4个元素位置上插入f元素\n");
	ListInsert(L,4,'f');
	printf("  (9)输出顺序表L:");
	DispList(L);
	printf("  (10)删除L的第3个元素\n");
    	ListDelete(L,3,e);
	printf("  (11)输出顺序表L:");
	DispList(L);
	printf("  (12)释放顺序表L\n");
	DestroyList(L);
}
