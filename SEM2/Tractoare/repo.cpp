#include "repo.h"
#include <fstream>
#include <sstream>

Repo::Repo(std::string nume_fisier) : nume_fisier(nume_fisier) {
    loadFromFile();
}

void Repo::loadFromFile() {
    std::ifstream in(nume_fisier);
    std::string linie;
    lista.clear();
    while (std::getline(in, linie)) {
        if (linie.empty()) continue;
        std::stringstream ss(linie);
        std::string s_id, denumire, tip, s_roti;
        
        std::getline(ss, s_id, ',');
        std::getline(ss, denumire, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, s_roti, '\n');
        
        Tractor t(std::stoi(s_id), denumire, tip, std::stoi(s_roti));
        lista.push_back(t);
    }
    in.close();
}

void Repo::saveToFile() {
    std::ofstream out(nume_fisier);
    for (const auto& t : lista) {
        out << t.getId() << "," 
            << t.getDenumire() << "," 
            << t.getTip() << "," 
            << t.getNumarRoti() << "\n";
    }
    out.close();
}

std::vector<Tractor> Repo::get_all() const { return lista; }

void Repo::addTractor(const Tractor& t) {
    lista.push_back(t);
    saveToFile();
}

void Repo::updateTractor(const Tractor& modified) {
    for (auto& t : lista) {
        if (t.getId() == modified.getId()) {
            t.setNumarRoti(modified.getNumarRoti());
            break;
        }
    }
    saveToFile();
}