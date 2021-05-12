#ifndef FUNCIONES
#define FUNCIONES

#include <iostream>
#include <stdlib.h>

void startMatrix(int** mat, int N){
    for(int i = 0; i < N; ++i){
        mat[i] = new int[N];
    }
}
void startVector(int** vec, int N){
    for(int i = 0; i < N; ++i){
        vec[i] = new int[1];
    }
}
void fillMatrix(int** mat, int N){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            mat[i][j] = rand() % 10 + 1;
        }
    }
}
void fillVector(int** vec, int N){
    for(int i = 0; i < N; ++i){
        vec[i][0] = rand() % 10 + 1;
    }
}
void transpose(int** vec, int* vec_t, int N) {
    for (int i = 0; i < N; ++i) {
        vec_t[i] = vec[i][0];
    }
}
void printMatrix(int** mat, int N){
    std::cout << "Matriz: " << std::endl;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            std::cout << mat[i][j] << ' ';
        }   
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void printVector(int** vec, int N){
    std::cout << "Vector: " << std::endl;
    for(int i = 0; i < N; ++i){
        std::cout << vec[i][0] << '\n';
    }
    std::cout << std::endl;
}
void printResult(int* result, int N){
    std::cout << "Resultado: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << result[i] << '\n';
    }
    std::cout << std::endl;
}

#endif