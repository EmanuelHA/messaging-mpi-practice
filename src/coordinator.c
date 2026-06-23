#include "../include/coordinator.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int processed_messages = 0;

int route_message(Message *msg) {
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int total_bytes = sizeof(Message) + msg->data_length + 1;

    if (msg->receiver == BROADCAST) {
        for (int i = 1; i < comm_size; i++) {
            if (i != msg->sender) {
                MPI_Send(msg, total_bytes, MPI_BYTE, i, MESSAGE, MPI_COMM_WORLD);
            }
        }
    }
    return 1;
}

void update_log() {
    processed_messages++;
}

int save_log_to_disk() {
    FILE *f = fopen("messaging.log", "w");
    if(f) {
        fprintf(f, "Total de paquetes enrutados: %d\n", processed_messages);
        fclose(f);
        return 1;
    }
    return 0;
}

int process_request() {
    int flag;
    MPI_Status status;
    printf("[Coordinador] Iniciando en R%d. Escuchando...\n", COORDINATOR);
    
    while (1) {
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
        if (flag) {
            int conteo;
            MPI_Get_count(&status, MPI_BYTE, &conteo);
            
            Message *msg = malloc(conteo);
            MPI_Recv(msg, conteo, MPI_BYTE, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            route_message(msg);
            update_log();
            free(msg);
        }
        // TODO: Add disconnection request handler.
    }
    save_log_to_disk();
    return 0;
}