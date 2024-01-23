#include <iostream>
#include <vector>
#include <omp.h>

int findMaxOfMinInRows(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int maxOfMin = matrix[0][0];

    omp_set_nested(2);

    #pragma omp parallel for reduction(max : maxOfMin)
    for (int i = 0; i < rows; ++i) {
        int rowMin = matrix[i][0];

        for (int k = 0; k < rows; ++k){
            if (matrix[i][k] < rowMin){
                rowMin = matrix[i][k];
            }
        }

        if (rowMin > maxOfMin) {
            maxOfMin = rowMin;
        }
    }

    return maxOfMin;
}

int findMaxOfMinInRowsNested(const std::vector<std::vector<int>>& matrix, int threads) {
    int rows = matrix.size();
    int maxOfMin = matrix[0][0];

    omp_set_nested(2);

    #pragma omp parallel for reduction(max : maxOfMin) num_threads(threads)
    for (int i = 0; i < rows; ++i) {
        int rowMin = matrix[i][0];

        #pragma omp parallel for reduction(min: rowMin) num_threads(2)
        for (int k = 0; k < rows; ++k){
            if (matrix[i][k] < rowMin){
                rowMin = matrix[i][k];
            }
        }

        if (rowMin > maxOfMin) {
            maxOfMin = rowMin;
        }
    }

    return maxOfMin;
}

int main(){
    const int N = 10000;
    const int numRows = N;
    const int numCols = N;

    std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

    for (int i = 2; i <= 10; i+=2){
        omp_set_num_threads(i);
        double t1 = omp_get_wtime();
        int result = findMaxOfMinInRows(matrix);
        double t2 = omp_get_wtime();
        std::cout<<t2-t1<<"\n";
    }

    return 0;
}