#!/bin/sh -eu
#SBATCH --job-name=taylor-for
#SBATCH --account=project_462000956
#SBATCH --partition=small-g
#SBATCH --reservation=SummerSchoolGPU
#SBATCH --gpus-per-node=1
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:05:00

# srun ./taylor 8 100 8
srun ./taylor_configs.sh
