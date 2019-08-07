//文件名:exp4-5.cpp
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MaxSize 100
typedef struct
{	
	char data[MaxSize];
	int length;			//串长
} SqString;
extern void StrAssign(SqString &,char []); //在algo4-1.cpp文件中
extern void DispStr(SqString);
SqString *MaxSubstr(SqString s)
{
	SqString *sp;	
	int index=0,length=0,length1,i=0,j,k;
	while (i<s.length) 
	{
		j=i+1;
		while (j<s.length) 
		{
			if (s.data[i]==s.data[j]) //找一子串,其序号为i,长度为length1
			{
				length1=1;
				for(k=1;s.data[i+k]==s.data[j+k];k++)
					length1++;
				if (length1>length)    //将较大长度者赋给index与length
				{
					index=i;
					length=length1;
				}
				j+=length1;
			}
			else
				j++;
		}
		i++;                                 //继续扫描第i字符之后的字符
	}
	sp=(SqString *)malloc(sizeof(SqString));
	sp->length=length;
	for (i=0;i<length;i++)
		sp->data[i]=s.data[index+i];
	return sp;
}
void main()
{
	char str[MaxSize];
	SqString s,*sp;
	printf("输入串:");
	gets(str);
	StrAssign(s,str);			//创建串s
	sp=MaxSubstr(s);
	printf("求最长重复子串:\n");
	printf("    原串:");
	DispStr(s);
	printf("  最长重复子串:");	//输出最长重复子串
	DispStr(*sp);
}
