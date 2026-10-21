#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#define MAX_SIZE 100

int main(int argc,char* argv[])
{
        char sir[]="BaeioucAEIOU";
        printf("Sir initial: %s\n",sir);
        char vocale[]="aeiouAEIOU";
        for(int i=0;i<strlen(vocale);++i)
        {
                int  pd[2];
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
                        close(pd[0]);//inchidem read
                        int k=0;
                        char* tmp=malloc(MAX_SIZE*sizeof(char));
                        for(int j=0;j<strlen(sir);++j)
                        {
                                if(sir[j]!=vocale[i])
                                {
                                        tmp[k]=sir[j];
                                        k++;
                                }
                        }
                        tmp[k]='\0';
                        write(pd[1],tmp,MAX_SIZE*sizeof(char));
                        close(pd[1]);
                        free(tmp);
                        exit(0);
                }
                close(pd[1]);//inchidem write
                char* tmp=malloc(MAX_SIZE*sizeof(char));
                read(pd[0],tmp,MAX_SIZE*sizeof(char));
                strcpy(sir,tmp);
                close(pd[0]);
                wait(NULL);//0
                free(tmp);
        }
        printf("Sirul lucrat este: %s\n",sir);
        return 0;
}