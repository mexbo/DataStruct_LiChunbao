//文件名:excise6.cpp
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>
#define MaxSize 50001
typedef int KeyType;
void initial(int R[],int low,int high)	//产生R[low..high中的随机数
{
	int i;
	srand((unsigned)time(NULL));
	for (i=low;i<high;i++)
		R[i]=rand()%99+1;
}
bool test(KeyType R[],int low,int high)	//验证排序结果的正确性
{
	int i;
	for (i=low;i<high-1;i++)
		if (R[i]>R[i+1])
			return false;
	return true;
}
void Difference(struct _timeb timebuf1,struct _timeb timebuf2)	//求时间差
{
	long s,ms;
	s=timebuf2.time-timebuf1.time;			//两时间相差的秒数
	ms=timebuf2.millitm-timebuf1.millitm;	//两时间相差的毫秒数
	if (ms<0)
	{
		s--;
		ms=1000+ms;
	}
	printf("%d秒%d毫秒",s,ms);
}
//-------直接插入排序----------
void InsertSort(KeyType R[],int n)
{
	int i,j;
	KeyType tmp;
	for (i=1;i<n;i++)
	{
		tmp=R[i];
		j=i-1;				//从右向左在有序区R[0..i-1]中找R[i]的插入位置
		while (j>=0 && tmp<R[j])
		{	R[j+1]=R[j];	//将关键字大于R[i]的元素后移
			j--;
		}
		R[j+1]=tmp;			//在j+1处插入R[i]
	}
}
void InsertSortTime()		//求直接插入排序的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("直接插入排序\t");
	initial(R,0,n-1);
	_ftime(&timebuf1);
	InsertSort(R,n);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,0,n-1))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
//------折半插入排序----------
void InsertSort1(KeyType R[],int n)
{
	int i,j,low,high,mid;
	int tmp;
	for (i=1;i<n;i++)
	{
		tmp=R[i];					//将R[i]保存到tmp中
		low=0;high=i-1;
		while (low<=high)			//在R[low..high]中折半查找有序插入的位置
		{
			mid=(low+high)/2;		//取中间位置
			if (tmp<R[mid])
				high=mid-1;			//插入点在左半区
			else
				low=mid+1;			//插入点在右半区
		}
		for (j=i-1;j>=high+1;j--)	//元素后移
			R[j+1]=R[j];
		R[high+1]=tmp;				//插入
	}
}
void InsertSort1Time()		//求折半插入排序的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("折半插入排序\t");
	initial(R,0,n-1);
	_ftime(&timebuf1);
	InsertSort1(R,n);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,0,n-1))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
//-----------希尔排序算法--------------
void ShellSort(KeyType R[],int n)
{
	int i,j,gap;
	KeyType tmp;
	gap=n/2;				//增量置初值
	while (gap>0)
	{	for (i=gap;i<n;i++) //对所有相隔gap位置的所有元素组采用直接插入排序
		{	tmp=R[i];
			j=i-gap;
			while (j>=0 && tmp<R[j])//对相隔gap位置的元素组进行排序
			{	R[j+gap]=R[j];
				j=j-gap;
			}
			R[j+gap]=tmp;
		}
		gap=gap/2;	//减小增量
	}
}
void ShellSortTime()		//求希尔排序算法的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("希尔排序\t");
	initial(R,0,n-1);
	_ftime(&timebuf1);
	ShellSort(R,n);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,0,n-1))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
//--------冒泡排序算法----------
void BubbleSort(KeyType R[],int n)
{
	int i,j;
	bool exchange;
	KeyType tmp;
	for (i=0;i<n-1;i++) 
	{
		exchange=false;
		for (j=n-1;j>i;j--)	//比较,找出最小关键字的元素
			if (R[j]<R[j-1])
			{	tmp=R[j];	//R[j]与R[j-1]进行交换,将最小关键字元素前移
				R[j]=R[j-1];
				R[j-1]=tmp;
				exchange=true;
			}
		if (!exchange)		//本趟没有发生交换，中途结束算法
			return;
	}
}
void BubbleSortTime()		//求冒泡排序算法的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("冒泡排序\t");
	initial(R,0,n-1);
	_ftime(&timebuf1);
	BubbleSort(R,n);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,0,n-1))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
//--------快速排序算法---------------
void QuickSort(KeyType R[],int s,int t)
{
	int i=s,j=t;
	KeyType tmp;
	if (s<t) 				//区间内至少存在两个元素的情况
	{
		tmp=R[s];			//用区间的第1个元素作为基准
		while (i!=j)		//从区间两端交替向中间扫描,直至i=j为止
		{
			while (j>i && R[j]>=tmp) 
				j--;		//从右向左扫描,找第1个小于tmp的R[j]
			R[i]=R[j];		//找到这样的R[j],R[i]和R[j]交换
			while (i<j && R[i]<=tmp) 
				i++;		//从左向右扫描,找第1个大于tmp的元素R[i]
			R[j]=R[i];		//找到这样的R[i],R[i]和R[j]交换
		}
		R[i]=tmp;
		QuickSort(R,s,i-1);	//对左区间递归排序
		QuickSort(R,i+1,t);	//对右区间递归排序
	}
}
void QuickSortTime()		//求快速排序算法的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("快速排序\t");
	initial(R,0,n-1);
	_ftime(&timebuf1);
	QuickSort(R,0,n-1);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,0,n-1))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
