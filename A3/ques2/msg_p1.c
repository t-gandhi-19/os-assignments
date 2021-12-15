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
#define MAX 10
 
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
 
int main(){
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
 
    key_t key1;
    int msgid1;
    // key_t key2;
    // int msgid2;
   
    key1 = ftok("prog1", 65);
    //errcheck(key1, "Error generating msg key P1\n");
    //key2 = ftok("progf2", 65);
 
    msgid1 = msgget(key1, 0666 | IPC_CREAT);
    //errcheck(msgid1, "Error retrieving queue id P1\n");
    //msgid2 = msgget(key2, 0666 | IPC_CREAT);
 
    int counter = 0;
    while(counter<=49){
    message.mtype = counter + 1;
    strcpy(message.d1.str, list[counter]); message.d1.index = counter;
    counter++;
    strcpy(message.d2.str, list[counter]); message.d2.index = counter;
    counter++;
    strcpy(message.d3.str, list[counter]); message.d3.index = counter;
    counter++;
    strcpy(message.d4.str, list[counter]); message.d4.index = counter;
    counter++;
    strcpy(message.d5.str, list[counter]); message.d5.index = counter;
    counter++;
    counter = counter -5;
 
    errcheck( msgsnd(msgid1, &message, sizeof(message), 0), "Error sending message P1\n");
   
    errcheck( msgrcv(msgid1, &sendBack, sizeof(sendBack), counter + 2, 0), "Error receiving message P1\n");
   
    counter = sendBack.ind + 1;
    printf("%d\n", counter);
    }
 
    //printf("hello\n");
    //printf("%d %s %d %s %d %s\n", message.d1.index, message.d1.str, message.d2.index, message.d2.str, message.d3.index, message.d3.str);
    errcheck(msgctl(msgid1, IPC_RMID, NULL), "Error removing queue P1\n");
    //msgctl(msgid2, IPC_RMID, NULL);
    return 0;
}
