//Name: Casey Bates
//Date: 10/8/2020
//Title: Lab 3 - Pthreads and Inter-process Communication - Pipes
//Description: This program uses popes to implement producer-consumer message communication.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <string.h>

//Main Function
int main(int argc, char *argv[]) {
	int fds[2];
	char buffer[60];
	int i, counter;
	pipe(fds);

	//Child 1: Producer - Writes to buffer
	if(fork() == 0) {
		close(fds[0]);
		for(i = 1; i < argc; i++) {
			//buffer[i] = *argv[i];
			strcat(buffer, argv[i]); //Write commandline arguments into buffer
		}
		write(fds[1], buffer, strlen(buffer)); //Write buffer to pipe upstream
		exit(0);
	}
	//Child 2: Consumer - Remove from buffer
	else if (fork() == 0) {
		close(fds[1]);
		/*while ((counter = read(fds[0], buffer, 60)) > 0) {
			for (i = 0; i < counter; i++) {
				write(1, buffer+i, 1);
			}
			printf("\n");
		}*/
		read(fds[0], buffer, 60); //Read pipe downstream into buffer
		write(1, buffer, strlen(buffer)); //Write buffer to the console
		printf("\n");
		exit(0);
	}
	//Parent: Closee pipe and wait for children to terminate
	else {
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(1);
	}
	return 0;
}
