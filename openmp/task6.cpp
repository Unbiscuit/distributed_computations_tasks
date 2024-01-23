#include <iostream>
#include <vector>
#include <omp.h>

int mpReduction(const std::vector<int>& vector1, const std::vector<int>& vector2, const int N){
    int product_reduction = 0;
    int sum = 0;
    #pragma omp parallel for reduction(+:sum) private(product_reduction)
    for (int i = 0; i < vector1.size(); ++i) {
        product_reduction = vector1[i] * vector2[i];
        sum+=product_reduction;
    }

    return sum;
}

int atomicReduction(const std::vector<int>& vector1, const std::vector<int>& vector2, const int N){
    int product_atomic = 0;
    int sum = 0;
    #pragma omp parallel for private(product_atomic)
    for (int i = 0; i < vector1.size(); ++i) {
        product_atomic = vector1[i] * vector2[i];
        #pragma omp atomic
        sum += product_atomic;
    }

    return sum;
}

int criticalReduction(const std::vector<int>& vector1, const std::vector<int>& vector2, const int N){
    int product_critical = 0;
    int local_product = 0;
    #pragma omp parallel private(local_product)
    {
        #pragma omp for
        for (int i = 0; i < vector1.size(); ++i) {
            local_product = vector1[i] * vector2[i];
            #pragma omp critical
            product_critical += local_product;
        }
    }

    return product_critical;
}

int lockReduction(const std::vector<int>& vector1, const std::vector<int>& vector2, const int N){
    int product_lock = 0;
    int local_product = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel private(local_product)
    {
        #pragma omp for
        for (int i = 0; i < vector1.size(); ++i) {
            local_product = vector1[i] * vector2[i];
            omp_set_lock(&lock);
            product_lock += local_product;
            omp_unset_lock(&lock);
        }
    }

    return product_lock;
}


int main() {
    const int N = 1000000;
    std::vector<int> vector1(N, 2);
    std::vector<int> vector2(N, 3);

    omp_set_num_threads(1);
    double t1 = omp_get_wtime();
    int product = atomicReduction(vector1, vector2, N);
    double t2 = omp_get_wtime();
    std::cout << t2 - t1 << "\n";

    return 0;
}