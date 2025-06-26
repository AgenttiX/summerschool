#!/usr/bin/env sh
set -eu

sbatch --job-name=sr-t01 --nodes=1 --ntasks-per-node=2 chain_sendrecv.sh
sbatch --job-name=sr-t04 --nodes=1 --ntasks-per-node=4 chain_sendrecv.sh
sbatch --job-name=sr-t08 --nodes=1 --ntasks-per-node=8 chain_sendrecv.sh
sbatch --job-name=sr-t16 --nodes=1 --ntasks-per-node=16 chain_sendrecv.sh
