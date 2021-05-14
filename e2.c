#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define num_threads 4

int **m1;
int *vector;
int *result;

struct data {
    int thread_id;
    int row_0;
    int row_1;
    int columns;
};

void allocmemory(int rows, int columns) {
    int i, j;
    m1 = (int **) malloc(rows*sizeof(int*));
    vector = (int *) malloc(rows*sizeof(int));
    result = (int *) malloc(rows*sizeof(int));
    for (i = 0; i < rows; i++) {
        m1[i] = (int*) malloc(columns*sizeof(int));
    }
};

void fillmatrix(int rows, int columns) {
    int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            m1[i][j] = 2*(rand()%10);
        }
    }
    for (i = 0; i < rows; i++) {
        vector[i] = 2*(rand()%10);
    }
};

void printmatrix(int **m, int rows, int columns) {
    int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
};

void printvector(int *v, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
};

void *multiply(void *args) {
    int i, j, k, row_0, row_1, columns;
    struct data *my_data;
    my_data = (struct data*) args;
    row_0 = my_data->row_0;
    row_1 = my_data->row_1;
    columns = my_data->columns;

    for (i = row_0; i < row_1; i++) {
        for (j = 0; j < columns; j++) {
            result[i] = 0;
            for (k = 0; k < columns; k++) {
                result[i] += m1[i][k]*vector[k];
            }
        }
    }

}

int main() {

    pthread_t thr[num_threads];
    struct data data_args[num_threads];
    printf("Enter the number of rows and columns: ");
    int rows;
    scanf("%d", &rows);
    int columns = rows;

    allocmemory(rows, columns);
    fillmatrix(rows, columns);

    int i, temp, cont;
    temp = 0;
    cont = rows/num_threads;
		if (cont % 2 == 0) {
			for (i = 0; i < num_threads; i++) {
        data_args[i].thread_id = i;
        data_args[i].columns = columns;
        data_args[i].row_0 = temp;
        data_args[i].row_1 = temp+cont;
        temp = temp+cont;
        if ( pthread_create(&thr[i], NULL, multiply, (void *) &data_args[i]) )
            printf("Error in creating thread %d\n", i);
			}
		}
		else {
			for (i = 0; i < num_threads-1; i++) {
        data_args[i].thread_id = i;
        data_args[i].columns = columns;
        data_args[i].row_0 = temp;
        data_args[i].row_1 = temp+cont;
        temp = temp+cont;
        if ( pthread_create(&thr[i], NULL, multiply, (void *) &data_args[i]) )
            printf("Error in creating thread %d\n", i);
			}
			data_args[num_threads-1].thread_id = num_threads-1;
			data_args[num_threads-1].columns = columns;
			data_args[num_threads-1].row_0 = temp;
			data_args[num_threads-1].row_1 = rows;
			temp = rows;
			if ( pthread_create(&thr[num_threads-1], NULL, multiply, (void *) &data_args[num_threads-1]) )
					printf("Error in creating thread %d\n", i);
		}

		for (i = 0; i < num_threads; i++) {
			pthread_join(thr[i], NULL);
		}

    /*printf("Matrix:\n");
    printmatrix(m1, rows, columns);
    printf("Vector:\n");
    printvector(vector, rows);
    printf("Result:\n");
    printvector(result, rows);*/

    return 0;
}