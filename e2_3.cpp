#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

#include "functions.h"

using namespace std;

// 2048, 4096, 8192.
#define N 3

int** matrix = new int*[N];
int* result = new int[N];
int** vec = new int*[N];
int* vec_t = new int[N];

void matVecMult();

int main(){
    srand (time(NULL));
    startMatrix(matrix, N);
    startVector(vec, N);
    fillMatrix(matrix, N);
    fillVector(vec, N);

    matVecMult();
    printMatrix(matrix, N);
    printVector(vec, N);
    printResult(result, N);
    return 0;
}

void matVecMult(){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            result[i] += matrix[i][j] * vec[j][0];
        }   
    }
}