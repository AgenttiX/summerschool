#!/usr/bin/env sh
set -eu

sbatch --job-name=n01 --nodes=1 --ntasks-per-node=1 --gpus-per-node=1 job.sh
sbatch --job-name=n02 --nodes=1 --ntasks-per-node=2 --gpus-per-node=2 job.sh
sbatch --job-name=n04 --nodes=1 --ntasks-per-node=4 --gpus-per-node=4 job.sh
sbatch --job-name=n08 --nodes=1 --ntasks-per-node=8 --gpus-per-node=8 job.sh
sbatch --job-name=n16 --nodes=2 --ntasks-per-node=8 --gpus-per-node=8 job.sh
