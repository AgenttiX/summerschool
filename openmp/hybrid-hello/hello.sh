#!/bin/sh -eu
#SBATCH --job-name=hybrid-hello
#SBATCH --account=project_462000956
#SBATCH --reservation=SummerSchoolCPU
#SBATCH --output=%x.%J.out
#SBATCH --partition=small
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00

export OMP_DISPLAY_AFFINITY=true
srun ./hello
