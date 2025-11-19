/* matmul_A.c */

/* Multiplication par la matrice A */

#include "matmul_A.h"
#include "variables.h"

double *matmul_A(const double *vec, double *res) {

  for (int k = 0; k < N; ++k) {

    int i = k % Nx;
    int j = k / Nx;

    res[k] = alpha * vec[k]; // Contribution du point k ~ (i, j)

    int left =
        (i == 0); // le point k est juste à côté du bord gauche; la contribution
                  // du point à gauche passe dans le second membre
    int right = (i == Nx - 1);
    int top = (j == Ny - 1);
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

  return res;
}
