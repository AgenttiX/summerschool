#!/usr/bin/env bash
# set -eu

. /projappl/project_462000956/apps/intel/oneapi/setvars.sh --include-intel-llvm

module load LUMI/24.03 partition/G rocm/6.2.2

export HSA_XNACK=1  # enables managed memory
export MPICH_GPU_SUPPORT_ENABLED=1  # Needed for using GPU-aware MPI
