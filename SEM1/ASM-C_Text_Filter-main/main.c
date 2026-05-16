#include <stdio.h>
#include <string.h>

extern void proceseaza(char *linie, char *rezultat);

int main()
{
    int n;
    char linie[256];
    char rezultat[256];
    printf("Introdu cate propozitii vrei sa citesti:");
    scanf("%d", &n);
    getchar(); 
    for (int i = 0; i < n; i++)
    {
        printf("Introduce o propozitie:");
        fgets(linie, 256, stdin);
        linie[strcspn(linie, "\n")] = 0;
        proceseaza(linie, rezultat);
        printf("Rezultatul este: %s\n", rezultat);
    }
    return 0;
}