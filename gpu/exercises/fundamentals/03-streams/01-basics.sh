#!/bin/sh -eu
#SBATCH --job-name=01-basics
#SBATCH --account=project_462000956
#SBATCH --partition=small-g
#SBATCH --reservation=SummerSchoolGPU
#SBATCH --gpus-per-node=1
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:05:00
#SBATCH --output=%x-%j.out

srun sh -c "rocprof -d 01-basics-prof --hip-trace ./01-basics; mv ./results* ./01-basics-prof"
