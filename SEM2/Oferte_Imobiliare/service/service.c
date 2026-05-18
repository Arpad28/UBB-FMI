#include "service.h"

#include <stdlib.h>
#include <string.h>
#include "../domain/oferta.h"
#include "../validator/valideaza.h"
void init_service(Service* s,Repo* r) {
    s->repo = r;
}

int adauga_oferta(Service* s,int id,char tip[],float suprafata,char adresa[],float pret) {
    if (e_valid(tip,suprafata,adresa,pret)) {
        Oferta o=creeaza_oferta(id,tip,suprafata,adresa,pret);
        adauga_oferta_repo(s->repo,o);
        return 1;
    }
    return 0;
}

int actualizare_oferta(Service* s,int id,char tip[],float suprafata,char adresa[],float pret) {
    int ind = id_valid(s->repo, id);

    if (ind != -1 && e_valid(tip, suprafata, adresa, pret)) {
        Oferta* nou = malloc(sizeof(Oferta));
        *nou = creeaza_oferta(id, tip, suprafata, adresa, pret);
        Oferta* vechi = (Oferta*)set_element(s->repo->oferta, ind, nou);
        distruge_oferta(vechi);
        free(vechi);

        return 1;
    }
    return 0;
}
int sterge_oferta(Service*s,int id) {
    int ind=id_valid(s->repo,id);
    if (ind!=-1) {
        sterge_oferta_repo(s->repo,ind);
        return 1;
    }
    return 0;
}
int cmp_pret_cresc(Oferta a, Oferta b) {
    return a.pret > b.pret;
}

int cmp_pret_desc(Oferta a, Oferta b) {
    return a.pret < b.pret;
}

int cmp_tip_cresc(Oferta a, Oferta b) {
    return strcmp(a.tip, b.tip) > 0;
}

int cmp_tip_desc(Oferta a, Oferta b) {
    return strcmp(a.tip, b.tip) < 0;
}

Oferta* sortare(Service* s, int criteriu) {
    if (criteriu == 1)
        return sortare_generica(s, cmp_pret_cresc);
    if (criteriu == 2)
        return sortare_generica(s, cmp_pret_desc);
    if (criteriu == 3)
        return sortare_generica(s, cmp_tip_cresc);
    if (criteriu == 4)
        return sortare_generica(s, cmp_tip_desc);
    return NULL;
}

Oferta* sortare_generica(Service* s, int (*cmp)(Oferta, Oferta)) {
    int n = get_lungime(s->repo);

    Oferta* sortat = malloc(sizeof(Oferta) * n);

    for (int i = 0; i < n; i++) {
        Oferta* o = (Oferta*)get_element(s->repo->oferta, i);
        sortat[i] = *o;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cmp(sortat[i], sortat[j])) {
                Oferta aux = sortat[i];
                sortat[i] = sortat[j];
                sortat[j] = aux;
            }
        }
    }

    return sortat;
}
Oferta *filtrare(Service* s,int filtru,float numar,int *dim) {
    int n = get_lungime(s->repo);
    int k = 0;
    Oferta *filtrat = malloc(sizeof(Oferta) * n);

    for (int i = 0; i < n; ++i) {
        Oferta* o = (Oferta*)get_element(s->repo->oferta, i);

        if (filtru==1 && strcmp(o->tip,"casa")==0)
            filtrat[k++] = *o;

        else if (filtru==2 && strcmp(o->tip,"apartament")==0)
            filtrat[k++] = *o;

        else if (filtru==3 && strcmp(o->tip,"teren")==0)
            filtrat[k++] = *o;

        else if (filtru==4 && o->pret == numar)
            filtrat[k++] = *o;

        else if (filtru==5 && o->suprafata == numar)
            filtrat[k++] = *o;
    }

    *dim = k;
    return filtrat;
}