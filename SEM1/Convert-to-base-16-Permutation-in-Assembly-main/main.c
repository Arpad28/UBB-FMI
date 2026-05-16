#include <stdio.h>

extern void modul(unsigned int a);

int main()
{
    unsigned int a;
    printf("Introduceti un numar: ");
    scanf("%u",&a);
    modul(a);
    return 0;
}