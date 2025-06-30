1. One grid is sufficient to saturate the GPU
    - The grid maps to the GPU
    - One GPU
    - It's possible to have multiple grids on the GPU at the same time, if there are free compute units.
2. The GPU can be saturated with 8 blocks
    - A block maps to a CU
    - There are 8 CUs
3. A CU/SM can be saturated with 32 * 4 = 128 threads
    - The warp size is 32
    - A warp maps to a vector unit
    - There are 4 vector units in a CU
    - Even though the vector units are 16 threads wide, a single warp can be assigned to only one vector unit.
      This means, that a warp of 32 threads is executed on a vector unit of 16 threads in two steps.
4. Number of threads per block * number of blocks = 128 * 8 = 1024
    - It takes 128 threads to saturate a CU
    - It takes 8 blocks to saturate the GPU

Miscellaneous
1. The number of threads in a warp is fixed.
    If you have less threads, the rest are masked.
2. Yes
3. Yes, but effectively only as a multiplier of warps.
