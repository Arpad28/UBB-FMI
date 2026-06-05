#pragma once
#include "repo.h"
class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo) : repo(repo) {}
    std::vector<cabinet> get_all() const;
    std::vector<cabinet> filt_specie(const std::string& specie) const;
    cabinet cauta(const std::string& cod) const;
};