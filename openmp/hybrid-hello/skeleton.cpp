#include <cstdio>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int rank, thread_id;
    int provided, required=MPI_THREAD_FUNNELED;

    // Initialize MPI with thread support.
    MPI_Init_thread(&argc, &argv, required, &provided);

    // MPI_Comm_size(MPI_COMM_WORLD, &n_tasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Investigate the provided thread support level. */
        printf(
            "Thread support levels:\n"
            "- MPI_THREAD_SINGLE=%d\n"
            "- MPI_THREAD_FUNNELED=%d\n"
            "- MPI_THREAD_SERIALIZED=%d\n"
            "- MPI_THREAD_MULTIPLE=%d\n",
            MPI_THREAD_SINGLE, MPI_THREAD_FUNNELED, MPI_THREAD_SERIALIZED, MPI_THREAD_MULTIPLE
        );
        printf("Provided thread support level: %d\n", provided);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // Find out the MPI rank and thread ID of each thread and print out the results.
    #pragma omp parallel private(thread_id)
    {
        thread_id = omp_get_thread_num();
        printf("I'm thread %d in process %d\n", thread_id, rank);
    }

    MPI_Finalize();
    return 0;
}
