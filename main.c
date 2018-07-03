#include <stdio.h>
#include <zconf.h>
#include "shm_queue.h"
long shmkey = 0x1234;
int element_size = 6400; // 基本块的大小，如果数据小于1个块，就按1个块存储，否则，存储到连续多个块中，只有第一个块有块头部信息
int element_count = 10240; // 队列的长度，总共有多少个块


void producer();
void consumer();
int main(int argc , char *argv[]) {
    if(argc<2){
        goto err;
    }
    if(argv[1][0]=='p'){
        producer();
        return 0;
    }
    if(argv[1][0]=='c'){
        consumer();
        return 0;
    }
    err:
    printf("参数错误,请输入参数 p=启动生产者 c=消费者\n");
    return 0;
}

/*生成者*/
void producer(){
    printf("启动生产者\n");
    struct sq_head_t *sq = sq_create(shmkey, element_size, element_count);
    char buf[255];
    for (int i = 1; i <10000000 ; ++i) {
        for (int j = 0; j <10000000 ; ++j) {
            sprintf(buf,"[%d,%d]",i,j);
            if(sq_put(sq, buf, strlen(buf))<0)
            {
                printf("队列满了\n");

            }else{
                printf("写入数据 %s \n",buf);
            }
            usleep(10000);
        }

    }
}


/*消费者*/
void consumer(){
    printf("启动消费者\n");

    struct sq_head_t *sq = sq_open(shmkey);
    while(1)
    {
        char buffer[255];
        int len = sq_get(sq, buffer, sizeof(buffer),NULL);
        if(len<=0) // 读失败
        {
          //  printf("暂无数据\n");
            usleep(10000);
        }
        else // 收到数据了
        {
            buffer[len]=0;
            printf("取出数据 %s\n",buffer);
        }
    }
}
