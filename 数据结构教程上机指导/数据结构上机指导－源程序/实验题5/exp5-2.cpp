//文件名:exp6-3.cpp
#include <stdio.h>
#define N 100
int limitw;  							//限制的总重量
int totv;  								//全部物品的总价
int maxv;
int option[N],cop[N];
struct
{
	int weight;							//物品重量
	int value;							//物品价值
} a[N];									//存放物品的数组
int n;     								//物品种数
void find(int i,int tw,int tv)
{
	int k;
	if (tw+a[i].weight<=limitw) 
	{
		cop[i]=1;
		if (i<n-1)
			find(i+1,tw+a[i].weight,tv);
		else 
		{
			for (k=0;k<n;k++)
				option[k]=cop[k];
			maxv=tv;
		}
		cop[i]=0;
	}
	if (tv-a[i].value>maxv)
	{
		if (i<n-1)
			find(i+1,tw,tv-a[i].value);
		else 
		{
			for (k=0;k<n;k++)
				option[k]=cop[k];
			maxv=tv-a[i].value;
		}
	}
}
void main()
{
	int k,w,v;
	printf("物品种数:");
	scanf("%d",&n);
	for (totv=0,k=0;k<n;k++) 
	{
		printf("  第%d种物品(重量,价值):",k+1);
		scanf("%d,%d",&w,&v);
		a[k].weight=w;
		a[k].value=v;
		totv+=v;
	}
	printf("背包所能承受的总重量:");
	scanf("%d",&limitw);
	maxv=0;
	for (k=0;k<n;k++)
		cop[k]=0;
	find(0,0,totv);
	printf("最佳装填方案是:\n");
	for (k=0;k<n;k++)
		if (option[k])
			printf("  第%d种物品\n",k+1);
	printf("总价值=%d\n",maxv);
}
