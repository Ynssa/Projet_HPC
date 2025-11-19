#include <mpi.h>

#include "distribution.h"
#include "variables.h"

int rank, nproc; // variables MPI

int Nloc, Nyloc; // taille du problème local
int iBeg;

int rank_prev, rank_next; // proc précédent/suivant

int iRecv_prev, iRecv_next; // numéro des lignes à envoyer

int charge_taille(int me, int Ny, int np, int rec) {
  
  int Ndist = Ny + rec*(np-1);

  int q = Ndist / np;
  int r = Ndist % np;

  if (me < r) {
    return (q + 1);
  } else {
    return q;
  }
}

int charge_pos(int me, int Ny, int np, int rec) {
  
  int pos = 0;
  for (int proc = 0; proc < me; ++proc) {
    pos += charge_taille(proc, Ny, np, rec);
    pos -= rec;
  }
  return pos*Nx;
}

void compute_distribution() {

  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Nyloc = charge_taille(rank, Ny, nproc, rec);
  Nloc = Nyloc*Nx;

  iBeg = charge_pos(rank, Ny, nproc, rec);

  if (rank > 0) {
    rank_prev = rank - 1;
  } else {
    rank_prev = MPI_PROC_NULL;
  }

  if (rank < np - 1) {
    rank_next = rank + 1;
  } else {
    rank_next = MPI_PROC_NULL;
  }

  iSend_prev = rec*Nx;
  iSend_next = (Nyloc-1-rec)*Nx;
}
