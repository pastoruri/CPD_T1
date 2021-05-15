#include <iostream>
#include <time.h>
#include "MatrixVectorMultiplicationBlockTilling.h"
using namespace std;

#define num_threads 4
// Amount of indexes of a matrix that can fix in the cache line we asume the number
#define num_indexes_cache_line 16

int **m1;
int *vec;
int *result;
mutex g_mutex;

void allocmemory(int rows, int columns) {
    m1 = new int*[rows];
    vec = new int[rows];
    result = new int[rows];
    for (int i = 0; i < rows; i++) {
        m1[i] = new int[columns];
    }
};

void fillmatrix(int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m1[i][j] = 2*(rand()%10);
        }
    }
    for (int i = 0; i < rows; i++) {
        vec[i] = 2*(rand()%10);
    }
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
    }
};

void printmatrix(int **m, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
};

void printvector(int *v, int size) {
    for (int i = 0; i < size; i++) {
        cout << v[i] << ' ';
    }
    cout << endl;
};

void multiply(struct data args) {

    for (int i = args.row_0; i < args.row_1; i++) {
        //for (int j = args.columns_0; j < args.columns_1; j++) {
            int temp = 0;
            for (int k = args.columns_0; k < args.columns_1; k++) {
                temp += m1[i][k] * vec[k];
            }
            g_mutex.lock();
            result[i] += temp;
            g_mutex.unlock();
        //}
    }

}

int main() {

    srand (time(NULL));
    int rows, columns;

    cout << "Enter the number of rows and columns : ";
    cin >> rows;
    columns = rows;

    allocmemory(rows, columns);
    fillmatrix(rows, columns);

    int temp_0, temp_1, cont_0, thr_cont;
    temp_0 = 0; thr_cont = 0;
    cont_0 = rows/num_indexes_cache_line;
    T thr[num_threads];

    for (int i = 0; i < cont_0; i++) {
        int rows_now_0 = temp_0;
        int rows_now_1 = temp_0 + cont_0;
        temp_1 = 0;
        for (int j = 0; j < cont_0; j++) {
            struct data data_args;
            data_args.thread_id = thr_cont;
            data_args.columns_0 = temp_1;
            data_args.columns_1 = temp_1 + cont_0;
            data_args.row_0 = rows_now_0;
            data_args.row_1 = rows_now_1;
            temp_1 = temp_1 + cont_0;
            thr[thr_cont++].push_func(multiply, data_args);
            if (thr_cont >= num_threads) { thr_cont = 0; }
        }
        temp_0 = temp_0 + cont_0;
    }

    for (auto& t : thr) {
        t.start();
    }

    for (auto& t : thr) {
        t.stop();
    }

    /*printmatrix(m1, rows, columns);
    printvector(vec, rows);
    printvector(result, rows);*/

    cout << "Finished Processing" << endl;

    return 0;
}