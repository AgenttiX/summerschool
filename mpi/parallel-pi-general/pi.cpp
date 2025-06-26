#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 847;

double compute_pi(int istart, int istop) {
    double pi = 0.0;
    for (int i=istart; i < istop; i++) {
        double x = (i - 0.5) / n;
        pi += 1.0 / (1.0 + x*x);
    }
    return pi;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, n_tasks;
    MPI_Comm_size(MPI_COMM_WORLD, &n_tasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int n_per_task = n / n_tasks;
    const int n_longer_tasks = n % n_tasks;
    const int n_normal_tasks = n_tasks - n_longer_tasks;
    int istart = rank * n_per_task;
    int istop = istart + n_per_task;
    // All tasks near the end get one extra index to work on
    if (rank >= n_normal_tasks) {
        istart += rank - n_normal_tasks;
        istop += 1;
    }
    printf("Computing pi with n=%d, rank=%d, istart=%d, istop=%d, inds=%d\n", n, rank, istart, istop, istop - istart);

    double pi = compute_pi(istart, istop);
    if (rank) {
        MPI_Send(&pi, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
        MPI_Finalize();
        return 0;
    }
    const double pi_serial = compute_pi(0, n) * 4.0 / n;

    for (int i_task = 1; i_task < n_tasks; i_task++) {
        double pi2;
        MPI_Recv(&pi2, 1, MPI_DOUBLE, i_task, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        pi += pi2;
    }
    pi *= 4.0 / n;
    printf("Approximate pi=%18.16f\nSerial pi=%18.16f\nDifference = %18.16f\nExact pi=%10.8f\n", pi, pi_serial, pi - pi_serial, M_PI);
    MPI_Finalize();
}
