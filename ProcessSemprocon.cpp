
// 无名信号量用于相关进程间同步

#include<iostream>
#include<unistd.h>
#include<semaphore.h>
#include <sys/mman.h>
#include<pthread.h>
using namespace std;

#define N 10

int main(){
    sem_t* sem_space = (sem_t*)mmap(NULL,sizeof(sem_t),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANON,-1,0);
    sem_t* sem_full = (sem_t*)mmap(NULL,sizeof(sem_t),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANON,-1,0);

    int* nums = (int*)mmap(NULL,sizeof(sizeof(int*)*N),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANON,-1,0);

    sem_init(sem_space,1,N);
    sem_init(sem_full,1,0);

    pid_t pid = fork();
    if(pid==0){
        int i = 0;
        while(1){
            sem_wait(sem_space);
            nums[i] = rand()%100+1;
            printf("+++++++%d\n",nums[i]);
            sem_post(sem_full);
            i = (i+1)%N;
            sleep(1);
        }
    }
    if(pid>0){
        int i = 0;
        while(1){
            sem_wait(sem_full);
            printf("---------------%d\n",nums[i]);
            sem_post(sem_space);
            nums[i]=0;
            i =(i+1)%N;
            sleep(2);
        }
    }
    return 0;
}