//---------直接选择排序
void SelectSort(KeyType R[],int n)
{	int i,j,k;
	KeyType tmp;
	for (i=0;i<n-1;i++)			//做第i趟排序
	{	k=i;
		for (j=i+1;j<n;j++)		//在当前无序区R[i..n-1]中选key最小的R[k]
			if (R[j]<R[k])
				k=j;			//k记下目前找到的最小关键字所在的位置
		if (k!=i)				//交换R[i]和R[k]
		{	tmp=R[i];
			R[i]=R[k];
			R[k]=tmp;
		}
	}
}
void SelectSortTime()		//求直接选择排序算法的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("直接选择排序\t");
	initial(R,0,n-1);
	_ftime(&timebuf1);
	SelectSort(R,n);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,0,n-1))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
//----------堆排序算法-------
void sift(KeyType R[],int low,int high)
{	
	int i=low,j=2*i;						//R[j]是R[i]的左孩子
	KeyType tmp=R[i];
	while (j<=high)
	{	if (j<high && R[j]<R[j+1]) 	//若右孩子较大,把j指向右孩子
			j++;
		if (tmp<R[j]) 
		{	R[i]=R[j];						//将R[j]调整到双亲节点位置上
			i=j;							//修改i和j值,以便继续向下筛选
			j=2*i;
		}
		else break;							//筛选结束
	}
	R[i]=tmp;								//被筛选节点的值放入最终位置
}
void HeapSort(KeyType R[],int n)
{
	int i;
	KeyType tmp;
	for (i=n/2;i>=1;i--)	//循环建立初始堆
		sift(R,i,n); 
	for (i=n;i>=2;i--)		//进行n-1趟完成推排序,每一趟堆排序的元素个数减1
	{
		tmp=R[1];			//将最后一个元素同当前区间内R[1]对换
		R[1]=R[i];
		R[i]=tmp;
		sift(R,1,i-1);		//筛选R[1]节点,得到i-1个节点的堆
	}
}
void HeapSortTime()			//求堆排序算法的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("堆 排 序\t");
	initial(R,1,n);
	_ftime(&timebuf1);
	HeapSort(R,n);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,1,n))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
//--------二路归并排序算法------------
void Merge(KeyType R[],int low,int mid,int high) 
{
	KeyType *R1;
	int i=low,j=mid+1,k=0; //k是R1的下标,i、j分别为第1、2段的下标
	R1=(KeyType *)malloc((high-low+1)*sizeof(KeyType));  //动态分配空间
	while (i<=mid && j<=high)		//在第1段和第2段均未扫描完时循环
		if (R[i]<=R[j])		//将第1段中的元素放入R1中
		{	R1[k]=R[i];
			i++;k++;
		}
		else						//将第2段中的元素放入R1中
		{	R1[k]=R[j];
			j++;k++; 
		}
	while (i<=mid)					//将第1段余下部分复制到R1
	{	R1[k]=R[i];
		i++;k++;
	}
	while (j<=high)					//将第2段余下部分复制到R1
	{	R1[k]=R[j];
		j++;k++;
	}
	for (k=0,i=low;i<=high;k++,i++) //将R1复制回R中
		R[i]=R1[k];
	free(R1);
}
void MergePass(KeyType R[],int length,int n)	//对整个数序进行一趟归并
{	int i;
	for (i=0;i+2*length-1<n;i=i+2*length)	//归并length长的两相邻子表
		Merge(R,i,i+length-1,i+2*length-1);
	if (i+length-1<n)					//余下两个子表,后者长度小于length
		Merge(R,i,i+length-1,n-1);		//归并这两个子表
}
void MergeSort(KeyType R[],int n)	//自底向上的二路归并算法
{	int length;
	for (length=1;length<n;length=2*length)//进行log2n趟归并
		MergePass(R,length,n);
}
void MergeSortTime()			//求二路归并排序算法的时间
{
	KeyType R[MaxSize];
	int n=50000;
	struct _timeb timebuf1,timebuf2;
	printf("二路归并排序\t");
	initial(R,0,n-1);
	_ftime(&timebuf1);
	MergeSort(R,n);
	_ftime(&timebuf2);
	Difference(timebuf1,timebuf2);
	if (test(R,0,n-1))
		printf("\t正确\n");
	else
		printf("\t错误\n");
}
void main()
{
	printf("随机产生50000个1-99的正整数,各种排序方法的比较\n");
	printf("------------------------------------------------\n");
	printf("排序方法         用时         结果验证\n");
	printf("------------------------------------------------\n");
	InsertSortTime();
	InsertSort1Time();
	ShellSortTime();
	BubbleSortTime();
	QuickSortTime();
	SelectSortTime();
	HeapSortTime();
	MergeSortTime();
	printf("------------------------------------------------\n");
}