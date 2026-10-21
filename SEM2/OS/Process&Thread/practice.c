#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_THR 100            // Numărul maxim de thread-uri
#define MAX_TEXT_SIZE 1000000  // Dimensiunea maximă a textului (1 MB)

// Variabile globale statice
int frecventa[26] = {0};
char text[MAX_TEXT_SIZE];
long dimensiune_text = 0;
int num_threads = 0;

pthread_mutex_t mtx;

// Funcția executată de thread
void* numara_litere(void* arg)
{
        // Preluăm id-ul (NU mai facem free)
        int id = *(int*)arg;

        // Calculez limitele intervalului pentru acest thread
        long chunk = dimensiune_text / num_threads;
        long left = id * chunk;
        long right = left + chunk;

        for (long i = left; i < right; ++i)
        {
                char c = tolower(text[i]);
                if (c >= 'a' && c <= 'z')
                {
                        // ZONĂ CRITICĂ - blocăm și deblocăm
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
                printf("Utilizare: %s <fisier_text> <numar_threaduri>\n", argv[0]);
                exit(1);
        }

        num_threads = atoi(argv[2]);
        if (num_threads <= 0 || num_threads > MAX_THR)
        {
                printf("Numărul de thread-uri trebuie să fie între 1 și %d.\n", MAX_THR);
                exit(1);
        }

        // 1. Citirea simplificată direct în vectorul static
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
                perror("fopen()");
                exit(1);
        }

        // fread citește până la MAX_TEXT_SIZE și returnează câte caractere a găsit în mod real
        dimensiune_text = fread(text, sizeof(char), MAX_TEXT_SIZE, file);
        fclose(file);

        // 2. Creez mutex
        pthread_mutex_init(&mtx, NULL);

        // 3. Vectori statici pentru thread-uri și id-uri
        pthread_t tids[MAX_THR];
        int ids[MAX_THR];

        // 4. Creez thread-urile
        for (int i = 0; i < num_threads; ++i)
        {
                ids[i] = i; // Salvăm i în vectorul static pentru a nu se suprascrie
                pthread_create(&tids[i], NULL, numara_litere, &ids[i]);
        }

        // 5. Aștept terminarea thread-urilor
        for (int i = 0; i < num_threads; ++i)
        {
                pthread_join(tids[i], NULL);
        }

        // 6. Afișez rezultatul
        printf("Frecvența literelor:\n");
        for (int i = 0; i < 26; ++i)
        {
                if (frecventa[i] > 0)
                {
                        printf("%c: %d\n", 'a' + i, frecventa[i]);
                }
        }

        // 7. Distrug mutex
        pthread_mutex_destroy(&mtx);

        return 0;
}