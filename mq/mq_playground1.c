#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX 1024

struct message_buffer{
    int msg_type;
    char msg_text[MAX];
};
int read_line(char text[], int n);
void writer(int msg_id);
void reader(int msg_id);

int main(){

    int msg_id;
    pid_t pid;
    msg_id = msgget(IPC_PRIVATE, 0600);
    if(msg_id == -1){
        perror("msgget");
    }
    pid = fork();
    switch(pid){
        case -1:
            perror("fork");
            break;
        case 0:
            reader(msg_id);
            break;
        default:
            writer(msg_id);
            break;
    }
    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}

int read_line(char text[], int n){
    char *ptext;
    int return_value;
    int length;
    ptext = fgets(text, n, stdin);
    if(ptext == NULL){
        return_value = EOF;
    }else{
        length = strlen(text);
        if(length>0 && text[length-1]=='\n'){
            text[length-1]='\0'; //==
        }
        return_value=!EOF;

        printf("The text entered is %s\n", text);
    }
    printf("Return value is %d\n", return_value);
    return return_value;
}

void writer(int msg_id){
    struct message_buffer m;
    m.msg_type = 1;
    // while(read_line(m.msg_text, MAX)!=EOF){
    //     int length;
    //     length = strlen(m.msg_text);

    //     printf("The text written is %s. The length is %d\n", m.msg_text, length);

    //     if(msgsnd(msg_id, &m, length, 0)==-1){
    //         perror("msgsnd");
    //         exit(1);
    //     }
    //     if(msgsnd(msg_id, &m, 0, 0)==-1){
    //         perror("msgsnd");
    //         exit(1);
    //     }
    // }

    int result = 0;
    for (int i = 1; i <= MAX/2; i++){
		result = result + i;
	}

    if (read_line(m.msg_text, MAX)==EOF) {
        return;
    }
    int length;
    length = strlen(m.msg_text);

    printf("The text written is %s. The length is %d\n", m.msg_text, length);

    if(msgsnd(msg_id, &m, length, 0)==-1){
        perror("msgsnd");
        exit(1);
    }
    if(msgsnd(msg_id, &m, 0, 0)==-1){
        perror("msgsnd");
        exit(1);
    }
}

void reader(int msg_id){
    int length, n;
    n=0;
    struct message_buffer m;
    while((length = msgrcv(msg_id, &m, MAX, 0, 0))>0){
        n+=length;
        printf("Here\n");
    }

    printf("The length received is %d\n", length);
    if(length==-1){
        perror("msgrcv");
        exit(1);
    }
    printf("Received number of bytes is %d\n", n);
}