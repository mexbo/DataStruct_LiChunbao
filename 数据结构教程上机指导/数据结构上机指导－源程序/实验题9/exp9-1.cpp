//文件名:exp9-1.cpp
#include <stdio.h>
#define MAXL 100					//定义表中最多记录个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct 
{	
	KeyType key;                		//KeyType为关键字的数据类型
    InfoType data;              		//其他数据
} NodeType;
typedef NodeType SeqList[MAXL];			 //顺序表类型
int SeqSearch(SeqList R,int n,KeyType k) //顺序查找算法

{
    int i=0;
    while (i<n && R[i].key!=k) 
	{
		printf("%d ",R[i].key);
		i++;					//从表头往后找
	}
    if (i>=n) 
		return -1;
    else 
	{
		printf("%d",R[i].key);
		return i;
	}
}
void main()
{
	SeqList R;
	int n=10,i;
	KeyType k=5;
	int a[]={3,6,2,10,1,8,5,7,4,9};
	for (i=0;i<n;i++)				//建立顺序表
		R[i].key=a[i];
	printf("关键字序列:");
	for (i=0;i<n;i++)
		printf("%d ",R[i].key);
	printf("\n");
	printf("查找%d所比较的关键字:\n\t",k);
	if ((i=SeqSearch(R,n,k))!=-1)
		printf("\n元素%d的位置是%d\n",k,i);
	else
		printf("\n元素%d不在表中\n",k);
	printf("\n");
}
