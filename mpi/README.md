# MPI section

## Learning objectives

At the end of the MPI section, the student should be able to

- Explain differences in communicating between processes/threads in a shared memory system vs a distributed memory system
- Describe deadlocking communication patterns and approaches to avoid deadlocks
- Contrast blocking and non-blocking communication
- Write MPI programs in C, C++, or Fortran for:
  - Communicating data between processes
  - Using collective communication calls over a subset of processes
- Compile and run MPI programs in supercomputers
- Start exploring some advanced MPI features relevant for their use case


## Demo codes

See [demos](demos/) for demo codes referred to in the slides.

## Wednesday exercises

### Introduction to MPI

- [Hello world](hello-world/)

### Point-to-point communication I

- [Message exchange](message-exchange/)
- [Parallel pi with two processes](parallel-pi-two-procs/)

### Point-to-point communication II

- [Message length](message-length/)
- [Message chain](message-chain/)
- [Parallel pi with any number of processes](parallel-pi-general/)
- [Heat equation solver](heat-equation/): Tasks 1-2

### Non-blocking communication

- [Non-blocking message chain](message-chain-non-blocking/)
- [Heat equation solver](heat-equation/): Task 3

## Thursday exercises

### Debugging

- [Debugging](debugging/)

### Collective operations

- [Broadcast and scatter](broadcast-scatter/)
- [(Bonus) Collective operations](collectives/)

### Collective reductions

- [Parallel pi with reduction](parallel-pi-reduction/)
- [Heat equation solver](heat-equation/): Task 4

### User-defined communicators

- [Communicators and collectives](communicator/)

### Further MPI topics

- Cartesian topology
  - [Cartesian grid process topology](cartesian-grid/)
  - [Message chain with Cartesian communicator](message-chain-cartesian/)
  - [Heat equation solver](heat-equation/): Task 5
- User-defined datatypes
  - [User-defined datatypes](datatypes/)
  - [Modifying extent](datatypes-extent/)
  - [Communicating struct](datatypes-struct/)
- Persistent communication
  - [Message chain with persistent communication](message-chain-persistent/)

### Bonus

- [Heat equation solver](heat-equation/): Remaining tasks


## Web resources

- List of MPI functions with detailed descriptions
  - <https://docs.open-mpi.org/en/v5.0.x/man-openmpi/man3/index.html>
  - <https://www.mpich.org/static/docs/v4.2.x/>
  - <https://rookiehpc.org/mpi/docs/>
- Online MPI tutorials
  - <https://hpc-tutorials.llnl.gov/mpi/>
  - <http://mpitutorial.com/tutorials/>
  - <https://www.youtube.com/watch?v=BPSgXQ9aUXY>
- MPI coding game in C
  - <https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi>
