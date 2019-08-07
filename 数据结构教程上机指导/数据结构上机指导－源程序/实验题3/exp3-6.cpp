//文件名:exap3-6.cpp
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
int cont=0;			//记录解个数
typedef struct
{	
	int col[MaxSize];	//col[i]存放第i个皇后的列号
	int top;			//栈顶指针
} StType;				//定义顺序栈类型
int count=0;
bool place(StType st,int i,int j)  //测试(i,j)是否与1～i-1皇后有冲突
{
	int k=1;
	if (i==1) return true;	//放第一个皇后时没有冲突
	while (k<=i-1)			//j=1到k-1是已放置了皇后的列
	{
		if ((st.col[k]==j)  
			|| (abs(j-st.col[k])==abs(k-i)))
			return false;
		k++;
	}
	return true;
}
void queen(int n)					//求解n皇后问题
{
	int i,j,k;
	bool find;
	StType st;						//定义栈st
	st.top=0;						//初始化栈顶指针
	st.top++;						//将(1,1)进栈
	st.col[st.top]=1;
	while (st.top>0)				//栈不空时循环
	{
		i=st.top;					//当前皇后为第i个皇后
		if (st.top==n)				//所有皇后均放好,输出一个解
		{
			printf("  第%d个解：",++count);
			for (k=1;k<=st.top;k++)
				printf("(%d,%d) ",k,st.col[k]);
			printf("\n");
		}
		find=false;
		for (j=1;j<=n;j++)
			if (place(st,i+1,j))	//在i+1行找到一个放皇后的位置(i+1,j)
			{
				st.top++;
				st.col[st.top]=j;
				find=true;
				break;
			}
		if (find==false)			//在i+1行找不到放皇后的位置,回溯
		{
			while (st.top>0)
			{
				if (st.col[st.top]==n)	//本行没有可放位置,退栈
					st.top--;
				for (j=st.col[st.top]+1;j<=n;j++)	//在本行找下一个位置
					if (place(st,st.top,j))
					{
						st.col[st.top]=j;
						break;
					}
				if (j>n)				//当前皇后在本行没有可放的位置
					st.top--;			//退栈
				else					//本行找到一个位置后退出回溯
					break;
			}
		}
	}
}

void main()
{
	int n;						//n存放实际皇后个数
	printf(" 皇后问题(n<20) n=");
	scanf("%d",&n);
	if (n>20)
		printf("n值太大,不能求解\n");
	else
	{	printf(" %d皇后问题求解如下：\n",n);
		queen(n);
		printf("\n");
	}
}

