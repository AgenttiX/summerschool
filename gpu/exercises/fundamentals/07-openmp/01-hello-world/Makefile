all: cpu gpu

# These settings don't seem to work, and the modules have to be set at the terminal instead.

cpu:
	. ../../../setup_cpu.sh
	CC -fopenmp hello.c -o hello-cpu

gpu:
	. ../../../setup_gpu.sh
	CC -fopenmp hello.c -o hello-gpu
