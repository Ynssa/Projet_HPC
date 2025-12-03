#include <stdio.h>
#include <mpi.h>

#include "distribution.h"
#include "variables.h"
#include "communication.h"


void communicate_interfaces(double* Uloc, double* bottom_interface, double* top_interface) {

  if (rank % 2 == 0) {
    MPI_Send(&Uloc[iSend_next], Nx, MPI_DOUBLE, rank_next, 0, MPI_COMM_WORLD);
    MPI_Recv(top_interface, Nx, MPI_DOUBLE, rank_next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(bottom_interface, Nx, MPI_DOUBLE, rank_prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&Uloc[iSend_prev], Nx, MPI_DOUBLE, rank_prev, 0, MPI_COMM_WORLD);
  } else {
    MPI_Recv(bottom_interface, Nx, MPI_DOUBLE, rank_prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&Uloc[iSend_prev], Nx, MPI_DOUBLE, rank_prev, 0, MPI_COMM_WORLD);
    MPI_Send(&Uloc[iSend_next], Nx, MPI_DOUBLE, rank_next, 0, MPI_COMM_WORLD);
    MPI_Recv(top_interface, Nx, MPI_DOUBLE, rank_next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
}
