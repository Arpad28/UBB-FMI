#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc,char* argv[]){//argv[0]- executabilul,argv[1] cuvantul de dupa
        //creez un copil
        int a=0,b=0;
        int pd[2];  //pd[0] READ; pd[1] WRITE
        pipe(pd);
        int ret= pipe(pd);
        if(ret==-1)
        {
        perror("pipe()");
        exit(1);
        }
        int pid =fork();
        if(pid == -1){//fork() a esuat
                perror("fork()");
                exit(EXIT_FAILURE);
        }

        if(pid == 0){//in copil
                close(pd[1]);//inchid descriptorul de scriere

                read(pd[0],&a,sizeof(int));
                read(pd[0],&b,sizeof(int));
                printf("Avem suma %d\n",a+b);

                close(pd[0]); //inchid descriptorul de citire
                exit(1);
        }
        else{//in parinte
                close(pd[0]);//inchid descriptorul de citire
                printf("Dati a: ");
                scanf("%d",&a);
                write(pd[1],&a,sizeof(int) );

                printf("Dati b: ");
                scanf("%d",&b);
                write(pd[1],&b,sizeof(int) );
                close(pd[1]); //inchid descriptorul de scriere

                int status;
                wait(&status); //sau NULL
                //int val = WEXITSTATUS(status);//pentru  a lua valoarea din exit,(man wait)
        }       return 0;
}