#ifndef VALIDEAZA_H
#define VALIDEAZA_H
#include <stdbool.h>
#include "../repo/repo.h"

/*Returneaza 1 daca e valid,0 in caz contrar
 *tip-tipul de validat,sir de caractere
 *suprafata-suprafata de validat,numar rational
 *adresa-adresa de validat,sir de caractere
 *pret-pretul de validat,numar rational
 */
bool e_valid(char tip[],float suprafata,char adresa[],float pret);
/*Returneaza indicele la care se afla oferta cu id ul dat,-1 in caz de nu exista
 *r-element de tip Repo
 *id-id ul ofertei pe care il cautam
 */
int id_valid(Repo *r,int id);

#endif