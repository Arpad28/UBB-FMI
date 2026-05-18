#ifndef SERVICE_H
#define SERVICE_H

#include "../repo/repo.h"
/*Tip de data pentru Service
 *repo-tip de data Repo cu care lucreaza Service
 */
typedef struct {
    Repo* repo;
}Service;
/*Initializam Service gol
 *s-Service
 */
void init_service(Service* s,Repo* r);
/*Adauga o oferta
 *s-element de tip Service
 *tip-un sir de caractere
 *suprafata-un numar rational poztiv
 *adresa-un sir de caractere
 *pret-un numar rational pozitiv
 */
int adauga_oferta(Service* s,int id,char tip[],float suprafata,char adresa[],float pret);
/*Actualizeaza o oferta existenta
 *id-id ul de acutalizat,numar natural
 *s-element de tip Service
 *tip-un sir de caractere
 *suprafata-un numar rational poztiv
 *adresa-un sir de caractere
 *pret-un numar rational pozitiv
 */
int actualizare_oferta(Service* s,int id,char tip[],float suprafata,char adresa[],float pret);
/*Sterge o oferta existenta
 *s-element de tip Service
 *id-id ul ofertei de sters,numar natural pozitiv
 */
int sterge_oferta(Service*s,int id);
/*Returneaza o lista noua unde elementele sunt sortate dupa un anumit criteriu
 *s-element de tip Service
 *criteriu-criteriul dupa care se sorteaza,numar natural
 */
Oferta *sortare(Service* s,int criteriu);
/*Returneaza o lista noua unde elementele sunt filtrate dupa un anumit filtru
 *s-element de tip Service
 *filtru-Filtrul care se aplica listei,numar natural pozitiv
 *numar-numar rational ce reprezinta un crieteriu al filtrului
 *dim-dimensiunea listei finale,numar natural
 */
Oferta *filtrare(Service* s,int filtru,float numar,int* dim);
int cmp_pret_cresc(Oferta a, Oferta b);
int cmp_pret_desc(Oferta a, Oferta b);
int cmp_tip_cresc(Oferta a, Oferta b);
int cmp_tip_desc(Oferta a, Oferta b);
/*Sortare custom
 *s-service
 *cmp-functia de comparare
 */
Oferta* sortare_generica(Service* s, int (*cmp)(Oferta, Oferta));
#endif