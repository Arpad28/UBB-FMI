#include <stdlib.h>
#include "repo.h"

void destroy_oferta_wrapper(TElem e) {
    Oferta* o = (Oferta*)e;
    distruge_oferta(o);
    free(o);
}

void init_repo(Repo* r) {
    r->oferta = creeaza_lista(destroy_oferta_wrapper);
}

void destroy(Repo* r) {
    destroyList(r->oferta);
    free(r->oferta);
}

void adauga_oferta_repo(Repo* r, Oferta o) {
    Oferta* copie = malloc(sizeof(Oferta));
    *copie = o;
    add(r->oferta, copie);
}

int get_lungime(Repo* r) {
    return size(r->oferta);
}

Oferta* get_oferte(Repo* r) {
    int n = size(r->oferta);
    Oferta* v = malloc(sizeof(Oferta) * n);
    for (int i = 0; i < n; i++) {
        Oferta* o = (Oferta*)get_element(r->oferta, i);
        v[i] = *o;
    }
    return v;
}

void sterge_oferta_repo(Repo* r, int poz) {
    TElem e = sterge_element(r->oferta, poz);
    destroy_oferta_wrapper(e);
}