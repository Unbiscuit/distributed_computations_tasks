#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>


int findMaxOfMinInRows(const std::vector<std::vector<int>>& matrix) {
    int maxOfMin = matrix[0][0];

    #pragma omp parallel for reduction(max : maxOfMin)
    for (int i = 0; i < matrix.size(); ++i) {
        int minOfRow = *std::min_element(matrix[i].begin(), matrix[i].end());

        if (minOfRow > maxOfMin) {
            maxOfMin = minOfRow;
        }
    }

    return maxOfMin;
}

int main() {
    const int N = 10000;
    const int numRows = N;
    const int numCols = N;

    std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

    omp_set_num_threads(10);
    double t1 = omp_get_wtime();
    int result = findMaxOfMinInRows(matrix);
    double t2 = omp_get_wtime();
    std::cout<<t2-t1<<"\n";

    return 0;
}