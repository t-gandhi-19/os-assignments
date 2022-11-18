#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/time.h>
#include <assert.h>
 
void S1_handler(int sig, siginfo_t *info, void *uncontext){
    //int a = info->si_value.sival_int;
    //printf("jk\n");
    union sigval val = info->si_value;
    //char *b = (char*)malloc(10*sizeof(char));
    //char (*b)[10];
    //b = val.sival_ptr;
    //b = info->si_value.sival_ptr;
    //printf("%s\n", val.sival_ptr);
    //int a  = info->si_pid;
    printf("inside s1 = %d\n", val.sival_int);
    //printf("%d\n", b);
}
 
int main(){
    pid_t ps1;
    ps1 = fork();
    if(ps1<0){
        return 1;
    }
    if(ps1 == 0){
        printf("S1 starts\n");
        struct sigaction sAction;
        sAction.sa_flags = SA_SIGINFO;
        sAction.sa_sigaction = &S1_handler;
        sigemptyset(&sAction.sa_mask);
        sigaction(SIGTERM, &sAction, NULL);
        for(;;);
    }
    else{
        pid_t psr;
        psr = fork();
        if(psr < 0){
            printf("ghh\n");
            return 1;
        }
        if(psr == 0){
            //printf("%d\n", ps1);
            char pidS1[30];
            sprintf(pidS1, "%d", ps1);
            char *args[] = {"./e1", pidS1, NULL};
            execvp(args[0], args);
        }
        pid_t pst;
        pst = fork();
        if(pst < 0){
            return 1;
        }
        if(pst == 0){
            char pidS2[64];
            sprintf(pidS2, "%d", ps1);
            char *args[] = {"./e2", pidS2, NULL};
            execvp(args[0], args);
        }
        sleep(7);
        kill(psr, SIGINT);
        kill(pst, SIGINT);
    }
    return 0;
}
