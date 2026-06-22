#include "../include/mpi_wrapper.h"
#include "mpi.h"

// https://docs.open-mpi.org/en/main/man-openmpi/man3/MPI_Init_thread.3.html
int init(int *argc, char ***argv) 
{
    int provided;
    MPI_Init_thread(argc, argv, MPI_THREAD_FUNNELED, &provided);

    return 0;
}

void finalize()
{

}