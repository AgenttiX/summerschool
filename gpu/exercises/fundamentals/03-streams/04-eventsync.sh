#!/bin/sh -eu
#SBATCH --job-name=04-eventsync
#SBATCH --account=project_462000956
#SBATCH --partition=small-g
#SBATCH --reservation=SummerSchoolGPU
#SBATCH --gpus-per-node=1
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:05:00
#SBATCH --output=%x-%j.out

srun sh -c "rocprof -d 04-eventsync-prof --hip-trace ./04-eventsync; mv ./results* ./04-eventsync-prof"
