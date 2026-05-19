#pragma once
#include <string>
class Masina {
private:
    int nrmatricol;
    std::string model;
    std::string culoare;
    int kmrulati;
public:
    Masina(int nrmatricol,std::string model,std::string culoare,int kmrulati);
    int get_nrmatricol() const;
    std::string get_model() const;
    std::string get_culoare() const;
    int get_kmrulati() const;

};