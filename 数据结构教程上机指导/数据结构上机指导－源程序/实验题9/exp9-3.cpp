//文件名:exp9-3.cpp
#include <stdio.h>
#define MAXL 100					//定义表中最多记录个数
#define MAXI 20						//定义索引表的最大长度
typedef int KeyType;
typedef char InfoType[10];
typedef struct 
{	
	KeyType key;                	//KeyType为关键字的数据类型
    InfoType data;              	//其他数据
} NodeType;
typedef NodeType SeqList[MAXL];		//顺序表类型
typedef struct 
{	
	KeyType key;					//KeyType为关键字的类型
	int link;						//指向分块的起始下标
} IdxType;
typedef IdxType IDX[MAXI];			//索引表类型

int IdxSearch(IDX I,int m,SeqList R,int n,KeyType k)	//分块查找算法
{
	int low=0,high=m-1,mid,i,count1=0,count2=0;
	int b=n/m;            	//b为每块的记录个数
	printf("二分查找\n");
	while (low<=high)    	//在索引表中进行二分查找,找到的位置存放在low中
	{	
		mid=(low+high)/2;
		printf("  第%d次比较:在[%d,%d]中比较元素R[%d]:%d\n",count1+1,low,high,mid,R[mid].key);
	    if (I[mid].key>=k)	
			high=mid-1;
	    else 
			low=mid+1;
		count1++;			//累计在索引表中的比较次数
	}
	if (low<m)             	//在索引表中查找成功后,再在线性表中进行顺序查找
	{	
		printf("比较%d次,在第%d块中查找元素%d\n",count1,low,k);
		i=I[low].link;
		printf("顺序查找:\n    ");
		while (i<=I[low].link+b-1 && R[i].key!=k)
		{ 
			i++;count2++; 
			printf("%d ",R[i].key);
		}			//count2累计在顺序表对应块中的比较次数
	    printf("\n");
		printf("比较%d次,在顺序表中查找元素%d\n",count2,k);
		if (i<=I[low].link+b-1) 
			return i;
	    else 
			return -1;
	}
	return -1;
}
void main()
{
	SeqList R;
	KeyType k=46;
	IDX I;
	int a[]={8,14,6,9,10,22,34,18,19,31,40,38,54,66,46,71,78,68,80,85,100,94,88,96,87},i;
	for (i=0;i<25;i++)				//建立顺序表
		R[i].key=a[i];
	I[0].key=14;I[0].link=0;
	I[1].key=34;I[1].link=4;
	I[2].key=66;I[2].link=10;
	I[3].key=85;I[3].link=15;
	I[4].key=100;I[4].link=20;
	if ((i=IdxSearch(I,5,R,25,k))!=-1)
		printf("元素%d的位置是%d\n",k,i);
	else
		printf("元素%d不在表中\n",k);
	printf("\n");
}
