//文件名:exp10-7.cpp
#include <stdio.h>
#include <malloc.h>
#define MAXE 20			//线性表中最多元素个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct       	//记录类型
{	
	KeyType key;   		//关键字项
    InfoType data; 		//其他数据项,类型为InfoType
} RecType;
void Merge(RecType R[],int low,int mid,int high) 
//将两个有序表R[low..mid]和R[mid+1..high]归并为一个有序表R[low..high]中
{
	RecType *R1;
	int i=low,j=mid+1,k=0; //k是R1的下标,i、j分别为第1、2段的下标
	R1=(RecType *)malloc((high-low+1)*sizeof(RecType));  //动态分配空间
	while (i<=mid && j<=high)     	//在第1段和第2段均未扫描完时循环
		if (R[i].key<=R[j].key)    	//将第1段中的记录放入R1中
		{	
			R1[k]=R[i];
			i++;k++; 
		}
        else                       	//将第2段中的记录放入R1中
		{	
			R1[k]=R[j];
			j++;k++; 
		}
    while (i<=mid)          	   	//将第1段余下部分复制到R1
	{   	
		R1[k]=R[i];
		i++;k++; 
	}
    while (j<=high)                	//将第2段余下部分复制到R1
	{	
		R1[k]=R[j];
		j++;k++;  
	}
    for (k=0,i=low;i<=high;k++,i++) //将R1复制回R中
	    R[i]=R1[k];
} 
void MergePass(RecType R[],int length,int n)	//实现一趟归并
{
	int i;
	for (i=0;i+2*length-1<n;i=i+2*length) 	//归并length长的两相邻子表
		Merge(R,i,i+length-1,i+2*length-1);
    if (i+length-1<n)                		//余下两个子表,后者长度小于length
		Merge(R,i,i+length-1,n-1);  		//归并这两个子表
}
void MergeSort(RecType R[],int n)  //二路归并排序算法
{
	int length,k,i=1;						//i用于累计归并的趟数
	for (length=1;length<n;length=2*length)
	{
		MergePass(R,length,n);
		printf(" 第%d趟归并:",i++);		//输出每一趟的排序结果
		for (k=0;k<n;k++)
			printf("%4d",R[k].key);
		printf("\n");
	}
}
void main()
{
	int i,k,n=10;
	KeyType a[]={18,2,20,34,12,32,6,16,5,8};
	RecType R[MAXE];
	for (i=0;i<n;i++)
		R[i].key=a[i];
	printf("初始关键字:");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%4d",R[k].key);
	printf("\n");
	MergeSort(R,n);
	printf("最后结果:  ");			//输出初始关键字序列
	for (k=0;k<n;k++)
		printf("%4d",R[k].key);
	printf("\n");
}
