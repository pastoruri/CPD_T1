#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

#define dim 3

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
    }cout << endl;
}



void matVecMult(int **mat, int *vec){
    for(int i =0; i<dim; ++i){
     for(int j =0; j<dim; ++j){
        result[i] += mat[i][j]*vec[j];
    }   
    }
}
int main(){
    srand (time(NULL));
    startMatrix(matrix);
    fillMatrix(matrix);
    fillVector(vec);

    matVecMult(matrix, vec);
    printMatrix(matrix);
    printVector(vec);
    printVector(result);
    return 0;
}