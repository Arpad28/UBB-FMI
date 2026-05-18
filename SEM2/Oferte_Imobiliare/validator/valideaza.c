#include "valideaza.h"
#include <string.h>

bool e_valid(char tip[],float suprafata,char adresa[],float pret) {
    char tipuri[3][15]={"casa","apartament","teren"};
    if (strcmp(adresa,"")==0)
        return false;
    bool ok=false;
    for (int i=0;i<3;++i)
        if (strcmp(tip,tipuri[i])==0)
            ok=true;
    if (!ok)
        return false;
    if (pret<=0 || suprafata<=0)
        return false;
    return true;
}

int id_valid(Repo *r,int id) {
    for (int i = 0; i < size(r->oferta); ++i) {
        Oferta* o = (Oferta*)get_element(r->oferta, i);
        if (o->id == id)
            return i;
    }
    return -1;
}