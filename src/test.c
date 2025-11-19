#include <stdio.h>
#include <distribution.h>

int main() {

  int np = 5;
  int Ny = 22;
  int rec = 0;
  
  for (int me = 0; me < np; ++me) {
    int taille = charge_taille(me, Ny, np, rec);
    int pos = charge_pos(me, Ny, np, rec);
    printf("proc %d: taille=%d, pos=%d\n", me, taille, pos);
  }
  
}
