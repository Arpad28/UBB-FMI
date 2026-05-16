#include <stdio.h>

extern void concatenare(char a[100],char b[100],char rez1[200],char rez2[200]);

int main()
{
    char a[100],b[100],rez1[200],rez2[200];
    printf("Introduce primul sir: ");
    scanf("%s",a);
    printf("Introduce al doilea sir: ");
    scanf("%s",b);
    concatenare(a,b,rez1,rez2);
    printf("Sirul 1+cifrele din sirul 2 este: %s\n",rez1);
    printf("Concatenarea sirurilor este: %s\n",rez2);
    return 0;
}