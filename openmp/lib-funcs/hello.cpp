#include <cstdio>
#include <omp.h>

int main()
{
    printf("Hello world!\n");
    #pragma omp parallel
    {
        printf("Threads: %d, id: %d\n", omp_get_num_threads(), omp_get_thread_num());
    }
    return 0;
}
