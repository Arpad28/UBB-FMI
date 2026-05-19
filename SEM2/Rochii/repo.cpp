#include "repo.h"
#include <fstream>
#include <sstream>
#include "exceptii.h"

Repo::Repo(std::string nume_fiser) : nume_fisier(nume_fiser) {
    loadfromfile();
}

void Repo::loadfromfile() {
    std::ifstream in(nume_fisier);
    if (!in.is_open()) {
        throw RepoException("Nu se poate deschide fisierul");
    }
    lista.clear();
    std::string linie;
    while (std::getline(in, linie)) {
        if (linie.empty()) continue;

        std::stringstream ss(linie);
        std::string token;

        std::getline(ss, token, ',');
        int cod = std::stoi(token);

        std::string nume, marime, disponibilitate;
        std::getline(ss, nume, ',');
        std::getline(ss, marime, ',');

        std::getline(ss, token, ',');
        int pret = std::stoi(token);

        std::getline(ss, disponibilitate, '\n'); // pana la finalul liniei
        Rochie roc(cod, nume, marime, pret, disponibilitate);
        lista.push_back(roc);
    }
    in.close();
}

void Repo::writetofile() {
    std::ofstream out(nume_fisier);
    if (!out.is_open()) {
        throw RepoException("Nu se poate deschide fisierul");
    }
    for (const auto& roc : lista) {
        out << roc.get_cod() << "," << roc.get_denumire() << ","
            << roc.get_marime() << "," << roc.get_pret() << ","
            << roc.get_disponibiliate() << '\n';
    }
    out.close();
}

std::vector<Rochie> Repo::get_all() const {
    return lista;
}

void Repo::modifica(const Rochie& rochie_noua) {
    for (auto& r : lista) {
        if (r.get_cod() == rochie_noua.get_cod()) {
            r = rochie_noua;
            break;
        }
    }
    writetofile();
}