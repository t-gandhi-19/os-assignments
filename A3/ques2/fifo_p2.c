#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
 
#define MAX_FILENAME_SIZE 512
#define BUFFLEN 2048
 
struct data
{
    char *str;
    int index;
};
 
int errcheck(int return_value, const char* msg)
{
    if(return_value < 0)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    else
    {
        return return_value;
    }
}
 
int main(int argc, char *argv[])
{
    char filename1[MAX_FILENAME_SIZE];
    strcpy(filename1, "P1_write_fifo");
 
    char filename2[MAX_FILENAME_SIZE];
    strcpy(filename2, "P1_read_fifo");
   
    int fifo_fd1 = errcheck(open(filename1, O_RDONLY), "Error opening FIFO!\n");
    int fifo_fd2 = errcheck(open(filename2, O_WRONLY), "Error opening FIFO!\n");
 
    int counter = 0;
    while(counter<=49){
    char buffer[BUFFLEN];
 
    errcheck(read(fifo_fd1, buffer, BUFFLEN), "Error reading from FIFO!\n");
   
    printf("%s\n", buffer);
 
    char send[2];
   
    int sz = strlen(buffer);
   
    char *tok;
    char *rest = buffer;
    int a;
    int c = 0;
    while((tok = strtok_r(rest, " ", &rest))){
        c++;
        //printf("%s\n", tok);
        if(c%2 == 0){
        sscanf(tok, "%d", &a);
        //printf("%d\n", a);
        counter = a;
        }
    }
    sprintf(send, "%d", a);
    //printf("%s\n", send);
    errcheck(write(fifo_fd2, send, strlen(send)), "Error writing to FIFO!\n");
 
    //printf("%d\n", counter);
    }
 
    errcheck(close(fifo_fd1), "Error closing FIFO!\n");
    errcheck(close(fifo_fd2), "Error closing FIFO!\n");
 
    exit(EXIT_SUCCESS);
 
}
