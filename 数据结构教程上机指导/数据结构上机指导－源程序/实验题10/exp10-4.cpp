//文件名:exp10-4.cpp
#include <stdio.h>
#define MAXE 20			//线性表中最多元素个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct			//记录类型
{	
	KeyType key;		//关键字项
    InfoType data; 		//其他数据项,类型为InfoType
} RecType;
int n;
void QuickSort(RecType R[],int s,int t) //对R[s]至R[t]的元素进行快速排序
{
	int i=s,j=t,k;
	RecType temp;
	if (s<t) 					//区间内至少存在一个元素的情况
	{	
		temp=R[s];     			//用区间的第1个记录作为基准
        while (i!=j)  			//从区间两端交替向中间扫描,直至i=j为止
		{	
			while (j>i && R[j].key>temp.key) 
			    j--;  			//从右向左扫描,找第1个关键字小于temp.key的R[j]
			R[i]=R[j];
            while (i<j && R[i].key<temp.key) 
			    i++;			//从左向右扫描,找第1个关键字大于temp.key的记录R[i] 
			R[j]=R[i];
		}
		R[i]=temp;
		printf(" 划分区间为R[%d..%d],结果为:",s,t);	//输出每一趟的排序结果
		for (k=0;k<10;k++)
			if (k==i)
				printf(" [%d]",R[k].key);
			else
				printf("%4d",R[k].key);
		printf("\n");
		QuickSort(R,s,i-1);		//对左区间递归排序
		QuickSort(R,i+1,t);		//对右区间递归排序
	}
}
void main()
{
	int i,k;
	n=10;
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	RecType R[MAXE];
	for (i=0;i<n;i++)
		R[i].key=a[i];
	printf("初始关键字: ");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%4d",R[k].key);
	printf("\n");
	QuickSort(R,0,n-1);
	printf("最后结果:  ");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%4d",R[k].key);
	printf("\n");
}
