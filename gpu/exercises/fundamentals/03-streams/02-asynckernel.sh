#!/bin/sh -eu
#SBATCH --job-name=02-asynckernel
#SBATCH --account=project_462000956
#SBATCH --partition=small-g
#SBATCH --reservation=SummerSchoolGPU
#SBATCH --gpus-per-node=1
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:05:00
#SBATCH --output=%x-%j.out

srun sh -c "rocprof -d 02-asynckernel-prof --hip-trace ./02-asynckernel; mv ./results* ./02-asynckernel-prof"
