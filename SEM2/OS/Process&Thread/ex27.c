#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 128
int M=0;
int contor=0;
int pozitie=0;
char sir[SIZE+1];

pthread_cond_t vcg = PTHREAD_COND_INITIALIZER;
pthread_cond_t vcp = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
//generatori
void* genereaza(void * arg)
{
        while(1)
        {
                pthread_mutex_lock(&mtx);
                if(pozitie==SIZE)
                {
                        pthread_cond_signal(&vcp);
                        while(pozitie==SIZE)
                                pthread_cond_wait(&vcg,&mtx);
                }
                if(contor==M)
                {
                        pthread_mutex_unlock(&mtx);
                        break;
                }

                char ch= 'a'+rand()%('a'-'A'+1);
                sir[pozitie]=ch;
                pozitie++;
                pthread_mutex_unlock(&mtx);
        }
        return NULL;
}

void* afiseaza(void* arg)
{
        while(1)
        {
                pthread_mutex_lock(&mtx);
                if(pozitie!=SIZE)
                {
                        pthread_cond_wait(&vcp,&mtx);
                        while(pozitie!=SIZE)
                        {
                                pthread_cond_wait(&vcp,&mtx);
                        }
                }
                if(contor==M)
                {
                        pthread_mutex_unlock(&mtx);
                        break;
                }
                printf("%s\n",sir);

                contor++;
                pozitie=0;
                memset(sir,0,SIZE);
                pthread_cond_broadcast(&vcg);
                pthread_mutex_unlock(&mtx);
        }


        return NULL;
}

int main(int argc,char** argv)
{
        //verific numarul de argumente
        if(argc!=3)
        {
                printf("Argumente insuficiente!\n");
                exit(1);
        }
        M=atoi(argv[2]);
        int N=atoi(argv[1]);
        pthread_t th[N+1];
        for(int i=0;i<N;++i)
        {
                pthread_create(&th[i],NULL,genereaza,NULL);
        }
        pthread_create(&th[N+1],NULL,afiseaza,NULL);
        for(int i=0;i<N+1;++i)
        {
                pthread_join(th[i],NULL);
        }

        return 0;
}