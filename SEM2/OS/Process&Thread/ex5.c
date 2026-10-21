#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_SIZE 50

int main(int argc,char* argv[])
{
        printf("Inainde de open()\n");
        //deschid fifo
        int fd =open("/tmp/fifo1",O_RDONLY);
        if(fd == -1)
        {
        perror("open()");
        exit(1);
        }
        printf("Dupa open()\n");
        //citesc din FIFO
        char msg[MAX_SIZE];
        read(fd,msg,MAX_SIZE);
        printf("%s\n",msg);
        //inchid fifo
        close(fd);
        return 0;
}