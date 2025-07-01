#!/usr/bin/env sh
# set -eu

module reset
module load LUMI/24.03 partition/G rocm/6.2.2

export PATH=/projappl/project_462000956/apps/ACPP/bin/:$PATH
export LD_LIBRARY_PATH=/appl/lumi/SW/LUMI-24.03/G/EB/Boost/1.83.0-cpeGNU-24.03/lib64/:$LD_LIBRARY_PATH
export LD_PRELOAD=/appl/lumi/SW/LUMI-24.03/G/EB/rocm/6.2.2/llvm/lib/libomp.so
export HSA_XNACK=1  # enables managed memory
export MPICH_GPU_SUPPORT_ENABLED=1  # Needed for using GPU-aware MPI
