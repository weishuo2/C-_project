#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

struct STACK{
    int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
    int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ���ﵽ-C��Ч�� 
int  size (const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany (const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem (const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p������-A�ȸ�A����ռ䣬�ٸ�ֵ��A 
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ

FILE *stream; 

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
	mystack = (STACK *)malloc(sizeof(STACK));
	newastack = (STACK *)malloc(sizeof(STACK));
	newcstack = (STACK *)malloc(sizeof(STACK));
	STACK &tidai=*mystack;//mystack��Ӧ�� 
	stream = fopen("U201514482_1.txt", "w" ); //�ļ��� 
	while(num < argc)//û�д����� 
	{
		if(strcmp(argv[num],"-S") == 0)//����ջ 
		{
			num = num + 1;//��ȡ��һ��������ջ�Ĵ�С 
			inmax = atoi(argv[num]);//ջ�Ĵ�С
			initSTACK(mystack,inmax);//����ջ 
			fprintf(stream,"S  %d",inmax);
			num++;
		}
		else if(strcmp(argv[num],"-I") == 0)//��ջ ,���ֱ�ӷ��أ����E���ܺ���Ĳ��� 
		{
			num++;
			//����Ϊ������ջ��Ϊ��ʱ����ѭ�� 
			while((num<argc)&&(strcmp(argv[num],"-S") != 0) && (strcmp(argv[num],"-I") != 0) && (strcmp(argv[num],"-G") != 0) && (strcmp(argv[num],"-O") != 0) && (strcmp(argv[num],"-A") != 0) && (strcmp(argv[num],"-C") != 0) && (strcmp(argv[num],"-N") != 0) && (mystack != NULL))
			{
				value = atoi(argv[num]);//��ջ��ֵ
				mystack=push(mystack,value);//��ջ
				num++; 
			}
			fprintf(stream,"  I");
			if(mystack == NULL)//˵����ջ�������˳� 
			{
				flag=1;
				break;
			} 				
			else
				print(mystack);
		} 
		else if(strcmp(argv[num],"-O") == 0)//��ջ
		{
			num++;
			fprintf(stream,"  O");
			jishu = atoi(argv[num]);//��ջ�ĸ���
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
		else if(strcmp(argv[num],"-C") == 0)//����һ��ջ 
		{
			fprintf(stream,"  C");
			print(mystack);
			initSTACK(newcstack,tidai);
			mystack = newcstack;//�����õ�ԭ���ķ��ţ�Ȼ����� 
			num++;
		}
		else if(strcmp(argv[num],"-A") == 0)// ���´���һ��ջ��Ȼ���ԭ����ֵ���� 
		{
			num++;
			fprintf(stream,"  A");
			print(mystack);
			amax = atoi(argv[num]);
			initSTACK(newastack,amax);//ΪA����һ��ջ
			mystack=assign(newastack,tidai);
		//	mystack = newastack;
			num++;
		}
		else if(strcmp(argv[num],"-N") == 0)//���ʣ��Ԫ�� 
		{
			fprintf(stream,"  N");
			fprintf(stream,"  %d",mystack->pos);
			num++;
		}
		else if(strcmp(argv[num],"-G") == 0)//�����Ӧλ�õ�ֵ
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

//ջ 
void initSTACK(STACK *const p, int m)
{
	p->elems = (int *)malloc(sizeof(int) * m);//����m�������ռ� 
	p->max = m;
	p->pos = 0;
}

void initSTACK(STACK *const p, const STACK&s)//ʵ��-C�Ĺ��� 
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

int  getelem (const STACK *const p, int x)//�ڵ����������ǰҪ���ж�x�Ƿ�Ϸ� 
{
		return *(p->elems + x);
}

STACK *const push(STACK *const p, int e)//������ջʱ����NULL 
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

STACK *const pop(STACK *const p, int &e)//���ܳ�ջʱ����NULL 
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

//�������ж�A�Ĵ�С�Ƿ�С��ԭ����ջ 
STACK *const assign(STACK*const p, const STACK&s)//��ΪA����ռ䣬Ȼ������s��A���и�ֵ 
{
	p->elems = (int *)realloc(p->elems,sizeof(int)*(s.max));
	p->max = s.max;		
	p->pos = s.pos;
	for(int i=0;i < s.pos;i++)
		*(p->elems + i)=*(s.elems + i);
	return p;
}

void print(const STACK*const p)//��ӡջ 
{
	int value=0;
	for(int i=0;i < p->pos;i++)
	{
		value =p->elems[i];
		fprintf(stream,"  %d",value);
	}
	
}

void destroySTACK(STACK*const p)//����ջ 
{
	free(p->elems);
	free(p);
} 


