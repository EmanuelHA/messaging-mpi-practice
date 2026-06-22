#ifndef MPI_WRAPPER_H
#define MPI_WRAPPER_H

#include <mpi.h>

int init(int *argc, char ***argv);
void finalize();

void run_coordinator();
void run_client();
void run_tests();

#endif // MPI_WRAPPER_H
