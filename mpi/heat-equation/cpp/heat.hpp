#pragma once
#include <string>
#include "matrix.hpp"
#include <mpi.h>

// Class for basic parallelization information
struct ParallelData {
    int size;            // Number of MPI tasks
    int rank;
    int nup, ndown;      // Ranks of neighbouring MPI tasks

    ParallelData() {      // Constructor
        // start: query number of MPI tasks and store it in
        // the size attribute of the class

        // Query MPI rank of this task and store it in the rank attribute
        // Determine also up and down neighbours of this domain and store
        // them in nup and ndown attributes, remember to cope with
        // boundary domains appropriatly
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        nup = (rank) ? rank - 1 : MPI_PROC_NULL;
        ndown = (rank + 1 < size) ? rank + 1 : MPI_PROC_NULL;
    };
};

// Class for temperature field
struct Field {
    // nx and ny are the true dimensions of the field. The temperature matrix
    // contains also ghost layers, so it will have dimensions nx+2 x ny+2
    int nx;                     // Local dimensions of the field
    int ny;
    int nx_full;                // Global dimensions of the field
    int ny_full;                // Global dimensions of the field
    double dx = 0.01;           // Grid spacing
    double dy = 0.01;

    Matrix<double> temperature;

    void setup(int nx_in, int ny_in, ParallelData parallel);

    void generate(ParallelData parallel);

    // standard (i,j) syntax for setting elements
    double& operator()(int i, int j) {return temperature(i, j);}

    // standard (i,j) syntax for getting elements
    const double& operator()(int i, int j) const {return temperature(i, j);}

};

// Function declarations
void initialize(int argc, char *argv[], Field& current,
                Field& previous, int& nsteps, ParallelData parallel);

void exchange(Field& field, const ParallelData parallel);
void exchange_nb_init(Field& field, const ParallelData parallel, MPI_Request requests[4]);
void exchange_nb_wait(MPI_Request requests[4]);

void evolve(Field& curr, const Field& prev, const double a, const double dt, const int margin);
void evolve_edges(Field& curr, const Field& prev, const double a, const double dt);
void evolve_inner(Field& curr, const Field& prev, const double a, const double dt, const double inv_dx2, const double inv_dy2);

void write_field(const Field& field, const int iter, const ParallelData parallel);

void read_field(Field& field, std::string filename,
                const ParallelData parallel);

double average(const Field& field, const ParallelData parallel);
