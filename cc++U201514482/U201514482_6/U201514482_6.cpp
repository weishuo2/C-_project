#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include <iostream>

using namespace std;

FILE *stream; //文件指针 


class STACK{//栈 
    int  *const elems;	//申请内存用于存放栈的元素
    const int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		   //初始化栈：最多存m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	virtual int  size ( ) const;		//返回栈的最大元素个数max
	virtual operator int() const;	//返回栈的实际元素个数pos
	virtual int  operator[] (int x) const;//取下标x处的栈元素，第1个元素x=0
	virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
	virtual STACK& operator>>(int &e); 	//出栈到e,并返回栈
	virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
	virtual void print( ) const;		//打印栈
	virtual ~STACK( );				//销毁栈
};

STACK::STACK(int m):max(m),elems(new int[m])//初始化栈 
{
	pos = 0;
}

STACK::STACK(const STACK&s):max(s.max), elems(new int[s.max])//栈还没有分配空间 
{//重新分配空间并且将现有数据移进去 
	pos = s.pos;
	for(int i=0;i < s.pos;i++)
		*(elems + i)=*(s.elems + i);
}

int STACK::size() const//返回栈的大小 
{
	return max;
}

STACK::operator int() const//返回当前占用大小 
{
	return pos;
}


//调用前先判断 
int STACK::operator[](int x) const//返回第x个元素 
{
	if(x >= pos)
	{
		return -2017;
	} 
	return elems[x];
}

//不能入栈会将pos置为负数 
STACK& STACK::operator<<(int e)
{
	if(pos < max)//可以入栈 
	{
		elems[pos]=e;
		pos = pos+1;
		return (*this);
	}
	else//不能入栈，将pos置为负数 
	{
		pos=-1;
		return (*this);
	}
}

//不能出栈将pos置为负数 
STACK& STACK::operator>>(int &e)
{
	if(pos != 0) 
	{
		pos = pos-1;
		e = elems[pos];
		return (*this);
	}
	else//不能出栈，将pos置为负数 
	{
		pos=-1;
		return (*this);
	}
}


STACK& STACK::operator=(const STACK&s)//栈的赋值 ,这个栈已经建立好了，只是没有赋值 
{			
	int *p = (int *)(&max);
	*p = s.max;
	
	
	pos = s.pos;
	for(int i=0;i < s.pos;i++)
		*(elems + i)=*(s.elems + i);
	return (*this);
}

void STACK::print() const
{
	int value=0;
	for(int i=0;i < pos;i++)
	{
		value =elems[i];
		fprintf(stream,"  %d",value);
	}
}

STACK::~STACK( )
{
	if(elems)//避免重复释放 
	{
		delete []elems;
		pos = 0;
	} 
}

class QUEUE:public STACK {
	STACK  s2;
public:
	QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
	virtual operator int() const;			//返回队列的实际元素个数
	virtual int full() const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素，第1个元素下标为0
	virtual QUEUE& operator<<(int e);  //将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	virtual void print() const;			//打印队列
	virtual ~QUEUE();					//销毁队列
};

//对m的初始化就是初始化两个栈 
QUEUE::QUEUE(int m):STACK(m),s2(m)//初始化两个栈 
{//继承过来的时候就自带了一个栈，所以在成员里面只用申明一个栈 
}

QUEUE::QUEUE(const QUEUE&s) :STACK(s),s2(s.s2)//深拷贝 
{//就是将现有队列的两个栈赋给新队列,还没有给空间 
}

QUEUE::operator int() const//返回队列的大小 
{
	return STACK::operator int() + s2;//队列大小 
	//相当于对基类在进行操作，所以需要前缀说明 
}

int QUEUE::full() const //栈1满了且s2不为空时即为栈满 
{//判断队列是否已满 
	int i = STACK::operator int();
	int max1 = STACK::size();
	if ((s2 != 0) && (i == max1))//栈2是用来倾倒的 
		return 1;
	else
		return 0;
}

