#include "../include/mpi_wrapper.h"
#include "../include/coordinator.h"
#include "../include/client.h"

int main(int argc, char* argv[])
{
    int rank, size;
    init(&argc, &argv, &rank, &size);

    if (rank == COORDINATOR) {
        process_request();
    } else {
        init_client(rank, argc, argv); 
    }

    finalize();
    return 0;
}