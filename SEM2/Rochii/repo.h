#pragma once
#include "rochie.h"
#include <vector>
#include <string>

class Repo {
private:
    std::vector<Rochie> lista;
    std::string nume_fisier;

    void writetofile();
    void loadfromfile();
public:
    Repo(std::string nume_fiser);
    std::vector<Rochie> get_all() const;

    void modifica(const Rochie& rochie_noua);
};