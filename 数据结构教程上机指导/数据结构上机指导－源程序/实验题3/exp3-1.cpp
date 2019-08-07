//文件名:exp3-1.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct 
{
	ElemType data[MaxSize];
	int top;		//栈顶指针
} SqStack;
extern void InitStack(SqStack *&s);
extern void DestroyStack(SqStack *&s);
extern bool StackEmpty(SqStack *s);
extern bool Push(SqStack *&s,ElemType e);
extern bool Pop(SqStack *&s,ElemType &e);
extern bool GetTop(SqStack *s,ElemType &e);
void main()
{
	ElemType e;
	SqStack *s;
	printf("栈s的基本运算如下:\n");
	printf("  (1)初始化栈s\n");
	InitStack(s);
	printf("  (2)栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("  (3)依次进栈元素a,b,c,d,e\n");
	Push(s,'a');
	Push(s,'b');
	Push(s,'c');
	Push(s,'d');
	Push(s,'e');
	printf("  (4)栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("  (5)出栈序列:");
	while (!StackEmpty(s))
	{
		Pop(s,e);
		printf("%c ",e);
	}
	printf("\n");
	printf("  (6)栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("  (7)释放栈\n");
	DestroyStack(s);
}
