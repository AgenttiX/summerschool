// Main solver routines for heat equation solver

#include <mpi.h>

#include "heat.hpp"

constexpr int tag_up = 11;
constexpr int tag_down = 12;

// Exchange the boundary values
void exchange(Field& field, const ParallelData parallel) {
    const int ny = field.temperature.ny;
    // double* sbuf;
    // double* rbuf;

    // You can utilize the data() method of the Matrix class to obtain pointer
    // to element, e.g. field.temperature.data(i, j)

    // Send to up, receive from down
    // MPI_Send(field.temperature.data(1, 0), ny, MPI_DOUBLE, parallel.nup, parallel.rank, MPI_COMM_WORLD);
    // MPI_Recv(field.temperature.data(field.nx+1, 0), ny, MPI_DOUBLE, parallel.ndown, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // Send to down, receive from up
    // MPI_Send(field.temperature.data(field.nx, 0), ny, MPI_DOUBLE, parallel.ndown, parallel.rank, MPI_COMM_WORLD);
    // MPI_Recv(field.temperature.data(0, 0), ny, MPI_DOUBLE, parallel.nup, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Sendrecv(
        field.temperature.data(1, 0), ny, MPI_DOUBLE, parallel.nup, tag_up,
        field.temperature.data(field.nx+1, 0), ny, MPI_DOUBLE, parallel.ndown, tag_up,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE
    );
    MPI_Sendrecv(
        field.temperature.data(field.nx, 0), ny, MPI_DOUBLE, parallel.ndown, tag_down,
        field.temperature.data(0, 0), ny, MPI_DOUBLE, parallel.nup, tag_down,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE
    );
}

void exchange_nb_init(Field& field, const ParallelData parallel, MPI_Request requests[2]) {
    const int ny = field.temperature.ny;
    MPI_Isendrecv(
        field.temperature.data(1, 0), ny, MPI_DOUBLE, parallel.nup, tag_up,
        field.temperature.data(field.nx+1, 0), ny, MPI_DOUBLE, parallel.ndown, tag_up,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE
    );
    MPI_Isendrecv(
        field.temperature.data(field.nx, 0), ny, MPI_DOUBLE, parallel.ndown, tag_down,
        field.temperature.data(0, 0), ny, MPI_DOUBLE, parallel.nup, tag_down,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE
    );
}

void exchange_nb_wait(MPI_Request requests[2]) {
    MPI_Waitall(2, requests MPI_STATUS_IGNORE);
}

// Todo: configure the limits in the outer evolve function instead
inline double evolve_inner(
        int i, int j, const Field& prev,
        const double a, const double dt,
        const double inv_dx2, const double inv_dy2) {
    return prev(i, j) + a * dt * (
        ( prev(i + 1, j) - 2.0 * prev(i, j) + prev(i - 1, j) ) * inv_dx2 +
        ( prev(i, j + 1) - 2.0 * prev(i, j) + prev(i, j - 1) ) * inv_dy2
    );
}

// Update the temperature values using five-point stencil */
void evolve(Field& curr, const Field& prev, const double a, const double dt, const int margin = 0) {
    // Compilers do not necessarily optimize division to multiplication, so make it explicit
    const double inv_dx2 = 1.0 / (prev.dx * prev.dx);
    const double inv_dy2 = 1.0 / (prev.dy * prev.dy);
    const j_min = 1 + margin;
    const j_max = curr.ny + 1 - margin;

    // Determine the temperature field at next time step
    // As we have fixed boundary conditions, the outermost gridpoints
    // are not updated.
    for (int i = 1 + margin; i < curr.nx + 1 - margin; i++) {
        for (int j = j_min; j < j_max; j++) {
          curr(i, j) = evolve_inner(i, j, prev, a, dt, inv_dx2, inv_dy2);
        }
    }
}

void evolve_edges(Field& curr, const Field& prev, const double a, const double dt) {
    const double inv_dx2 = 1.0 / (prev.dx * prev.dx);
    const double inv_dy2 = 1.0 / (prev.dy * prev.dy);
    i_max = curr.ny

    for (int i = 1; i < curr.nx + 1; i++) {
        curr(i, 1) = evolve_inner(i, 1, prev, a, dt, inv_dx2, inv_dy2);
        curr(i, curr.ny + 1) = evolve_inner(i, curr.ny + 1, prev, a, dt, inv_dx2, inv_dy2);
    }
    // The corners have already been updated
    for (int j = 2; j < curr.ny; j++) {
        curr(1, j) = evolve_inner(1, j, prev, a, dt, inv_dx2, inv_dy2);
        curr(curr.nx + 1, j) = evolve_inner(curr.nx + 1, j, prev, a, dt, inv_dx2, inv_dy2);
    }
}
