// --- lista_activitati.h ---
#pragma once
#include "activitate.h"
#include <vector>

class ListaActivitati {
private:
    std::vector<Activitate> lista_curenta;
public:
    void goleste();
    void adauga(const Activitate& a);
    void genereaza_aleator(int numar, const std::vector<Activitate>& oferte_disponibile);
    const std::vector<Activitate>& get_toate() const;
    int size() const;
};