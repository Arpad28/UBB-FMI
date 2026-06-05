#pragma once
#include <vector>
#include "domain.h"

class Repo {
private:
    std::string  nume_fisier;
    std::vector<cabinet>lista;
    void loadfromfile();
public:
    Repo(std::string nume_fiser);
    std::vector<cabinet> get_all();
};