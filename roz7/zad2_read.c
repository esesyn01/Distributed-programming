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
    char message_upper[80];
    if(mkfifo("fifo",0777) != -1)
    {
        scanf("%s" ,message);
        int fd = open("fifo", O_WRONLY);
        write(fd, message, sizeof(message));
        close(fd);
        return 0;
    }
    return -1;
}