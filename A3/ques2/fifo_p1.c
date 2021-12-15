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
    char list[50][6];
    int index;
    int wordIndex;
    char randChar;
    for(index = 0; index<50; index++){
       for(wordIndex = 0; wordIndex < 5; wordIndex++){  
       randChar = 'A' + (rand() % 26);
       list[index][wordIndex] = randChar;
       }
    list[index][5] = '\0';
    //printf("%s\n", list[index]);
    }
 
    struct data d1;
    struct data d2;
    struct data d3;
    struct data d4;
    struct data d5;
    struct data d6;
 
 
    char filename1[MAX_FILENAME_SIZE];
    strcpy(filename1, "P1_write_fifo");
 
    errcheck(mkfifo(filename1, 0777), "Error creating FIFO!\n");
 
    char filename2[MAX_FILENAME_SIZE];
    strcpy(filename2, "P1_read_fifo");
 
    errcheck(mkfifo(filename2, 0777), "Error creating FIFO!\n");
 
 
    // * Open FIFO for writing (blocking mode)
    int fifo_fd1 = errcheck(open(filename1, O_WRONLY), "Error opening FIFO!\n");
    int fifo_fd2 = errcheck(open(filename2, O_RDONLY), "Error opening FIFO!\n");
   
    int counter = 0;
    while(counter <=49){
    d1.str = list[counter]; d1.index = counter;
    counter++;
    d2.str = list[counter]; d2.index = counter;
    counter++;
    d3.str = list[counter]; d3.index = counter;
    counter++;
    d4.str = list[counter]; d4.index = counter;
    counter++;
    d5.str = list[counter]; d5.index = counter;
    counter++;
   
    char msg[100];
 
    sprintf(msg, "%s %d %s %d %s %d %s %d %s %d \0", d1.str ,d1.index , d2.str, d2.index, d3.str, d3.index, d4.str, d4.index, d5.str, d5.index);
 
    errcheck(write(fifo_fd1, msg, strlen(msg)), "Error writing to FIFO!\n");
   
    char buffer[BUFFLEN];
 
    errcheck(read(fifo_fd2, buffer, BUFFLEN), "Error reading from FIFO!\n");
 
    char *tok;
    char *rest = buffer;
    int a;
    int c = 0;
    while((tok = strtok_r(rest, " ", &rest))){
        c++;
        sscanf(tok, "%d", &a);
        //printf("%d\n", a);
        counter = a;
        break;
    }  
   
    counter++;
    printf("%d\n", counter);
    }
   
    errcheck(close(fifo_fd1), "Error closing FIFO!\n");
    errcheck(close(fifo_fd2), "Error closing FIFO!\n");
   
 
    errcheck(remove(filename1), "Error removing FIFO!\n");
    errcheck(remove(filename2), "Error removing FIFO!\n");
 
    exit(EXIT_SUCCESS);
}
