#include <stdlib.h>
#include <stdio.h>
#include<fcntl.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
#define SYS_initialK  448
#define SYS_writerK  449
#define SYS_readerK  450
 
#define QueueSz 8
 
int main(){
    long dequeueData;
    long enqueueData;
 
    syscall(SYS_initialK,QueueSz);
 
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd<0){perror("File not opening\n"); exit(1);}          
   
    pid_t pid = fork();
    if(pid<0){
        perror("Process C not created");
        exit(1);
    }
 
    else if(pid == 0){
        //P process
        while(1){
        int size = read(fd, &enqueueData, sizeof(enqueueData));
 
        if(size<0){perror("File not read\n"); exit(1);}
 
        printf("send/enqueue data: %ld\n", enqueueData);
        sleep(1);
        syscall(SYS_writerK, enqueueData, QueueSz);
       
        }
    }
 
    else{
        //C process
        while(1){
        sleep(1);
        syscall(SYS_readerK,&dequeueData, QueueSz);
        printf("received/dequeued data: %ld\n",dequeueData);
        }
    }
 
    close(fd);
    return 0;
}
