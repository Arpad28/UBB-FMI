#include <stdio.h>

extern void verifica(int x);
extern int neg[],poz[];
extern int n_neg,n_poz;

int main()
{
FILE *f=fopen("fisier.txt","r");
int x;
if(!f){
    printf("Fisierul nu se poate deschide");
    return 0;
}
while(fscanf(f,"%d",&x)==1)
{
    verifica(x);
}
printf("Numerele negative sunt:\n");
for(int i=0;i<n_neg;++i)
    printf("%d ",neg[i]);
printf("\nNumerele pozitive sunt:\n");
for(int i=0;i<n_poz;++i)
    printf("%d ",poz[i]);
return 0;
}