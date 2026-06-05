#include "domain.h"
#include <iostream>

cabinet::cabinet(std::string cod,std::string nume,std::string specie,std::string tip,int pret):cod(cod),nume(nume),specie(specie),tip(tip),pret(pret){}

std::string cabinet::get_cod() const {
    return cod;
}
std::string cabinet::get_nume() const {
    return nume;
}
std::string cabinet::get_specie() const {
    return specie;
}
std::string cabinet::get_tip() const {
    return tip;
}
int cabinet::get_pret() const {
    return pret;
}