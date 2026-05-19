#pragma once
#include "repo.h"

class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo) : repo(repo) {}
    std::vector<Apartament> filtrare_suprafata(double a, double b) const;
    std::vector<Apartament> filtrare_pret(int a, int b) const;
    std::vector<Apartament> get_all() const;
    void sterge(std::string strada, double suprafata, int pret);
};