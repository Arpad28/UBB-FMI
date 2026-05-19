#pragma once
#include <string>

class Procesor {
private:
    std::string nume;
    int numarThreaduri;
    std::string socluProcesor;
    double pret;
public:
    Procesor(std::string nume, int threaduri, std::string soclu, double pret)
        : nume(nume), numarThreaduri(threaduri), socluProcesor(soclu), pret(pret) {}

    std::string getNume() const { return nume; }
    int getNumarThreaduri() const { return numarThreaduri; }
    std::string getSocluProcesor() const { return socluProcesor; }
    double getPret() const { return pret; }
};

class PlacaDeBaza {
private:
    std::string nume;
    std::string socluProcesor;
    double pret;
public:
    PlacaDeBaza(std::string nume, std::string soclu, double pret)
        : nume(nume), socluProcesor(soclu), pret(pret) {}

    std::string getNume() const { return nume; }
    std::string getSocluProcesor() const { return socluProcesor; }
    double getPret() const { return pret; }
};