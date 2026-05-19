#include "service.h"
#include <algorithm>
#include "exceptii.h"

std::vector<Rochie> Service::get_all() const {
    return repo.get_all();
}

void Service::inchiriaza(int cod) {
    auto lista = repo.get_all();
    auto it = std::find_if(lista.begin(), lista.end(), [cod](const Rochie& r) {
        return r.get_cod() == cod;
    });

    if (it == lista.end())
        throw RepoException("Nu exista rochie cu acest ID");

    if (it->get_disponibiliate() == "True") {
        Rochie rochie_modificata = *it;
        rochie_modificata.set_disponibilitate("False");
        repo.modifica(rochie_modificata);
    } else {
        throw RepoException("Rochia este indisponibila (deja inchiriata).");
    }
}

std::vector<Rochie> Service::sortare_marime() const {
    auto lista = repo.get_all();
    std::sort(lista.begin(), lista.end(), [](const Rochie& r1, const Rochie& r2) {
        return r1.get_marime() > r2.get_marime();
    });
    return lista;
}

std::vector<Rochie> Service::sortare_pret() const {
    auto lista = repo.get_all();
    std::sort(lista.begin(), lista.end(), [](const Rochie& r1, const Rochie& r2) {
        return r1.get_pret() < r2.get_pret();
    });
    return lista;
}