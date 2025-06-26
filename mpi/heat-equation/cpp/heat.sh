#!/bin/sh -eu
#SBATCH --job-name=heat-equation
#SBATCH --account=project_462000956
#SBATCH --reservation=SummerSchoolCPU
#SBATCH --output=%x.%J.out
#SBATCH --partition=small
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --time=00:05:00

srun ./heat_mpi
