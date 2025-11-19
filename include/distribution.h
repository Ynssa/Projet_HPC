extern int rank, nproc; // variables MPI

extern int Nloc, Nyloc; // taille du problème local
extern int iBeg;

extern int rank_prev, rank_next; // proc précédent/suivant

extern int iSend_prev, iSend_next;

int charge_taille(int me, int Ny, int np, int rec);
int charge_pos(int me, int Ny, int np, int rec);

void compute_distribution();
