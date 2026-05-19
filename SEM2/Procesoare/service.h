#pragma once
#include "repo.h"

class Service {
private:
    RepoProcesoare& repoP;
    RepoPlaciDeBaza& repoB;
public:
    Service(RepoProcesoare& rp, RepoPlaciDeBaza& rb) : repoP(rp), repoB(rb) {}

    const std::vector<Procesor>& getProcesoare() const { return repoP.getAll(); }
    const std::vector<PlacaDeBaza>& getPlaciDeBaza() const { return repoB.getAll(); }

    void adaugaPlacaDeBaza(const std::string& nume, const std::string& soclu, double pret);

    std::vector<PlacaDeBaza> filtreazaPlaciDupaSoclu(const std::string& soclu);
};