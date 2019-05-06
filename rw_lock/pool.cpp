#include<iostream>
#include<queue>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

class MyTask
{
    private:
	void *data;
    public:
	void Run()
	{   
	    srand(time(NULL));
	    int s = rand() % 5;
	    printf("thread %p get data %s sleep -- %d\n",pthread_self(),data,s);
	    sleep(s);
	}
};

class ThreadPool
{
    private:
	std::queue<MyTask *> _list;
	int _cap;
	pthread_mutex_t _mutex;
	pthread_cond_t _full;
	pthread_cond_t _empty;

	int _max_thr;
	static void *thr_start(void *arg)
	{
	    ThreadPool *p = (ThreadPool*)arg;
	    pthread_mutex_lock(&p->_mutex);
	    pthread_mutex_unlock(&p->_mutex);
	    return NULL;   
	}
    public:
	ThreadPool(int thr = 5,int q = 10)
	    :_max_thr(thr), _cap(q)
	{
	    pthread_mutex_init(&_mutex,NULL);
	    pthread_cond_init(&_full,NULL);
	    pthread_cond_init(&_empty,NULL);
	}

	~ThreadPool()
	{
	    pthread_mutex_destroy(&_mutex);
	    pthread_cond_destroy(&_full);
	    pthread_cond_destroy(&_empty); 
	}
	bool Init()
	{
	    int ret,i;
	    pthread_t tid;
	    for(i = 0; i < _max_thr; i++)
	    {
		ret = pthread_create(&tid,NULL,thr_start,(void*)this);
		if(ret != 0)
		{
		    printf("create thread error\n");
		    return false;
		}
	    }
	    pthread_detach(tid);
	    return true;
	}
	bool AddTask(MyTask *task)
	{
	    pthread_mutex_lock(&_mutex);
	    // QueuePush(task);
	    pthread_mutex_unlock(&_mutex);
	    return true;
	}
};

int main()
{
    return 0;
}
