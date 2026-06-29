#include "domain.h"

Tractor::Tractor(int id, std::string denumire, std::string tip, int numarRoti)
    : id(id), denumire(denumire), tip(tip), numarRoti(numarRoti) {}

int Tractor::getId() const { return id; }
std::string Tractor::getDenumire() const { return denumire; }
std::string Tractor::getTip() const { return tip; }
int Tractor::getNumarRoti() const { return numarRoti; }

void Tractor::setNumarRoti(int roti) { numarRoti = roti; }