#pragma once
#include <string>
class Apartament {
private:
    double suprafata;
    std::string strada;
    int pret;
public:
    Apartament(double suprafata, std::string strada, int pret);
    double get_suprafata() const;
    std::string get_strada() const;
    int get_pret() const;
};