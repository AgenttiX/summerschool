import glob
import os.path

import pandas as pd

DIR = os.path.dirname(os.path.abspath(__file__))


class Result:
    def __init__(self, n: int):
        search = os.path.join(DIR, f"n{n:02d}.*.out")
        paths = glob.glob(search)
        if len(paths) != 1:
            raise ValueError(f"Expected exactly one output file, got: {paths} for {search}")
        with open(paths[0], "r") as file:
            lines = file.readlines()
            shape_line = lines[0].split()
            mpi_line = lines[1].split()
            self.height = int(shape_line[3])
            self.width = int(shape_line[5])
            self.length = int(shape_line[7])
            self.time_steps = int(shape_line[-1])
            self.n_tasks = int(mpi_line[4])
            self.mpi_shape = (int(mpi_line[5][1:]), int(mpi_line[7]), int(mpi_line[9][:-1]))
            self.gpus_per_node = int(lines[2].split()[-1])
            self.avg_temp_start = float(lines[4].split()[-1])
            self.time = float(lines[5].split()[2])
            self.time_copy = float(lines[6].split()[2])
            self.time_comm = float(lines[7].split()[1])
            self.time_comp = float(lines[8].split()[1])
            self.avg_temp = float(lines[9].split()[-1])
            self.ref_value = float(lines[10].split()[-1])

    def output(self) -> str:
        return \
            f"""Simulation parameters: height: {self.height} width: {self.width} length: {self.length} time steps: {self.time_steps}
            Number of MPI tasks: {self.n_tasks} ({" x ".join([str(val) for val in self.mpi_shape])})
            Number of GPUs per node: {self.gpus_per_node}
            ...
            Average temperature at start: {self.avg_temp_start}
            Iteration took {self.time} seconds.
              Memory copies {self.time_copy:.6f} s.
              Communication {self.time_comm:.6f} s.
              Compute       {self.time_comp:.6f} s.
            Average temperature: {self.avg_temp:.6f}
            Reference value with default arguments: {self.ref_value:.6f}
            """

def main():
    results = [Result(n) for n in [1, 2, 4, 8, 16]]
    for result in results:
        print(result.output())

    frame = pd.DataFrame({
        "GCDs": [result.n_tasks for result in results],
        "Runtime (s)": [result.time for result in results],
        "Resource cost (GCD-s)": [result.time * result.n_tasks for result in results],
        "Time spent in communication (s)": [result.time_comm for result in results],
        "Time spent in computing (s)": [result.time_comp for result in results],
        "Speedup": [results[0].time / result.time for result in results],
        "Parallel efficiency": [results[0].time / (result.n_tasks * result.time) for result in results]
    })
    frame.to_markdown(os.path.join(DIR, "results.md"))

if __name__ == "__main__":
    main()
