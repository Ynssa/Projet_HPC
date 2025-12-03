#include <stdio.h>
#include "distribution.h"
#include "variables.h"

int main() {

  int np = 5;
  int Ny = 22;
  Nx = 10;
  int rec = 3;
  
  for (int me = 0; me < np; ++me) {
    int taille = charge_taille(me, Ny, np, rec);
    int pos = charge_pos(me, Ny, np, rec);
    printf("proc %d: taille=%d, pos=%d\n", me, taille, pos);
  }
  
}
