// --- ui.h ---
#pragma once
#include "../service/service.h"

class UI {
private:
    Service& srv;
    void meniu();
    void adauga();
    void afiseaza(const std::vector<Activitate>& lista);
    void sterge();
    void modifica();
    void cauta();
    void filtreaza();
    void sorteaza();
    void submeniu_lista();
    void raport_tipuri_ui();
    void undo(); // Comanda NOUA

public:
    UI(Service& s);
    void run();
};