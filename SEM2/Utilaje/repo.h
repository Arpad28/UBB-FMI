#pragma once
#include <vector>
#include "domain.h"

/*Defineste clasa repo care are acces la utilajele noastre si functiile acestuia
 */
class Repo {
private:
    std::string nume_fisier;
    std::vector<Utilaj> lista;
    void loadFromFile();
    void saveToFile();
public:
    Repo(std::string nume_fisier);
    std::vector<Utilaj> get_all() const;
    Utilaj cauta(int id) const;
    void sterge(int id);
    void update(const Utilaj& u);
};