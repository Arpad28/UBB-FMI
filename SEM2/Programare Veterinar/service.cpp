#include "service.h"
#include <algorithm>

std::vector<cabinet> Service::get_all() const {
    return repo.get_all();
}

std::vector<cabinet> Service::filt_specie(const std::string& specie) const {
    std::vector<cabinet> all = repo.get_all();
    std::vector<cabinet> rez;

    std::copy_if(all.begin(), all.end(), std::back_inserter(rez),[&specie](const cabinet& c) {
        std::string specie_animal = c.get_specie();
        int pozitie = specie_animal.find(specie);
        if (pozitie !=-1) {
            return true;
        }
        else {
            return false;
        }
    });

    return rez;
}

cabinet Service::cauta(const std::string& cod) const {
    auto all = repo.get_all();
    auto it = std::find_if(all.begin(), all.end(), [&cod](const cabinet& c) {
        return c.get_cod() == cod;
    });
    if (it != all.end()) {
        return *it;
    }
}