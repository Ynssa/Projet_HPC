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

  /* printf("starting conjugate gradient\n"); */
  /* printf("allocation size in bytes: %ld\n", Nloc*sizeof(double)); */
  /* printf("allocation 1\n"); */
  double *r = malloc(Nloc*sizeof(double));
  /* printf("allocation 2\n"); */
  double *rprev = malloc(Nloc * sizeof(double)); // Pour sauvegarder le r de l'itération précédente
  /* printf("allocation 3\n"); */
  double *p = malloc(Nloc * sizeof(double));
  /* printf("allocation 4\n"); */
  double *temp = malloc(Nloc * sizeof(double)); // Pour les calculs intermédiaires
  /* printf("allocation 5\n"); */

  /* printf("finished memory allocations\n"); */
  
  /* Itération 0 */

  /* printf("iteration 0 started\n"); */
  copy(U, U0);                  // Initialisation de U
  if (rank == 0)
    printf("(cg)[0]: Uloc's norm after copy: %lf\n", norm(U));
  /* printf("copy successful\n"); */
  sub(r, b, matmul_A(U, temp)); // r_0 := b - AU_0
  if (rank == 0)
    printf("(cg)[%d]: rk's norm: %lf\n", 0, norm(temp));
  /* printf("sub successful\n"); */
  copy(p, r);                   // p_0 := r_0
  if (rank == 0)
    printf("(cg)[%d]: pk's norm: %lf\n", 0, norm(p));
  /* printf("copy 2 successful\n"); */
  copy(rprev, r);
  /* printf("copy 3 successful\n"); */
  /* printf("iteration 0 ended\n"); */
  
  /* Itérations suivantes */
  /* return U; */
  for (int k = 0; k < Nloc; ++k) {

    double ak = dot(rprev, rprev) /
                dot(p, matmul_A(p, temp)); // alpha_k := r_k.r_k / p_k.(Ap_k)
    if (rank == 0) {
      printf("(cg)[%d]: ak: %lf\n", k, ak);
      printf("(cg)[%d]: p's norm: %lf\n", k, norm(p));
    }
    add(U, U, scalar_mul(temp, ak, p)); // U_k+1 := U_k + alpha_k*p_k
    if (rank == 0)
      printf("(cg)[%d]: Uloc's norm: %lf\n", k, norm(U));
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
