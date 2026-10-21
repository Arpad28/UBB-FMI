#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THR 100
#define MAX_NUM 100000

int suma=0;
int* numere=NULL;

pthread_mutex_t mtx;//=PTHREAD_MUTEX_INITIALIZER;

//thread start routine
void* do_sum(void* arg)
{
        int id=*(int*)arg;
        free(arg);

        //calculez limitele  intervalului
        int left=id*(MAX_NUM/MAX_THR);
        int right=left+(MAX_NUM/MAX_THR);

        for(int i=left;i<right;++i)
        {
                pthread_mutex_lock(&mtx);
                suma+=numere[i];
                pthread_mutex_unlock(&mtx);
        }

        return NULL;
}


//1.generati 100K de numere aleatoare si calculati suma lor utilizand 100 thread-uri.
int main(int argc,char*argv[])
{
        //aloc dinamic tabloul de numere
        numere=malloc(MAX_NUM*sizeof(int));
        if(numere==NULL)
        {
                perror("malloc()");
                exit(1);
        }
        //generez numerele aleatoare
        for(int i=0;i<MAX_NUM;++i)
        {
                numere[i]=rand()%100;
        }
        //creez mutex
        pthread_mutex_init(&mtx,NULL);
        //creez thread-urile
        int* id=NULL;
        pthread_t tids[MAX_THR];
        for(int i=0;i<MAX_THR;++i)
        {
                id=malloc(sizeof(int));
                *id=i;
                pthread_create(&tids[i],NULL,do_sum,id);
        }

        //astept terminarea thread urilor
        for(int i=0;i<MAX_THR;++i)
        {
                pthread_join(tids[i],NULL);//suspenda executia si asteapta terminarea
        }
        //afisez rezultatul
        printf("Suma:%d\n",suma);
        //distrug mutex
        pthread_mutex_destroy(&mtx);
        //dealoc tabloul de numere
        free(numere);
        return 0;
}