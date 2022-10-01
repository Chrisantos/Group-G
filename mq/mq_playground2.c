#include<stdlib.h>
 #include<stdio.h>
 #include<string.h>
 #include<unistd.h>
 #include<sys/types.h>
 #include<sys/ipc.h>
 #include<sys/msg.h>
 #define MAX_TEXT 512   //maximum length of the message that can be sent allowed
 struct my_msg{
         long int msg_type;
         char some_text[MAX_TEXT];
 };

 void send(int msgid);
 void receive(int msgid);

 int main() {

    int msgid;
    pid_t pid;
    
    msgid = msgget(IPC_PRIVATE, 0600);
    if(msgid == -1){
        perror("msgget");
        printf("Error in creating queue\n");
        exit(0);
    }

    pid = fork();
    switch(pid){
        case -1:
            perror("fork");
            break;
        case 0:
            receive(msgid);
            break;
        default:
            send(msgid);
            break;
    }
    return 0;
 }

 void send(int msgid) {
    struct my_msg some_data;

    some_data.msg_type=1;
    strcpy(some_data.some_text, 
    "Hey, my name is Chris and I am a Computer science PhD student at Oklahoma State University, Stillwater OK. Its nice to meet you!");

    if(msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) { // msgsnd returns -1 if the message is not sent
        printf("Msg not sent\n");
    }
 }

 void receive(int msgid) {
    struct my_msg some_data;
    long int msg_to_rec=0;
    msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_rec, 0);                 
    printf("Data received: %s\n", some_data.some_text);
    msgctl(msgid,IPC_RMID,0);
 }