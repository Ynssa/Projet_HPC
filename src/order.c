/* order.c */

/* Calcul de l'ordre de la méthode par différences finies (on utilisera le cas
 * 2) */

#include "conjugate_gradient.h"
#include "fgh.h"
#include "io.h"
#include "linalg.h"
#include "right_hand_side.h"
#include "variables.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  /* Usage */

  if (argc != 3) {
    fprintf(stderr, "Erreur: nombre incorrect d'arguments\n");
    fprintf(stderr, "Usage: order [input filename] [output filename]\n");
    return 1;
  }

  /* Lecture du fichier d'entrée (nombres de noeuds selon x et y ignorés) */

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

  /* Valeurs de Nx et Ny pour le calcul de l'ordre */

  int Nds_len = 7;

  int *Nds = malloc(Nds_len * sizeof(int));

  /* Ici on utilise des puissances de 2 (à partir de 4) */

  int pow2 = 4;

  for (int k = 0; k < Nds_len; ++k) {
    Nds[k] = pow2;
    pow2 *= 2;
  }

  double *err = malloc(
      Nds_len * sizeof(double)); // Contient l'erreur pour chaque valeur de Nd

  for (int k = 0; k < Nds_len; ++k) {

    int Nd = Nds[k];

    Nx = Nd;
    Ny = Nd;

    compute_values();

    /* La procédure est la même que dans heat.c */

    double *U = malloc(N * sizeof(double));

    double *zeros = malloc(N * sizeof(double));
    for (int k = 0; k < N; ++k)
      zeros[k] = 0;

    double *F = malloc(N * sizeof(double));

    copy(U, zeros);

    for (int n = 1; n <= nmax; ++n) {
      F = generate_rhs(f, g, h, n, U, F);
      U = conjugate_gradient(F, U, eps, U);
    }

    if (sol != NULL) {

      double *solv = malloc(N * sizeof(double));

      for (int k = 0; k < N; ++k) {
        int i = k % Nx;
        int j = k / Nx;
        double x = (i + 1) * dx;
        double y = (j + 1) * dy;
        solv[k] = sol(x, y, 0);
      }

      double *diff = malloc(N * sizeof(double));
      sub(diff, U, solv);
      err[k] = norm(diff) / Nd; // Norme L2

      free(solv);
      free(diff);
    }

    free(U);
    free(zeros);
    free(F);
  }

  /* Écriture dans le fichier de sortie */

  char *ofilename = argv[2];

  FILE *ofile = fopen(ofilename, "w");

  fprintf(ofile, "# delta err\n");

  for (int k = 0; k < Nds_len; ++k) {
    fprintf(ofile, "%lf %le\n", (double)1 / Nds[k], err[k]);
  }

  fclose(ofile);

  /* Affichage de l'ordre (approximatif) */

  double ordre = (log(err[Nds_len - 1]) - log(err[0])) /
                 (log(1. / Nds[Nds_len - 1]) - log(1. / Nds[0]));

  printf("Ordre en norme L2: %lf\n", ordre);

  free(Nds);
  free(err);
}
