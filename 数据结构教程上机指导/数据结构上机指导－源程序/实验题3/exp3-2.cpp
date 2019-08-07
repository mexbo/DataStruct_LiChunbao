//文件名:exp3-2.cpp
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct linknode
{
	ElemType data;				//数据域
	struct linknode *next;		//指针域
} LiStack;
extern void InitStack(LiStack *&s);
extern void DestroyStack(LiStack *&s);
extern bool StackEmpty(LiStack *s);
extern void Push(LiStack *&s,ElemType e);
extern bool Pop(LiStack *&s,ElemType &e);
extern bool GetTop(LiStack *s,ElemType &e);
void main()
{
	ElemType e;
	LiStack *s;
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
