#ifndef OFERTA_H
#define OFERTA_H
/*Tip de data noua pentru a retine ofertele
 *tip-un sir de caractere
 *suprafata-un numar rational poztiv
 *adresa-un sir de caractere
 *pret-un numar rational pozitiv
 */
typedef struct {
    int id;
    char* tip;
    float suprafata;
    char* adresa;
    float pret;
} Oferta;
/*Creaza si returneaza un tip de data Oferta
 */
Oferta creeaza_oferta(int id,char tip[],float suprafata,char adresa[],float pret);
/*Dealoca memoria utilizata pentru  o oferta
 */
void distruge_oferta(Oferta* oferta);

#endif