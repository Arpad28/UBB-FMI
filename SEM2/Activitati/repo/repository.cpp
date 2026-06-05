#include "repository.h"
#include "../domain/exceptii.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>

void MemoryRepo::adauga(const Activitate& a) {
    auto it = std::find_if(lista.begin(), lista.end(), [&a](const Activitate& act) {
        return act.get_id() == a.get_id();
    });
    if (it != lista.end()) throw RepoException("Activitatea cu acest ID exista deja!");
    lista.push_back(a);
}

void MemoryRepo::sterge(int id) {
    auto it = std::find_if(lista.begin(), lista.end(), [id](const Activitate& act) {
        return act.get_id() == id;
    });
    if (it == lista.end()) throw RepoException("Activitatea nu a fost gasita pentru stergere!");
    lista.erase(it);
}

void MemoryRepo::modifica(const Activitate& a) {
    auto it = std::find_if(lista.begin(), lista.end(), [&a](const Activitate& act) {
        return act.get_id() == a.get_id();
    });
    if (it == lista.end()) throw RepoException("Activitatea nu a fost gasita pentru modificare!");
    *it = a;
}

const Activitate& MemoryRepo::cauta(int id) const {
    auto it = std::find_if(lista.begin(), lista.end(), [id](const Activitate& act) {
        return act.get_id() == id;
    });
    if (it == lista.end()) throw RepoException("Activitatea cautata nu exista!");
    return *it;
}

std::vector<Activitate> MemoryRepo::get_all() const {
    return lista; // Se returneaza o copie a vectorului
}

// ================= FILE REPO =================
FileRepo::FileRepo(const std::string& nume_fisier) : nume_fisier(nume_fisier) {
    loadFromFile();
}

void FileRepo::loadFromFile() {
    std::ifstream in(nume_fisier);
    if (!in.is_open()) return;

    lista.clear();
    std::string linie;

    while (std::getline(in, linie)) {
        if (linie.empty()) continue;
        std::stringstream ss(linie);
        std::string token;

        std::getline(ss, token, ','); int id = std::stoi(token);
        std::string titlu, descriere, tip;
        std::getline(ss, titlu, ',');
        std::getline(ss, descriere, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, token, ','); int durata = std::stoi(token);

        Activitate act(id, titlu, descriere, tip, durata);
        MemoryRepo::adauga(act);
    }
    in.close();
}

void FileRepo::writeToFile() {
    std::ofstream out(nume_fisier);
    if (!out.is_open()) throw RepoException("Eroare la deschiderea fisierului pentru scriere!");
    for (const auto& a : lista) {
        out << a.get_id() << "," << a.get_titlu() << "," << a.get_descriere() << ","
            << a.get_tip() << "," << a.get_durata() << "\n";
    }
    out.close();
}

void FileRepo::adauga(const Activitate& a) { MemoryRepo::adauga(a); writeToFile(); }
void FileRepo::sterge(int id) { MemoryRepo::sterge(id); writeToFile(); }
void FileRepo::modifica(const Activitate& a) { MemoryRepo::modifica(a); writeToFile(); }



MapRepo::MapRepo(double prob) : probabilitate{prob} {}

void MapRepo::random_fail() const {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_real_distribution<> dist(0.0, 1.0);
    if (dist(mt) < probabilitate) {
        throw RepoException("Eroare aleatoare MapRepo (Probabilitate: " + std::to_string(probabilitate) + ") !");
    }
}

void MapRepo::adauga(const Activitate& a) {
    random_fail();
    if (dict.find(a.get_id()) != dict.end()) throw RepoException("Activitatea cu acest ID exista deja!");
    dict[a.get_id()] = a;
}

void MapRepo::sterge(int id) {
    random_fail();
    if (dict.find(id) == dict.end()) throw RepoException("Activitatea nu a fost gasita pentru stergere!");
    dict.erase(id);
}

void MapRepo::modifica(const Activitate& a) {
    random_fail();
    if (dict.find(a.get_id()) == dict.end()) throw RepoException("Activitatea nu a fost gasita pentru modificare!");
    dict[a.get_id()] = a;
}

const Activitate& MapRepo::cauta(int id) const {
    random_fail();
    auto it = dict.find(id);
    if (it == dict.end()) throw RepoException("Activitatea cautata nu exista!");
    return it->second;
}

std::vector<Activitate> MapRepo::get_all() const {
    random_fail();
    std::vector<Activitate> v;
    for (const auto& pereche : dict) {
        v.push_back(pereche.second); // Punem doar activitatile, nu si cheile (id-urile)
    }
    return v;}