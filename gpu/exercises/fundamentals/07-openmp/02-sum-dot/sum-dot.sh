#!/bin/sh -eu
#SBATCH --job-name=sum-dot
#SBATCH --account=project_462000956
#SBATCH --partition=small-g
#SBATCH --reservation=SummerSchoolGPU
#SBATCH --gpus-per-node=1
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:05:00
#SBATCH --output=%x-%j.out

srun ./sum-dot
