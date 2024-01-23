#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <omp.h>

void fillVectorFromFile(std::vector<std::vector<int>>& myVector, int numberOfRows) {
    std::ifstream inputFile("/home/uncookie/Documents/openMP_dist_comp/vectors.txt");

    std::string line;
    int position = 0;

    while (std::getline(inputFile, line)) {
        if (numberOfRows == position){
            break;
        }
        for (int i = 0; i < line.length(); ++i) {
            char currentChar = line[i];
            int element = currentChar;
            myVector[position][i] = element - 48;
        }
        position+=1;

    }

    inputFile.close();
}

int multiplyTwoVectors(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    int result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

int main() {
    const int N = 10000000;
    std::vector<std::vector<int>> myVector(N, std::vector<int>(10, 0));
    std::vector<int> prodVector(N, 0);
    int numOfActions = N - 1;
    omp_set_num_threads(2);

    double start_time = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            fillVectorFromFile(myVector, N);
        }

        #pragma omp section
        {
            while(numOfActions != 0){
                for (int i = 1; i < N; i++){
                    if (myVector[i].size() == 10 and myVector[i-1].size() == 10 and prodVector[i-1] == 0){
                        prodVector[i-1] = multiplyTwoVectors(myVector[i], myVector[i-1]);
                        numOfActions-=1;
                    }
                }
            }
        }
    }
    double end_time = omp_get_wtime();
    std::cout << end_time - start_time << " секунд." << std::endl;
    return 0;
}