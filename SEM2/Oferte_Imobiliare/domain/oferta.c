#include "oferta.h"
#include <string.h>
#include <stdlib.h>

Oferta creeaza_oferta(int id, char tip[], float suprafata, char adresa[], float pret) {
    Oferta oferta;
    oferta.id = id;
    oferta.tip = (char*)malloc((strlen(tip) + 1) * sizeof(char));
    strcpy_s(oferta.tip, strlen(tip) + 1, tip);
    oferta.suprafata = suprafata;
    oferta.adresa = (char*)malloc((strlen(adresa) + 1) * sizeof(char));
    strcpy_s(oferta.adresa, strlen(adresa) + 1, adresa);
    oferta.pret = pret;
    return oferta;
}

void distruge_oferta(Oferta* oferta) {
    free(oferta->tip);
    free(oferta->adresa);
    oferta->tip = NULL;
    oferta->adresa = NULL;
}