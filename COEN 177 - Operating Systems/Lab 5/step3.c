//Name: Casey Bates
//Date: 22 October 2020
//Title: Lab 5 - Synchronization Using Semaphores, Locks, and Condition Variables
//Description: This program demonstrates a solution to the producer-consumer problem using semaphores
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

#define NTHREADS 10
#define n 10

pthread_t threads[NTHREADS];

sem_t *mutex;	 // init to 1
sem_t *empty;	 // init to n
sem_t *full;	 // init to 0

int buffer[n];
int buffIn;
int buffOut;

//Code for producer threads
void producer(void *arg) {
	int item;
	do {
		//Produce item
		item = rand() % 20; //Random item between 0-19
		sleep(1);
		printf("Thread %d: Producing item %d\n", (int)arg, item);
		
		//Enter critical section
		sem_wait(empty); //wait until buffer is empty
		sem_wait(mutex);
		
		//Add item to buffer
		buffer[buffIn] = item;
		buffIn = (buffIn + 1) % n;

		//Exit critical section
		sem_post(mutex);
		sem_post(full); //signal that buffer is full

	} while(1);
}

//Code for consumer threads
void consumer(void *arg) {
	int item;
	do {
		//Enter critical section
		sem_wait(full); //Wait until buffer is full
		sem_wait(mutex);
		
		//Remove item from buffer
		item = buffer[buffOut];
		buffOut = (buffOut + 1) % n;
		
		//Exit critical section
		sem_post(mutex);
		sem_post(empty); //signal that buffer is empty
		
		//Consume item
		sleep(1);
		printf("Thread %d: Consume item %d\n", (int)arg, item);
	} while(1);
}



//Main function - Create producer and consumer threads
int main() {
	int i;
	srand(time(NULL));
	////// Initialize Semaphores //////
	mutex = sem_open("mutex2", O_CREAT, 0644, 1);
	empty = sem_open("empty2", O_CREAT, 0644, n);
	full = sem_open("full2", O_CREAT, 0644, 0);
	
	////// Create Producer and Consumer Threads //////
	for(i = 0; i < NTHREADS; i++) {
		// Create NTHREADS/2 Producers
		if(i < NTHREADS/2)
			pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);
		// Create NTHREADS/2 Consumers
		else if(i >= NTHREADS/2 && i < NTHREADS)
			pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);
	}
	
	////// Join threads with the main thread after completion //////
	for(i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	
	////// Unlink Semaphores //////
	sem_unlink("mutex2");
	sem_unlink("empty2");
	sem_unlink("full2");
	
	return 0;
}
