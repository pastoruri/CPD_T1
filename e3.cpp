#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <immintrin.h>
#include <chrono>
using namespace std;

#define dim 8

float ** matrix = new float*[dim];
float * result = new float[dim];
float * vec = new float[dim];

void startMatrix(float **mat){
	for(int i=0; i<dim; ++i){
		mat[i] = new float[dim];
	}
}
void fillMatrix(float ** mat){
	for(int i=0; i<dim; ++i){
		for(int j=0; j<dim; ++j){
			mat[i][j] = rand() % 10 + 1;
    }
  }
}
void fillVector(float * vec){
	for(int i=0; i<dim; ++i){
		vec[i] = rand() % 10 + 1;
	}
}
void printMatrix(float **mat){
	for(int i =0; i<dim; ++i){
		for(int j =0; j<dim; ++j){
			cout << setw(4) << mat[i][j] << " ";
		}   
		cout << endl;
	}
}
void printVector(float * vec){
	for(int i =0; i<dim; ++i){
		cout << setw(5) << vec[i] ;
	} cout << endl;
}

void matVecMult(float **mat, float *vec){

  for (int i = 0; i < dim; ++i) {
    __m128 temp = _mm_setzero_ps();
    for (int col = 0; col < dim; col += 4) {
        __m128 v = _mm_load_ps(&vec[col]);
        __m128 m = _mm_load_ps(matrix[i] + col);
        __m128 res = _mm_mul_ps(m, v);
        temp = _mm_add_ps(temp, res);
    }
    temp = _mm_add_ps(temp, temp);
    temp = _mm_add_ps(temp, temp);
    _mm_store_ss(&result[i], temp);
}
}
int main(){
	srand (time(NULL));
	startMatrix(matrix);
	fillMatrix(matrix);
	fillVector(vec);

    auto start = chrono::steady_clock::now();
	matVecMult(matrix, vec);
	auto end = chrono::steady_clock::now();
    cout << "Tiempo en microseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " μs\n";


	printMatrix(matrix);
	printVector(vec);
	printVector(result);
	return 0;
}