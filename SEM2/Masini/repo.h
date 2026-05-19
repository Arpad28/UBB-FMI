#pragma once
#include "domain.h"
#include <vector>
class Repo {
private:
    std::string nume_fisier;
    std::vector<Masina>lista;
    void loadfromfile();
    void writetofile() const;
public:
    Repo(std::string nume_fisier);
    std::vector<Masina>get_all() const;
};