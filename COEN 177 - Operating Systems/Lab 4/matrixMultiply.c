//Name: Casey Bates
//Date: 15 October 2020
//Title: Lab 4 - Developing Multi-threaded Applications
//Description: This program uses multiple threads to multiply two matricies.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MATRIX_SIZE 3

pthread_t threads[MATRIX_SIZE];
double matrixA[MATRIX_SIZE][MATRIX_SIZE], matrixB[MATRIX_SIZE][MATRIX_SIZE], matrixC[MATRIX_SIZE][MATRIX_SIZE];

//Eeach thread is responsible for one row of ther final matrix, arg being the identifier of that row.
void *multiply(void * arg) {
	int row = *(int *) arg;
	int a, b;
	for(a = 0; a < MATRIX_SIZE; a++) {
		double temp = 0;
		for(b = 0; b < MATRIX_SIZE; b++) {
			temp += matrixA[row][b] * matrixB[b][a];
		}
		matrixC[row][a] = temp;
	}
}

int main() {
	int N = MATRIX_SIZE;
	int M = MATRIX_SIZE;
	int L = MATRIX_SIZE;
	int i, j;

	/***Fill matricies with random values***/
	//matrix A
	printf("Matrix A: \n");
	srand(time(NULL));
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++) {
			matrixA[i][j] = rand() % 20; //Random values from 0-19
			printf("%.2f \t", matrixA[i][j]);
		}
		printf("\n\n");
	}
	//matrix B
	printf("\nMatrix B: \n");
        for(i = 0; i < M; i++){
                for(j = 0; j < L; j++) {
                        matrixB[i][j] = rand() % 20;
			printf("%.2f \t", matrixB[i][j]);
                }
		printf("\n\n");
        }
	
	/***Create threads for each row of C***/
	for(i = 0; i < N; i++) {
		usleep(i);
		pthread_create(&threads[i], NULL, multiply, &i);
	}

	/***Print the resulting matrix C ***/
	//Join all threads with main thread
	for(i = 0; i < MATRIX_SIZE; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d returned.\n", i);
	}

	//Print matrix c
	printf("\nFinal Matrix: \n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < L; j++) {
			printf("%.1f \t", matrixC[i][j]);
		}
		printf("\n\n");
	}

}

