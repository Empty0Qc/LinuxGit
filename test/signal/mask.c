/*  信号的阻塞
 *  int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
 *  how:
 *	    SIG_BLOCK	    阻塞set集合中的信号，将原有阻塞放到old中
 *	    SIG_UNBLOCK	    对set集合中的信号解除阻塞
 *	    SIG_SETMASK	    将set集合中的信号添加到阻塞集合中
 *  *set:	 集合
 *  *oldset:	  
 * */


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void sigcb(int signo)
{
    printf("rev signo:%d\n",signo);
}

int main()
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sigcb;
    act.sa_flags = 0;
    //int sigaction(int signum, const struct sigaction *act,
    //                     struct sigaction *oldact);
    //          signum        信号编号
    //          act	      自定义处理动作 
    //          oldact        保存原有的处理动作
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGRTMIN+5,&act,NULL);
    /* 定义一个集合
     * 向集合中添加要阻塞的信号
     * 阻塞这个集合中的所有信号
     * getchar()
     * 对集合中的信号解除阻塞
     * */
    sigset_t newset,oldset;
    //int sigemptyset(sigset_t *set); 清空集合信号
    sigemptyset(&newset);
    //int sigfillset(sigset_t *set); 将所有信号添加到集合中
    //int sigaddset(sigset_t *set, int signum); 将指定信号添加到集合中
    sigfillset(&newset);
    //int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
    sigprocmask(SIG_BLOCK,&newset,&oldset);
    printf("all signal blocked,enter for  unblocked\n");
    getchar();
    //int sigpending(sigset_t *set);
    //获取未决信号
    sigset_t set;
    sigpending(&set);
    int i = 1;
    for(i = 1; i< 64;i++){
	//int sigismember(const sigset_t *set, int signum);
	//判断指定信号是否在集合中
	if(sigismember(&set,i))	 printf("1 ");
	else printf("0 ");
    }
    sigprocmask(SIG_UNBLOCK,&newset,NULL);
    //sigprocmask(SIG_UNBLOCK,&oldset,NULL))
}

