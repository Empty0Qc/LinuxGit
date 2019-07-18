#include<iostream>
#include<queue>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

class BlockQueue
{
private:
    std::queue<int> _list;
    int _cap;
    pthread_mutex_t _mutex;
    pthread_cond_t _productor;
    pthread_cond_t _consumer;
    bool QueueIsFull()
    {
	return(_list.size() == _cap);
    }
    bool QueueIsEmpty()
    {
	return (_list.size() == 0);
    }
public:
    BlockQueue(int cap = 10):_cap(cap)
    {
	pthread_mutex_init(&_mutex,NULL);
	pthread_cond_init(&_productor,NULL);
	pthread_cond_init(&_consumer,NULL);
    }
    ~BlockQueue()
    {
	pthread_mutex_destroy(&_mutex);
	pthread_cond_destroy(&_productor);
	pthread_cond_destroy(&_consumer);

    }
    bool QueuePush(int data)
    {	
	pthread_mutex_lock(&_mutex);
	while(QueueIsFull())
	{
	    printf("queue is full!!\n");
	    pthread_cond_wait(&_productor,&_mutex);
	}
	_list.push(data);
	pthread_mutex_unlock(&_mutex);
	pthread_cond_signal(&_consumer);
    }
    bool QueuePop(int *data)
    {
	pthread_mutex_lock(&_mutex);
	while(QueueIsEmpty())
	{
	    printf("queue is empty!!\n");
	    pthread_cond_wait(&_consumer,&_mutex);
	}
	*data = _list.front();
	_list.pop();
	pthread_mutex_unlock(&_mutex);
	pthread_cond_signal(&_productor);
    }
};

void *thr_consumer(void *arg)
{
    BlockQueue *q = (BlockQueue*)arg;
    while(1)
    {
	int data;
	q->QueuePop(&data);
	 printf("consumer get data:%d\n",data);
    }
}

void *thr_productor(void *arg)
{
    BlockQueue *q = (BlockQueue*)arg;
    int i = 0;
    while(1)
    {
	printf("product put data:%d\n",i);
	q->QueuePush(i++);
	usleep(100000);
    }
}
int main()
{
    BlockQueue q;
    int ret,i;
    pthread_t ctid[4],ptid[4];
    for(i = 0 ; i < 4 ; i++ )
    {
	ret = pthread_create(&ctid[i],NULL,thr_consumer,(void*)&q);
	if(ret != 0)
	{
	    printf("create thread error\n");
	    return -1;
	}
	ret = pthread_create(&ptid[i],NULL,thr_productor,(void*)&q);
	if(ret != 0)
	{
	    printf("create thread error\n");
	    return -1;
	}
    }
    for(i = 0 ; i < 4 ; i++ )
    {
	pthread_join(ctid[i],NULL);
	pthread_join(ptid[i],NULL);
    }
    return 0;   
}
