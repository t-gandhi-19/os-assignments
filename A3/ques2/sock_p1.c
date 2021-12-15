#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
 
#define SOCK_PATH "echo_socket"
 
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
 
int main(void)
{
    int s, s2, t, len;
    struct sockaddr_un local, remote;
    char str[100];
 
    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
 
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }
 
    if (listen(s, 1) == -1) {
        perror("listen");
        exit(1);
    }
 
    if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
    }
    printf("Connected.\n");
 
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
 
    errcheck(send(s2, msg, strlen(msg), 0), "Error writing to socket!\n");
    char buffer[1024];
 
    errcheck(recv(s2, buffer, 1024, 0), "Error reading from FIFO!\n");
 
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
    return 0;
   
}
