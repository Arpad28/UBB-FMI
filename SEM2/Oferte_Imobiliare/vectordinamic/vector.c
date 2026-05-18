#include "./vector.h"

#include <stdlib.h>

mylist *creeaza_lista(destroyfunction fn) {
    mylist *lista=malloc(sizeof(mylist));
    lista->capacitate=2;
    lista->lungime=0;
    lista->destroy=fn;
    lista->elements=malloc(sizeof(TElem)*lista->capacitate);
    return lista;
}

void add(mylist *lista,TElem e) {
    if (lista->lungime>=0.8*lista->capacitate) {
        TElem *new_element=malloc(sizeof(TElem)*lista->capacitate*2);
        for (int i=0;i<lista->lungime;++i)
            new_element[i]=lista->elements[i];
        free(lista->elements);
        lista->elements=new_element;
        lista->capacitate=lista->capacitate*2;
    }
    lista->elements[lista->lungime++]=e;
}

TElem get_element(mylist *lista,int poz) {
    return lista->elements[poz];
}

TElem set_element(mylist *lista,int poz,TElem e) {
    TElem element_vechi=lista->elements[poz];
    lista->elements[poz]=e;
    return element_vechi;
}

TElem sterge_element(mylist *lista,int poz) {
    TElem element_vechi=lista->elements[poz];
    for (int i=poz;i<lista->lungime;++i)
        lista->elements[i]=lista->elements[i+1];
    lista->lungime--;
    if (lista->capacitate>1 && lista->lungime<0.8*lista->capacitate/2) {
        TElem *new_element=malloc(sizeof(TElem)*lista->capacitate/2);
        for (int i=0;i<lista->lungime;++i)
            new_element[i]=lista->elements[i];
        free(lista->elements);
        lista->elements=new_element;
        lista->capacitate=lista->capacitate/2;
    }
    return element_vechi;
}

// mylist *copy_list(mylist *lista,copyfunction copyfn) {
//     de facut
// }

void destroyList(mylist *lista) {
    for (int i=0;i<lista->lungime;++i) {
        TElem element=get_element(lista,i);
        lista->destroy(element);
    }
    free(lista->elements);
}

int size(mylist *lista) {
    return lista->lungime;
}