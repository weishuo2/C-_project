#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

using namespace std;


class QUEUE{
    int  *const  elems;	//�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int   max;	//elems�ܴ�ŵ����Ԫ�ظ���
    int   head, tail;		//����ͷ��β�����п�ʱhead=tail;��ʼʱhead=tail=0
public:
QUEUE(int m);		//��ʼ��ѭ�����У�elems��m��Ԫ��
QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
virtual operator int ( ) const			//���ض��е�ʵ��Ԫ�ظ���
{
	if((tail<0) || (head<0))//˵������кʹ����е�ʱ����� 
		return -1;
	else
		return ((tail - head + max) % max);
} 
virtual int full ( ) const;		       //���ض����Ƿ�������������1�����򷵻�0
virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
virtual QUEUE& operator<<(int e); 	//��e�����,�����ض���
virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
virtual void print( ) const;			//��ӡ����
virtual ~QUEUE( );					//���ٶ���
};

FILE *stream; //�ļ�ָ�� 

QUEUE::QUEUE(int m):max(m),elems(new int[m])//��7���ռ䣬ֻ����6�������һ���������ֶ����Ƿ����� 
{
	head = 0;
	tail = 0;//��һ��Ԫ��Ϊ0�����һ��Ԫ��Ϊm-1 
}

//��� 
QUEUE::QUEUE(const QUEUE&s):max(s.max), elems(new int[s.max])//�ö���s������ʼ������
{
	head = s.head;
	tail = s.tail; 
	for(int i = head;(i%s.max) != s.tail;i++)//tail������û��Ԫ�ص� 
		*(elems + i)=*(s.elems + i);
}


int QUEUE::full ( ) const//���ض����Ƿ�������������1�����򷵻�0
{
	if((tail<0) || (head<0))//˵������кʹ����е�ʱ����� 
		return -1;
	else if(((tail+1)%max) == head)
		return 1;
	else
		return 0;
}	

int QUEUE::operator[ ](int x)const   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
{
	return elems[x];
}


QUEUE& QUEUE::operator<<(int e) 	//��e�����,�����ض���
{
	if((tail+1)%max == head)//�������ˣ�������� 
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


QUEUE& QUEUE::operator>>(int &e) //�����е�e,�����ض���
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

//�����Ѿ��������ˣ�ֻ��û�и�ֵ 
QUEUE& QUEUE::operator=(const QUEUE&s)//��s������,�����ر���ֵ�Ķ���
{
	int *p = (int *)(&max);
	*p = s.max;
	
	
	head = s.head;
	tail = s.tail;//ͷβ 
	for(int i = head;(i%s.max) != s.tail;i++)//tail������û��Ԫ�ص� 
		*(elems + i)=*(s.elems + i);
	return (*this);
}

QUEUE::~QUEUE()					//���ٶ���
{
	if(elems)//�����ظ��ͷ� 
	{
		delete []elems;
		head = 0;
		tail = 0;
	} 
}

void QUEUE::print() const			//��ӡ����
{
	int value=0;
	for(int i = head;(i%max) != tail;i++)//tail������û��Ԫ�ص� 
	{
		i = i % max;  
		value =elems[i];
		fprintf(stream,"  %d",value);
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
	QUEUE *myqueue,*newcqueue,*newaqueue;//ջָ��,��û�з���ռ� 
	stream = fopen("U201514482_4.txt", "w" ); //�ļ��� 
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
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0) && (*myqueue != -1))
			{
				value = atoi(argv[num]);//��ջ��ֵ
				*myqueue<<value;//��ջ
				num++; 
			}
			fprintf(stream,"  I");
			if(*myqueue != -1)//˵�������������˳� 
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
		else if(strcmp(argv[num],"-C") == 0)//����һ��ջ 
		{
			fprintf(stream,"  C");
			myqueue->print(); 
			newcqueue=new QUEUE(*myqueue);//������������涨��newcstack����Ϊ�����������������棬��������ͻᱻ���� 
			myqueue->~QUEUE();
			myqueue = newcqueue;//�����õ�ԭ���ķ��ţ�Ȼ����� 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// ���´���һ��ջ��Ȼ���ԭ����ֵ���� 
		{
			num++;
			fprintf(stream,"  A");
			myqueue->print();
			amax = atoi(argv[num]);
			newaqueue=new QUEUE(amax);//ΪA����һ��ջ
			*newaqueue=*myqueue;
			myqueue->~QUEUE();
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





