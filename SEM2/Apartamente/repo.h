#pragma once
#include "domain.h"
#include <vector>
#include <string>

class Repo {
private:
    std::string nume_fisier;
    std::vector<Apartament> lista;
    void loadfromfile();
    void writetofile();
public:
    Repo(std::string nume_fisier);
    std::vector<Apartament> get_all() const;
    void sterge(std::string strada, double suprafata, int pret); // NOU
};