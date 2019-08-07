//文件名:excise2.cpp
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXNAME 7			//标识符中的最多字符个数
#define MAXPRIORITY 6		//最大的运算符优先级
#define MAXTOKEN 100		//最大的标识符个数
#define MAXSTACK 100		//栈大小
#define MAXSTRING 101		//表达式中最多的字符个数
#define HASHSIZE 101		//哈希表的大小
#define LASTOPERAND 17		//最后一个运算数的下标
typedef double Value_type;
typedef enum kind_tag {UNARYOP,BINARYOP,OPERAND,LEFTPAREN,RIGHTPAREN,ENDEXPR} Kind_type;
typedef struct
{
	char name[MAXNAME];		//标识符名
	Kind_type kind;			//标识符类型
	union 
	{	
		int pri;			//优先级
		Value_type val;		//值
	} info;
} Token_type;
Token_type lexicon[MAXTOKEN]={	//标识符表
	{"#",ENDEXPR},			//0:结束符
	{"(",LEFTPAREN},		//1:左括号
	{")",RIGHTPAREN},		//2:右括号
	{"~",UNARYOP,6},		//3:负号
	{"abs",UNARYOP,6},		//4:求绝对值
	{"sqrt",UNARYOP,6},		//5:求平方根
	{"exp",UNARYOP,6},		//6:求ex
	{"ln",UNARYOP,6},		//7:求log2
	{"log10",UNARYOP,6},	//8:求log10
	{"sin",UNARYOP,6},		//9:求sin
	{"cos",UNARYOP,6},		//10:求cos
	{"tanh",UNARYOP,6},		//11:求tanh
	{"+",BINARYOP,4},		//12:二元"+"
	{"-",BINARYOP,4},		//13:二元"-"
	{"*",BINARYOP,5},		//14:二元"*"
	{"/",BINARYOP,5},		//15:二元"/"
	{"%",BINARYOP,5},		//16:二元"%"
	{"^",BINARYOP,6}};		//17:二元"^"
