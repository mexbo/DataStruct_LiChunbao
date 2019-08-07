//文件名:excise1.cpp
#include <stdio.h>
#include <malloc.h>
typedef struct
{
	int no;						//职工号
	char name[10];				//姓名
	int depno;					//部门号
	float salary;				//工资数
} EmpType;						//职工类型
typedef struct node
{
	EmpType data;				//存放职工信息
	struct node *next;			//指向下一个节点的指针
}  EmpList;						//职工单链表节点类型
void DelAll(EmpList *&L)		//清除职工文件中全部记录
{
	FILE *fp;
	EmpList *p,*q;
	if ((fp=fopen("emp.dat","wb"))==NULL)	//重写清空emp.dat文件
	{	
		printf("  提示:不能打开职工文件\n");
		return;
	}
	fclose(fp);
	p=L->next;
	if (p!=NULL)
	{
		q=p->next;
		while (q!=NULL)
		{
			free(p);
			p=q;
			q=q->next;
		}
		free(p);
		L->next=NULL; 
	}
	else
		printf("  提示:不存在任何职工记录\n");
	printf("  提示:职工数据清除完毕\n");
}
void ReadFile(EmpList *&L)		//读emp.dat文件建立职工单键表L
{
	FILE *fp;
	EmpType emp;
	EmpList *p,*r;
	int n=0;
	L=(EmpList *)malloc(sizeof(EmpList));	//建立头节点
	r=L;
	if ((fp=fopen("emp.dat","rb"))==NULL) 
	{	
		 if ((fp=fopen("emp.dat","wb"))==NULL) 
			 printf("  提示:不能创建emp.dat文件\n");
	}
	else		//存在emp.dat文件
	{
		while (fread(&emp,sizeof(EmpType),1,fp)==1)
		{	//采用尾插法建立单链表L
			p=(EmpList *)malloc(sizeof(EmpList));
			p->data=emp;
			r->next=p;
			r=p;
			n++;
		}
	}
	r->next=NULL;
	printf("  提示:职工单键表L建立完毕,有%d个记录\n",n);
	fclose(fp);
}
void SaveFile(EmpList *L)	//将职工单链表数据存入数据文件
{
	EmpList *p=L->next,*q;
	FILE *fp;
	if ((fp=fopen("emp.dat","wb"))==NULL) 
	{	
		printf("  提示:不能创建文件emp.dat\n");
		return;
	}
	while (p!=NULL)
	{
		fwrite(&p->data,sizeof(EmpType),1,fp);
		p=p->next;
	}
	fclose(fp);
	p=L;					//释放职工单链表
	q=p->next;
	while (q!=NULL)
	{
		free(p);
		p=q;
		q=q->next;
	}
	free(p);
	printf("  提示:所有职工记录成功写入到emp.dat文件中\n");
}
void InputEmp(EmpList *&L)	//添加一个职工记录
{
	EmpList *p;
	printf("  >>输入职工号,姓名,部门号,工资:");
	p=(EmpList *)malloc(sizeof(EmpList));
	scanf("%d%s%d%f",&p->data.no,p->data.name,&p->data.depno,&p->data.salary);
	p->next=L->next;		//采用头插法插入节点*p
	L->next=p;
}
void Sortno(EmpList *&L)	//采用直接插入法单链表L按no递增有序排序
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.no<p->data.no)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  提示:按no递增排序完毕\n");
}
void Sortdepno(EmpList *&L) //采用直接插入法单链表L按depno递增有序排序
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.depno<p->data.depno)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  提示:按depno递增排序完毕\n");
}
void Sortsalary(EmpList *&L) //采用直接插入法单链表L按salary递增有序排序
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.salary<p->data.salary)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  提示:按salary递增排序完毕\n");
}
void Display(EmpList *L)	//输出所有职工记录
{
	EmpList *p=L->next;
	if (p==NULL)
		printf("  提示:没有任何职工记录\n");
	else
	{
		printf("      编号  姓名  部门号       工资\n");
		printf("   ----------------------------------\n");
		while (p!=NULL)
		{
			printf("  >>%3d%10s    %-8d%7.2f\n",p->data.no,p->data.name,p->data.depno,p->data.salary);
			p=p->next; 
		}
		printf("   ----------------------------------\n");
	}
}
void main()
{
	EmpList *L;
	int sel;
	printf("由emp.dat文件建立职工单键表L\n");
	ReadFile(L);
	do
	{	
		printf("1:输入 2:显示 3:按no排序 4:按depno排序 5:按salary排序 9:全清 0:退出 请选择:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 9:
			DelAll(L);
			break;
		case 1:
			InputEmp(L);
			break;
		case 2:
			Display(L);
			break;
		case 3:
			Sortno(L);
			break;
		case 4:
			Sortdepno(L);
			break;
		case 5:
			Sortsalary(L);
			break;
		}
	} while (sel!=0);
	SaveFile(L);
}
