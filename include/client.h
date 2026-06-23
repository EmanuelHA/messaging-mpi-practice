#ifndef CLIENT_H
#define CLIENT_H

#include "protocol.h"
#include <pthread.h>
#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER_LEN 512

typedef struct message_node_t {
    Message* msg;
    struct message_node_t* next;
} message_node_t;

typedef struct network_data {
    int rank_id;
    int is_running;
    message_node_t *queue_head;
    message_node_t *queue_tail;
    pthread_mutex_t queue_mutex;
    
    int argc;
    char **argv;
} network_data_t;

extern network_data_t net_data;

void init_client(int rank, int argc, char **argv);
int send_message(char* msg);

#endif