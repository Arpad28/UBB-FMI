#include "repo.h"
#include <fstream>
#include <sstream>

Repo::Repo(std::string nume_fisier):nume_fisier(nume_fisier) {
    loadfromfile();
}

void Repo::loadfromfile() {
    lista.clear();
    std::ifstream in(nume_fisier);
    std::string linie;
    while (std::getline(in, linie)) {
        std::stringstream ss(linie);
        std::string token;
        int nrmatricol,kmrulati;
        std::string model,culoare;
        std::getline(ss, token, ',');
        nrmatricol = std::stoi(token);
        std::getline(ss, model, ',');
        std::getline(ss,culoare, ',');
        std::getline(ss, token, '\n');
        kmrulati = std::stoi(token);
        Masina m(nrmatricol,model,culoare,kmrulati);
        lista.push_back(m);
    }
    in.close();
}

void Repo::writetofile() const {
    std::ofstream out(nume_fisier);
    for (auto& m:lista)
        out<<m.get_nrmatricol()<<','<<m.get_model()<<','<<m.get_culoare()<<','<<m.get_kmrulati()<<'\n';
    out.close();
}
std::vector<Masina> Repo::get_all() const {
    return lista;
}
