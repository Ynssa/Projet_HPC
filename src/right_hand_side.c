/* right_hand_side.c */

/* Génération du second membre */

#include "right_hand_side.h"
#include "variables.h"

double *generate_rhs(double (*f)(), double (*g)(), double (*h)(), int n,
                     const double *U0, double *F) {

  for (int k = 0; k < N; ++k) {

    int i = k % Nx;
    int j = k / Nx;

    double x = (i + 1) * dx;
    double y = (j + 1) * dy;
    double t = n * dt;

    F[k] = U0[k] + dt * f(x, y, t); // Contribution du point k ~ (i, j)

    int left = (i == 0); // le point k est à côté du bord gauche; le point à
                         // gauche se trouve sur le bord gauche, il y a une
                         // contribution supplémentaire
    int right = (i == Nx - 1);
    int top = (j == Ny - 1);
    int bottom = (j == 0);

    if (left)
      F[k] -= beta * h(x - dx, y, t);
    if (right)
      F[k] -= beta * h(x + dx, y, t);
    if (top)
      F[k] -= gmma * g(x, y + dy, t);
    if (bottom)
      F[k] -= gmma * g(x, y - dy, t);
  }

  return F;
}
