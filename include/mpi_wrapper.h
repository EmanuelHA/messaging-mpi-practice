#ifndef MPI_WRAPPER_H
#define MPI_WRAPPER_H

#include <mpi.h>

bool init(int *argc, char ***argv);

void finalize();

MPI_Request send_msg_async();
MPI_Status receive_msg();

#endif // MPI_WRAPPER_H
