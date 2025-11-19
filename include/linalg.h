double* add(double* res, const double* x, const double* y);
double* sub(double* res, const double* x, const double* y);
double* scalar_mul(double* res, double a, const double* x);
double dot(const double* x, const double* y);
double norm(const double* x);
double* copy(double* x, const double* y);
double* matmul(double* res, const double* mat, const double* vec);
double* eye(double* res);
