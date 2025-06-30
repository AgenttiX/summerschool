#!/usr/bin/env bash
# set -eu

# Arguments:
# - Number of Taylor's expansion iterations
# - Size of vector
# - Size of threads
ITERS=(1 8 32)
VECTOR_POWERS=(6 7 8)
THREADS=(1 128 1024)

VECTORS=()
for pow in "${VECTOR_POWERS[@]}"; do
  VECTORS+=($((10**pow)))
done
echo "Iterations: ${ITERS[*]}"
echo "Vector sizes: ${VECTORS[*]}"
echo "Thread counts: ${THREADS[*]}"

for n_iters in "${ITERS[@]}"; do
  for n_vecs in "${VECTORS[@]}"; do
    for n_threads in "${THREADS[@]}"; do
      # echo "Launching Taylor with: ${n_iters} ${n_vecs} ${n_threads}"
      ./taylor "${n_iters}" "${n_vecs}" "${n_threads}"
    done
  done
done
