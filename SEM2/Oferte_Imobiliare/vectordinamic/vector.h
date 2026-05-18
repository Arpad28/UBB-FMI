#ifndef LAB2_4_VECTOR_H
#define LAB2_4_VECTOR_H

#include "../domain/oferta.h"

typedef void *TElem;

typedef void (*destroyfunction)(TElem);

typedef TElem (*copyfunction)(TElem);

typedef struct vector {
    TElem *elements;
    int capacitate;
    int lungime;
    destroyfunction destroy;
}mylist;

mylist *creeaza_lista(destroyfunction fn);

void add(mylist *lista,TElem e);

TElem get_element(mylist *lista,int poz);

TElem set_element(mylist *lista,int poz,TElem e);

TElem sterge_element(mylist *lista,int poz);

mylist *copy_list(mylist *lista,copyfunction copyfn);

void destroyList(mylist *lista);

int size(mylist *lista);
#endif