#include <cstdio>

#define NX 102400

int main(void)
{
    long vecA[NX];
    long sum, psum, sumex;
    int i;

    /* Initialization of the vectors */
    for (i = 0; i < NX; i++) {
        vecA[i] = (long) i + 1;
    }

    sumex = (long) NX * (NX + 1) / ((long) 2);
    printf("Arithmetic sum formula (exact): %ld\n", sumex);

    sum = 0.0;
    /* Version with data race */
    #pragma omp parallel for private(i) reduction(+:sum) num_threads(4)
    for (i = 0; i < NX; i++) {
        sum += vecA[i];
    }
    printf("Sum with fixed data race:       %ld\n", sum);

    return 0;
}
