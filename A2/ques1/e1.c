#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/time.h>
#include<sys/types.h>
#include <assert.h>
#include <stdint.h>
 
int pid;
void SR_handler(int sig){
    int64_t number = 0;
    __asm__ volatile("rdrand %0"  : "=r" (number));
    int sd = number;
    //printf("%lld\n", number);
    printf("inside sr random no. = %d\n", sd);
    int ret;
    union sigval value;
    value.sival_int = number;
    ret = sigqueue(pid, SIGTERM, value);
    if(ret)
        perror("sigqueue");
    //kill(pid, SIGTERM);
}
 
int main(int argc, char *argv[]){
    printf("e1 starts\n");
    int x;
    sscanf(argv[1], "%d", &x);
    //printf("%d\n",x);
    pid = x;
 
    struct sigaction sAction;
    sAction.sa_flags =0;
    sAction.sa_handler = &SR_handler;
    sigemptyset(&sAction.sa_mask);
    sigaction(SIGALRM, &sAction, NULL);
   
    struct itimerval tv;
    tv.it_value.tv_sec = 1;
    tv.it_value.tv_usec = 0;
    tv.it_interval.tv_sec = 1;
    tv.it_interval.tv_usec = 0;
    int iRet = setitimer(ITIMER_REAL, &tv, NULL);
    assert(iRet != -1);
    for(;;);
    return 0;
}

