#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

using namespace std;

class STACK{
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

FILE *stream; 

STACK::STACK(int m):max(m),elems(new int[m])
{
	pos = 0;
}

STACK::STACK(const STACK&s):max(s.max), elems(new int[s.max])//���� ,ջ��û�з���ռ� 
{
	pos = s.pos;
	for(int i=0;i < s.pos;i++)
		*(elems + i)=*(s.elems + i);
}

int STACK::size() const
{
	return max;
}

STACK::operator int() const
{
	return pos;
}

int STACK::operator[](int x) const
{
	return elems[x];
}

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


int main(int argc,char *argv[])
{
	int num=1;//��¼�����ڼ������� 
	int i=0;//����ѭ������ 
	int flag=0;//�����ж��Ƿ����쳣�˳� 
	int inmax,amax,Gnum;//�����ջ�Ĵ�С������ָ��-Aջ�Ĵ�С ,��Ҫ���ص�λ�� 
	int jishu;//���ڳ�ջ���� 
	int value;//��ջ������ 
	int &e=value;//��ջ����ʱ�����֣�Ҳ��value�Ŀռ� 
	STACK *mystack,*newcstack,*newastack;//ջָ��,��û�з���ռ� 
	stream = fopen("U201514482_3.txt", "w" ); //�ļ��� 
	while(num < argc)//û�д����� 
	{
		if(strcmp(argv[num],"-S") == 0)//����ջ 
		{
			num = num + 1;//��ȡ��һ��������ջ�Ĵ�С 
			inmax = atoi(argv[num]);//ջ�Ĵ�С
			mystack = new STACK(inmax);//����ջ 
			fprintf(stream,"S  %d",inmax);
			num++;
		}
		else if(strcmp(argv[num],"-I") == 0)//��ջ ,���ֱ�ӷ��أ����E���ܺ���Ĳ��� 
		{
			num++;
			//����Ϊ������ջ��Ϊ��ʱ����ѭ�� 
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0) && (*mystack != -1))
			{
				value = atoi(argv[num]);//��ջ��ֵ
				*mystack<<value;//��ջ
				num++; 
			}
			fprintf(stream,"  I");
			if((*mystack) != -1)//˵����ջ�������˳� 
			{
				mystack->print();
			
			} 				
			else
			{
				flag=1;
				break;
			} 				
		} 
		else if(strcmp(argv[num],"-O") == 0)//��ջ
		{
			num++;
			fprintf(stream,"  O");
			jishu = atoi(argv[num]);//��ջ�ĸ���
			i=0; 
			while((i < jishu) && (*mystack!= -1))
			{
				*mystack>>e;
				i++;
			}
				
			if(*mystack != -1)
			{
				mystack->print();
			
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
			mystack->print(); 
			newcstack=new STACK(*mystack);//������������涨��newcstack����Ϊ�����������������棬��������ͻᱻ���� 
			mystack->~STACK();
			mystack = newcstack;//�����õ�ԭ���ķ��ţ�Ȼ����� 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// ���´���һ��ջ��Ȼ���ԭ����ֵ���� 
		{
			num++;
			fprintf(stream,"  A");
			mystack->print();
			amax = atoi(argv[num]);
			newastack=new STACK(amax);//ΪA����һ��ջ,Ӧ�ý�amax��Ϊmystack->size() 
			*newastack=*mystack;
			mystack->~STACK();
			mystack = newastack;
			num++;
		}
		else if(strcmp(argv[num],"-N") == 0)//���ʣ��Ԫ�� 
		{
			fprintf(stream,"  N");
			int adnum=*mystack;
			fprintf(stream,"  %d",adnum);
			num++;
		}
		else if(strcmp(argv[num],"-G") == 0)//�����Ӧλ�õ�ֵ
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
			{
				int adnum2=(*mystack)[Gnum];
				fprintf(stream,"  %d",adnum2);
			}
				
		} 
	}
	if(flag == 1)
		fprintf(stream,"  E");
	fclose( stream ); 
	return 1;
}

