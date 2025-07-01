#include <omp.h>
#include <stdio.h>

#define NX 102400

int main(void) {
    double vecA[NX], vecB[NX], vecC[NX];

    /* Initialization of the vectors */
    for (int i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }

    // Start: create a data region and offload the two computations
    // so that data is kept in the device between the computations

    // NOTE! This code should be correct, but here may be a mistake in the model solution.
    // Is res correctly initialized in the GPU memory there? It's only in the map(from) clause
    // and therefore may be uninitialized.
    double res = 0.0;

    #pragma omp target data map(to: vecA, vecB) map(from: vecC) map(tofrom: res)
    {
    #pragma omp target teams distribute parallel for
    for (int i = 0; i < NX; i++) {
        // c = a + a^2
        vecC[i] = vecA[i] + vecB[i];
    }

    #pragma omp target teams distribute parallel for reduction(+:res)
    for (int i = 0; i < NX; i++) {
        // res = sum((a + a^2) * a^2)
        res += vecC[i] * vecB[i];
    }
    }

    double sum = 0.0;
    /* Compute the check value */
    for (int i = 0; i < NX; i++) {
        // sum = sum(a + a^2)
        sum += vecC[i];
    }
    // Reference values with OpenMP disabled:
    // Reduction sum: 13.7587868405645448
    // Dot product: 2.2843801368230490
    printf("Reduction sum: %18.16f\n", sum);
    printf("Dot product: %18.16f\n", res);

    return 0;
}
