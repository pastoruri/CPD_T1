#include <iostream>
#include <time.h>
#include "e2MatrixBlockTilling.h"
using namespace std;

#define num_threads 4
// Amount of indexes of a matrix that can fix in the cache line we asume the number
#define num_indexes_cache_line 2

int **m1;
int **m2;
int **m3;
mutex g_mutex;

int **transpose_matrix(int **m, int rows, int columns) {
    int **transpose = new int*[rows];
    for (int i = 0; i < rows; i++) {
        transpose[i] = new int[columns];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            transpose[j][i] = m[i][j];
        }
    }
    return transpose;
};

void allocmemory(int rows, int columns) {
    m1 = new int*[rows];
    m2 = new int*[rows];
    m3 = new int*[rows];
    for (int i = 0; i < rows; i++) {
        m1[i] = new int[columns];
    }
    for (int i = 0; i < rows; i++) {
        m2[i] = new int[columns];
    }
    for (int i = 0; i < rows; i++) {
        m3[i] = new int[columns];
    }
};

void fillmatrix(int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m1[i][j] = 2*(rand()%10);
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m2[i][j] = 2*(rand()%10);
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m3[i][j] = 0;
        }
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

void multiply(struct data args) {

    for (int i = args.row_0; i < args.row_1; i++) {
        for (int j = args.columns_0; j < args.columns_1; j++) {
            int temp = 0;
            for (int k = args.columns_0; k < args.columns_1; k++) {
                temp += m1[i][k] * m2[k][j];
            }
            g_mutex.lock();
            m3[i][j] += temp;
            g_mutex.unlock();
        }
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
    m2 = transpose_matrix(m2, rows, columns);

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
    printmatrix(m2, rows, columns);
    printmatrix(m3, rows, columns);*/

    cout << "Finished Processing" << endl;

    return 0;
}