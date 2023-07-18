#include <stdlib.h>
#include <stdio.h>
#include<fcntl.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
#define SYS_initialK  448
#define SYS_writerK  449
 
#define QueueSz 8
 
int main(){
    long enqueueData;
 
    syscall(SYS_initialK,QueueSz);
 
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd<0){perror("File not opening\n"); exit(1);}          
   
    while(1){
        int size = read(fd, &enqueueData, sizeof(enqueueData));
 
        if(size<0){perror("File not read\n"); exit(1);}
 
        printf("send/enqueue data: %ld\n", enqueueData);
        sleep(1);
        syscall(SYS_writerK, enqueueData, QueueSz);    
    }
    close(fd);
    return 0;
}
