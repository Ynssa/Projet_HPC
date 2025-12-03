/* conjugate_gradient.c */

/* Selon l'article de Wikipedia */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linalg.h"
#include "matmul_A.h"
#include "variables.h"
#include "distribution.h"

double *conjugate_gradient(const double *b, const double *U0, const double eps,
                           double *U) {

  double *r = malloc(Nloc*sizeof(double));
  double *rprev = malloc(Nloc * sizeof(double)); // Pour sauvegarder le r de l'itération précédente
  double *p = malloc(Nloc * sizeof(double));
  double *temp = malloc(Nloc * sizeof(double)); // Pour les calculs intermédiaires
  /* Itération 0 */

  copy(U, U0);                  // Initialisation de U
  sub(r, b, matmul_A(U, temp)); // r_0 := b - AU_0
  copy(p, r);                   // p_0 := r_0
  copy(rprev, r);
  
  /* Itérations suivantes */

  for (int k = 0; k < Nloc; ++k) {

    double ak = dot(rprev, rprev) /
                dot(p, matmul_A(p, temp)); // alpha_k := r_k.r_k / p_k.(Ap_k)
    add(U, U, scalar_mul(temp, ak, p)); // U_k+1 := U_k + alpha_k*p_k
    sub(r, r,
        scalar_mul(temp, ak, matmul_A(p, temp))); // r_k+1 := r_k - alpha_k*Ap_k

    if (norm(r) < eps)
      break;

    double bk = dot(r, r) / dot(rprev, rprev); // beta_k := r_k+1.r_k+1/r_k.r_k
    add(p, r, scalar_mul(temp, bk, p));        // p_k+1 := r + beta_k*p

    copy(rprev, r); // Sauvegarder r_k+1
  }

  free(r);
  free(rprev);
  free(p);
  free(temp);

  return U;
}
