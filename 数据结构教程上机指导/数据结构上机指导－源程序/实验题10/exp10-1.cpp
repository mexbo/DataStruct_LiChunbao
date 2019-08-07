//文件名:exp10-1.cpp
#include <stdio.h>
#define MAXE 20			//线性表中最多元素个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct       	//记录类型
{	
	KeyType key;   		//关键字项
	InfoType data; 		//其他数据项,类型为InfoType
} RecType;
void InsertSort(RecType R[],int n) //对R[0..n-1]按递增有序进行直接插入排序
{
	int i,j,k;
	RecType temp;
	for (i=1;i<n;i++) 
	{
		temp=R[i];
		j=i-1;           	//从右向左在有序区R[0..i-1]中找R[i]的插入位置
		while (j>=0 && temp.key<R[j].key) 
		{ 	
			R[j+1]=R[j];	//将关键字大于R[i].key的记录后移
			j--;
		}
        R[j+1]=temp;			//在j+1处插入R[i]
		printf("i=%d,",i);		//输出每一趟的排序结果
		printf("插入%d,结果为: ",temp);
		for (k=0;k<n;k++)
			printf("%3d",R[k].key);
		printf("\n");
	}
}
void main()
{
	int i,k,n=10;
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	RecType R[MAXE];
	for (i=0;i<n;i++)
		R[i].key=a[i];
	printf("初始关键字: ");		//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%3d",R[k].key);
	printf("\n");
	InsertSort(R,n);
	printf("最后结果: ");		//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%3d",R[k].key);
	printf("\n");
}
