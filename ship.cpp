/* 数学建模-渡轮调度问题
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
using namespace std;


pthread_mutex_t mutex;
int people = 0,_time = 0,had_go = 0;
void *thr_ship(void *arg)
{
    people = _time * 3 - had_go;
    pthread_mutex_lock(&mutex);
    for(int x = 90; x <= 150; x++)
    {
	while(people >= x)
	{
	printf("One ship with %d people had go\n",people);
    	had_go += people;
    	pthread_mutex_unlock(&mutex);
	}
        _time += 1;	  
	people = _time * 3 - had_go;
    }
}
int main()
{
    pthread_mutex_init(&mutex,NULL);
    int i,ret,x = 90;
    pthread_t tid[2];
    for(i = 0; i < 2; i++)
    {
	ret = pthread_create(&tid[i],NULL,thr_ship,NULL);
	if(ret != 0)
	{
	    printf("error create!!");
	    return -1;
	}
    }
    printf("一天捎了%d人，收入%d元\n",had_go,had_go * 25);
    for(i = 0; i < 2; i++)
    {
	pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
