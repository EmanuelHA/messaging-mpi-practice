#ifndef MPI_WRAPPER_H
#define MPI_WRAPPER_H

#include <mpi.h>
#include <stdio.h>

int init(int *argc, char ***argv, int* rank, int* size);
void finalize();

void run_coordinator();
void run_client();
void run_tests();

#endif // MPI_WRAPPER_H
