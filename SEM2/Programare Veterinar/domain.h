#pragma once
#include <string>
class cabinet {
private:
    std::string cod;
    std::string nume;
    std::string specie;
    std::string tip;
    int pret;
public:
    cabinet(std::string cod,std::string nume,std::string specie,std::string tip,int pret);
    std::string get_cod() const;
    std::string get_nume() const;
    std::string get_specie() const;
    std::string get_tip() const;
    int get_pret() const;
};