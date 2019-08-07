//文件名:exp3-5.cpp
#include <stdio.h>
#define M 4					//行数
#define N 4					//列数
#define MaxSize 100			//栈最多元素个数
int mg[M+2][N+2]={			//一个迷宫,其四周要加上均为1的外框
{1,1,1,1,1,1},
{1,0,0,0,1,1},
{1,0,1,0,0,1},
{1,0,0,0,1,1},
{1,1,0,0,0,1},
{1,1,1,1,1,1}
};
struct 
{
	int i,j;
	int di;
} Stack[MaxSize],Path[MaxSize];		//定义栈和存放最短路径的数组
int top=-1;							//栈顶指针
int count=1;						//路径数计数
int minlen=MaxSize;					//最短路径长度
void mgpath(int xi,int yi,int xe,int ye)		//求迷宫路径
{
	int i,j,di,find,k;
	top++;							//进栈
	Stack[top].i=xi;
	Stack[top].j=yi;
	Stack[top].di=-1;mg[xi][yi]=-1;	//初始方块进栈
	while (top>-1)					//栈不空时循环
	{
		i=Stack[top].i;j=Stack[top].j;di=Stack[top].di;
		if (i==xe && j==ye)			//找到了出口,输出路径
		{ 
			printf("%4d:   ",count++);
			for (k=0;k<=top;k++)
			{
				printf("(%d,%d)    ",Stack[k].i,Stack[k].j);
				if ((k+1)%5==0) printf("\n\t");		//输出时每5个方块换一行
			}
			printf("\n");
			if (top+1<minlen)						//比较找最短路径
			{
				for (k=0;k<=top;k++)
					Path[k]=Stack[k];
				minlen=top+1;
			}
			mg[Stack[top].i][Stack[top].j]=0;		//让该位置变为其他路径可走方块
			top--; 
			i=Stack[top].i;j=Stack[top].j;di=Stack[top].di;
		}
		find=0;
		while (di<4 && find==0)		//找下一个可走方块
		{	di++;
			switch(di)
			{
			case 0:i=Stack[top].i-1;j=Stack[top].j;break;
			case 1:i=Stack[top].i;j=Stack[top].j+1;break;
			case 2:i=Stack[top].i+1;j=Stack[top].j;break;
			case 3:i=Stack[top].i,j=Stack[top].j-1;break;
			}
			if (mg[i][j]==0) find=1;
		}
		if (find==1)				//找到了下一个可走方块
		{	Stack[top].di=di;		//修改原栈顶元素的di值
			top++;Stack[top].i=i;Stack[top].j=j;Stack[top].di=-1;//下一个可走方块进栈
			mg[i][j]=-1;			//避免重复走到该方块
		}
		else						//没有路径可走,则退栈
		{
			mg[Stack[top].i][Stack[top].j]=0;    //让该位置变为其他路径可走方块
			top--;
		}
	}
	printf("最短路径如下:\n");
	printf("长度:   %d\n",minlen);
	printf("路径:   ");
	for (k=0;k<minlen;k++)
	{
		printf("(%d,%d)   ",Path[k].i,Path[k].j);
		if ((k+1)%5==0) printf("\n\t");  //输出时每5个方块换一行
	}
	printf("\n");
}
void main()
{
	printf("迷宫所有路径如下:\n");
	mgpath(1,1,M,N);
}
