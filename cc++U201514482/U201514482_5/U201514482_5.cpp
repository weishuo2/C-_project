#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include <iostream>

using namespace std;

FILE *stream; //�ļ�ָ�� 


class STACK{//ջ 
    int  *const elems;	//�����ڴ����ڴ��ջ��Ԫ��
    const int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		   //��ʼ��ջ������m��Ԫ��
	STACK(const STACK&s); //��ջs������ʼ��ջ
	virtual int  size ( ) const;		//����ջ�����Ԫ�ظ���max
	virtual operator int() const;	//����ջ��ʵ��Ԫ�ظ���pos
	virtual int  operator[] (int x) const;//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
	virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
	virtual STACK& operator>>(int &e); 	//��ջ��e,������ջ
	virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	virtual void print( ) const;		//��ӡջ
	virtual ~STACK( );				//����ջ
};

STACK::STACK(int m):max(m),elems(new int[m])//��ʼ��ջ 
{
	pos = 0;
}

STACK::STACK(const STACK&s):max(s.max), elems(new int[s.max])//ջ��û�з���ռ� 
{//���·���ռ䲢�ҽ����������ƽ�ȥ 
	pos = s.pos;
	for(int i=0;i < s.pos;i++)
		*(elems + i)=*(s.elems + i);
}

int STACK::size() const//����ջ�Ĵ�С 
{
	return max;
}

STACK::operator int() const//���ص�ǰռ�ô�С 
{
	return pos;
}


//����ǰ���ж� 
int STACK::operator[](int x) const//���ص�x��Ԫ�� 
{
	if(x >= pos)
	{
		return -2017;
	} 
	return elems[x];
}

//������ջ�Ὣpos��Ϊ���� 
STACK& STACK::operator<<(int e)
{
	if(pos < max)//������ջ 
	{
		elems[pos]=e;
		pos = pos+1;
		return (*this);
	}
	else//������ջ����pos��Ϊ���� 
	{
		pos=-1;
		return (*this);
	}
}

//���ܳ�ջ��pos��Ϊ���� 
STACK& STACK::operator>>(int &e)
{
	if(pos != 0) 
	{
		pos = pos-1;
		e = elems[pos];
		return (*this);
	}
	else//���ܳ�ջ����pos��Ϊ���� 
	{
		pos=-1;
		return (*this);
	}
}


STACK& STACK::operator=(const STACK&s)//ջ�ĸ�ֵ ,���ջ�Ѿ��������ˣ�ֻ��û�и�ֵ 
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
	if(elems)//�����ظ��ͷ� 
	{
		delete []elems;
		pos = 0;
	} 

}

class QUEUE{
    STACK s1, s2;
public:
QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
virtual operator int ( ) const;			//���ض��е�ʵ��Ԫ�ظ���
virtual int full ( ) const;		       //���ض����Ƿ�������������1�����򷵻�0
virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
virtual QUEUE& operator<<(int e); 	//��e�����,�����ض���
virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
virtual void print( ) const;			//��ӡ����
virtual ~QUEUE( );					//���ٶ���
};

//��m�ĳ�ʼ�����ǳ�ʼ������ջ 
QUEUE::QUEUE(int m):s1(m),s2(m)//��ʼ������ջ 
{
}

QUEUE::QUEUE(const QUEUE&s) :s1(s.s1),s2(s.s2)//��� 
{//���ǽ����ж��е�����ջ�����¶���,��û�и��ռ� 
}

QUEUE::operator int() const//���ض��еĴ�С 
{
	return s1 + s2;//���д�С 
}

int QUEUE::full() const //ջ1������s2��Ϊ��ʱ��Ϊջ�� 
{//�ж϶����Ƿ����� 
	int i = s1;
	int j = s2;
	if ((i == s1.size()) && (j != 0))//ջ2�������㵹�� 
		return 1;
	else
		return 0;
}

int QUEUE::operator[ ](int x)const 
{//����ȡ�����е�i��Ԫ�� 
	if((x >= 0)&&(x <= (s2-1)))//˵����ջ2�� 
		return s2[s2 - 1 - x];
	else if((x <= (s1+s2-1)) && (x >= s2))//˵����ջ1�� 
	 	return s1[x - s2];
	else if ((x > (s1 + s2 - 1)) || (x < 0)) //˵�������� 
		return -2017;
	
}
//��Ҫ�ڵ���ǰ���ж��Ƿ����� 
QUEUE& QUEUE::operator<<(int e) //��e��Ӳ����ض��� 
{
	int n = 0;
	int jishu=s1;
	if (s1 < s1.size())//�ŵ�ջ1�� 
		s1 << e;
	else 
	{
		if ((s1 == s1.size()) && (s2 == 0)) 
		{//ջ1������ջ2Ϊ�գ��Ƚ�ջ1Ԫ�ص���ջ2��Ȼ����ջ1 
			for (int i = 0; i < jishu; i++) //������s1������jishu����Ϊÿ����һ��s1��ֵ�ͷ����˱仯��ʵ��ѭ������Ҳ�����˱仯 
			{
				s1 >> n;
				s2 << n;//��s1��Ԫ���Ƶ�s2�� 
			}
			s1 << e;//Ȼ����ջ 
		}
		return *this;
	}
}

