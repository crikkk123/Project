#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdlib.h>

#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

#define LINE_MAX_SIZE 256
#define API_NAME_MAX_LEN 128
#define TIMEOUT 0.001

typedef struct logNode{
    char api_name[API_NAME_MAX_LEN];       //接口名字
    int visits;                         //访问次数
    double total_response_time;         //visits次访问响应的时间和
    int timeout_visits;                 //超时访问的次数
    double average_response_time;       //平均响应时间
    struct logNode* pnext;
}logNode;

logNode* head = NULL;

char* get_parse_line(FILE* fp, char* log_buf, char* api_name, double* d_response_time){
    char* response_time;
    //从文件中读取一行
    char*ret = fgets(log_buf, LINE_MAX_SIZE, fp);
    //如果fgets读到了文件末尾会返回NULL
    if(ret == NULL){
        return NULL;
    }
    //strchr函数目的：在log_buf中找到第一次出现 空格 的位置，返回该指针
    api_name = strchr(log_buf, ' ') + 1;
    //strchr函数目的：在api_name中找到第一次出现 空格 的位置，返回该指针
    response_time = strchr(api_name, ' ');
    *response_time = '\0';
    response_time++;
    *d_response_time = atof(response_time);
    return api_name;
}

logNode* nodeinit(const char* api_name, double d_response_time){
    logNode* node = (logNode*)malloc(sizeof(logNode));
    bzero(node->api_name, API_NAME_MAX_LEN);       //接口名字
    node->visits = 0;                         //访问次数
    node->total_response_time = 0;         //visits次访问响应的时间和
    node->timeout_visits = 0;                 //超时访问的次数
    node->average_response_time = 0;       //平均响应时间
    node->pnext = NULL;
    strcpy(node->api_name, api_name);
    node->visits = 1;
    node->total_response_time = d_response_time;
    if(d_response_time > TIMEOUT){
        node->timeout_visits = 1;
    }
    return node;
}

int process_one_log(const char* api_name, double d_response_time){
    if(head == NULL){
        logNode* node = nodeinit(api_name, d_response_time);
        head = node;
        return 0;
    }
    else{
        logNode* temp;
        logNode* prev_temp;
        for(temp = head; temp != NULL; temp = temp->pnext){
            prev_temp = temp;
            if(strcmp(api_name, temp->api_name) == 0){
                temp->visits++;
                temp->total_response_time += d_response_time;
                if(d_response_time > TIMEOUT){
                    temp->timeout_visits++;
                }
                return 0;
            }
        }
        if(temp == NULL){
            logNode* node = nodeinit(api_name, d_response_time);
            prev_temp->pnext = node;
            return 0;
        }
    }
}

void average_response_time(logNode* head){
    logNode* temp;
    for(temp = head; temp!= NULL; temp = temp->pnext){
        temp->average_response_time = temp->total_response_time / temp->visits;
    }

}

//链表排序
logNode* merge(logNode* l1, logNode* l2) {
    if (!l1 && l2) {
        return l2;
    }
    if (l1 && !l2) {
        return l1;
    }
    if (l1 == l2) {
        return l1;
    }
    if (l1->visits > l2->visits) {
        l1->pnext = merge(l1->pnext, l2);
        return l1;
    }
    else {
        l2->pnext = merge(l1, l2->pnext);
        return l2;
    }
}
logNode* sort_list(logNode* head) {
    if (!head || !head->pnext) {
        return head;
    }
    logNode* slow = head;
    logNode* fast = head;
    logNode* pre = head;
    while (fast && fast->pnext) {
        pre = slow;
        slow = slow->pnext;
        fast = fast->pnext->pnext;
    }
    pre->pnext = NULL;
    return merge(sort_list(head), sort_list(slow));
}

//打印链表
void print_list(logNode* head){
    logNode* temp;
    for(temp = head; temp!= NULL; temp = temp->pnext){
        printf(LIGHT_RED"visits"NONE);
        printf(" = %d      \t", temp->visits);
        printf(LIGHT_PURPLE"timeout_visits"NONE);
        printf(" = %d      \t", temp->timeout_visits);
        printf(LIGHT_CYAN"average_response_time"NONE);
        printf(" = %lf \t", temp->average_response_time);
        printf(BROWN"total_response_time"NONE);
        printf(" = %lf  \t", temp->total_response_time);
        printf(BROWN"api_name"NONE);
        printf(" = %s\n", temp->api_name);
    }
}

int main(int argc, char* argv[])
{
    double d_response_time = 0;//浮点类型的本条日志记录接口的响应时间
    char* api_name;//本条日志记录接口的名字
    char log_buf[LINE_MAX_SIZE];//本条日志
    bzero(log_buf, LINE_MAX_SIZE);
    //打开日志文件
    FILE* fp =  fopen("./server_access.log", "r");
    //循环处理日志文件
    while(1){
        api_name = get_parse_line(fp, log_buf, api_name, &d_response_time);
        //如果读到了文件的末尾，结束循环
        if(api_name == NULL){
            break;
        }
        process_one_log(api_name, d_response_time);
    }

    head = sort_list(head);
    average_response_time(head);
    print_list(head);
    
    return 0;
}

