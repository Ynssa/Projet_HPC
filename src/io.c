/* io.c */

/* Fonctions d'affichage et de lecture/écriture dans les fichiers */

#include "variables.h"
#include <stdio.h>

/* Lire dans un fichier les paramètres du problème */
/* Format du fichier (dans l'ordre, un unique espace séparant les valeurs puis
 * un retour à la ligne à la fin): */
/* Nx Ny Lx Ly D dt nmax eps cas */

void read_values(FILE *file) {
  fscanf(file, "%d %d %lf %lf %lf %lf %d %le %d\n", &Nx, &Ny, &Lx, &Ly, &D, &dt,
         &nmax, &eps, &cas);
}

/* Écrire dans un fichier les valeurs d'un vecteur associé à une fonction du
 * domaine */

void write_vec(const double *vec, FILE *file) {

  fprintf(file, "# i j x y U\n");

  for (int k = 0; k < N; ++k) {

    int i = k % Nx;
    int j = k / Nx;
    double x = (i + 1) * dx;
    double y = (j + 1) * dy;

    fprintf(file, "%d\t%d\t%lf\t%lf\t%lf\n", i, j, x, y, vec[k]);
  }
}

/* Afficher un vecteur dans la sortie standard */

void print_vec(const double *vec) {
  for (int k = 0; k < N; ++k) {
    printf("%lf ", vec[k]);
  }
  printf("\n");
}

/* Afficher une matrice dans la sortie standard */

void print_mat(const double *mat) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%lf ", mat[i * N + j]);
    }
    printf("\n");
  }
}
