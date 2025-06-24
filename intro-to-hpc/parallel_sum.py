"""Exercise solution: time complexity of a parallel sum of numbers"""

import math


def sum_time(n_numbers: int, n_workers: int, comp_time: float = 1, comm_time: float = 0.1) -> float:
    n_sums = n_numbers - 1
    if n_workers == 1:
        return comm_time + n_sums * comp_time
    return (math.ceil(n_numbers/n_workers) - 1) * comp_time + math.ceil(math.log2(n_workers)) * (comp_time + comm_time)


def main():
    n_numbers_list = [20, 1020]
    n_workers_list = [1, 2, 4, 8]
    for n_numbers in n_numbers_list:
        print(f"N={n_numbers}")
        for n_workers in n_workers_list:
            print(f"n_workers={n_workers}, time={sum_time(n_numbers, n_workers):.2f} s")


if __name__ == "__main__":
    main()
