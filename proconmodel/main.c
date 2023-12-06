#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdlib.h>

//生产者消费者模型

pthread_mutex_t mutex;
pthread_cond_t cond;

struct food{
    int nu;
    struct food* next;
};

struct food* head;

int a = 0;
//生产者线程
void* pr(void* arg){
    while(1){
        a = rand() % 500 + 1;
        struct food* node = (struct food*)malloc(sizeof(struct food));
        node->nu = a;
        //node->next = NULL;
        pthread_mutex_lock(&mutex);
        node->next = head;
        head = node;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        printf("++++%d\n", a);
        //sleep(5);
    }
    return NULL;
}
//消费者线程
void* co(void* arg){
    struct food* node;
    while(1){
        pthread_mutex_lock(&mutex);
        while(head == NULL){
            pthread_cond_wait(&cond, &mutex);//让线程阻塞  可以被唤醒的
        }
        node = head;
        head = head->next;
        pthread_mutex_unlock(&mutex);
        printf("------------%d\n", node->nu);
        free(node);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL, pr, NULL);
    pthread_create(&tid2, NULL, co, NULL);
    pthread_create(&tid2, NULL, co, NULL);
    pthread_create(&tid2, NULL, co, NULL);
    pthread_create(&tid2, NULL, co, NULL);
    pthread_create(&tid2, NULL, co, NULL);
    pthread_create(&tid2, NULL, co, NULL);
    pthread_create(&tid2, NULL, co, NULL);
    while(1);
    pthread_exit(NULL);
}

