#include <hip/hip_runtime.h>

// Go to this file and fill in the blanks there
#include "error_checking.hpp"

__global__ void hello() {
    if (threadIdx.x == 0 && threadIdx.y == 0 && threadIdx.z == 0 &&
        blockIdx.x == 0 && blockIdx.y == 0 && blockIdx.z == 0) {
        printf("You fixed me! Hooray!\n");
    }
}

int main(int argc, char **argv) {
    // TODO 2: After completing the error checking in the separate file
    // fix any errors with this launch.
    // To do that,
    // - compile the program
    // - run it
    // - fix any errors with the launch parameters
    // - repeat

    // LUMI has AMD MI250X GPUs:
    // 220 CUs -> Must have at least 220 blocks for optimal performance

    // Arguments: kernel, blocks, threads, shared_mem, stream
    // LAUNCH_KERNEL(hello, dim3(0, 0, 1), dim3(1025, 30000, 1), 9999999, 0);
    LAUNCH_KERNEL(hello, dim3(1, 1, 256), dim3(8, 128, 1), 65535, 0);
    [[maybe_unused]] const auto result = hipDeviceSynchronize();

    return 0;
}
