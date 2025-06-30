#!/bin/sh -eu
#SBATCH --job-name=hello-cpu
#SBATCH --account=project_462000956
#SBATCH --partition=small
#SBATCH --reservation=SummerSchoolCPU
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:05:00
#SBATCH --output=%x-%j.out

srun ./hello-cpu
