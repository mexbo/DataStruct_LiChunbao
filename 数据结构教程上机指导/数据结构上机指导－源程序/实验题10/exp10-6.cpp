//文件名:exp10-6.cpp
#include <stdio.h>
#define MAXE 20			//线性表中最多元素个数
typedef int KeyType;
typedef char InfoType[10];
typedef struct       	//记录类型
{	
	KeyType key;   		//关键字项
    InfoType data; 		//其他数据项,类型为InfoType
} RecType;
int count=1;
void DispHeap(RecType R[],int i,int n)	//以括号表示法输出建立的堆
{
	if (i<=n)
		printf("%d",R[i].key);			//输出根结点
	if (2*i<=n || 2*i+1<n)
	{
		printf("(");
		if (2*i<=n)
			DispHeap(R,2*i,n);			//递归调用输出左子树
		printf(",");
		if (2*i+1<=n)
			DispHeap(R,2*i+1,n);		//递归调用输出右子树
		printf(")");
	}
}
void Sift(RecType R[],int low,int high)	//调整堆
{
	int i=low,j=2*i;     					//R[j]是R[i]的左孩子
	RecType temp=R[i];
	while (j<=high) 
	{	
		if (j<high && R[j].key<R[j+1].key) 	//若右孩子较大,把j指向右孩子
			j++;    						//变为2i+1
	    if (temp.key<R[j].key) 
		{	
			R[i]=R[j];              		//将R[j]调整到双亲结点位置上
		    i=j;                    		//修改i和j值,以便继续向下筛选
		    j=2*i;
		}
	    else break;                 		//筛选结束
	}
    R[i]=temp;                      		//被筛选结点的值放入最终位置
}
void HeapSort(RecType R[],int n)	//对R[1]到R[n]元素实现堆排序
{
	int i,j;
	RecType temp;
	for (i=n/2;i>=1;i--)  	//循环建立初始堆
		Sift(R,i,n); 
	printf("  初始堆:");DispHeap(R,1,n);printf("\n");	//输出初始堆
	for (i=n;i>=2;i--)   	//进行n-1次循环,完成推排序
	{  	
		printf("第%d趟排序:\n",count++);
		printf("  交换%d与%d,输出%d\n",R[i].key,R[1].key,R[1].key);
		temp=R[1];        	//将第一个元素同当前区间内R[1]对换
        R[1]=R[i];
        R[i]=temp;
		printf("  排序结果:");	//输出每一趟的排序结果
		for (j=1;j<=n;j++)
			printf("%2d",R[j].key);
		printf("\n");
        Sift(R,1,i-1);     	//筛选R[1]结点,得到i-1个结点的堆
		printf("筛选调整得到堆:");DispHeap(R,1,i-1);printf("\n");
	}
}
void main()
{
	int i,k,n=10;
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	RecType R[MAXE];
	for (i=1;i<=n;i++)
		R[i].key=a[i-1];
	printf("初始关键字: ");
	for (k=1;k<=n;k++)
		printf("%2d",R[k].key);
	printf("\n");
	for (i=n/2;i>=1;i--)  	//循环建立初始堆
		Sift(R,i,n); 
	HeapSort(R,n);
	printf("最终结果: ");	//输出最终结果
	for (k=1;k<=n;k++)
		printf("%d ",R[k].key);
	printf("\n");
}