int QUEUE::operator[ ](int x)const 
{//用来取队列中第i个元素 
	int i = STACK::operator int();
	if((x >= 0)&&(x <= (s2-1)))//说明在栈2中 
		return s2[s2 - 1 - x];
	else if((x <= (i+s2-1)) && (x >= s2))//说明在栈1中 
	 	return STACK::operator[](x - s2);
	else  //说明不存在 
		return -2017;//--------------------------------------------------------
	
}
//需要在调用前先判断是否满了 
QUEUE& QUEUE::operator<<(int e) //将e入队并返回队列 
{
	int n = 0;
	int pos1=STACK::operator int();//栈1的现在大小
	int max1=STACK::size();//栈1的最大大小 
	if (pos1 < max1)//放到栈1中 
		STACK::operator << (e);
	else 
	{
		if ((pos1 == max1) && (s2 == 0)) 
		{//栈1满了且栈2为空，先将栈1元素倒入栈2，然后入栈1 
			for (int i = 0; i < pos1; i++) //不能用s1来代替jishu，因为每运行一次s1的值就发生了变化，实际循环次数也发生了变化 
			{
				STACK::operator  >> (n);
				s2 << n;//将s1的元素移到s2中 
			}
			STACK::operator << (e);//然后入栈 
		}
		return *this;
	}
}

//调用前先判断为不为空 
QUEUE& QUEUE::operator>>(int &e) 
{//出队列 
	int n=0;
	int pos1 = STACK::operator int();
	if (s2)//栈2不为空，从栈2出栈 
		e = s2 >> e;
	else
	{//栈2为空，把栈1所有元素倒入栈2 
		for (int i = 0; i < pos1; i++) 
		{
			STACK::operator  >> (n);
			s2 << n;
		}
		e = s2 >> e;
	}		
	return *this;
}


QUEUE& QUEUE::operator=(const QUEUE&s)//队列已经建立好了，只是没有赋值------------------------------------ 
{
	STACK::operator=(s);
	s2 = s.s2;
	return (*this);
}

void  QUEUE::print() const //输出队列   fprintf(stream,"  %d",value);
{
	int x = s2;
	int pos1 = STACK::operator int();
	int value;
	if (x) 
	{
		for (int i = 0; i < s2; i++) 
		{
			x--;
			value = s2[x];
			fprintf(stream,"  %d",value);
		}
	}
	for (int i = 0; i < pos1; i++)
		fprintf(stream,"  %d",STACK::operator[](i));
}
QUEUE::~QUEUE() //销毁 
{
	s2.~STACK();
	
}

int dance(int M,int F,int m,int f); 

