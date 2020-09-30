//Name: Casey Bates
//Date: 10/1/20
//Title: Lab 2 - Programming in C and use of Systems Calls
//Description: Program that creates exactly seven processes, with each only having two children or none.

#include <stdio.h>	 // printf, stderr
#include <sys/types.h>	 // pid_t
#include <unistd.h>	 // fork
#include <stdlib.h> 	 // atoi
#include <errno.h> 	 // errno

//Function to create two children processes from each parent that runs this code.
pid_t createTwoChildren() {
	pid_t pid;
	pid = fork(); //Create the first child process
        if(pid == -1) {
        	fprintf(stderr, "can't fork, error %d\n", errno);
        }
	
	if(pid) { //If parent process
		pid = fork(); //create second child process
                if(pid == -1) {
                        fprintf(stderr, "can't fork, error %d\n", errno);
                }

	}
	return pid;
}

//Main function
int main() {
	pid_t pid;
	printf("\n Before forking.\n");
	
	pid = createTwoChildren(); //After this function completes, there will be 3 total processes (parent and two children)
	if(!pid) { //If child process
		createTwoChildren(); //Create two more children (Both previous children will run this. Now we have seven total processes)
		printf("Child Finished\n");
	}
	else {
		wait(); //Wait until all child processes are terminated
		printf("Parent Finished\n");
	}
	return 0;
}
