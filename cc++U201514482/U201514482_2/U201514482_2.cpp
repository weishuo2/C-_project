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
	int  size ( ) const;		//����ջ�����Ԫ�ظ���max
	int  howMany ( ) const;	//����ջ��ʵ��Ԫ�ظ���pos
	int  getelem (int x) const;//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
	STACK& push(int e); 	//��e��ջ,������ջ
	STACK& pop(int &e); 	//��ջ��e,������ջ
	STACK& assign(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	void print( ) const;		//��ӡջ
	~STACK( );				//����ջ
};

FILE *stream; 

STACK::STACK(int m):max(m),elems(new int[m])
{
	pos = 0;
}

STACK::STACK(const STACK&s):max(s.max), elems(new int[s.max])//���� 
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

STACK& STACK::pop(int &e)
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
	stream = fopen("U201514482_2.txt", "w" ); //�ļ��� 
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
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0) && (mystack->howMany() != -1))
			{
				value = atoi(argv[num]);//��ջ��ֵ
				mystack->push(value);//��ջ
				num++; 
			}
			fprintf(stream,"  I");
			if(mystack->howMany() == -1)//˵����ջ�������˳� 
			{
				flag=1;
				break;
			} 				
			else
				mystack->print();
		} 
		else if(strcmp(argv[num],"-O") == 0)//��ջ
		{
			num++;
			fprintf(stream,"  O");
			jishu = atoi(argv[num]);//��ջ�ĸ���
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
			newastack=new STACK(amax);//ΪA����һ��ջ
			newastack->assign(*mystack);
			mystack->~STACK();
			mystack = newastack;
			num++;
		}
		else if(strcmp(argv[num],"-N") == 0)//���ʣ��Ԫ�� 
		{
			fprintf(stream,"  N");
			fprintf(stream,"  %d",mystack->howMany());
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
				fprintf(stream,"  %d",mystack->getelem(Gnum));
		} 
	}
	if(flag == 1)
		fprintf(stream,"  E");
	fclose( stream ); 
	return 1;
}

