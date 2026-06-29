#pragma once
#include <string>

class Tractor {
private:
    int id;
    std::string denumire;
    std::string tip;
    int numarRoti;
public:
    Tractor(int id, std::string denumire, std::string tip, int numarRoti);

    int getId() const;
    std::string getDenumire() const;
    std::string getTip() const;
    int getNumarRoti() const;

    void setNumarRoti(int roti);
};