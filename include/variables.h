/* Variables lues en entrée */

extern int Nx, Ny;
extern double Lx, Ly;
extern double D;
extern double dt;
extern int nmax;
extern double eps;
extern int cas;
extern int rec;

/* Valeurs déduites */

extern double dx, dy;
extern double alpha, beta, gmma;
extern int N;

extern double (*farr[3])(double x, double y, double t);
extern double (*garr[3])(double x, double y, double t);
extern double (*harr[3])(double x, double y, double t);
extern double (*solarr[3])(double x, double y, double t);

extern double (*f)(double x, double y, double t);
extern double (*g)(double x, double y, double t);
extern double (*h)(double x, double y, double t);
extern double (*sol)(double x, double y, double t);

void compute_values();
