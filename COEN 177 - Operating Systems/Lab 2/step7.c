//Name:Casey Bates
//Date: 10/1/20
//Title: Lab2 - Programming in C and use of Systems Calls
//Description: This program creates a child process to run the "ls" command. The parent process wates until the child terminates before it exits.

#include <stdio.h>	 // printf, stderr
#include <sys/types.h>	 // pid_t
#include <unistd.h>	 // fork
#include <stdlib.h> 	 // atoi
#include <errno.h> 	 // errno

// Main function
int main() {
	pid_t pid;
	pid = fork(); //Create child process
	if(pid == -1) {
	//If there is an error creating child process
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	else if(pid == 0) {
	// Child Process
		execlp("/bin/ls", "ls", NULL); //Execute ls command
	}
	else {
	//Parent Process
		wait(NULL); //Wait until child is complete
		printf("Child Complete");
		exit(0);
	}
	return 0;
}
