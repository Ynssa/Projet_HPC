/* right_hand_side.c */

/* Génération du second membre */

#include "right_hand_side.h"
#include "variables.h"
#include "distribution.h"

double *generate_rhs(double (*f)(), double (*g)(), double (*h)(), double* bottom_interface, double* top_interface, int n,
                     const double *U0, double *F) {
  
  for (int k = 0; k < Nloc; ++k) {

    int k_glob = iBeg + k;
    
    int i = k_glob % Nx;
    int j = k_glob / Nx;

    int jloc = k / Nx;
    
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

    int top_inter = (!top) && (jloc == Nyloc - 1);
    int bottom_inter = (!bottom) && (jloc == 0);
    
    if (left)
      F[k] -= beta * h(x - dx, y, t);
    if (right)
      F[k] -= beta * h(x + dx, y, t);
    if (top)
      F[k] -= gmma * g(x, y + dy, t);
    if (bottom)
      F[k] -= gmma * g(x, y - dy, t);
    if (top_inter)
      F[k] -= gmma * top_interface[i];
    if (bottom_inter)
      F[k] -= gmma * bottom_interface[i];
  }

  return F;
}
