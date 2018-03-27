#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

using namespace std;

class STACK{
    int  *const elems;	//申请内存用于存放栈的元素
    const int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		   //初始化栈：最多存m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	int  size ( ) const;		//返回栈的最大元素个数max
	int  howMany ( ) const;	//返回栈的实际元素个数pos
	int  getelem (int x) const;//取下标x处的栈元素，第1个元素x=0
	STACK& push(int e); 	//将e入栈,并返回栈
	STACK& pop(int &e); 	//出栈到e,并返回栈
	STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
	void print( ) const;		//打印栈
	~STACK( );				//销毁栈
};

FILE *stream; 

STACK::STACK(int m):max(m),elems(new int[m])
{
	pos = 0;
}

STACK::STACK(const STACK&s):max(s.max), elems(new int[s.max])//存疑 
{
	pos = s.pos;
	for(int i=0;i < s.pos;i++)
		*(elems + i)=*(s.elems + i);
}

int STACK::size() const
{
	return max;
}

int STACK::howMany() const
{
	return pos;
}

int STACK::getelem(int x) const
{
	return elems[x];
}

STACK& STACK::push(int e)
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

STACK& STACK::pop(int &e)
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

STACK& STACK::assign(const STACK&s)
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
	stream = fopen("U201514482_2.txt", "w" ); //文件流 
	while(num < argc)//没有处理完 
	{
		if(strcmp(argv[num],"-S") == 0)//建立栈 
		{
			num = num + 1;//读取下一个参数，栈的大小 
			inmax = atoi(argv[num]);//栈的大小
			mystack = new STACK(inmax);//建立栈 
			fprintf(stream,"S  %d",inmax);
			num++;
		}
		else if(strcmp(argv[num],"-I") == 0)//入栈 ,溢出直接返回，输出E不管后面的操作 
		{
			num++;
			//输入为数字且栈不为空时进行循环 
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0) && (mystack->howMany() != -1))
			{
				value = atoi(argv[num]);//入栈的值
				mystack->push(value);//入栈
				num++; 
			}
			fprintf(stream,"  I");
			if(mystack->howMany() == -1)//说明入栈出错导致退出 
			{
				flag=1;
				break;
			} 				
			else
				mystack->print();
		} 
		else if(strcmp(argv[num],"-O") == 0)//出栈
		{
			num++;
			fprintf(stream,"  O");
			jishu = atoi(argv[num]);//出栈的个数
			i=0; 
			while((i < jishu) && (mystack->howMany() != -1))
			{
				mystack->pop(e);
				i++;
			}
				
			if(mystack->howMany() == -1)
			{
				flag=1;
				break;	
			}				
			else
				mystack->print();	
			num++;		
		} 
		else if(strcmp(argv[num],"-C") == 0)//复制一个栈 
		{
			fprintf(stream,"  C");
			mystack->print(); 
			newcstack=new STACK(*mystack);//不能在这个里面定义newcstack，因为其作用域仅在这个里面，除了这个就会被析构 
			mystack->~STACK();
			mystack = newcstack;//还是用的原来的符号，然后输出 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// 重新创建一个栈，然后把原来的值给它 
		{
			num++;
			fprintf(stream,"  A");
			mystack->print();
			amax = atoi(argv[num]);
			newastack=new STACK(amax);//为A建立一个栈
			newastack->assign(*mystack);
			mystack->~STACK();
			mystack = newastack;
			num++;
		}
		else if(strcmp(argv[num],"-N") == 0)//输出剩余元素 
		{
			fprintf(stream,"  N");
			fprintf(stream,"  %d",mystack->howMany());
			num++;
		}
		else if(strcmp(argv[num],"-G") == 0)//输出对应位置的值
		{
			num++;
			fprintf(stream,"  G");
			Gnum = atoi(argv[num]);
			num++;
			if(Gnum >= mystack->size())
			{
				flag = 1;
				break;
			}
			else
				fprintf(stream,"  %d",mystack->getelem(Gnum));
		} 
	}
	if(flag == 1)
		fprintf(stream,"  E");
	fclose( stream ); 
	return 1;
}

