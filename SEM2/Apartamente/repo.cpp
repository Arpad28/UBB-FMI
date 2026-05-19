#include "repo.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Repo::Repo(std::string nume_fisier):nume_fisier(nume_fisier) {
    loadfromfile();
}

void Repo::loadfromfile() {
    std::ifstream in(nume_fisier);
    std::string linie;
    while (std::getline(in,linie)) {
        if (linie.empty()) continue;
        std::stringstream ss(linie);
        std::string token,strada;
        std::getline(ss,token,',');
        double suprafata=stod(token);
        std::getline(ss,strada,',');
        std::getline(ss,token,'\n');
        int pret=std::stoi(token);
        Apartament a(suprafata,strada,pret);
        lista.push_back(a);
    }
    in.close();
}

void Repo::writetofile() {
    std::ofstream out(nume_fisier);
    for (auto& a:lista)
        out<<a.get_suprafata()<<","<<a.get_strada()<<","<<a.get_pret()<<'\n';
    out.close();
}

std::vector<Apartament> Repo::get_all() const {
    return lista;
}

void Repo::sterge(std::string strada, double suprafata, int pret) {
    auto it = std::find_if(lista.begin(), lista.end(), [&](const Apartament& a) {
        return a.get_strada() == strada && a.get_suprafata() == suprafata && a.get_pret() == pret;
    });
    if (it != lista.end()) {
        lista.erase(it);
        writetofile();
    }
}