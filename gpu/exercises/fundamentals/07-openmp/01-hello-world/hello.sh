#!/usr/bin/env sh
set -eu

# These settings don't seem to work, and the modules have to be set at the terminal instead.

. ../../../setup_cpu.sh
sbatch ./hello-cpu.sh

. ../../../setup_gpu.sh
sbatch ./hello-gpu.sh
