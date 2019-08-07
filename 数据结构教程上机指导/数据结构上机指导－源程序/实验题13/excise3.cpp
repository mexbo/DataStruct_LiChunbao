//文件名:excise3.cpp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxWidth 40			//凹入表示法时的最大场宽
#define MaxSize 30			//栈的最大元素个数
#define NAMEWIDTH 10		//姓名的最多字符个数
typedef struct fnode
{
	char father[NAMEWIDTH];	//父
	char wife[NAMEWIDTH];	//母
	char son[NAMEWIDTH];	//子
} FamType;
typedef struct tnode
{
	char name[NAMEWIDTH];
	struct tnode *lchild,*rchild;
} BTree;					//家谱树类型
BTree *CreatBTree(char *root,FamType fam[],int n)	//从fam(含n个记录)递归创建一棵二叉树
{
	int i=0,j;
	BTree *bt,*p;
	bt=(BTree *)malloc(sizeof(BTree));	//创建父亲节点
	strcpy(bt->name,root);
	bt->lchild=bt->rchild=NULL;
	while (i<n && strcmp(fam[i].father,root)!=0) 
		i++;
	if (i<n)									//找到了该姓名的记录
	{
		p=(BTree *)malloc(sizeof(BTree));		//创建母亲节点
		p->lchild=p->rchild=NULL;
		strcpy(p->name,fam[i].wife);
		bt->lchild=p;
		for (j=0;j<n;j++)						//找所有儿子
			if (strcmp(fam[j].father,root)==0)	//找到一个儿子
			{
				p->rchild=CreatBTree(fam[j].son,fam,n);
				p=p->rchild;
			}
	}
	return(bt);
}
void DispTree1(BTree *b)	//以括号表示法输出二叉树
{
	if (b!=NULL)
	{
		printf("%s",b->name);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{
			printf("(");
			DispTree1(b->lchild);
			if (b->rchild!=NULL) 
				printf(",");
			DispTree1(b->rchild);
			printf(")");
		}
	}
}
void DispTree2(BTree *bt)	//以凹入表示法输出
{
	BTree *St[MaxSize],*p;
	int Level[MaxSize][2],top,n,i,width=4;
	if (bt!=NULL)
	{
		printf("  >>家谱凹入表示法:\n");
        top=1;
		St[top]=bt;				//根节点进栈
		Level[top][0]=width;
		while (top>0)
        {
			p=St[top];			//退栈并凹入显示该节点值
			n=Level[top][0];
			for (i=1;i<=n;i++)  //其中n为显示场宽,字符以右对齐显示
				printf(" ");
			printf("%6s",p->name);
			if (Level[top][1]==1)
				printf("(l)");
			else
				printf("(r)");
			for (i=n+1;i<=MaxWidth-6;i+=2)
				printf("--");
			printf("\n");
			top--;
			if (p->rchild!=NULL)
			{								//将右子树根节点进栈
				top++;
				St[top]=p->rchild;
				Level[top][0]=n+width;		//显示场宽增width
				Level[top][1]=2;			//为右孩子节点
			}
			if (p->lchild!=NULL)
			{								//将左子树根节点进栈
				top++;
				St[top]=p->lchild;
				Level[top][0]=n+width;		//显示场宽增width
				Level[top][1]=1;			//为左孩子节点
			}
        }
	}
}
BTree *FindNode(BTree *bt,char xm[]) //采用先序递归算法找name为xm的节点
{
	BTree *p=bt;
	if (p==NULL) 
		return(NULL);
	else
	{
		if (strcmp(p->name,xm)==0)
			return(p);
		else
		{
			bt=FindNode(p->lchild,xm);
			if (bt!=NULL) 
				return(bt);
			else 
				return(FindNode(p->rchild,xm));
		}
	}
}
void FindSon(BTree *bt)	//输出某人的所有儿子
{
	char xm[NAMEWIDTH];
	BTree *p;
	printf("  >>父亲姓名:");
	scanf("%s",xm);
	p=FindNode(bt,xm);
	if (p==NULL)
		printf("  >>不存在%s的父亲!\n",xm);
	else
	{
		p=p->lchild;
		if (p==NULL)
			printf("  >>%s没有妻子\n",xm);
		else
		{
			p=p->rchild;
			if (p==NULL)
				printf("  >>%s没有儿子!\n",xm);
			else
			{
				printf("  >>%s的儿子:",xm);
				while (p!=NULL)
				{
					printf("%10s",p->name);
					p=p->rchild;
				}
				printf("\n");
			}
		} 
	}
}
int Path(BTree *bt,BTree *s)	//采用后序非递归遍历方法输出从根节点到*s节点的路径
{
	BTree *St[MaxSize];
	BTree *p;
	int i,flag,top=-1;				//栈指针置初值
	do
	{
		while (bt)                 	//将bt的所有左节点进栈
		{	
			top++;
			St[top]=bt;
			bt=bt->lchild;
		}
		p=NULL;                   	//p指向当前节点的前一个已访问的节点
		flag=1;                   	//设置bt的访问标记为已访问过
		while (top!=-1 && flag)
		{	
			bt=St[top];          	//取出当前的栈顶元素
			if (bt->rchild==p)      //右子树不存在或已被访问,访问之
			{	if (bt==s)          //当前访问的节点为要找的节点,输出路径
				{	
					printf("  >>所有祖先:");
					for (i=0;i<top;i++) 
					   	printf("%s ",St[i]->name);
					printf("\n");
				   	return 1;
				}
				else
				{	
					top--;
				   	p=bt;           //p指向则被访问的结
				}
			}
			else
			{	
				bt=bt->rchild;      //bt指向右子树
				flag=0;            	//设置未被访问的标记
			}
		}
	} while (top!=-1);				//栈不空时循环
	return 0;						//其他情况时返回0
}
void Ancestor(BTree *bt)	//输出某人的所有祖先
{
	BTree *p;
	char xm[NAMEWIDTH];
	printf("  >>输入姓名:");
	scanf("%s",xm);
	p=FindNode(bt,xm);
	if (p!=NULL)
		Path(bt,p);
	else
		printf("  >>不存在%s\n",xm);
}
void DelAll(FamType fam[],int &n)	//清除家谱文件全部记录
{
	FILE *fp;
	if ((fp=fopen("fam.dat","wb"))==NULL) 
	{	
		printf("  >>不能打开家谱文件\n");
		return;
	}
	n=0;
	fclose(fp);
}
void ReadFile(FamType fam[],int &n) //读家谱文件存入fam数组中
{
	FILE *fp;
	long len;
	int i;
	if ((fp=fopen("fam.dat","rb"))==NULL) 
	{
		n=0;
		return;
	}
	fseek(fp,0,2);				//家谱文件位置指针移到家谱文件尾
	len=ftell(fp);    			//len求出家谱文件长度
	rewind(fp);					//家谱文件位置指针移到家谱文件首
	n=len/sizeof(FamType); 		//n求出家谱文件中的记录个数
	for (i=0;i<n;i++)
		fread(&fam[i],sizeof(FamType),1,fp);//将家谱文件中的数据读到fam中
	fclose(fp);
}
void SaveFile(FamType fam[],int n) //将fam数组存入数据家谱文件
{
	int i;
	FILE *fp;
	if ((fp=fopen("fam.dat","wb"))==NULL) 
	{	
		printf("  >>数据家谱文件不能打开\n");
		return;
	}
	for (i=0;i<n;i++)
		fwrite(&fam[i],sizeof(FamType),1,fp);
	fclose(fp);
}
void InputFam(FamType fam[],int &n)		//添加一个记录
{
	printf("  >>输入父亲、母亲和儿子姓名:");
	scanf("%s%s%s",fam[n].father,fam[n].wife,fam[n].son);
	n++;
}
void OutputFile(FamType fam[],int n)//输出家谱文件全部记录
{
	int i;
	if (n<=0)
	{
		printf("  >>没有任何记录\n");
		return;
	}
	printf("         父亲     母亲      儿子\n");
	printf("       ------------------------------\n");
	for (i=0;i<n;i++)
		printf("  %10s%10s%10s\n",fam[i].father,fam[i].wife,fam[i].son);
	printf("       ------------------------------\n");
}
void main()
{
	BTree *bt;
	FamType fam[MaxSize];
	int n,sel,sel1;
	ReadFile(fam,n);
	do
	{	
		printf("1.文件操作 2:家谱操作 0:退出 请选择:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 1:
			do 
			{
				printf(" 1:输入 2:输出 9:全清 0:存盘返回 请选择:");
				scanf("%d",&sel1);
				switch(sel1)
				{
				case 9:
					DelAll(fam,n);
					break;
				case 1:
					InputFam(fam,n);
					break;
				case 2:
					OutputFile(fam,n);
					break;
				case 0:
					SaveFile(fam,n);
					break;
				} 
			} while (sel1!=0);
			break;
		case 2:
			bt=CreatBTree("f1",fam,n);
			do 
			{
				printf(" 1:括号表示法 2.凹入表示法 3.找某人所有儿子 4.找某人所有祖先 0:返回 请选择:");
				scanf("%d",&sel1);
				switch(sel1)
				{
				case 1:
					printf("  >>");DispTree1(bt);printf("\n");
					break;
				case 2:
					DispTree2(bt);
					break;
				case 3:
					FindSon(bt);
					break;
				case 4:
					printf("  >>");Ancestor(bt);
					break;
				} 
			} while (sel1!=0);
			break;
		}
	} while (sel!=0);
}
