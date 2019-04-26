/*  线程的终止与等待
 *	return	pthread_exit  pthread_cancel
 * */


#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<pthread.h>

void *thr_start(void *arg)
{
    //pthread_cancel((pthread_t)arg);
    // void pthread_exit(void *retval);
    // 线程退出，并可以返回一个数据
    sleep(3);
    pthread_exit("Big Cat!!");
    //返回的这个字符串是一个常量 在常量区
    while(1)
    {
	printf("i am child!\n");
	sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_t mtid = pthread_self();//此处去获取主线程的tid 然后传给create 去创建新的
    int ret = pthread_create(&tid,NULL,thr_start,(void*)mtid);
    if(ret != 0)
    {
	printf("thread create error!!\n");
	return -1;
    }
    //int pthread_detach(pthread_t thread);
    //该线程被分离，不需要其他线程等待他退出
    pthread_detach(tid);
    char *ptr;
    //pthread_cancel(tid);
    //线程被取消，则返回值不能作为标准结果，返回值是-1
    ret = pthread_join(tid,(void**)&ptr);
    if(ret == EINVAL)
    {
	printf("thread is not a joinable thread.\n");
    }
    printf("child thread retval:%s\n",ptr);

    // int pthread_join(pthread_t thread, void **retval);
    //等待线程退出，并获取返回值
    // thread:	指定线程
    // retval:	获取返回值
    //int pthread_cancel(pthread_t thread);
    //	取消其他线程
    //pthread_exit(NULL);
    while(1)
    {
	printf("i am main\n");
	sleep(1);
    }
    return 0;
}

