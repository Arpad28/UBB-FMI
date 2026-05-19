#include "domain.h"
#include <iostream>

Masina::Masina(int nrmatricol,std::string model,std::string culoare,int kmrulati)
    :nrmatricol(nrmatricol),model(model),culoare(culoare),kmrulati(kmrulati){}

int Masina::get_nrmatricol() const {
    return nrmatricol;
}
std::string Masina::get_model() const {
    return model;
}
std::string Masina::get_culoare() const {
    return culoare;
}
int Masina::get_kmrulati() const {
    return kmrulati;
}