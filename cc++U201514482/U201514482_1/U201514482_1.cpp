#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

struct STACK{
    int  *elems;	//申请内存用于存放栈的元素
    int   max;	//栈能存放的最大元素个数
    int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈，达到-C的效果 
int  size (const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany (const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem (const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p，就是-A先跟A分配空间，再赋值给A 
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

FILE *stream; 

int main(int argc,char *argv[])
{
	int num=1;//记录处理到第几个参数 
	int i=0;//用于循环计数 
	int flag=0;//用于判断是否是异常退出 
	int inmax,amax,Gnum;//输入的栈的大小，调用指令-A栈的大小 ,需要返回的位置 
	int jishu;//用于出栈计数 
	int value;//入栈的数字 
	int &e=value;//出栈调用时的数字，也用value的空间 
	STACK *mystack,*newcstack,*newastack;//栈指针,还没有分配空间 
	mystack = (STACK *)malloc(sizeof(STACK));
	newastack = (STACK *)malloc(sizeof(STACK));
	newcstack = (STACK *)malloc(sizeof(STACK));
	STACK &tidai=*mystack;//mystack的应用 
	stream = fopen("U201514482_1.txt", "w" ); //文件流 
	while(num < argc)//没有处理完 
	{
		if(strcmp(argv[num],"-S") == 0)//建立栈 
		{
			num = num + 1;//读取下一个参数，栈的大小 
			inmax = atoi(argv[num]);//栈的大小
			initSTACK(mystack,inmax);//建立栈 
			fprintf(stream,"S  %d",inmax);
			num++;
		}
		else if(strcmp(argv[num],"-I") == 0)//入栈 ,溢出直接返回，输出E不管后面的操作 
		{
			num++;
			//输入为数字且栈不为空时进行循环 
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0) && (mystack != NULL))
			{
				value = atoi(argv[num]);//入栈的值
				mystack=push(mystack,value);//入栈
				num++; 
			}
			fprintf(stream,"  I");
			if(mystack == NULL)//说明入栈出错导致退出 
			{
				flag=1;
				break;
			} 				
			else
				print(mystack);
		} 
		else if(strcmp(argv[num],"-O") == 0)//出栈
		{
			num++;
			fprintf(stream,"  O");
			jishu = atoi(argv[num]);//出栈的个数
			i=0; 
			while((i < jishu) && (mystack != NULL))
			{
				mystack=pop(mystack,e);
				i++;
			}
				
			if(mystack == NULL)
			{
				flag=1;
				break;	
			}				
			else
				print(mystack);	
			num++;		
		} 
		else if(strcmp(argv[num],"-C") == 0)//复制一个栈 
		{
			fprintf(stream,"  C");
			print(mystack);
			initSTACK(newcstack,tidai);
			mystack = newcstack;//还是用的原来的符号，然后输出 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// 重新创建一个栈，然后把原来的值给它 
		{
			num++;
			fprintf(stream,"  A");
			print(mystack);
			amax = atoi(argv[num]);
			initSTACK(newastack,amax);//为A建立一个栈
			mystack=assign(newastack,tidai);
		//	mystack = newastack;
			num++;
		}
		else if(strcmp(argv[num],"-N") == 0)//输出剩余元素 
		{
			fprintf(stream,"  N");
			fprintf(stream,"  %d",mystack->pos);
			num++;
		}
		else if(strcmp(argv[num],"-G") == 0)//输出对应位置的值
		{
			num++;
			fprintf(stream,"  G");
			Gnum = atoi(argv[num]);
			num++;
			if(Gnum >= mystack->max)
			{
				flag = 1;
				break;
			}
			else
				fprintf(stream,"  %d",getelem(mystack,Gnum));
		} 
	}
	if(flag == 1)
		fprintf(stream,"  E");
	fclose( stream ); 
	return 1;
}

//栈 
void initSTACK(STACK *const p, int m)
{
	p->elems = (int *)malloc(sizeof(int) * m);//分配m个整数空间 
	p->max = m;
	p->pos = 0;
}

void initSTACK(STACK *const p, const STACK&s)//实现-C的功能 
{
	p->elems = (int *)malloc(sizeof(int) * s.max);
	p->max = s.max;
	p->pos = s.pos;
	for(int i = 0;i < p->pos;i++)
		*(p->elems + i) = *(s.elems + i);
}

int  size (const STACK *const p)
{
	return p->max;
}

int  howMany (const STACK *const p)
{
	return p->pos;
}

int  getelem (const STACK *const p, int x)//在调用这个函数前要先判断x是否合法 
{
		return *(p->elems + x);
}

STACK *const push(STACK *const p, int e)//不能入栈时返回NULL 
{
	if(p->pos < p->max)
	{
		*(p->elems + p->pos)=e;
		p->pos = p->pos+1;
		return p;
	}
	else
		return NULL;
} 

STACK *const pop(STACK *const p, int &e)//不能出栈时返回NULL 
{
	if(p->pos != 0) 
	{
		p->pos = p->pos-1;
		e = *(p->elems + p->pos);
		return p;
	}
	else
		return NULL;
}

//必须先判断A的大小是否小于原来的栈 
STACK *const assign(STACK*const p, const STACK&s)//先为A分配空间，然后再用s对A进行赋值 
{
	p->elems = (int *)realloc(p->elems,sizeof(int)*(s.max));
	p->max = s.max;		
	p->pos = s.pos;
	for(int i=0;i < s.pos;i++)
		*(p->elems + i)=*(s.elems + i);
	return p;
}

void print(const STACK*const p)//打印栈 
{
	int value=0;
	for(int i=0;i < p->pos;i++)
	{
		value =p->elems[i];
		fprintf(stream,"  %d",value);
	}
	
}

void destroySTACK(STACK*const p)//销毁栈 
{
	free(p->elems);
	free(p);
} 


