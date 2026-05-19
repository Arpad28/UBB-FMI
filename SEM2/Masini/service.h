#pragma once
#include "repo.h"

class Service {
private:
    Repo& repo;
    public:
    Service(Repo& repo) : repo(repo) {}
    std::vector<Masina> sorteaza_model() const;
    std::vector<Masina> sorteaza_nrmatricol() const;
    std::vector<Masina> get_all() const;
};