#include "service.h"
#include <algorithm>

std::vector<Apartament> Service::filtrare_suprafata(double a, double b) const {
    auto all = repo.get_all();
    std::vector<Apartament> rez;
    std::copy_if(all.begin(), all.end(), std::back_inserter(rez),[&a,&b](const Apartament& p) {
        return a<=p.get_suprafata() && b>=p.get_suprafata();
    });
    return rez; // ADAUGAT RETURN (lipsea în codul tău)
}

std::vector<Apartament> Service::filtrare_pret(int a, int b) const {
    auto all = repo.get_all();
    std::vector<Apartament> rez;
    std::copy_if(all.begin(), all.end(), std::back_inserter(rez),[&a,&b](const Apartament& p) {
        return a<=p.get_pret() && b>=p.get_pret();
    });
    return rez; // ADAUGAT RETURN (lipsea în codul tău)
}

std::vector<Apartament> Service::get_all() const {
    return repo.get_all();
}

void Service::sterge(std::string strada, double suprafata, int pret) {
    repo.sterge(strada, suprafata, pret);
}