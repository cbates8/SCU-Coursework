//Name: Casey Bates
//Date: 22 October 2020
//Title: Lab 5 - Synchronization Using Semaphonres, Locks, and Condition Variables
//Description: Thread Sychronization using mutex locks rather than semaphores
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
//#include <fcntl.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
//sem_t *mutex; 
pthread_mutex_t lock;

void* go(void* arg) {   
	//sem_wait(mutex); //entry section
	pthread_mutex_lock(&lock);  
	printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section    
	sleep(1);   
	//sem_post(mutex); //exit section 
	pthread_mutex_unlock(&lock);  
	return (NULL);
} 

int main() { 
	//mutex = sem_open("mutex2", O_CREAT, 0644, 1);
	pthread_mutex_init(&lock, NULL);
	static int i;
	for (i = 0; i < NTHREADS; i++)     
		pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
	for (i = 0; i < NTHREADS; i++) {   
		pthread_join(threads[i],NULL);   
		printf("\t\t\tThread %d returned \n", i);   
	}
	printf("Main thread done.\n");
	//sem_unlink("mutex2");
	pthread_mutex_destroy(&lock); 
	return 0; 
} 
