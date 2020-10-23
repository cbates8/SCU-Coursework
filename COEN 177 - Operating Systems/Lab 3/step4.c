//Name: Casey Bates
//Date: 10/8/2020
//Title: Lab 3 - Pthreads and Inter-process Communication - Pipes
//Description: This program implements the shell command "cat /etc/passwd | grep root".
//A parent process will create two children: The first to execute "cat" and pass the value to the
//other child, which will execute "grep" and print to console.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>

//Main function
int main() {
	int fds[2];
	pipe(fds);
	
	//Child 1: Upstream - Execute "cat /etc/passwd"
	if(fork() == 0) {
		dup2(fds[1], 1); //duplicate upstream fd to stdout
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", 0);
	}
	//Child 2: Downstream - Execute "grep root"
	else if (fork() == 0) {
		dup2(fds[0], 0); //duplicate downstream fd to stdin
		close(fds[1]);
		execlp("grep", "grep", "root", 0);
	}
	//Parent: Close pipe and wait for children to terminate
	else {
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
