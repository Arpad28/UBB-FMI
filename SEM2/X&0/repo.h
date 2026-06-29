#pragma once
#include <vector>
#include "domain.h"

class Repo {
private:
    std::string nume_fisier;
    std::vector<Game> lista;
    void loadFromFile();
    void saveToFile();
public:
    Repo(std::string nume_fisier);
    std::vector<Game> get_all() const;
    void addGame(const Game& g);
    void updateGame(const Game& g);
};