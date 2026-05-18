#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../service/service.h"
#include "../validator/valideaza.h"

void teste_service() {
    Repo r;
    init_repo(&r);
    Service s;
    init_service(&s,&r);
    adauga_oferta(&s,1,"apartament",60,"Cluj",50000); // index 0 -> ID 1
    assert(get_lungime(&r)==1);
    assert(adauga_oferta(&s,2,"casa",60,"Cluj",50000)==1); // index 1 -> ID 2
    assert(adauga_oferta(&s,2,"casaaa",60,"Cluj",50000)==0);
    assert(get_lungime(&r)==2);
    adauga_oferta(&s,3,"apartament",60,"Cluj",50000); // index 2 -> ID 3
    assert(get_lungime(&r)==3);
    assert(r.oferta->capacitate==4);
    sterge_oferta_repo(&r,1);
    Oferta* o = get_oferte(&r);
    assert(o[1].id==3);
    free(o);
    assert(get_lungime(&r)==2);
    assert(sterge_oferta(&s, 3) == 1);
    assert(r.oferta->capacitate==2);
    assert(e_valid("casa",60,"cluj",30000)==1);
    assert(e_valid("casa",60,"",30000)==0);
    assert(e_valid("casaa",60,"cluj",30000)==0);
    assert(e_valid("casa",-60,"cluj",30000)==0);
    assert(e_valid("casa",60,"cluj",-30000)==0);
    assert(actualizare_oferta(&s,1,"casa",60,"Cluj",50000)==1);
    assert(actualizare_oferta(&s,1,"casa",-60,"Cluj",50000)==0);
    assert(actualizare_oferta(&s,4,"casa",60,"Cluj",50000)==0);
    destroy(&r);
}
void teste_busniess() {
    Repo r;
    init_repo(&r);
    Service s;
    init_service(&s,&r);
    adauga_oferta(&s,1,"apartament",60,"Cluj",30000);
    adauga_oferta(&s,2,"casa",60,"Cluj",20000);
    adauga_oferta(&s,3,"apartament",60,"Cluj",50000);
    assert(sortare(&s,5)==NULL);
    Oferta *test=sortare(&s,1);
    assert(test[1].pret==30000);
    assert(test[0].pret==20000);
    free(test);
    test=sortare(&s,2);
    assert(test[1].pret==30000);
    assert(test[0].pret==50000);
    free(test);
    test=sortare(&s,3);
    assert(strcmp(test[0].tip,"apartament")==0);
    assert(strcmp(test[2].tip,"casa")==0);
    free(test);
    test=sortare(&s,4);
    assert(strcmp(test[2].tip,"apartament")==0);
    assert(strcmp(test[0].tip,"casa")==0);
    free(test);
    int k;
    test=filtrare(&s,1,0,&k);
    assert(k==1);
    free(test);
    test=filtrare(&s,2,0,&k);
    assert(k==2);
    free(test);
    adauga_oferta(&s,2,"teren",600,"Cluj",10000);
    test=filtrare(&s,3,0,&k);
    assert(k==1);
    free(test);
    test=filtrare(&s,4,30000,&k);
    assert(k==1);
    free(test);
    test=filtrare(&s,5,60,&k);
    assert(k==3);
    free(test);
    assert(sterge_oferta(&s,5)==0);
    assert(sterge_oferta(&s,2)==1);
    destroy(&r);

}
void ruleaza_teste() {
    teste_service();
    teste_busniess();
    printf("Au trecut toate testele cu succes\n\n");
}