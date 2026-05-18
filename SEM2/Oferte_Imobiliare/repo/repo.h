#ifndef REPO_H
#define REPO_H

#include "../domain/oferta.h"
#include "../vectordinamic/vector.h"

typedef struct {
    mylist* oferta;
} Repo;

void init_repo(Repo* r);
void destroy(Repo* r);

void adauga_oferta_repo(Repo* r, Oferta o);
int get_lungime(Repo* r);
Oferta* get_oferte(Repo* r);
void sterge_oferta_repo(Repo* r, int poz);

#endif