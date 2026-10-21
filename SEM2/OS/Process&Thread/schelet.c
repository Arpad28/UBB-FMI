#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char* argv[])
{
        if(argc<2)
        {
                printf("Numar insuficient de argumente\n");
                exit(1);
        }
        int pd[2];
        if(pipe(pd)<0)
        {
                perror("pipe()");
                exit(1);
        }
        int pid=fork();
        if(pid<0)
        {
                perror("fork()");
                exit(2);
        }
        if(pid==0)//copil
        {
                close(pd[0]);//inchid read

                int n=atoi(argv[1]);
                write(pd[1],&n,sizeof(int));

                close(pd[1]);
                exit(0);

        }
        close(pd[1]);//inchid write

        int n=0;
        read(pd[0],&n,sizeof(int));
        printf("Am citit numarul %d\n",n);

        wait(NULL);
        return 0;
}