#pragma once
#include <vector>
#include "domain.h"

class Repo {
private:
    std::string nume_fisier;
    std::vector<Tractor> lista;
    void loadFromFile();
    void saveToFile();
public:
    Repo(std::string nume_fisier);
    std::vector<Tractor> get_all() const;
    void addTractor(const Tractor& t);
    void updateTractor(const Tractor& t);
};