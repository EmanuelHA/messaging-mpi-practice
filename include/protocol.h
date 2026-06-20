#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef struct Message {
    int sender;
    int receiver;
    unsigned int data_length;
    char data[];
} Message;

#endif // PROTOCOL_H
