#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <chrono>
using namespace std;

#define dim 20

int ** matrix = new int*[dim];
int * result = new int[dim];
int * vec = new int[dim];

void startMatrix(int **mat){
	for(int i=0; i<dim; ++i){
		mat[i] = new int[dim];
	}
}
void fillMatrix(int ** mat){
    for(int i=0; i<dim; ++i){
		for(int j=0; j<dim; ++j){
			mat[i][j] = rand() % 10 + 1;
        }
    }
}
void fillVector(int * vec){
	for(int i=0; i<dim; ++i){
		vec[i] = rand() % 10 + 1;
	}
}
void printMatrix(int **mat){
	for(int i =0; i<dim; ++i){
		for(int j =0; j<dim; ++j){
			cout << setw(4) << mat[i][j] << " ";
		}   
		cout << endl;
	}
}
void printVector(int * vec){
	for(int i =0; i<dim; ++i){
		cout << setw(5) << vec[i] ;
	} cout << endl;
}

void matVecMult(int **mat, int *vec){
  for(int i = 0; i<=dim/2; i+=2){
    for(int j = 0; j<dim; ++j){
        result[i] += mat[i][j]*vec[j];
		result[i+1] += mat[i+1][j]*vec[j];
    }   
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
	//printMatrix(matrix);
	//printVector(vec);
	//printVector(result);
	return 0;
}