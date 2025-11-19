/* heat.c */

/* Résolution de l'équation de la chaleur par différences finies */

#include "conjugate_gradient.h"
#include "fgh.h"
#include "io.h"
#include "linalg.h"
#include "right_hand_side.h"
#include "variables.h"

#include <stdio.h>
#include <stdlib.h>

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

  /* Calcul de la solution approchée */

  double *U =
      malloc(N * sizeof(double)); // Vecteur contenant la solution approchée

  double *zeros = malloc(
      N * sizeof(double)); // Pour l'initialisation de la descente de gradient
  for (int k = 0; k < N; ++k)
    zeros[k] = 0;

  double *F = malloc(N * sizeof(double)); // Second membre

  copy(U, zeros); // Initialisation

  for (int n = 1; n <= nmax; ++n) {
    F = generate_rhs(f, g, h, n, U, F);   // Calcul du second membre F
    U = conjugate_gradient(F, U, eps, U); // Résolution du système AU = F
  }

  /* Écriture de la solution approchée dans le fichier de sortie */

  char *ofilename = argv[2];

  FILE *ofile = fopen(ofilename, "w");

  write_vec(U, ofile);

  fclose(ofile);

  /* Calcul de l'erreur en norme L2 si il existe une solution exacte */

  if (sol != NULL) {

    double *solv =
        malloc(N * sizeof(double)); // Contient les valeurs de la solution aux
                                    // noeuds du maillage

    for (int k = 0; k < N; ++k) {

      int i = k % Nx;
      int j = k / Nx;

      double x = (i + 1) * dx;
      double y = (j + 1) * dy;

      solv[k] = sol(x, y, 0);
    }

    double *diff = malloc(N * sizeof(double));
    sub(diff, U, solv);

    double err = norm(diff) / N;

    printf("Erreur en norme L2 : %le\n", err);

    free(solv);
    free(diff);
  }

  free(U);
  free(zeros);
  free(F);
}
