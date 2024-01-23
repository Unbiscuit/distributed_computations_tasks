#include <iostream>
#include <vector>
#include <omp.h>

void sumMatrixParallel(const std::vector<std::vector<int>>& matrix, std::vector<int>& result) {
    #pragma omp parallel for
    for (int i = 0; i < matrix.size(); ++i) {
        #pragma omp parallel for
        for (int j = 0; j < matrix[i].size(); ++j) {
            #pragma omp atomic
            result[i] += matrix[i][j];
        }
    }
}

void sumMatrix(const std::vector<std::vector<int>>& matrix, std::vector<int>& result) {
    #pragma omp parallel for
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            #pragma omp atomic
            result[i] += matrix[i][j];
        }
    }
}\

int main() {
    const int N = 10;
    const int numRows = N;
    const int numCols = N;
    std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

    for (int k = 2; k <= 10; k+=2){
        omp_set_num_threads(k);
        std::vector<int> result(numRows, 0);
        double start_time = omp_get_wtime();
        sumMatrix(matrix, result);
        double end_time = omp_get_wtime();
        std::cout << "С использованием вложенного параллелизма: " << end_time - start_time << " секунд." << std::endl;
    }



    return 0;
}