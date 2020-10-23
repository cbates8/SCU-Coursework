/* unsafe.c */

/* This program has a buffer overflow vulnerability. */
/* Our task is to exploit this vulnerability */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int copyfunc(char *str)
{
    char buffer[38];

    /* The following statement has a buffer overflow problem */ 
    strcpy(buffer, str);

    return 1;
}

int main(int argc, char **argv)
{
    char str[517];
    FILE *inputfile;

    inputfile = fopen("inputfile", "r");
    fread(str, sizeof(char), 517, inputfile);
    copyfunc(str);

    printf("%s\n", "Successfully returned.");
    return 0;
}
