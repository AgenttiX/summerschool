#!/usr/bin/env sh
set -eu

sbatch --job-name=t01 --nodes=1 --ntasks-per-node=2 chain.sh
sbatch --job-name=t04 --nodes=1 --ntasks-per-node=4 chain.sh
sbatch --job-name=t08 --nodes=1 --ntasks-per-node=8 chain.sh
sbatch --job-name=t16 --nodes=1 --ntasks-per-node=16 chain.sh
