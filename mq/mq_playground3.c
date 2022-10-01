#include "unique_record_struct.h"
#include "../process.c"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_TEXT 512   //maximum length of the message that can be sent allowed. Note: If this is not 512, the message does not go through

struct my_msg{
    long int msg_type;
    char some_text[MAX_TEXT];
 };

// extern struct uniqueRecordStruct uniqueRecordArray;

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
    // struct uniqueRecordStruct uniqueRecordArray;

    // uniqueRecordArray.colSize = 6;
    // uniqueRecordArray.rowSize = 120;
   
    // strcpy(uniqueRecordArray.uniqueValue, 
    // "Hey, my name is Chris and I am a Computer science PhD student at Oklahoma State University, Stillwater OK. Its nice to meet you!Title,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,QuantityTitle,Book category,Star rating,Price,Stock,Quantity");

    // strcpy(uniqueRecordArray.recordArray[0][0], "Chris");
    
    int row = 0;
    int col = 0;

    struct uniqueRecordStruct uniqueRecordArray = readFileByUniqueValue("../txtfiles/bookInfo1.txt", "Stock", "In stock", &row, &col);

    // for (int i = 0; i < uniqueRecordArray.rowSize; i++) {
    //     for (int j = 0; j < uniqueRecordArray.colSize; j++) {
    //         printf("Item: %s\n", uniqueRecordArray.recordArray[i][j]);
    //     }
    // } 

    if(msgsnd(msgid, (void *)&uniqueRecordArray, MAX_TEXT, 0) == -1) { // msgsnd returns -1 if the message is not sent
        printf("Msg not sent\n");
    } else {
        printf("Message sent!\n");
    }


    
    // for (int i = 0; i < uniqueRecordArray.rowSize; i++) {
    //     for (int j = 0; j < uniqueRecordArray.colSize; j++) {

    //         char colItem[MAX_TEXT];
    //         strcpy(colItem, uniqueRecordArray.recordArray[i][j]);

    //         int result = 0;
    //         for (int k = 0; k < MAX_TEXT; k++) {
    //             result++;
    //         }

    //         if(msgsnd(msgid, (void *)&colItem, MAX_TEXT, 0) == -1) { // msgsnd returns -1 if the message is not sent
    //             printf("Msg not sent\n");
    //         } else {
    //             printf("Message sent!\n");
    //         }

    //     }
    // } 
}

void receive(int msgid) {
    struct uniqueRecordStruct myRecord;

    long int msg_to_rec=0;
    msgrcv(msgid, (void *)&myRecord, BUFSIZ, msg_to_rec, 0);  

    printf("Row size is %d and the col size is %d\n", myRecord.rowSize, myRecord.colSize);
    
    for (int i = 0; i < myRecord.rowSize; i++) {
        for (int j = 0; j < myRecord.colSize; j++) {

            // char colItem[300];
            // msgrcv(msgid, (void *)&colItem, BUFSIZ, msg_to_rec, 0); 

            // printf("Data received: %s\n", colItem);

            printf("Data received: %s\n", myRecord.recordArray[i][j]);    
        }
        printf("\n");
    }

    // msgrcv(msgid, (void *)&colItem, BUFSIZ, msg_to_rec, 0); 

    // printf("Data received: %s\n", myRecord.recordArray[][]);               
   
    msgctl(msgid, IPC_RMID, 0);
}