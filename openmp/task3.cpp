#include <iostream>
#include <omp.h>

double function(double x) {
    return x * x;
}

double calculateParallelIntegral(double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; ++i) {
        double x_i = a + i * h;
        result += function(x_i) * h;
    }

    return result;
}


int main() {
    double a = 0.0;
    double b = 1.0;
    int n = 10000000;


    omp_set_num_threads(1);
    double t1 = omp_get_wtime();
    double parallelIntegralResult = calculateParallelIntegral(a, b, n);
    double t2 = omp_get_wtime();
    std::cout<<t2-t1<<"\n";


    return 0;
}