//文件名：exp1-1.cpp
#include <stdio.h>
#include <math.h>
bool prime(int n)					//判断正整数n是否为素数
{
	int i;
	for (i=2;i<=(int)sqrt(n);i++)
		if (n%i==0) 
			return false;			//若n不是素数,则退出并返回false
	return true;
}
void main()
{
	int n,i,j=0;					//j用于累计素数个数
	printf("n:");
	scanf("%d",&n);
	printf("小于等于%d的素数:\n",n);
	if (n>2)
	{	printf("%4d",2);
		j++;
	}
	for (i=3;i<=n;i+=2)
		if (prime(i))
		{	printf("%4d",i);
			if (j!=0 && ++j%10==0)	//每行最多显示10个素数
				printf("\n");
		}
	printf("\n");
}
