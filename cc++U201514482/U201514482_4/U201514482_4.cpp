#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

using namespace std;


class QUEUE{
    int  *const  elems;	//申请内存用于存放队列的元素
    const  int   max;	//elems能存放的最大元素个数
    int   head, tail;		//队列头和尾，队列空时head=tail;初始时head=tail=0
public:
QUEUE(int m);		//初始化循环队列：elems有m个元素
QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
virtual operator int ( ) const			//返回队列的实际元素个数
{
	if((tail<0) || (head<0))//说明入队列和处队列的时候出错 
		return -1;
	else
		return ((tail - head + max) % max);
} 
virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
virtual void print( ) const;			//打印队列
virtual ~QUEUE( );					//销毁队列
};

FILE *stream; //文件指针 

QUEUE::QUEUE(int m):max(m),elems(new int[m])//给7个空间，只能用6个，最后一个用来区分队列是否满了 
{
	head = 0;
	tail = 0;//第一个元素为0，最后一个元素为m-1 
}

//深拷贝 
QUEUE::QUEUE(const QUEUE&s):max(s.max), elems(new int[s.max])//用队列s拷贝初始化队列
{
	head = s.head;
	tail = s.tail; 
	for(int i = head;(i%s.max) != s.tail;i++)//tail那里是没有元素的 
		*(elems + i)=*(s.elems + i);
}


int QUEUE::full ( ) const//返回队列是否已满，满返回1，否则返回0
{
	if((tail<0) || (head<0))//说明入队列和处队列的时候出错 
		return -1;
	else if(((tail+1)%max) == head)
		return 1;
	else
		return 0;
}	

int QUEUE::operator[ ](int x)const   //取下标为x的元素,第1个元素下标为0
{
	return elems[x];
}


QUEUE& QUEUE::operator<<(int e) 	//将e入队列,并返回队列
{
	if((tail+1)%max == head)//队列满了，不能入队 
	{
		tail = -1;
		head = -1; 
		return (*this);
	}
	else
	{
		elems[tail] = e;
		tail++;
		tail = tail % max; 
		return (*this); 
	}

	
}


QUEUE& QUEUE::operator>>(int &e) //出队列到e,并返回队列
{
	if(head == tail)
	{
		tail = -1;
		head = -1; 
		return (*this);
	}
	else
	{
		e=elems[head];
		head = head + max + 1;
		head = head % max;
		return (*this);
	}
	
}

//队列已经建立好了，只是没有赋值 
QUEUE& QUEUE::operator=(const QUEUE&s)//赋s给队列,并返回被赋值的队列
{
	int *p = (int *)(&max);
	*p = s.max;
	
	
	head = s.head;
	tail = s.tail;//头尾 
	for(int i = head;(i%s.max) != s.tail;i++)//tail那里是没有元素的 
		*(elems + i)=*(s.elems + i);
	return (*this);
}

QUEUE::~QUEUE()					//销毁队列
{
	if(elems)//避免重复释放 
	{
		delete []elems;
		head = 0;
		tail = 0;
	} 
}

void QUEUE::print() const			//打印队列
{
	int value=0;
	for(int i = head;(i%max) != tail;i++)//tail那里是没有元素的 
	{
		i = i % max;  
		value =elems[i];
		fprintf(stream,"  %d",value);
	}
}

int main(int argc,char *argv[])
{
	int num=1;//记录处理到第几个参数 
	int i=0;//用于循环计数 
	int flag=0;//用于判断是否是异常退出 
	int inmax,amax,Gnum;//输入的栈的大小，调用指令-A栈的大小 ,需要返回的位置 
	int jishu;//用于出栈计数 
	int value;//入栈的数字 
	int &e=value;//出栈调用时的数字，也用value的空间 
	QUEUE *myqueue,*newcqueue,*newaqueue;//栈指针,还没有分配空间 
	stream = fopen("U201514482_4.txt", "w" ); //文件流 
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
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0) && (*myqueue != -1))
			{
				value = atoi(argv[num]);//入栈的值
				*myqueue<<value;//入栈
				num++; 
			}
			fprintf(stream,"  I");
			if(*myqueue != -1)//说明队列满导致退出 
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
			while((i < jishu) && (*myqueue != -1))
			{
				*myqueue>>e;
				i++;
			}
				
			if(*myqueue != -1)
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
			myqueue->~QUEUE();
			myqueue = newcqueue;//还是用的原来的符号，然后输出 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// 重新创建一个栈，然后把原来的值给它 
		{
			num++;
			fprintf(stream,"  A");
			myqueue->print();
			amax = atoi(argv[num]);
			newaqueue=new QUEUE(amax);//为A建立一个栈
			*newaqueue=*myqueue;
			myqueue->~QUEUE();
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





