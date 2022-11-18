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
#include <time.h>
 
int pid;
void ST_handler(int sig){
    uint64_t nr = 0;
    __asm__ volatile("rdtsc\t\n"
                    "shl $32 , %%rdx\t\n"
                    "xor %%rdx , %0\t\n"
                    : "=a" (nr)
                    :
                    : "%rdx");
   
    int64_t c = nr/(2592000000);
    //printf("%llu\n", c);
    int t = c;
    int sec = t%60;
    t = t/60;
    int min = t%60;
    t = t/60;
    int hr = t%24;
    t = t/24;
    int days = t%365;
    t = t/365;
    int years = t;
    printf("inside st timestamp = total seconds:%d time: %d:%d:%d days:%d years:%d\n",c , hr, min, sec, days, years);
    //char buf[10];
    int x = c;
    //char *buf = (char*)malloc(10*sizeof(char));
    //sprintf(buf,"%d:%d:%d\n",sec, min, hr);
    int ret;
    union sigval value;
    //value.sival_ptr = buf;
    value.sival_int = x;
    //printf("string in ST is %s\n", value.sival_ptr);
    //printf("%d\n", value.sival_ptr);
    sigqueue(pid, SIGTERM, value);
    if(ret)
        perror("sigqueue");
    //kill(pid, SIGTERM);
}
 
int main(int argc, char *argv[]){
    printf("e2 starts\n");
    int x;
    sscanf(argv[1], "%d", &x);
    //printf("%d\n",x);
    pid = x;
    struct sigaction sAction;
    sAction.sa_flags =0;
    sAction.sa_handler = &ST_handler;
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
