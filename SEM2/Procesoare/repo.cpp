#include "repo.h"
#include <fstream>
#include <sstream>

RepoProcesoare::RepoProcesoare(std::string filename) : filename(filename) {
    loadFromFile();
}

void RepoProcesoare::loadFromFile() {
    std::ifstream f(filename);
    if (!f.is_open()) return;
    std::string linie;
    while (std::getline(f, linie)) {
        if (linie.empty()) continue;
        std::stringstream ss(linie);
        std::string nume, soclu, thStr, pretStr;
        std::getline(ss, nume, ',');
        std::getline(ss, thStr, ',');
        std::getline(ss, soclu, ',');
        std::getline(ss, pretStr, ',');
        procesoare.push_back(Procesor(nume, std::stoi(thStr), soclu, std::stod(pretStr)));
    }
    f.close();
}

RepoPlaciDeBaza::RepoPlaciDeBaza(std::string filename) : filename(filename) {
    loadFromFile();
}

void RepoPlaciDeBaza::loadFromFile() {
    std::ifstream f(filename);
    if (!f.is_open()) return;
    std::string linie;
    while (std::getline(f, linie)) {
        if (linie.empty()) continue;
        std::stringstream ss(linie);
        std::string nume, soclu, pretStr;
        std::getline(ss, nume, ',');
        std::getline(ss, soclu, ',');
        std::getline(ss, pretStr, ',');
        placi.push_back(PlacaDeBaza(nume, soclu, std::stod(pretStr)));
    }
    f.close();
}

void RepoPlaciDeBaza::saveToFile() {
    std::ofstream f(filename);
    for (const auto& p : placi) {
        f << p.getNume() << "," << p.getSocluProcesor() << "," << p.getPret() << "\n";
    }
    f.close();
}

void RepoPlaciDeBaza::adauga(const PlacaDeBaza& p) {
    placi.push_back(p);
    saveToFile();
}