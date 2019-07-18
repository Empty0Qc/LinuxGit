#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void sigcb()
{   
}
void mysleep(int n)
{
    struct  sigaction act,old;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sigcb;
    sigaction(SIGALRM,&act,&old);
    sigset_t set;
    sigaddset(&set,SIGALRM);
    sigprocmask(SIG_BLOCK,&set,NULL);
    alarm(n);
    //sigprocmask(SIG_UNBLOCK,);
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask,SIGALRM);
    //sigsuspend---临时阻塞mask信号，陷入休眠，被唤醒后阻塞的信号还原回去
    sigsuspend(&mask);//仅仅SIGALRM没有被阻塞
    
    sigaction(SIGALRM,&old,NULL);
}
int main()
{
    mysleep(3);
    printf("-------\n");
    return 0;
}
