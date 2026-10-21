#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
        FILE *f=fopen("matrix.txt","r");
        if(f==NULL){
                perror("Fisierul nu a putut fi deschis");
                exit(1);
        }
        int **matrice=malloc(3*sizeof(int *));
        if(matrice==NULL){
                perror("Eroare la primul malloc");
                exit(1);
        }
        for(int i=0;i<3;++i){
                matrice[i]=malloc(4*sizeof(int));
                if(matrice[i]==NULL){
                        perror("Eroare la al doilea malloc");
                        exit(1);
                }
                for(int j=0;j<4;++j)
                        fscanf(f,"%d",&matrice[i][j]);
        }
        fclose(f);
        for(int i=0;i<3;++i,printf("\n"))
                for(int j=0;j<4;++j)
                        printf("%d ",matrice[i][j]);
        for(int i=0;i<3;++i)
                free(matrice[i]);
        free(matrice);
        return 0;
}