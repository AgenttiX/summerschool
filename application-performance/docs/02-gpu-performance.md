---
title:  Single node performance optimization
event:  CSC Summer School in High-Performance Computing 2024
lang:   en
---

# GPU performance optimization {.section}

# Introduction
- GPUs (Graphics Processing Units) are widely used in High-Performance Computing (HPC) applications.
- GPUs are powerful and complex processors designed for parallel computing.
- GPUs require explicit expression of parallelism by the programmer.

# General Principles for High GPU Performance 

<div class=column>
- Keep all the compute resources busy (idle resources are a waste)
- Minimize the synchronization at all levels
- Minimize the data transfers between host and device 
- Keep the data in faster memory and use an appropriate access pattern
</div>
<div class=column>
![](img/lumi_node.png){.center width=40%}
</div>

# GPU performance analysis {.section}

# Performance analysis cycle

![](img/perf-analysis-single-gpu.svg){.center width=60%}

# Measuring performance
- Don’t speculate about performance – measure it!
- Performance analysis tools help to
    - Find hot-spots
    - Identify the cause of less-than-ideal performance
- Tools covered here
    - TAU, Omniperf
- Other tools
    - Perf, CrayPAT, Tau, Scalasca, gprof, PAPI, ...
    - CUPTI, AMD ROCm Profiler, ...
    - <http://www.vi-hps.org/tools/tools.html>

# Hardware performance counters

- Hardware performance counters are special registers on CPU \& GPU that count
  hardware events
- They enable more accurate statistics and low overhead
    - In some cases they can be used for tracing without any extra
      instrumentation

- Number of counters is much smaller than the number of events that can be
  recorded
- Different devices have different counters

# PAPI

- Performance Application Programming Interface (PAPI)
- Consistent interface and methodology for collecting performance counter information 
- Support for most major CPUs and GPUs
- Several performance analysis tools use PAPI underneath
    - API for collecting metrics within application
- Command line tools for investigating available counters *etc.*
    - `papi_avail`

# Profiling application

- Collecting all possible performance metrics with single run is not practical
    - Simply too much information
    - Profiling overhead can alter application behavior
- Start with an overview!
    - Call tree information, what routines are most expensive?

# Sampling vs. Tracing

<div class=column>
Sampling

- Application is stopped at predetermined intervals 
    - Information is collected about the state of application
- Lightweight, but may give skewed results
    - Statistical information

</div>
<div class=column>
Tracing

- Records events, e.g., every function call
- Requires usually modification to the executable *i.e.* instrumentation
- More accurate, but may affect program behavior
- Generates often lots of data

</div>

# Sampling vs. Tracing

<div class=column>
Sampling

![](img/sampling.png){.left width=80%}

</div>
<div class=column>
Tracing

![](img/tracing.png){.left width=80%}

</div>

# Tau  Analysis Utilities

<small> 

- TAU is a powerful performance evaluation toolkit
- Runs on all HPC platforms, relatively easy to install
- Targets all parallel programming/execution paradigms (GPU, MPI, OpenMP, pthreads, ...)
- Programming languages: Fortran, C, C++, UPC,  Java, Python, ...
- TAU has instrumentation, measurement and analysis tools 
- User-friendly graphical interface
- Profiling: Measures total time spent in each routine
- Tracing: Shows events and their timings across processes on a timeline
- I/O performance evaluation
- Memory debugging

</small>

# Omniperf Tools

 - system performance profiling tool for machine
learning/HPC workloads running on AMD MI GPUs. 
 - presently targets usage on MI100 and MI200 accelerators.
 - profiling, roofline model, tracing
 - built on top of `roctracer` and `rocprof`  
 - supports both a web-based GUI and a command-line analyzer for user convenience.


# Web Resources
 - TAU homepage
    - <https://www.cs.uoregon.edu/research/tau/home.php>
 - Omniperf
    - <https://amdresearch.github.io/omniperf/getting_started.html>
