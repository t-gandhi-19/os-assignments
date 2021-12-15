#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
 
#define SYS_delay_vr 448      
     
int main(int argc, char* argv[]){
    int del_time = 1000;   //in msec
 
    struct timeval ch_st, ch_end, p_st, p_end;
 
    int pid = fork();
 
    if(pid==0){  
        printf("Child process pid %d\n",getpid());
 
        gettimeofday(&ch_st, NULL);  
        for(int i=1000000000;i>0;i--);           //task
        gettimeofday(&ch_end, NULL);    
 
        printf("normal process execution time in msec = %lf\n", (double)(ch_end.tv_usec - ch_st.tv_usec)/1000 + (double)(ch_end.tv_sec - ch_st.tv_sec)*1000);
    }
 
 
    else if(pid>0){  
 
        printf("Parent process pid %d\n", getpid());
 
        long rt_Ret = syscall(SYS_delay_vr, (long)getpid() , del_time);   //delay parent
 
        gettimeofday(&p_st,NULL);
        for(int i=1000000000;i>0;i--);
        gettimeofday(&p_end,NULL);
 
        printf("delayed process execution time in msec = %lf\n",(double)(p_end.tv_usec - p_st.tv_usec)/1000 + (double)(p_end.tv_sec - p_st.tv_sec)*1000);
 
    }
 
    else{  
        perror("Fork failed!!!");
        exit(0);
    }
 
    return 0;
}