int main(int argc,char *argv[])
{
	if(argc == 1)
	{
		int M,F,m,f,result;
		printf("请输入男士队列长度：");
		scanf("%d",&M);
		printf("请输入女士队列长度：");
		scanf("%d",&F);
		printf("请输入男士编号：");
		scanf("%d",&m);
		printf("请输入女士编号：");
		scanf("%d",&f);
		
		result = dance(M,F,m,f);
		printf("第%d男士和第%d位女士在第%d支曲可以一起跳舞\n",m,f,result); 
		return 0;
	}
	int num=1;//记录处理到第几个参数 
	int i=0;//用于循环计数 
	int flag=0;//用于判断是否是异常退出 
	int inmax,amax,Gnum;//输入的栈的大小，调用指令-A栈的大小 ,需要返回的位置 
	int jishu;//用于出栈计数 
	int value;//入栈的数字 
	int &e=value;//出栈调用时的数字，也用value的空间 
	QUEUE *myqueue,*newcqueue,*newaqueue;//栈指针,还没有分配空间 
	stream = fopen("U201514482_6.txt", "w" ); //文件流 
	while(num < argc)//没有处理完 
	{
		if(strcmp(argv[num],"-S") == 0)//建立队列 
		{
			num = num + 1;//读取下一个参数，队列的大小 
			inmax = atoi(argv[num]);//队列的大小
			myqueue = new QUEUE(inmax);//建立队列 
			fprintf(stream,"S  %d",inmax);
			num++;
		}
		//存疑------------------------------------------------------------------- 
		else if(strcmp(argv[num],"-I") == 0)//入队列,溢出直接返回，输出E不管后面的操作 
		{
			num++;
			//输入为数字且栈不为空时进行循环 
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0))
			{
				if(myqueue->full())//栈满了
				{
					flag=1;
					break;
				} 
				value = atoi(argv[num]);//入栈的值
				*myqueue<<value;//入栈
				num++; 
			}
			fprintf(stream,"  I");
			if(flag != 1)//说明队列满导致退出 
			{
				myqueue->print();
			
			} 				
			else
			{
				flag=1;
				break;
			} 				
		} 
		else if(strcmp(argv[num],"-O") == 0)//出队列 
		{
			num++;
			fprintf(stream,"  O");
			jishu = atoi(argv[num]);//出栈的个数
			i=0; 
			while((i < jishu))
			{
				if(*myqueue == 0)//队列为空 
				{
					flag = 1;
					break;
				}
				*myqueue>>e;
				i++;
			}
				
			if(flag != 1)
			{
				myqueue->print();			
			}				
			else
			{
				flag=1;
				break;	
			}
					
			num++;		
		} 
		else if(strcmp(argv[num],"-C") == 0)//复制一个栈 
		{
			fprintf(stream,"  C");
			myqueue->print(); 
			newcqueue=new QUEUE(*myqueue);//不能在这个里面定义newcstack，因为其作用域仅在这个里面，除了这个就会被析构 
//			myqueue->~QUEUE();
			myqueue = newcqueue;//还是用的原来的符号，然后输出 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// 重新创建一个栈，然后把原来的值给它 
		{
			num++;
			fprintf(stream,"  A");
			myqueue->print();
			amax = atoi(argv[num]);
			newaqueue=new QUEUE(inmax);//为A建立一个栈
			*newaqueue=*myqueue;
//			myqueue->~QUEUE();
			myqueue = newaqueue;
			num++;
		}
		else if(strcmp(argv[num],"-N") == 0)//输出剩余元素个数 
		{
			fprintf(stream,"  N");
			int adnum=*myqueue;
			fprintf(stream,"  %d",adnum);
			num++;
		}
		else if(strcmp(argv[num],"-G") == 0)//输出对应位置的值
		{
			num++;
			fprintf(stream,"  G");
			Gnum = atoi(argv[num]);
			num++;
			if(Gnum >= *myqueue)
			{
				flag = 1;
				break;
			}
			else
			{
				int adnum2=(*myqueue)[Gnum];
				fprintf(stream,"  %d",adnum2);
			}
				
		} 
	}
	if(flag == 1)
		fprintf(stream,"  E");
	fclose( stream ); 
	return 1;
}

int dance(int M,int F,int m,int f)
{
	QUEUE *MEN,*WOMEN;
	MEN = new QUEUE(M+1); 
	WOMEN = new QUEUE(F+1); //创建队列 
	int man,woman; 
	int i,j,k,n;
	m = M-m;
	f = F-f;
	for(i = 0;i < M;i++)//初始化队列 
	{
		*MEN<<(M-i);
	}
		
	for(j = 0;j < F;j++)//队列的入队有点怪怪的，但是main调用没问题 
	{
		*WOMEN<<(F-i); 
	}
		
	for(k = 0;k <= M*F;k++)
	{
		*MEN>>man;
		*WOMEN>>woman;	
		if((man == m) && (woman == f))
			return k+1;
		else
		{
			*MEN<<man;
			*WOMEN<<woman;
		}
	}
	return -1;//出错 
}


