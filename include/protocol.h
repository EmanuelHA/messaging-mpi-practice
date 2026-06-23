#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_BUFFER_LEN 512

typedef enum TAGS {
    MESSAGE     = 1,
    BROADCAST   = 2,
    DISCONNECT  = -1,
} TAG;

typedef struct Message {
    int sender;
    int receiver;
    unsigned int data_length;
    char data[];
} Message;

void message_alloc(Message* msg, unsigned int length);

#endif // PROTOCOL_H
