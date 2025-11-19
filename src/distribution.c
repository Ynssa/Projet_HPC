#include <mpi.h>

#include "distribution.h"

void charge(int me, int n, int np, int *iBeg, int *iEnd) {
  
}

void compute_distribution() {

  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
}
