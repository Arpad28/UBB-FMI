#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void start_ui(Repo* r,Service* s) {
    int optiune,id=0;
    do {
        printf("==============MENIU==============\n");
        printf("1.Adauga o oferta\n");
        printf("2.Actualizeaza o oferta\n");
        printf("3.Afiseaza toate ofertele\n");
        printf("4.Sterge o oferta\n");
        printf("5.Sorteaza ofertele\n");
        printf("6.Filtreaza ofertele\n");
        printf("7.Exit\n");
        printf("=================================\n");
        printf("Alege o optiune: ");
        int result =scanf_s("%d",&optiune);
        if (result!=1) {
            while (getchar()!='\n'){}
            printf("Comanda invalida\n");
        }
        else {
            switch(optiune) {
                case 1: {
                    char tip[20];
                    float suprafata;
                    char adresa[100];
                    float pret;
                    printf("Tip: ");
                    scanf_s("%19s", tip, (unsigned)sizeof(tip));
                    printf("Suprafata: ");
                    scanf_s("%f", &suprafata);
                    printf("Adresa: ");
                    scanf_s("%99s", adresa, (unsigned)sizeof(adresa));
                    printf("Pret: ");
                    scanf_s("%f", &pret);
                    if (adauga_oferta(s, id + 1, tip, suprafata, adresa, pret) == 1) {
                        id++;
                        printf("Oferta adaugata cu succes\n");
                    } else
                        printf("Date invalide\n");
                    break;
                }
                case 2: {
                    int id_cautat;
                    char tip[20];
                    float suprafata;
                    char adresa[100];
                    float pret;
                    printf("ID oferta de actualizat:");
                    scanf_s("%d", &id_cautat);
                    printf("Tipul actualizat: ");
                    scanf_s("%19s", tip, (unsigned)sizeof(tip));
                    printf("Suprafata actualizata: ");
                    scanf_s("%f", &suprafata);
                    printf("Adresa actualizata: ");
                    scanf_s("%99s", adresa, (unsigned)sizeof(adresa));
                    printf("Pretul actualizat: ");
                    scanf_s("%f", &pret);
                    if (actualizare_oferta(s, id_cautat, tip, suprafata, adresa, pret) == 1)
                        printf("Oferta actualizata cu succes\n");
                    else
                        printf("Date invalide\n");
                    break;
                }
                case 3: {
                    int n = get_lungime(r);
                    if (n == 0) {
                        printf("Nu exista oferte\n");
                    } else {
                        for (int i = 0; i < n; ++i) {
                            Oferta* o = (Oferta*)get_element(r->oferta, i);
                            printf("Oferta %d:| Tip %s |Suprafata %.2f| Adresa %s| Pret %.2f\n",
                                   o->id, o->tip, o->suprafata, o->adresa, o->pret);
                        }
                    }
                    break;
                }
                case 4: {
                    int id_sters;
                    printf("ID de sters:");
                    scanf_s("%d", &id_sters);
                    if (sterge_oferta(s, id_sters) == 1)
                        printf("Oferta stearsa cu succes\n");
                    else
                        printf("Date invalide\n");
                    break;
                }
                case 5: {
                    int conditie;
                    printf("1.Sorteaza dupa pret crescator\n");
                    printf("2.Sorteaza dupa pret descrescator\n");
                    printf("3.Sorteaza dupa tip crescator\n");
                    printf("4.Sorteaza dupa tip descrescator\n");
                    printf("Introdu criteriul: ");
                    scanf_s("%d", &conditie);
                    if (conditie < 1 || conditie > 4)
                        printf("Conditie invalida\n");
                    else {
                        int lung = get_lungime(r);
                        if (lung == 0)
                            printf("Nu exista oferta adaugata\n");
                        else {
                            Oferta *oferta_sortata = sortare(s, conditie);
                            for (int i = 0; i < lung; ++i)
                                printf("Oferta %d:| Tip %s |Suprafata %.2f| Adresa %s| Pret %.2f\n",
                                       oferta_sortata[i].id, oferta_sortata[i].tip,
                                       oferta_sortata[i].suprafata, oferta_sortata[i].adresa,
                                       oferta_sortata[i].pret);
                            free(oferta_sortata);
                        }
                    }
                    break;
                }
                case 6: {
                    int filtru;
                    printf("1.Filtreaza casele\n");
                    printf("2.Filtreaza apartamentele\n");
                    printf("3.Filtreaza terenurile\n");
                    printf("4.Filtreaza dupa pret\n");
                    printf("5.Filtreaza dupa suprafata\n");
                    printf("Introdu filtrul: ");
                    scanf_s("%d", &filtru);
                    int lung = get_lungime(r);
                    if (lung == 0)
                        printf("Nu exista oferta adaugata\n");
                    else {
                        if (filtru < 1 || filtru > 5)
                            printf("Filtrare invalida\n");
                        else {
                            float numar = 0;
                            if (filtru == 4 || filtru == 5) {
                                printf("Introdu numarul: ");
                                scanf_s("%f", &numar);
                                if (numar <= 0) {
                                    printf("Numar invalid\n");
                                    break;
                                }
                            }
                            int dim;
                            Oferta* filtrat = filtrare(s, filtru, numar, &dim);
                            if (dim == 0)
                                printf("Nu avem oferte care respecta acest filtru\n");
                            else {
                                for (int i = 0; i < dim; ++i)
                                    printf("Oferta %d:| Tip %s |Suprafata %.2f| Adresa %s| Pret %.2f\n",
                                           filtrat[i].id, filtrat[i].tip, filtrat[i].suprafata,
                                           filtrat[i].adresa, filtrat[i].pret);
                            }
                            free(filtrat);
                        }
                    }
                    break;
                }
                case 7:
                    printf("La revedere\n");
                    break;
                default:
                    printf("Comanda inexistenta\n");
                    break;
            }
        }
    }while (optiune!=7);
}