#include <stdio.h>

#define NX 102400

int main(void) {
    double vecA[NX], vecB[NX];

    // Initialization of the vectors
    for (int i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }

    // Offload and parallelize the computation

    double res = 0.0;
    // The res variable is not dynamically allocated, and therefore should not be specified with a map() clause.
    // (If you do, this will return zero.)
    // The teams construct is needed to use more than one block.

    // This results in a crash for some reason.
    // #pragma omp target map(to: vecA[:NX], vecB[:NX])
    // #pragma omp teams distribute parallel for reduction(+:res)

    // This works
    #pragma omp target teams distribute parallel for map(to: vecA, vecB) reduction(+:res)
    for (int i = 0; i < NX; i++) {
        res += vecA[i] * vecB[i];
    }

    printf("Dot product: %18.16f\n", res);
    printf("Ref value:   1.2020569031119110\n");

    return 0;
}
