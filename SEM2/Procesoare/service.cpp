#include "service.h"
#include <algorithm>
#include <stdexcept>

void Service::adaugaPlacaDeBaza(const std::string& nume, const std::string& soclu, double pret) {
    if (nume.empty() || soclu.empty() || pret <= 0) {
        throw std::runtime_error("Date invalide!");
    }

    const auto& placi = repoB.getAll();
    auto it = std::find_if(placi.begin(), placi.end(), [&nume](const PlacaDeBaza& p) {
        return p.getNume() == nume;
    });

    if (it != placi.end()) {
        throw std::runtime_error("Aceasta placa de baza exista deja!");
    }

    repoB.adauga(PlacaDeBaza(nume, soclu, pret));
}

std::vector<PlacaDeBaza> Service::filtreazaPlaciDupaSoclu(const std::string& soclu) {
    const auto& toatePlacile = repoB.getAll();
    std::vector<PlacaDeBaza> rezultat;
    std::copy_if(toatePlacile.begin(), toatePlacile.end(), std::back_inserter(rezultat), [&soclu](const PlacaDeBaza& p) {
        return p.getSocluProcesor() == soclu;
    });
    std::sort(rezultat.begin(), rezultat.end(), [](const PlacaDeBaza& a, const PlacaDeBaza& b) {
        return a.getPret() < b.getPret();
    });
    return rezultat;
}