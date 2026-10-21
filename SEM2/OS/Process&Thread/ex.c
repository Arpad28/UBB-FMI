#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc,char* argv[]){//argv[0]- executabilul,argv[1] cuvantul de dupa

        char* args[]={"ls", "-l", NULL};
        //creez un copil
        int pid =fork();
        if(pid == -1){//fork() a esuat
                perror("fork()");
                exit(EXIT_FAILURE);
        }

        if(pid == 0){//in copil
                int fd = open("lista_fisiere",O_CREAT | O_TRUNC | O_RDWR,0644);
                if(fd == -1)
                {
                        perror("open()");
                        exit(2);
                }

                //redirectez STDOUT
                dup2(fd,1);//0-in 1-out 2-error
                close(fd);
                if(execvp(args[0],args)<0)
                {
                        perror("execvp()");
                        exit(3);
                }
}
        else{//in parinte
                int status;
                wait(&status); //sau NULL
                //int val = WEXITSTATUS(status);//pentru  a lua valoarea din exit,(man wait)
        }
        return 0;
}