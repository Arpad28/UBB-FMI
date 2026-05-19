#include "domain.h"

Apartament::Apartament(double suprafata, std::string strada, int pret):suprafata(suprafata),strada(strada),pret(pret) {}

double Apartament::get_suprafata() const {
    return suprafata;
}
std::string Apartament::get_strada() const {
    return strada;
}

int Apartament::get_pret() const {
    return pret;
}
