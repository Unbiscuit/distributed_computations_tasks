#include <iostream>
#include <vector>
#include <omp.h>

int findMin(const std::vector<int>& vec){
    int min_value = vec[0];

    #pragma omp parallel for reduction(min : min_value)
    for (int i : vec) {
        if (i < min_value) {
            min_value = i;
        }
    }

    return min_value;
}

int main() {

    omp_set_num_threads(1);
    const int N = 100000000;
    std::vector<int> vector(N, 2);
    double t1 = omp_get_wtime();
    int min = findMin(vector);
    double t2 = omp_get_wtime();
    std::cout<<t2-t1<<"\n";


    return 0;
}