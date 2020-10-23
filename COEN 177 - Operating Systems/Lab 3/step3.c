//Name: Casey Bates
//Date: 10/8/2020
//Title: Lab 3 - Pthreads and Inter-process Communication - Pipes
//Description: This program creates three processes: The first child will execute
//the 'ls'command and pass the output to the other process, which will print it to the console. 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
	int  fds[2];
	char buff[60];
	int count;
	int i;
	pipe(fds);

	//Child 1: writes upstream
	if (fork()==0){
		printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
		dup2(fds[1], 1); //Duplicate the upstream file descriptor to stdout
		close(fds[0]);
		execlp("ls", "ls", 0);
		exit(0);
	}
	//Child 2: reads downstream, prints to console
	else if(fork()==0){
		printf("\nReader on the downstream end of the pipe \n");
		//dup2(fds[0], 0); //Duplicates downstream file descriptor to stdin
		close(fds[1]);
		while((count=read(fds[0],buff,60))>0){
			for(i=0;i<count;i++){
				write(1,buff+i,1);
				write(1," ",1);
			}
			printf("\n");
		}
		exit(0);
	}
	//Parent: Closes pipe and waits for children to terminate
	else{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
return 0;
}
