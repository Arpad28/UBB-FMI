// --- lista_activitati.cpp ---
#include "lista_activitati.h"
#include <random>

void ListaActivitati::goleste() {
    lista_curenta.clear();
}

void ListaActivitati::adauga(const Activitate& a) {
    lista_curenta.push_back(a);
}

void ListaActivitati::genereaza_aleator(int numar, const std::vector<Activitate>& oferte_disponibile) {
    if (oferte_disponibile.empty()) return;

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, (int)oferte_disponibile.size() - 1);

    for (int i = 0; i < numar; i++) {
        int rndNr = dist(mt);
        lista_curenta.push_back(oferte_disponibile[rndNr]);
    }
}

const std::vector<Activitate>& ListaActivitati::get_toate() const {
    return lista_curenta;
}

int ListaActivitati::size() const {
    return (int)lista_curenta.size();}