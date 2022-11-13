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

This file is responsible for the process reads from the message queue and counts
the words. Start this process first in a shell, then start lab1_part2.c in
another shell.
----------------------------------------------------------------------------- */

#define MAX_MESSAGE_SIZE 2048
#define MAX_NUM_MESSAGES 10

int main() {
    char *messageQueue = "/queue";
    mqd_t messageQueueDescriptor;
    struct mq_attr attributes;
    attributes.mq_msgsize = MAX_MESSAGE_SIZE;
    attributes.mq_maxmsg = MAX_NUM_MESSAGES;
    messageQueueDescriptor = mq_open(messageQueue, O_CREAT | O_RDONLY, (S_IRUSR | S_IWUSR), &attributes);
    char buffer[MAX_MESSAGE_SIZE];
    /*
    Read the message from the message queue
    */
    mq_receive(messageQueueDescriptor, buffer, MAX_MESSAGE_SIZE, NULL);

    /*
    Count the words.
    */
    int words = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ' ') {
            words++;
        }
    }
    printf("Number of words: %d\n", words + 1); // + 1 for the last word

    /*
    Close the queue.
    */
    mq_unlink(messageQueue);
    mq_close(messageQueueDescriptor);
    return 0;
}
