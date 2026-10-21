#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc,char* argv[]){//argv[0]- executabilul,argv[1] cuvantul de dupa
        //creez un copil
        int n=0;
        int pd[2];  //pd[0] READ; pd[1] WRITE
        pipe(pd);
        int pid =fork();
        if(pid == -1){//fork() a esuat
                perror("fork()");
                exit(EXIT_FAILURE);
        }

        if(pid == 0){//in copil
                close(pd[1]);//inchid descriptorul de scriere

                read(pd[0],&n,sizeof(int));
                printf("Am citit %d\n",n);

                close(pd[0]); //inchid descriptorul de citire
                exit(1);
        }
        else{//in parinte
                close(pd[0]);//inchid descriptorul de citire
                n=5;
                write(pd[1],&n,sizeof(int) );

                close(pd[1]); //inchid descriptorul de scriere

                int status;
                wait(&status); //sau NULL
                //int val = WEXITSTATUS(status);//pentru  a lua valoarea din exit,(man wait)
        }
        return 0;
}