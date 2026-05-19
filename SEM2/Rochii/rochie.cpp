#include "rochie.h"

Rochie::Rochie(int cod, std::string denumire, std::string marime, int pret, std::string disponibilitate)
    : cod(cod), denumire(denumire), marime(marime), pret(pret), disponibilitate(disponibilitate) {}

int Rochie::get_cod() const { return cod; }
std::string Rochie::get_denumire() const { return denumire; }
std::string Rochie::get_marime() const { return marime; }
int Rochie::get_pret() const { return pret; }
std::string Rochie::get_disponibiliate() const { return disponibilitate; }

void Rochie::set_disponibilitate(std::string disponibilitat) {
    this->disponibilitate = disponibilitat;
}