//����ǰ���ж�Ϊ��Ϊ�� 
QUEUE& QUEUE::operator>>(int &e) 
{//������ 
	int n=0;
	int jishu = s1;
	if (s2)//ջ2��Ϊ�գ���ջ2��ջ 
		e = s2 >> e;
	else
	{//ջ2Ϊ�գ���ջ1����Ԫ�ص���ջ2 
		for (int i = 0; i < jishu; i++) 
		{
			s1 >> n;
			s2 << n;
		}
		e = s2 >> e;
	}		
	return *this;
}

//���� 
QUEUE& QUEUE::operator=(const QUEUE&s)//�����Ѿ��������ˣ�ֻ��û�и�ֵ------------------------------------ 
{
	s1 = s.s1;
	s2 = s.s2;
	return (*this);
}

void  QUEUE::print() const //�������   fprintf(stream,"  %d",value);
{
	int x = s2;
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
	for (int i = 0; i < s1; i++)
		fprintf(stream,"  %d",s1[i]);
}
QUEUE::~QUEUE() //���� 
{

	s1.~STACK();
	s2.~STACK();
	
}

int main(int argc,char *argv[])
{
	int num=1;//��¼�����ڼ������� 
	int i=0;//����ѭ������ 
	int flag=0;//�����ж��Ƿ����쳣�˳� 
	int inmax,amax,Gnum;//�����ջ�Ĵ�С������ָ��-Aջ�Ĵ�С ,��Ҫ���ص�λ�� 
	int jishu;//���ڳ�ջ���� 
	int value;//��ջ������ 
	int &e=value;//��ջ����ʱ�����֣�Ҳ��value�Ŀռ� 
	QUEUE *myqueue,*newcqueue,*newaqueue;//ջָ��,��û�з���ռ� 
	stream = fopen("U201514482_5.txt", "w" ); //�ļ��� 
	while(num < argc)//û�д����� 
	{
		if(strcmp(argv[num],"-S") == 0)//�������� 
		{
			num = num + 1;//��ȡ��һ�����������еĴ�С 
			inmax = atoi(argv[num]);//���еĴ�С
			myqueue = new QUEUE(inmax);//�������� 
			fprintf(stream,"S  %d",inmax);
			num++;
		}
		//����------------------------------------------------------------------- 
		else if(strcmp(argv[num],"-I") == 0)//�����,���ֱ�ӷ��أ����E���ܺ���Ĳ��� 
		{
			num++;
			//����Ϊ������ջ��Ϊ��ʱ����ѭ�� 
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0))
			{
				if(myqueue->full())//ջ����
				{
					flag=1;
					break;
				} 
				value = atoi(argv[num]);//��ջ��ֵ
				*myqueue<<value;//��ջ
				num++; 
			}
			fprintf(stream,"  I");
			if(flag != 1)//˵�������������˳� 
			{
				myqueue->print();
			
			} 				
			else
			{
				flag=1;
				break;
			} 				
		} 
		else if(strcmp(argv[num],"-O") == 0)//������ 
		{
			num++;
			fprintf(stream,"  O");
			jishu = atoi(argv[num]);//��ջ�ĸ���
			i=0; 
			while((i < jishu))
			{
				if(*myqueue == 0)//����Ϊ�� 
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
		else if(strcmp(argv[num],"-C") == 0)//����һ��ջ 
		{
			fprintf(stream,"  C");
			myqueue->print(); 
			newcqueue=new QUEUE(*myqueue);//������������涨��newcstack����Ϊ�����������������棬��������ͻᱻ���� 
//			myqueue->~QUEUE();
			myqueue = newcqueue;//�����õ�ԭ���ķ��ţ�Ȼ����� 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// ���´���һ��ջ��Ȼ���ԭ����ֵ���� 
		{
			num++;
			fprintf(stream,"  A");
			myqueue->print();
			amax = atoi(argv[num]);
			newaqueue=new QUEUE(inmax);//ΪA����һ��ջ
			*newaqueue=*myqueue;
//			myqueue->~QUEUE();
			myqueue = newaqueue;
			num++;
		}
		else if(strcmp(argv[num],"-N") == 0)//���ʣ��Ԫ�ظ��� 
		{
			fprintf(stream,"  N");
			int adnum=*myqueue;
			fprintf(stream,"  %d",adnum);
			num++;
		}
		else if(strcmp(argv[num],"-G") == 0)//�����Ӧλ�õ�ֵ
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
