#include "../include/mpi_wrapper.h"
#include <gtk/gtk.h>

// https://docs.open-mpi.org/en/main/man-openmpi/man3/MPI_Init_thread.3.html
int init(int *argc, char*** argv, int* rank, int* size)
{
    gtk_init(argc, argv);

    int provided;
    MPI_Init_thread(argc, argv, MPI_THREAD_FUNNELED, &provided);
    
    if (provided < MPI_THREAD_FUNNELED) {
        printf("ERR: System has no support for MPI_THREAD_FUNNELED.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, size);

    return 0;
}

void finalize()
{
    MPI_Finalize();
}