#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 840;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, istart, istop;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Computing approximation to pi with N=%d, rank=%d\n", n, rank);

    if (rank == 0) {
        istart = 1;
        istop = n / 2 - 1;
    } else {
        istart = n / 2;
        istop = n;
    }

    double pi = 0.0;
    for (int i=istart; i <= istop; i++) {
        double x = (i - 0.5) / n;
        pi += 1.0 / (1.0 + x*x);
    }

    if (rank != 0) {
        MPI_Send(&pi, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
        MPI_Finalize();
        return 0;
    }

    double pi2;
    MPI_Recv(&pi2, 1, MPI_DOUBLE, 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    pi += pi2;

    double pi_serial = 0.0;
    for (int i=1; i <= n; i++) {
        double x = (i - 0.5) / n;
        pi_serial += 1.0 / (1.0 + x*x);
    }
    pi *= 4.0 / n;
    pi_serial *= 4.0 / n;

    printf("Approximate pi=%18.16f\nSerial pi=%18.16f\nExact pi=%10.8f\n", pi, pi_serial, M_PI);
    MPI_Finalize();
}
