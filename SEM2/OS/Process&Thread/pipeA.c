#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_SIZE 100

int main()
{
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
        if(pid==0)
        {
                close(pd[1]);
                char c;
                char sir[MAX_SIZE];
                read(pd[0],&c,sizeof(char));
                read(pd[0],sir,MAX_SIZE*sizeof(char));
                close(pd[0]);
                int cnt=0;
                for(int i=0;i<strlen(sir);++i)
                        if(sir[i]==c)
                                cnt++;
                printf("Caracterul %c apare de %d ori in sirul dat\n",c,cnt);
                exit(0);
        }
        else
        {
                close(pd[0]);
                char c;
                char sir[MAX_SIZE];
                printf("Introdu un caracter:");
                scanf("%c",&c);
                printf("Introdu un sir de caractere:");
                getchar();
                fgets(sir,MAX_SIZE,stdin);
                sir[strlen(sir)-1]='\0';
                write(pd[1],&c,sizeof(char));
                write(pd[1],sir,MAX_SIZE*sizeof(char));
                close(pd[1]);
                wait(NULL);
        }
        return 0;
}