#include <stdio.h>
#include <unistd.h>

int main() {
	/*
	printf("This is my ls program\n");
	printf("Real user ID: %d\n", getuid());
	printf("Effective user ID: %d\n", geteuid());
	*/
	
	system("/bin/sh");
	return 0;
}