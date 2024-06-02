
// 信号量实现的多线程的生产者消费者模型

#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include <semaphore.h>

using namespace std;

#define N  10

sem_t sem_space;
sem_t sem_full;

int nums[N];

void* producer(void* arg){
    int i = 0;
    while(1){
        sem_wait(&sem_space);
        nums[i] = rand()%10+1;
        printf("+++++++++++++++++%d\n",nums[i]);
        sem_post(&sem_full);
        i = (i+1)%N;
        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg){
    int i = 0;
    while(1){
        sem_wait(&sem_full);
        printf("-------%d\n",nums[i]);
        nums[i]=0;
        sem_post(&sem_space);
        i = (i+1)%N;
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(){
    sem_init(&sem_space,0,N);
    sem_init(&sem_full,0,0);

    pthread_t tid1,tid2;

    pthread_create(&tid1,NULL,producer,NULL);
    pthread_create(&tid1,NULL,producer,NULL);
    pthread_create(&tid1,NULL,producer,NULL);
    pthread_create(&tid2,NULL,consumer,NULL);
    pthread_create(&tid2,NULL,consumer,NULL);

    pthread_detach(tid1);
    pthread_detach(tid2);

    sem_destroy(&sem_space);
    sem_destroy(&sem_full);

    pthread_exit(NULL);
}

