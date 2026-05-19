#include "service.h"
#include <algorithm>
std::vector<Masina> Service::sorteaza_model() const {
    auto lista=repo.get_all();
    std::sort(lista.begin(), lista.end(),[](const Masina& a,const Masina& b) {
        return a.get_model()<b.get_model();
    });
    return lista;
}

std::vector<Masina> Service::sorteaza_nrmatricol() const {
    auto lista=repo.get_all();
    std::sort(lista.begin(), lista.end(),[](const Masina& a, const Masina& b) {
        return a.get_nrmatricol()<b.get_nrmatricol();
    });
    return lista;
}
std::vector<Masina> Service::get_all() const {
    return repo.get_all();
}
