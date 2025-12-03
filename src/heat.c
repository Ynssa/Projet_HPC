/* heat.c */

/* Résolution de l'équation de la chaleur par différences finies */

#include "conjugate_gradient.h"
#include "fgh.h"
#include "io.h"
#include "linalg.h"
#include "right_hand_side.h"
#include "variables.h"
#include "distribution.h"
#include "communication.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

  /* Usage */

  if (argc != 3) {
    fprintf(stderr, "Erreur: nombre incorrect d'arguments\n");
    fprintf(stderr, "Usage: heat [input filename] [output filename]\n");
    return 1;
  }

  /* Lecture du fichier d'entrée */

  char *ifilename = argv[1];

  FILE *ifile = fopen(ifilename, "r");

  if (ifile == NULL) {
    fprintf(stderr,
            "Erreur: le fichier '%s' n'existe pas dans le répertoire courant\n",
            ifilename);
    return 1;
  }

  read_values(ifile);

  fclose(ifile);

  /* Calcul des autres valeurs */

  compute_values();

  /* Distribution des charges */

  MPI_Init(&argc, &argv);
  
  compute_distribution();

  print_distribution();
  
  /* Calcul de la solution approchée */

  double *U =
      malloc(Nloc * sizeof(double)); // Vecteur contenant la solution approchée

  double *bottom_interface = NULL;
  double *top_interface = NULL;
  
  bottom_interface = malloc(Nx*sizeof(double));
  top_interface = malloc(Nx*sizeof(double));

  for (int i = 0; i < Nx; ++i) {
    bottom_interface[i] = 0;
    top_interface[i] = 0;
  }
  
  double *zeros = malloc(Nloc * sizeof(double)); // Pour l'initialisation de la descente de gradient
  for (int k = 0; k < Nloc; ++k)
    zeros[k] = 0;
  
  double *F = malloc(Nloc * sizeof(double)); // Second membre

  copy(U, zeros); // Initialisation

  for (int n = 1; n <= nmax; ++n) {
    for (int k = 1; k <= iter_schwarz; ++k) {
      communicate_interfaces(U, bottom_interface, top_interface);
      F = generate_rhs(f, g, h, bottom_interface, top_interface, n, U, F);   // Calcul du second membre F
      U = conjugate_gradient(F, U, eps, U); // Résolution du système AU = F
    }
  }

  /* Écriture de la solution approchée dans le fichier de sortie */

  char *ofilename = argv[2];
  char *ofilename_ext = malloc((strlen(ofilename)+4+4+1)*sizeof(char));
  sprintf(ofilename_ext, "%s.%d.%d", ofilename, nproc, rank);
  FILE *ofile = fopen(ofilename_ext, "w");
  
  write_vec(U, ofile);

  fclose(ofile);

  /* Calcul de l'erreur en norme L2 si il existe une solution exacte */

  /* if (sol != NULL) { */

  /*   double *solv = */
  /*       malloc(N * sizeof(double)); // Contient les valeurs de la solution aux */
  /*                                   // noeuds du maillage */

  /*   for (int k = 0; k < N; ++k) { */

  /*     int i = k % Nx; */
  /*     int j = k / Nx; */

  /*     double x = (i + 1) * dx; */
  /*     double y = (j + 1) * dy; */

  /*     solv[k] = sol(x, y, 0); */
  /*   } */

  /*   double *diff = malloc(N * sizeof(double)); */
  /*   sub(diff, U, solv); */

  /*   double err = norm(diff) / N; */

  /*   printf("Erreur en norme L2 : %le\n", err); */

  /*   free(solv); */
  /*   free(diff); */
  /* } */
  
  MPI_Finalize();
  free(U);
  free(zeros);
  free(F);
  free(bottom_interface);
  free(top_interface);
}
