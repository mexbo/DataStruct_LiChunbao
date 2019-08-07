//文件名:exp10-2.cpp
#include <stdio.h>
#define MAXE 20			//线性表中最多元素个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct       	//记录类型
{
	KeyType key;		//关键字项
	InfoType data;		//其他数据项,类型为InfoType
} RecType;
void ShellSort(RecType R[],int n)	//希尔排序算法
{
	int i,j,d,k;
	RecType temp;
	d=n/2;					//d取初值n/2
	while (d>0) 
	{	
		for (i=d;i<n;i++)	//将R[d..n-1]分别插入各组当前有序区中
		{	
			j=i-d;
			while (j>=0 && R[j].key>R[j+d].key) 
			{	
				temp=R[j];      //R[j]与R[j+d]交换
				R[j]=R[j+d];
				R[j+d]=temp;
				j=j-d;
			}
		}
		printf("d=%d: ",d);	//输出每一趟的排序结果
		for (k=0;k<n;k++)
			printf("%3d",R[k].key);
		printf("\n");
        d=d/2;               //递减增量d
	}
}
void main()
{
	int i,k,n=10;
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	RecType R[MAXE];
	for (i=0;i<n;i++)
		R[i].key=a[i];
	printf("初始关键字: ");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%3d",R[k].key);
	printf("\n");
	ShellSort(R,n);
	printf("最后结果: ");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%3d",R[k].key);
	printf("\n\n");
}
