#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<signal.h>

void sig_catch(int signu){          //系统传参
    printf("catch signal %d\n",signu);
    alarm(5);                       //循环
}

int main(){
    //注册信号捕捉函数
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sig_catch;
    sigaction(SIGALRM,&act,NULL);
    alarm(5);
    //信号阻塞   SIGALRM
    // sigset_t set;
    // sigemptyset(&set);
    // sigaddset(&set, SIGALRM);
    //sigprocmask(SIG_BLOCK, &set, NULL);
    int i = 0;
    while(1){
    printf("%d\n",i++); 
    sleep(1);
    }
    return 0;
}
