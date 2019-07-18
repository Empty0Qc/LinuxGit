#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void sigcb(int signo)
{
    printf("recv signo:%d\n",signo);
}

int main()
{
    //sighandler_t signal(int signum, sighandler_t handler);
    // 修改信号在内核中的处理方式
    // signum:	    信号编号
    // handler:	    处理方式
    //	    SIG_DFL 默认处理方式
    //	    SIG_IGN 忽略处理方式
    //	    typedef void(*sighandler_t)(int)
    //signal(SIGQUIT,SIG_IGN);
    //signal(SIGQUIT,sigcb);

    //int kill(pid_t pid, int sig);
    // pid : 指定的进程id 
    // sig : 发送的信号编号 /usr/include/bits/signum.h
    //kill(getpid(),SIGSEGV);
    
    //int raise(int sig);
    // 给调用进程发送指定信号
    raise(SIGQUIT);

    //void abort(void);
    // 给调用程序发送SIGABRT信号
    //abort();
    
    //unsigned int alarm(unsigned int seconds);
    //	定时器: 在seconds秒之后向调用进程发送SIGALRM信号
    //alarm(3);
    //sleep(1);
    //alarm(5);
    while(1)
    {
	printf("hello word!\n");
	sleep(1);
    }
    return 0;
}
