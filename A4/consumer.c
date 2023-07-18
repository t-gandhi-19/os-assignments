#include <stdlib.h>
#include <stdio.h>
#include<fcntl.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
#define SYS_readerK  450
 
#define QueueSz 8
 
int main(){
    long dequeueData;  
    while(1){
        sleep(1);
        syscall(SYS_readerK,&dequeueData, QueueSz);
        printf("received/dequeued data: %ld\n",dequeueData);
    }
    return 0;
}
