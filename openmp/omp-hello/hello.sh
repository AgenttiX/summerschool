#!/usr/bin/env sh
set -eu

OMP_NUM_THREADS=1 ./hello
OMP_NUM_THREADS=2 ./hello
OMP_NUM_THREADS=4 ./hello
