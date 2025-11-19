/* fgh.c */

/* Fonctions pour les cas tests */

#include "fgh.h"
#include "variables.h"
#include <math.h>

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

/* Cas 1 */

double f1(double x, double y, double t) {
  (void)t; // éviter les avertissements du compilateur (variables non utilisées)
  return 2 * (y - pow(y, 2) + x - pow(x, 2));
}

double g1(double x, double y, double t) {
  (void)x, (void)y, (void)t;
  return 0;
}

double h1(double x, double y, double t) {
  (void)x, (void)y, (void)t;
  return 0;
}

double sol1(double x, double y, double t) {
  (void)t;
  return x * (1 - x) * y * (1 - y);
}

/* Cas 2 */

double f2(double x, double y, double t) {
  (void)t;
  return sin(x) + cos(y);
}

double g2(double x, double y, double t) {
  (void)t;
  return sin(x) + cos(y);
}

double h2(double x, double y, double t) {
  (void)t;
  return sin(x) + cos(y);
}

double sol2(double x, double y, double t) {
  (void)t;
  return sin(x) + cos(y);
}

/* Cas 3 */

double f3(double x, double y, double t) {
  return exp(-pow(x - Lx / 2, 2)) * exp(-pow(y - Ly / 2, 2)) *
         cos(M_PI / 2 * t);
}

double g3(double x, double y, double t) {
  (void)x, (void)y, (void)t;
  return 0;
}

double h3(double x, double y, double t) {
  (void)x, (void)y, (void)t;
  return 1;
}
