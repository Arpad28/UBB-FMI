#pragma once
#include "domain.h"
#include <vector>
#include <string>

class RepoProcesoare {
private:
    std::vector<Procesor> procesoare;
    std::string filename;
    void loadFromFile();
public:
    RepoProcesoare(std::string filename);
    const std::vector<Procesor>& getAll() const { return procesoare; }
};

class RepoPlaciDeBaza {
private:
    std::vector<PlacaDeBaza> placi;
    std::string filename;
    void loadFromFile();
    void saveToFile();
public:
    RepoPlaciDeBaza(std::string filename);
    void adauga(const PlacaDeBaza& p);
    const std::vector<PlacaDeBaza>& getAll() const { return placi; }
};