int hashtable[MAXTOKEN];	//哈希表
int infix[MAXTOKEN];		//存放中缀表达式
int postfix[MAXTOKEN];		//存放后缀表达式
int inlength;				//扫描infix表达式的指针
int postlength;				//扫描postfix表达式的指针
int parencount;				//表达式中括号个数
int tokencount;				//lexicon[]中的标识符个数
int Hash(char *name)		//在哈希表中查找name的下标
{
	int h=name[0] % HASHSIZE;
	while (1)
	{
		if (hashtable[h]==-1)
			break;
		else if (strcmp(lexicon[hashtable[h]].name,name)==0)
			break;		//name在哈希表中
		else
		{
			if (name[1]=='\0')
				h+=31;
			else
				h+=name[1];
			h%=HASHSIZE;	//找另一个位置
		}
	}
	return abs(h);
}
void MakeHashTable()	//构造哈希表
{
	int i;
	for (i=0;i<HASHSIZE;i++)		//置初值
		hashtable[i]=-1;
	for (i=1;i<=LASTOPERAND;i++)
		hashtable[Hash(lexicon[i].name)]=i;
}
Kind_type Kind(int h)	//返回lexicon[h]的类型
{
	return(lexicon[h].kind);
}
int Priority(int h)		//返回lexicon[h]的优先级
{
	return(lexicon[h].info.pri);
}
int Leading()	//判断是否为开头位置
{
	int k;
	if (inlength<=-1)
		return 1;
	else
		return (k=Kind(infix[inlength]))==LEFTPAREN || k==UNARYOP || k==BINARYOP;
}
void PutToken(int h)	//将lexicon中的下标h添加到infix中
{
	inlength++;
	infix[inlength]=h;
}
void PutToken1(int h)	//将lexicon中的下标h添加到postfix中
{
	postlength++;
	postfix[postlength]=h;
}
int ExtractWord(char str[],int pos,char *word)	//从str[]的pos处提取一个单词
{
	int i;
	char *pw=word;
	for (i=pos;isalpha(str[i]) || isdigit(str[i]);i++) //当前字符为字母或数字时
		*pw++=tolower(str[i]);		//转化为小写字母后添加到word中
	*pw='\0';
	return i;
}
int FindWord(char str[],int pos)	//找到一个单词,进行相应的处理
{
	int h;
	char word[MAXTOKEN];
	pos=ExtractWord(str,pos,word);
	h=hashtable[Hash(word)];
	if (h!=-1)	//在哈希表中找到时
	{
		if (Leading()==1)
		{
			if (Kind(h)==BINARYOP)
			{
				printf("二元运算符位置不正确\n");
				return -1;
			}
			else
				PutToken(h);
		}
		else
		{
			if (Kind(h)!=BINARYOP)
			{
				printf("应为二元运算符\n");
				return -1;
			}
			else
				PutToken(h);
		}
		return pos;
	}
	else	//h==-1时
	{
		printf("  >>不正确的标识符\n");
		return -1;
	}
}
int FindNumber(char str[],int pos)	//找到一个操作数,进行相应的处理
{
	if (Leading()==0)
	{
		printf("常量位置不正确\n");
		return -1;
	}
	else	//将当前识别的操作数添加到lexicon表中
	{
		lexicon[++tokencount].kind=OPERAND;
		lexicon[tokencount].info.val=atof(&str[pos]);	//将该操作数串转换成数值
		strcpy(lexicon[tokencount].name,"number");
		PutToken(tokencount);							//将lexicon中对应的下标添加到infix中
		for (;isdigit(str[pos]) || str[pos]=='.';pos++); //扫描完该操作数
		return pos;
	}
}
int FindSymbol(char str[],int pos)	//找到一个符号或括号,进行相应的处理
{
	int h,k;
	char word[MAXTOKEN];
	word[0]=str[pos];
	word[1]='\0';
	pos++;
	if ((h=hashtable[Hash(word)])==-1)	//在lexicon中找不到该符号
	{
		printf("表达式中存在不能识别的符号\n");
		return -1;
	}
	else if (Leading()==1)				//若之前有"("、一元或二元运算符
	{
		if (Kind(h)==RIGHTPAREN)		//当前符号为")"
		{
			printf("不应为右括号\n");
			return -1;
		}
		else if (Kind(h)!=BINARYOP)		//当前符号不为二元运算符,将其添加到infix中
			PutToken(h);
		else		//当前符号为二元运算符
		{
			if (strcmp(word,"+")==0);		//为"+"时,应是一元"+",不做任何事件
			else if (strcmp(word,"-")==0)	//为"-"时,应是一元"-",将"~"添加到infix中
				PutToken(hashtable[Hash("~")]);
			else		//其他二元运算符为非法
			{
				printf("  >>二元运算符不正确\n");
				return -1;
			}
		}
	}
	else			//当Leading()=0时
	{
		if (Kind(h)==BINARYOP || Kind(h)==RIGHTPAREN) //将二元运算符或")"添加到infix中
			PutToken(h);
		else
		{
			printf("二元运算符不正确\n");
			return -1;
		}
	}
	if ((k=Kind(h))==LEFTPAREN)
		parencount++;
	else if (k==RIGHTPAREN)
		if (--parencount<0)		//左、右括号不匹配
		{
			printf("太多的右括号\n");
			return -1;
		}
	return pos;
}
void GetToken(int &h)	//从infix中取一个标识符
{
	inlength++;
	h=infix[inlength];
}
void GetToken1(int &h)	//从postfix中取一个标识符
{
	postlength++;
	h=postfix[postlength];
}
void Translate()		//将中缀表达式infix转换成后缀表达式postfix
{
	int St[MAXSTACK];int top=-1;		//定义栈及栈指针
	int h,h1;
	Kind_type type;
	postlength=-1;
	inlength=-1;
	int endright;	//取1或0.1:表示一个运算符处理完毕(需考虑优先级)
	do
	{
		GetToken(h);
		switch(type=Kind(h))
		{
		case OPERAND:		//为运算符,直接添加到postfix中
			PutToken1(h);
			break;
		case LEFTPAREN:		//为"(",将其进栈
			top++;
			St[top]=h;
			break;
		case RIGHTPAREN:	//为")",出栈运算符添加到postfix中直到遇到"("
			h=St[top];top--;
			while (top>-1 && Kind(h)!=LEFTPAREN)
			{
				PutToken1(h);
				h=St[top];top--;
			}
			break;
		case UNARYOP:		//为一元或二元运算符
		case BINARYOP:
			endright=0;
			do
			{
				if (top==-1)	//栈空
					endright=1;
				else if (Kind(St[top])==LEFTPAREN)
					endright=1;
				else if (Priority(St[top])<Priority(h))
					endright=1;
				else if (Priority(St[top])==Priority(h) && Priority(h)==MAXPRIORITY)
					endright=1;
				else
				{
					h1=h;		//将当前h放在当前高优先运算符的后面
					endright=0;
					h=St[top];top--;
					PutToken1(h);
					h=h1;
				}
			} while (endright==0);
			top++;St[top]=h;
			break;
		case ENDEXPR:
			while (top>-1)
			{
				h=St[top];top--;
				PutToken1(h);
			}
			break;
		}
	} while (type!=ENDEXPR);
	PutToken1(0);	//在postfix中添加ENDEXPR
}
int ProcessExpress(char *instring) //对原表达式进行预处理
{
	int len,pos;
	inlength=-1;
	parencount=0;
	tokencount=LASTOPERAND;
	len=strlen(instring);
	instring[len]='\0';
	for (pos=0;pos<len;)
	{
		if (instring[pos]==' ')				//忽略空格字符
			pos++;
		else if (isalpha(instring[pos]))	//处理字母
			pos=FindWord(instring,pos);
		else if (isdigit(instring[pos]) || instring[pos]=='.') //处理数字
			pos=FindNumber(instring,pos);
		else			//处理符号
			pos=FindSymbol(instring,pos);
		if (pos==-1)
			return 0;
	}
	if (parencount!=0)
		printf("左右括号不匹配\n");
	PutToken(0);	//在infix中添加ENDEXPR
	return 1;
}
void DispInfix()	//输出中缀表达式
{
	int i;
	printf(" 中缀表达式(变换前):");
	for (i=0;i<=inlength;i++)
	{
		if (strcmp(lexicon[infix[i]].name,"number")==0)
			printf("%g ",lexicon[infix[i]].info.val);
		else
			printf("%s ",lexicon[infix[i]].name);
	}
	printf("\n");
	printf(" 中缀表达式(变换后):");
	for (i=0;i<=inlength;i++)
		printf("%d ",infix[i]);
	printf("\n");
}
void DispPostfix()	//输出后缀表达式
{
	int i;
	printf(" 后缀表达式(变换前):");
	for (i=0;i<=postlength;i++)
	{
		if (strcmp(lexicon[postfix[i]].name,"number")==0)
			printf("%g ",lexicon[postfix[i]].info.val);
		else
			printf("%s ",lexicon[postfix[i]].name);
	}
	printf("\n");
	printf(" 后缀表达式(变换后):");
	for (i=0;i<=postlength;i++)
		printf("%d ",postfix[i]);
	printf("\n");
}
Value_type DoBinary(int h,Value_type x,Value_type y)  //进行二元运算
{
	switch(h)
	{
	case 12:			//加
		return(x+y);
	case 13:			//减
		return(x-y);
	case 14:			//乘
		return(x*y);
	case 15:			//除
		if (y!=(Value_type)0)
			return(x/y);
		else
		{
			printf("  >>除零错误\n");
			break;
		}
	case 16:			//%
		if (y!=(Value_type)0)
			return(fmod(x,y));
		else
		{
			printf("  >>除零错误\n");
			break;
		}
	case 17:			//^
		return(pow(x,y));
	default:			//其他
		printf("  >>%d是无效的二元运算符\n",h);
		break;
	}
}
Value_type DoUnary(int h,Value_type x) //进行一元运算
{
	switch(h)
	{
	case 3:					//-
		return(-x);
	case 4:					//求绝对值
		return(abs(x));
	case 5:					//求平方根
		if (x>=0)
			return(sqrt(x));
		else
		{
			printf("  >>负数不能开平方\n");
			break;
		}
	case 6:					//求exp
		return(exp(x));
	case 7:					//求log2
		if (x>0)
			return(log(x));
		else
		{
			printf("  >>负数不能求ln\n");
			break;
		}
	case 8:					//求log10
		if (x>0)
			return(log10(x));
		else
		{
			printf("  >>负数不能求log10\n");
			break;
		}
	case 9:					//求sin
		return(sin(x));
	case 10:				//求cos
		return(cos(x));
	case 11:				//求tanh
		return(tanh(x));
	}
}
Value_type GetValue(int h)  //从lexicon[h]获取值
{
	if (Kind(h)!=OPERAND)
		printf("  >>不是一个操作数\n");
	else
		return(lexicon[h].info.val);
}
Value_type EvaluatePostfix()   //计算后缀表达式值
{
	Kind_type type;
	int h;
	Value_type x,y;
	double St[MAXSTACK];
	int top=-1;
	postlength=-1;
	do
	{
		GetToken1(h);
		switch(type=Kind(h))
		{
		case OPERAND:				//操作数
			top++;
			St[top]=GetValue(h);
			break;
		case UNARYOP:				//一元运算符
			x=St[top];
			top--;
			top++;
			St[top]=DoUnary(h,x);
			break;
		case BINARYOP:				//二元运算符
			y=St[top];top--;
			x=St[top];top--;
			top++;
			St[top]=DoBinary(h,x,y);
			break;
		case ENDEXPR:				//结束符
			x=St[top];top--;
			if (top>-1)			//栈不空,出错
				printf("  >>不正确的表达式\n");
			break;
		}
	} while (type!=ENDEXPR);
	return(x);
}
void main()
{
	char instring[MAXSTRING];
	MakeHashTable();
	printf("输入一个中缀表达式:");
	gets(instring);
	while (strlen(instring)!=0)
	{
		if (ProcessExpress(instring))
		{
			DispInfix();
			Translate();
			DispPostfix();
			printf(" 运算结果:%g\n\n",EvaluatePostfix());
		}
		printf("输入一个中缀表达式:");
		gets(instring);
	}
	printf("\n");
}
