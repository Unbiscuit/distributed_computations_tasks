#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

int maxOfMinWithoutSchedule(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int maxOfMin = matrix[0][0];

    for (int i = 0; i < rows; ++i) {
        int minOfRow = *std::min_element(matrix[i].begin(), matrix[i].end());

        if (minOfRow > maxOfMin) {
            maxOfMin = minOfRow;
        }
    }

    return maxOfMin;
}

int staticMaxOfMin(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int maxOfMin = matrix[0][0];
    #pragma omp parallel for reduction(max: maxOfMin) schedule(static)
    for (int i = 0; i < rows; ++i) {
        int minOfRow = *std::min_element(matrix[i].begin(), matrix[i].end());

        if (minOfRow > maxOfMin) {
            maxOfMin = minOfRow;
        }
    }

    return maxOfMin;
}

int dynamicMaxOfMin(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int maxOfMin = matrix[0][0];
    #pragma omp parallel for reduction(max: maxOfMin) schedule(dynamic)
    for (int i = 0; i < rows; ++i) {
        int minOfRow = *std::min_element(matrix[i].begin(), matrix[i].end());

        if (minOfRow > maxOfMin) {
            maxOfMin = minOfRow;
        }
    }

    return maxOfMin;
}

int guidedMaxOfMin(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int maxOfMin = matrix[0][0];
    #pragma omp parallel for reduction(max: maxOfMin) schedule(guided)
    for (int i = 0; i < rows; ++i) {
        int minOfRow = *std::min_element(matrix[i].begin(), matrix[i].end());

        if (minOfRow > maxOfMin) {
            maxOfMin = minOfRow;
        }
    }

    return maxOfMin;
}

int autoMaxOfMin(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int maxOfMin = matrix[0][0];
    #pragma omp parallel for reduction(max: maxOfMin) schedule(auto)
    for (int i = 0; i < rows; ++i) {
        int minOfRow = *std::min_element(matrix[i].begin(), matrix[i].end());

        if (minOfRow > maxOfMin) {
            maxOfMin = minOfRow;
        }
    }

    return maxOfMin;
}

int main(){
    const int N = 10000;

    std::vector<std::vector<int>> matrix(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < (N-i); ++j) {
            matrix[i].push_back(rand() % 100 + 1);
        }
    }
    for (int i = 2; i<=10; i+=2){
        omp_set_num_threads(i);
        double t1 = omp_get_wtime();
        int result = autoMaxOfMin(matrix);
        double t2 = omp_get_wtime();
        std::cout<<t2-t1<<"\n";
    }

    return 0;
}

