#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int n_tasks;
    MPI_Comm_size(MPI_COMM_WORLD, &n_tasks);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        std::cout << "There are " << n_tasks << " tasks in total." << std::endl;
    }
    if (rank == n_tasks - 1) {
        std::cout << "I'm the last but not least." << std::endl;
    }
    if (rank == 42) {
        std::cout << "I'm the Answer to the Ultimate Question of Life, the Universe, and Everything!" << std::endl;
    }

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int processor_name_length;
    MPI_Get_processor_name(processor_name, &processor_name_length);
    std::cout << "I'm running on the node " << processor_name << " with the rank " << rank << "." << std::endl;

    MPI_Finalize();
}
