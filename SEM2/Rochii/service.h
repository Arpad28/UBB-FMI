#pragma once
#include <vector>
#include "rochie.h"
#include "repo.h"

class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo) : repo(repo) {}
    std::vector<Rochie> get_all() const;
    void inchiriaza(int cod);
    std::vector<Rochie> sortare_marime() const;
    std::vector<Rochie> sortare_pret() const;
};