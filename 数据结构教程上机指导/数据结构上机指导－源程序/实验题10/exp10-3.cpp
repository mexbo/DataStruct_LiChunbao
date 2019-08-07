//文件名:exp10-3.cpp
#include <stdio.h>
#define MAXE 20			//线性表中最多元素个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct       	//记录类型
{	
	KeyType key;   		//关键字项
    InfoType data; 		//其他数据项,类型为InfoType
} RecType;
void BubbleSort(RecType R[],int n)	//冒泡排序算法
{
	int i,j,k;
	RecType temp;
	for (i=0;i<n-1;i++) 
	{	
		for (j=n-1;j>i;j--)	//比较,找出本趟最小关键字的记录
			if (R[j].key<R[j-1].key)   
			{	
				temp=R[j];  //R[j]与R[j-1]进行交换,将最小关键字记录前移
				R[j]=R[j-1];
				R[j-1]=temp;
			}
		printf("i=%d,冒出的最小关键字:%d,结果为: ",i,R[i].key);	//输出每一趟的排序结果
		for (k=0;k<n;k++)
			printf("%2d",R[k].key);
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
	printf("初始关键字: ");	//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%2d",R[k].key);
	printf("\n");
	BubbleSort(R,n);
	printf("最后结果:  ");	//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%2d",R[k].key);
	printf("\n");
}
