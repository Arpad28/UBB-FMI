#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define MAX_THR 100
#define MAX_NUM 100000

int suma=0;
int* numere=NULL;

pthread_mutex_t mtx;// = PTHREAD_MUTEX_INITIALIZER;

//thread start routine
void* aduna(void* arg)
{
        int id=*(int*)arg;
        free(arg);

        //calculez limitele intervalului
        int st=id*(MAX_NUM/MAX_THR);
        int dr=st+(MAX_NUM/MAX_THR);

        //fac suma numerelor
        for(int i=st;i<dr;++i)
        {
                pthread_mutex_lock(&mtx);
                suma+=numere[i];
                pthread_mutex_unlock(&mtx);
        }
        return NULL;
}
//generati 100k numere aleatoare si calculati suma lor utilizand 100 thread-uri
int main(int argc,char* argv[])
{
        //aloc tabloul de numere
        numere=malloc(MAX_NUM*sizeof(int));
        if(numere == NULL)
        {
                perror("malloc()");
                exit(1);
        }

        //generez numere aleatoare
        int suma_corecta=0;
        srand(time(NULL));
        for(int i=0;i<MAX_NUM;++i)
        {
                numere[i]=rand()%256;
                suma_corecta+=numere[i];
        }
        //creez  mutex
        pthread_mutex_init(&mtx,NULL);
        //creez threadurile
        pthread_t tids[MAX_THR];
        for(int i=0;i<MAX_THR;++i)
        {
                int *id=malloc(sizeof(int));
                *id=i;
                pthread_create(&tids[i],NULL,aduna,id);
        }
        //astept terminarea threadurilor
        for(int i=0;i<MAX_THR;++i)
        {
                pthread_join(tids[i],NULL);
        }
        //afisez rezultatul
        printf("Am calculat suma:%d %d\n",suma,suma_corecta);
        //eliberez memoria alocata
        free(numere);
        pthread_mutex_destroy(&mtx);

        return 0;
}