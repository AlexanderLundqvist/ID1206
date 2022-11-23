#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <mqueue.h>

/* -----------------------------------------------------------------------------
Part 2
In this part, you will work with message queues. You need to implement two
processes, such that the first process reads the content of a text file and passes it
to the second process through a message queue. Upon receipt of the file content,
the second process should count and print out the number of words in the file.

This file is responsible for the process that reads the contents of a text file
and sends it to the message queue.The file "Words.txt" contains 42 words.

Written by Max Dern and Alexander Lundqvist
2022-11-13
----------------------------------------------------------------------------- */

#define MAX_MESSAGE_SIZE 2048
#define MAX_NUM_MESSAGES 10

int main() {
    /*
    Create/open the message queue.
    */
    char *messageQueue = "/queue";
    mqd_t messageQueueDescriptor;
    struct mq_attr attributes;
    attributes.mq_msgsize = MAX_MESSAGE_SIZE;
    attributes.mq_maxmsg = MAX_NUM_MESSAGES;
    messageQueueDescriptor = mq_open(messageQueue, O_CREAT | O_WRONLY, (S_IRUSR | S_IWUSR), &attributes);

    /*
    Open the text file and read the contents.
    */
    char fileContent[MAX_MESSAGE_SIZE];
    FILE *filePointer;
    filePointer = fopen("Words.txt", "r");
    fgets(fileContent, MAX_MESSAGE_SIZE, filePointer);

    /*
    Send the messages and then close the queue.
    */
    mq_send(messageQueueDescriptor, fileContent, strlen(fileContent) + 1, 0);
    mq_unlink(messageQueue);
    mq_close(messageQueueDescriptor);
    return 0;
}
