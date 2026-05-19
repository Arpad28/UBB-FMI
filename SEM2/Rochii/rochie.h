#pragma once
#include <string>

class Rochie {
private:
    int cod;
    std::string denumire;
    std::string marime;
    int pret;
    std::string disponibilitate;
public:
    Rochie(int cod, std::string denumire, std::string marime, int pret, std::string disponibilitate);

    int get_cod() const;
    std::string get_denumire() const;
    std::string get_marime() const;
    int get_pret() const;
    std::string get_disponibiliate() const;

    void set_disponibilitate(std::string disponibilitat);
    ~Rochie() = default;
};