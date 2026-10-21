#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
        int pipe_B0_B[2];
        int pipe_B_B1[2];

        if(pipe(pipe_B0_B)<0)
        {
                perror("pipe()");
                exit(1);
        }
        if(pipe(pipe_B_B1)<0)
        {
                perror("pipe()");
                exit(2);
        }

        if(fork()==0){//B0
                close(pipe_B0_B[0]);
                close(pipe_B_B1[0]);close(pipe_B_B1[1]);
                int fd=open("fifo_a0_b0",O_RDONLY);
                if(fd == -1)
                {
                        perror("open()");
                        exit(3);
                }
                for(int i=1;i<=10;++i)
                {
                        int val;
                        read(fd,&val,sizeof(int));
                        write(pipe_B0_B[1],&val,sizeof(int));
                }
                close(fd);
                close(pipe_B0_B[1]);
                exit(0);
        }

        if(fork()==0){//B1
                close(pipe_B0_B[0]);close(pipe_B0_B[1]);
                close(pipe_B_B1[1]);
                int fd=open("fifo_b1_a1",O_WRONLY);
                if(fd == -1)
                {
                        perror("open()");
                        exit(4);
                }
                for(int i=1;i<=10;++i)
                {
                        int val;
                        read(pipe_B_B1[0],&val,sizeof(int));
                        write(fd,&val,sizeof(int));
                }
                close(fd);
                close(pipe_B_B1[0]);
                exit(0);
        }
        close(pipe_B0_B[1]);
        close(pipe_B_B1[0]);
        for(int i=1;i<=10;++i)
        {
                int val;
                read(pipe_B0_B[0],&val,sizeof(int));
                write(pipe_B_B1[1],&val,sizeof(int));
        }
        close(pipe_B0_B[0]);
        close(pipe_B_B1[1]);

        wait(NULL);
        wait(NULL);

        return 0;
}