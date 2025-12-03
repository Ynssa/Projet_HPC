/* matmul_A.c */

/* Multiplication par la matrice A */
#include <stdio.h>
#include "matmul_A.h"
#include "variables.h"
#include "distribution.h"
#include "linalg.h"

double *matmul_A(const double *vec, double *res) {

  /* printf("entered matmul_A\n"); */
  
  for (int k = 0; k < Nloc; ++k) {

    /* int k_glob = k + iBeg; */
    /* int i = k_glob % Nx; */
    /* int j = k_glob / Nx; */

    int i = k % Nx;
    int j = k / Nx;

    res[k] = alpha * vec[k]; // Contribution du point k ~ (i, j)
    /* printf("assignement successful %d\n", k); */
    int left =
        (i == 0); // le point k est juste à côté du bord gauche; la contribution
                  // du point à gauche passe dans le second membre
    int right = (i == Nx - 1);
    int top = (j == Nyloc - 1);
    int bottom = (j == 0);

    if (!left)
      res[k] += beta * vec[k - 1];
    if (!right)
      res[k] += beta * vec[k + 1];
    if (!top)
      res[k] += gmma * vec[k + Nx];
    if (!bottom)
      res[k] += gmma * vec[k - Nx];
  }

  /* printf("exiting matmul_A\n"); */
  if (rank == 0) {
    printf("matmul_A res norm: %lf\n", norm(res));
    printf("matmul_A vec norm: %lf\n", norm(vec));
  }
  return res;
}
