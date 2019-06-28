#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<error.h>

void *pthread_func1(void *arg);
void *pthread_func2(void *arg);
void *pthread_fun3(void *arg);

int  gsum=0;
pthread_mutex_t mutex;
struct psend{
	int *data;
};
void *pthread_func1(void *arg)
{
	int i =0;
	//for(i=0;i<5;i++)
	while(1)
	{
		//pthread_mutex_lock(&mutex);
		//sleep(1);
		printf("pthread_fun1 sum:%d\n",gsum++);
		//pthread_mutex_unlock(&mutex);
		sleep(1);   //�ͷ�
	}	
	pthread_exit(NULL);
}

void *pthread_fun2(void *arg)
{
	int i = 0;
	//for(i=0;i<5;i++)
	while(1)
	{
		//pthread_mutex_lock(&mutex);
		//sleep(1);
		printf("pthread_fun2 sum:%d\n",gsum++);
		//pthread_mutex_unlock(&mutex);
		sleep(1);   //�ͷ��߳���Դ
	}
	pthread_exit(NULL);
}

void *pthread_fun3(void *arg)
{
	int i = 0;
	//for(i=0;i<5;i++)
	while(1)
	{
		//pthread_mutex_lock(&mutex);
		//sleep(1);
		printf("pthread_fun3 sum:%d\n",gsum++);
		//pthread_mutex_unlock(&mutex);
		sleep(1);   //�ͷ��߳���Դ
	}
	pthread_exit(NULL);
}
void func(void *arg)
{
	int thread = 0;
	thread = (int)(*((int *)arg));           //����ǿ��ת��
	printf("thread data:%d\n",thread);
}

int main(int argc,char *argv[])
{
	struct psend *psend;           						    //��֤�ṹ��ָ����÷�
	psend = (struct psend *)malloc(sizeof(struct psend));   //ʹ�ýṹ��ָ�������г�ʼ��,��Ȼ���г��ֶδ���
	int a = 5;
	int b[10];
	printf("b size:%d\n",sizeof(b));      				    //sizeof(b)ռ�õ�������b�������ڴ���ռ�õ��ֽ���
	/*char *yyf = (char *)0xbfe168a4;  						//��16������ת���ɵ�ַ
	*yyf = 15;       
	printf("yyf data:%d\n",*yyf);*/
	/*char *mm = "addsdsd";         						//��̬�ַ������������Ǵ����ڴ�ֻ����
	*(mm+2) = 'Y';*/             						    //��linux��ָ��ָ����ַ���������ֻ���ڴ����ǲ��ɸı�ģ����������ǿ���޸���ᱨ�δ���
	//printf("p data:%s\n",mm);
	func(&a);
	psend->data = &a;
	printf("send data:%p\n",psend->data);     			   //��ӡָ��ĵ�ַ
	printf("send data:%d\n",*(psend->data));   			   //��ӡָ���ֵ     
	
	pthread_t pid1=0;
	pthread_t pid2=0;
	pthread_t pid3=0;
	
	int ret=0;
	ret = pthread_create(&pid1,NULL,pthread_func1,NULL);
	if(ret != 0)
	{
		perror("pthread_fun1 failed\n");
	}
	ret = pthread_create(&pid2,NULL,pthread_fun2,NULL);
	if(ret != 0)
	{
		perror("pthread_fun2 failed\n");
	}
	ret = pthread_create(&pid3,NULL,pthread_fun3,NULL);
	if(ret !=0)
	{
		perror("pthread_fun3 failed\n");
	}
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	pthread_join(pid3,NULL);
	free(psend);
}