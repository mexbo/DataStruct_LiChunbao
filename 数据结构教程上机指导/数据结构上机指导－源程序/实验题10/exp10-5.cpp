//文件名:exp10-5.cpp
#include <stdio.h>
#define MAXE 20			//线性表中最多元素个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct       	//记录类型
{	
	KeyType key;   		//关键字项
    InfoType data; 		//其他数据项,类型为InfoType
} RecType;
void SelectSort(RecType R[],int n)	//直接选择排序算法
{
	int i,j,k,l;
	RecType temp;
	for (i=0;i<n-1;i++)    	 	//做第i趟排序
	{	
		k=i;
		for (j=i+1;j<n;j++)  	//在当前无序区R[i..n-1]中选key最小的R[k] 
			if (R[j].key<R[k].key)
				k=j;           	//k记下目前找到的最小关键字所在的位置
		if (k!=i)          		//交换R[i]和R[k] 
		{	
			temp=R[i];R[i]=R[k];R[k]=temp;  
		}
		printf(" i=%d,选择的关键字:%d,结果为:",i,R[i].key);
		for (l=0;l<n;l++)		//输出每一趟的排序结果
			printf("%2d",R[l].key);
		printf("\n");
	}
}
void main()
{
	int i,k,n=10,m=5;
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	RecType R[MAXE];
	for (i=0;i<n;i++)
		R[i].key=a[i];
	printf("初始关键字:");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%2d",R[k].key);
	printf("\n");
	SelectSort(R,n);
	printf("最后结果:");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%2d",R[k].key);
	printf("\n");
}
