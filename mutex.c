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
		sleep(1);   //释放
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
		sleep(1);   //释放线程资源
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
		sleep(1);   //释放线程资源
	}
	pthread_exit(NULL);
}
void func(void *arg)
{
	int thread = 0;
	thread = (int)(*((int *)arg));           //类型强制转换
	printf("thread data:%d\n",thread);
}

int main(int argc,char *argv[])
{
	struct psend *psend;           						    //验证结构体指针的用法
	psend = (struct psend *)malloc(sizeof(struct psend));   //使用结构体指针必须进行初始化,不然运行出现段错误。
	int a = 5;
	int b[10];
	printf("b size:%d\n",sizeof(b));      				    //sizeof(b)占用的是数组b在整个内存中占用的字节数
	/*char *yyf = (char *)0xbfe168a4;  						//将16进制数转换成地址
	*yyf = 15;       
	printf("yyf data:%d\n",*yyf);*/
	/*char *mm = "addsdsd";         						//静态字符串变量本身是存在内存只读区
	*(mm+2) = 'Y';*/             						    //在linux中指针指向的字符串常量在只读内存区是不可改变的，如果像这样强制修改则会报段错误。
	//printf("p data:%s\n",mm);
	func(&a);
	psend->data = &a;
	printf("send data:%p\n",psend->data);     			   //打印指针的地址
	printf("send data:%d\n",*(psend->data));   			   //打印指针的值     
	
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