#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<ctype.h>
#include<fcntl.h>
#define ODCZYT 0
#define ZAPIS 1

int main()
{
    char message[80];
    int fd = open("fifo", O_RDONLY);
    read(fd, message, sizeof(message));
    printf("%s \n", message);
    close(fd);
    return 0;
}