#include "repo.h"
#include <fstream>
#include <iostream>
#include <sstream>

Repo::Repo(std::string nume_fiser):nume_fisier(nume_fiser) {
    loadfromfile();
}

void Repo::loadfromfile() {
    std::ifstream in(nume_fisier);
    std::string linie;
    while (std::getline(in,linie)) {
        std::stringstream ss(linie);
        std::string cod,nume,specie,tip;
        std::string token;
        std::getline(ss, cod, ',');
        std::getline(ss, nume, ',');
        std::getline(ss, specie, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, token, '\n');
        int pret=std::stoi(token);
        cabinet cab(cod,nume,specie,tip,pret);
        lista.push_back(cab);
    }
    in.close();
}

std::vector<cabinet> Repo::get_all() {
    return lista;
}