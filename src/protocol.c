#include "../include/protocol.h"

void message_alloc(Message *msg, unsigned int length)
{
    msg = (Message*) malloc(sizeof(Message) + (length) + 1);
}