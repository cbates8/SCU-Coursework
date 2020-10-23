//Name: Casey Bates
//Date: 22 October 2020
//Title: Lab 5 - Synchronization Using Semaphores, Locks, and Condition Variables
//Description: This program demonstrates a solution to the producer-consumer problem using condition variables

#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

#define NTHREADS 10
#define n 10

pthread_t threads[NTHREADS];

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

int buffer[n];
int buffIn;
int buffOut;
int occupied;

//Code for producer threads
void producer(void *arg) {
	int item;
	do {
		//Produce item
		item = rand() % 20; //Random item between 0-19
		sleep(1);
		printf("Thread %d: Producing item %d\n", (int)arg, item);
		
		//Enter critical section
		pthread_mutex_lock(&mutex);
		while(occupied >= n)
			pthread_cond_wait(&empty, &mutex); //wait until buffer is empty

		//Add item to buffer
		buffer[buffIn] = item;
		buffIn = (buffIn + 1) % n;
		occupied++;

		//Exit critical section
		pthread_cond_signal(&full);  //signal that buffer is full
		pthread_mutex_unlock(&mutex);

	} while(1);
}

//Code for consumer threads
void consumer(void *arg) {
	int item;
	do {
		//Enter critical section
		pthread_mutex_lock(&mutex);
		while(occupied <= 0)
			pthread_cond_wait(&full, &mutex); //Wait until buffer is full
		
		//Remove item from buffer
		item = buffer[buffOut];
		buffOut = (buffOut + 1) % n;
		occupied--;
		//Exit critical section
		pthread_cond_signal(&empty); //signal that buffer is empty
		pthread_mutex_unlock(&mutex);

		//Consume item
		sleep(1);
		printf("Thread %d: Consume item %d\n", (int)arg, item);
	} while(1);
}



//Main function - Create producer and consumer threads
int main() {
	int i;
	srand(time(NULL));
	////// Initialize Mutex Lock  //////
	pthread_mutex_init(&mutex, NULL);
	
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
	
	////// Destroy Mutex Lock //////
	pthread_mutex_destroy(&mutex);
	
	return 0;
}
