/* variables.c */

/* Variables globales créées pour ne pas encombrer la liste des arguments dans
 * les fonctions */

#include "variables.h"
#include "fgh.h"

#include <math.h>
#include <stddef.h>

/* Variables lues en entrée */

int Nx, Ny;
double Lx, Ly;
double D;
double dt;
int nmax;
double eps;
int cas;
int rec;

/* Valeurs déduites */

double dx, dy;
double alpha, beta, gmma;
int N;

/* Tableaux de pointeurs de fonctions "contenant" les fonctions tests */

double (*farr[3])(double x, double y, double t) = {f1, f2, f3};
double (*garr[3])(double x, double y, double t) = {g1, g2, g3};
double (*harr[3])(double x, double y, double t) = {h1, h2, h3};
double (*solarr[3])(double x, double y, double t) = {sol1, sol2, NULL};

/* Fonctions "choisies" */

double (*f)(double x, double y, double t);
double (*g)(double x, double y, double t);
double (*h)(double x, double y, double t);
double (*sol)(double x, double y, double t);

/* Calculer les autres valeurs en fonction des variables lues */

void compute_values() {

  dx = Lx / (Nx + 1);
  dy = Ly / (Ny + 1);
  alpha = 1 + 2 * D * dt * (pow(dx, -2) + pow(dy, -2));
  beta = -D * dt * pow(dx, -2);
  gmma = -D * dt * pow(dy, -2);
  N = Nx * Ny;
  f = farr[cas - 1];
  g = garr[cas - 1];
  h = harr[cas - 1];
  sol = solarr[cas - 1];
}
