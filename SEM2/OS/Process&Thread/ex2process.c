#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char* argv[])
{
        FILE *fd=fopen("file1.txt","r");
        if(fd==NULL)
        {
                perror("fopen()");
                exit(1);
        }
        for(char ch='a';ch<='z';++ch)
        {
                int pd[2];
                if(pipe(pd)<0)
                {
                        perror("pipe()");
                        exit(2);
                }
                int pid=fork();
                if(pid<0)
                {
                        perror("fork()");
                        exit(2);
                }
                if(pid==0)
                {
                        close(pd[0]);//inchid citirea
                        char ch1;
                        int contor=0;
                        fseek(fd,0L,SEEK_SET);//pentru a da rewind la fisier sa mai poti parcurge dupa
                        while((ch1=fgetc(fd))!=EOF)//citim caracter cu caracter din fisier
                        {
                                if(ch1==ch || ch==tolower(ch1))
                                {
                                        contor++;
                                }
                        }
                        write(pd[1],&contor,sizeof(int));
                        close(pd[1]);//inchid scrierea
                        exit(0);
                }
                //in parinte
                close(pd[1]);
                int aparitii=0;
                read(pd[0],&aparitii,sizeof(int));
                printf("%c apare de %d ori\n",ch,aparitii);
                close(pd[0]);
                wait(NULL);
        }
        fclose(fd);
}