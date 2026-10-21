#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

#define MAX_THR 100        // Numărul maxim de thread-uri (și linii) permise
#define MAX_LINIE 1000     // Lungimea maximă a unei linii

// Variabile globale statice
int frecventa[26] = {0};
char text[MAX_THR][MAX_LINIE]; // Matrice: fiecare linie din fișier devine un rând

pthread_mutex_t mtx;

// Funcția executată de thread
void* numara_litere(void* arg)
{
        // Preluăm id-ul, care ne va spune și la ce linie din matrice ne uităm
        int id = *(int*)arg;

        // Parcurgem DOAR linia specifică acestui thread, caracter cu caracter
        for (int i = 0; text[id][i] != '\0'; ++i)
        {
                char c = tolower(text[id][i]);
                if (c >= 'a' && c <= 'z')
                {
                        // ZONĂ CRITICĂ - protejăm scrierea în vectorul comun
                        pthread_mutex_lock(&mtx);
                        frecventa[c - 'a']++;
                        pthread_mutex_unlock(&mtx);
                }
        }

        return NULL;
}

int main(int argc, char* argv[])
{
        if (argc != 3)
        {
                printf("Utilizare: %s <fisier_text> <numar_maxim_threaduri>\n", argv[0]);
                exit(1);
        }

        int max_threads = atoi(argv[2]);
        if (max_threads <= 0 || max_threads > MAX_THR)
        {
                printf("Numărul de thread-uri trebuie să fie între 1 și %d.\n", MAX_THR);
                exit(1);
        }

        // 1. Deschiderea fișierului
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
                perror("fopen()");
                exit(1);
        }

        // 2. Citirea linie cu linie
        int numar_linii = 0;
        // fgets citește până dă de '\n' sau până atinge limita MAX_LINIE
        // Ne oprim din citit dacă am atins numărul maxim de thread-uri permise
        while (numar_linii < max_threads && fgets(text[numar_linii], MAX_LINIE, file) != NULL)
        {
                numar_linii++; // Am citit o linie cu succes
        }
        fclose(file);

        if (numar_linii == 0)
        {
                printf("Fișierul este gol sau nu s-a putut citi.\n");
                return 0;
        }

        // 3. Creez mutex
        pthread_mutex_init(&mtx, NULL);

        // 4. Vectori statici pentru thread-uri și id-uri
        pthread_t tids[MAX_THR];
        int ids[MAX_THR];

        // 5. Creez exact atâtea thread-uri câte linii am citit
        for (int i = 0; i < numar_linii; ++i)
        {
                ids[i] = i; // Salvăm id-ul (linia) pentru a-l trimite thread-ului
                pthread_create(&tids[i], NULL, numara_litere, &ids[i]);
        }

        // 6. Aștept terminarea thread-urilor
        for (int i = 0; i < numar_linii; ++i)
        {
                pthread_join(tids[i], NULL);
        }

        // 7. Afișez rezultatul
        printf("Frecvența literelor:\n");
        for (int i = 0; i < 26; ++i)
        {
                if (frecventa[i] > 0)
                {
                        printf("%c: %d\n", 'a' + i, frecventa[i]);
                }
        }

        // 8. Distrug mutex
        pthread_mutex_destroy(&mtx);

        return 0;
}