//Name: Casey Bates
//Date: 10/8/2020
//Title: Lab 3 - Pthreads and Inter-Process Communication - Pipes
//Description: This program creates 10 threads that will each print a unique value.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];

//main function
int main() {
	int i;
	for (i = 0; i < NTHREADS; i++) {
		usleep(i); //Each thread will be staggered by 1 microsecond, preventing them from printing the same value of i more than once
		pthread_create(&threads[i], NULL, go, &i);
	}
	for (i = 0; i < NTHREADS; i++) {
		printf("Thread %d returned\n", i);
		pthread_join(threads[i],NULL);
	}
	printf("Main thread done.\n");
	return 0;
}

void *go(void *arg) {
	printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), *(int *)arg);
	return 0;
}


