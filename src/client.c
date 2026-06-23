#include "../include/client.h"
#include "../include/gui.h"

network_data_t net_data;

int send_message(char* msg_text)
{
    if ((msg_text == NULL) || (strlen(msg_text) == 0)) return 0;
    
    int text_len = strlen(msg_text);
    
    Message *msg = calloc(1, sizeof(Message) + text_len + 1);
    if (!msg) return 0;

    msg->sender = net_data.rank_id;
    //TODO: Add send user selection system to direct msg (default mode: BCAST)
    msg->receiver = BROADCAST;
    msg->data_length = text_len;
    strncpy(msg->data, msg_text, text_len);
    
    message_node_t *node = calloc(1, sizeof(message_node_t));
    if (!node) {
        free(msg);
        return 0;
    }
    node->msg = msg;
    node->next = NULL;

    pthread_mutex_lock(&net_data.queue_mutex);
    if (net_data.queue_tail == NULL)
    {
        net_data.queue_head = node;
        net_data.queue_tail = node;
    } else {
        net_data.queue_tail->next = node;
        net_data.queue_tail = node;
    }
    pthread_mutex_unlock(&net_data.queue_mutex);
    
    return 1;
}

void init_client(int rank, int argc, char **argv)
{
    net_data.rank_id = rank;
    net_data.is_running = 1;
    net_data.queue_head = NULL;
    net_data.queue_tail = NULL;
    net_data.argc = argc;
    net_data.argv = argv;
    pthread_mutex_init(&net_data.queue_mutex, NULL);

    pthread_t gui_thread;
    pthread_create(&gui_thread, NULL, launch_gui_thread, NULL);

    int flag;
    MPI_Status status;

    while (net_data.is_running)
    {
        pthread_mutex_lock(&net_data.queue_mutex);
        if (net_data.queue_head != NULL)
        {
            message_node_t *node = net_data.queue_head;
            Message *msg = node->msg;
            net_data.queue_head = node->next;
            if (net_data.queue_head == NULL) net_data.queue_tail = NULL;
            pthread_mutex_unlock(&net_data.queue_mutex);

            int size = sizeof(Message) + msg->data_length + 1;
            MPI_Send(msg, size, MPI_BYTE, 0, MESSAGE, MPI_COMM_WORLD);
            
            free(msg);
            free(node);
        }
        else
        {
            pthread_mutex_unlock(&net_data.queue_mutex);
        }

        MPI_Iprobe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
        if (flag) {
            int count;
            MPI_Get_count(&status, MPI_BYTE, &count);
            
            Message *msg_in = calloc(1, count);
            MPI_Recv(msg_in, count, MPI_BYTE, 0, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            char buffer[MAX_BUFFER_LEN] = {0};
            char data[MAX_BUFFER_LEN] = {0};
            strncpy(data, msg_in->data, msg_in->data_length);
            
            snprintf(buffer, 511, "[Rank %d]: %s\n", msg_in->sender, data);
            show_text(buffer); 
            
            free(msg_in);
        }
    }

    pthread_join(gui_thread, NULL);
    pthread_mutex_destroy(&net_data.queue_mutex);
}