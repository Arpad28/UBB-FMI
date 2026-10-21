#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 50
int main(int argc,char* argv[])
{
        printf("Inainte de open ca write\n");
        //deschid fifo
        int fd =open("/tmp/fifo1",O_WRONLY);
        if(fd == -1)
        {
        perror("open()");
        exit(1);
        }
        printf("Dupa open ca write\n");
        char msg[MAX_SIZE];
        strcat(msg,"Helloooooooo");
        write(fd,msg,MAX_SIZE);

        //inchid fifo
        close(fd);
        return 0;
}