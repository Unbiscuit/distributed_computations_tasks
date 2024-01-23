#include <iostream>
#include <vector>
#include <omp.h>

int calculateScalarProduct(const std::vector<int>& vector1, const std::vector<int>& vector2) {
    int scalar_product = 0;

    #pragma omp parallel for reduction(+:scalar_product)
    for (size_t i = 0; i < vector1.size(); ++i) {
        scalar_product += vector1[i] * vector2[i];
    }

    return scalar_product;
}

int main() {
    const int N = 10;
    std::vector<int> vector1(N, 2);
    std::vector<int> vector2(N, 3);


    omp_set_num_threads(1);
    double t1 = omp_get_wtime();
    int product = calculateScalarProduct(vector1, vector2);
    double t2 = omp_get_wtime();
    std::cout<<t2-t1<<"\n";


    return 0;
}