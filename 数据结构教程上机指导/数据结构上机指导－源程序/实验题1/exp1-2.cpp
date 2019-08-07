//文件名：exp1-2.cpp
#include <stdio.h>
int func(int num)
{
	int s=0;
   	do
   	{   	
		s+=num%10;
		num/=10;
   	} while(num);
   	return(s);
}
void main()
{
	int n;
   	printf("输入一个整数:");
   	scanf("%d",&n);
   	printf("各位数字之和:%d\n",func(n));
	printf("\n");
}
