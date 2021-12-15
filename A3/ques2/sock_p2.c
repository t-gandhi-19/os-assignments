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
    int s, t, len;
    struct sockaddr_un remote;
    char str[100];
 
    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
 
    printf("Trying to connect...\n");
 
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }
 
    printf("Connected.\n");
 
    int counter = 0;
    while(counter <=49){
    char buffer[1024];
 
    errcheck(recv(s, buffer, 1024, 0), "Error reading from FIFO!\n");
    printf("%s\n", buffer);
    char sen[2];
   
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
    sprintf(sen, "%d", a);
    //printf("%s\n", sen);
    errcheck(send(s, sen, strlen(sen), 0), "Error writing to FIFO!\n");
    }
 
    close(s);
 
    return 0;
 
}
