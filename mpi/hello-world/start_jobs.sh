#!/usr/bin/env sh
set -eu

sbatch --job-name=n01-t01 --nodes=1 --ntasks-per-node=1 job.sh
sbatch --job-name=n01-t04 --nodes=1 --ntasks-per-node=4 job.sh
sbatch --job-name=n01-t42 --nodes=1 --ntasks-per-node=42 job.sh
sbatch --job-name=n01-t64 --nodes=1 --ntasks-per-node=64 job.sh
sbatch --job-name=n02-t01 --nodes=2 --ntasks-per-node=1 job.sh
sbatch --job-name=n02-t04 --nodes=2 --ntasks-per-node=4 job.sh
