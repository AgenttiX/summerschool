#!/usr/bin/env sh
set -eu

OMP_NUM_THREADS=1 ./mandelbrot
OMP_NUM_THREADS=2 ./mandelbrot
OMP_NUM_THREADS=4 ./mandelbrot
OMP_NUM_THREADS=8 ./mandelbrot
OMP_NUM_THREADS=16 ./mandelbrot
OMP_NUM_THREADS=32 ./mandelbrot
