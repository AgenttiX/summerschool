#!/bin/sh -eu
#SBATCH --job-name=ping-pong
#SBATCH --account=project_462000956
#SBATCH --partition=small-g
#SBATCH --reservation=SummerSchoolGPU
#SBATCH --gpus-per-node=2
#SBATCH --nodes=1
#SBATCH --tasks-per-node=2
#SBATCH --time=00:05:00

export MPICH_GPU_SUPPORT_ENABLED=1
srun ./ping-pong
