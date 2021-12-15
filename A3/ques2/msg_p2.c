
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
struct data
{
    char str[10];
    int index;
};
 
struct pirate_msgbuf {
    long mtype;
    struct data d1;
    struct data d2;
    struct data d3;
    struct data d4;
    struct data d5;
} message;
 
struct index_back {
    long msgType;
    int ind;
}sendBack;
 
int errcheck(int return_value, const char* msg)
{
    if(return_value == -1)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    else
    {
        return return_value;
    }
}
 
int main()
{
    key_t key1;
    int msgid1;
    // key_t key2;
    // int msgid2;
 
    key1 = ftok("prog1", 65);
    //errcheck(key1, "Error generating msg key P2\n");
    //key2 = ftok("progf2", 65);
 
    msgid1 = msgget(key1, 0666 | IPC_CREAT);
   
    //errcheck(msgid1, "Error retrieving queue id P2\n");
   
    int counter = 0;
    // int f = 0;
    // while(f<2){
    //     f++;
    while(counter <= 49){
    errcheck(msgrcv(msgid1, &message, sizeof(message),counter + 1, 0), "Error receiving  message P2\n");
 
    printf("%d %s %d %s %d %s %d %s %d %s\n", message.d1.index, message.d1.str, message.d2.index, message.d2.str, message.d3.index, message.d3.str , message.d4.index, message.d4.str , message.d5.index, message.d5.str);
   
    sendBack.msgType = counter + 2;
    sendBack.ind = message.d5.index;
 
    errcheck(msgsnd(msgid1, &sendBack, sizeof(sendBack), 0),"Error sending message P2\n");
    counter = counter + 5;
    }
   
    return 0;
}
 
