//Name: Casey Bates
//Date: 10/1/20
//Title: Programming in C and use of Systems Calls
//Description: This program creats two threads and has each run a loop, printing each value from 0-99
#include <stdio.h>	 // printf, stderr
#include <pthread.h>	 // pthread_create
#include <stdlib.h> 	 // atoi
#include <unistd.h>	 // usleep

//To be run by the created thread
void *newThread(void *n) {
	int i;
	for(i = 0; i<100; i++) {
		printf("\t\t\t New Thread %d\n", i);
		usleep(*(int *)n);
	}
}

// Main function with command-line arguments to pass
int main(int argc, char *argv[]) {
	int n = atoi(argv[1]); 	//n microseconds to input from keyboard to delay
	pthread_t threadid;
	printf("\n Before Threading.\n");
	
	pthread_create(&threadid, NULL, newThread, (void *) &n); //Create seperate thread to run newThread() function
	
	//Loop executed by original thread
	int i;
	for(i = 0; i < 100; i++) {
		printf("Original Thread %d\n", i);
		usleep(n);
	}

	pthread_join(threadid, NULL); //terminate previously created thread
	printf("\n After Threading. \n");
	return 0;
}
