extern int rank, nproc; // variables MPI

extern int Nloc; // taille du problème local

extern int rank_prev, rank_next; // proc précédent/suivant

extern double *send_prev, *recv_prev, *send_next, *recv_next; // lignes à envoyer/recevoir
extern int nsend, nrecv; // numéro des lignes à envoyer
