/* linalg.c */

/* Opérations élémentaires sur les vecteurs */

/* Prototype des fonctions : résultat en premier, opérandes ensuite */
/* Le résultat est retourné pour pouvoir enchaîner les opérations sur une même
 * ligne */

#include "variables.h"

#include <math.h>

double *add(double *res, const double *x, const double *y) {
  for (int k = 0; k < N; ++k) {
    res[k] = x[k] + y[k];
  }
  return res;
}

double *sub(double *res, const double *x, const double *y) {
  for (int k = 0; k < N; ++k) {
    res[k] = x[k] - y[k];
  }
  return res;
}

double *scalar_mul(double *res, double a, const double *x) {
  for (int k = 0; k < N; ++k) {
    res[k] = a * x[k];
  }
  return res;
}

/* Produit scalaire */

double dot(const double *x, const double *y) {
  double res = 0;
  for (int k = 0; k < N; ++k) {
    res += x[k] * y[k];
  }
  return res;
}

/* Norme 2 vectorielle */

double norm(const double *x) { return sqrt(dot(x, x)); }

double *copy(double *x, const double *y) {
  for (int k = 0; k < N; ++k) {
    x[k] = y[k];
  }
  return x;
}

/* Les fonctions suivantes ont été utilisées pour tester le code */

double *matmul(double *res, const double *mat, const double *vec) {
  for (int k = 0; k < N; ++k) {
    res[k] = 0;
    for (int l = 0; l < N; ++l) {
      res[k] += mat[k * N + l] * vec[l];
    }
  }
  return res;
}

/* Génère les vecteurs de la base canonique */

double *eye(double *res) {
  for (int k = 0; k < N; ++k) {
    for (int l = 0; l < N; ++l) {
      res[k * N + l] = (k == l);
    }
  }
  return res;
}
