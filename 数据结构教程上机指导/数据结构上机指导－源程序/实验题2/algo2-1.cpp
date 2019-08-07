//文件名:algo2-1.cpp*/
#include <stdio.h>
#include <malloc.h>
#define MaxSize 50
typedef char ElemType;
typedef struct 
{
	ElemType data[MaxSize];
   	int length;
} SqList;
void InitList(SqList *&L)	//初始化线性表
{
	L=(SqList *)malloc(sizeof(SqList));	//分配存放线性表的空间
	L->length=0;						//置空线性表长度为0
}
void DestroyList(SqList *L)		//销毁线性表
{
	free(L);
}
bool ListEmpty(SqList *L)	//判线性表是否为空表
{
	return(L->length==0);
}
int ListLength(SqList *L)	//求线性表的长度
{
	return(L->length);
}
void DispList(SqList *L)	//输出线性表
{
	int i;
	if (ListEmpty(L)) return;
	for (i=0;i<L->length;i++)
		printf("%c ",L->data[i]);
	printf("\n");
}
bool GetElem(SqList *L,int i,ElemType &e)	//求线性表中某个数据元素值
{
	if (i<1 || i>L->length)
		return false;			//参数错误时返回false
	e=L->data[i-1];				//取元素值
	return true;				//成功找到元素时返回true
}
int LocateElem(SqList *L, ElemType e)	//按元素值查找
{
	int i=0;
	while (i<L->length && L->data[i]!=e)
		i++;					//查找元素e
	if (i>=L->length)			//未找到时返回0
		return 0;
	else
		return i+1;				//找到后返回其逻辑序号
}

bool ListInsert(SqList *&L,int i,ElemType e)	//插入数据元素
{
	int j;
	if (i<1 || i>L->length+1)
		return false;			//参数错误时返回false
	i--;						//将顺序表逻辑序号转化为物理序号
	for (j=L->length;j>i;j--)	//将data[i]及后面元素后移一个位置
		L->data[j]=L->data[j-1];
	L->data[i]=e;				//插入元素e
	L->length++;				//顺序表长度增1
	return true;				//成功插入返回true
}
bool ListDelete(SqList *&L,int i,ElemType &e)	//删除数据元素
{
	int j;
	if (i<1 || i>L->length)		//参数错误时返回false
		return false;
	i--;						//将顺序表逻辑序号转化为物理序号
	e=L->data[i];
	for (j=i;j<L->length-1;j++)	//将data[i]之后的元素前移一个位置
		L->data[j]=L->data[j+1];
	L->length--;				//顺序表长度减1
	return true;				//成功删除返回true
}
