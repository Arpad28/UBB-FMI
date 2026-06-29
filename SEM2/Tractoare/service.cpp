#include "service.h"
#include <algorithm>
#include <stdexcept>

std::vector<Tractor> Service::get_all_sorted() const {
    std::vector<Tractor> all = repo.get_all();
    std::sort(all.begin(), all.end(), [](const Tractor& a, const Tractor& b) {
        return a.getDenumire() < b.getDenumire();
    });
    return all;
}

std::map<std::string, int> Service::get_tip_counts() const {
    std::map<std::string, int> counts;
    for (const auto& t : repo.get_all()) {
        counts[t.getTip()]++;
    }
    return counts;
}

std::vector<std::string> Service::get_distinct_types() const {
    std::set<std::string> types;
    for (const auto& t : repo.get_all()) types.insert(t.getTip());
    return std::vector<std::string>(types.begin(), types.end());
}

Tractor Service::cauta(int id) const {
    auto all = repo.get_all();
    auto it = std::find_if(all.begin(), all.end(), [id](const Tractor& t) {
        return t.getId() == id;
    });
    if (it != all.end()) return *it;
    throw std::runtime_error("Tractor inexistent!");
}

void Service::addTractor(int id, const std::string& denumire, const std::string& tip, int numarRoti) {
    std::string erori = "";
    
    if (denumire.empty()) erori += "Denumirea nu poate fi vida!\n";
    if (tip.empty()) erori += "Tipul nu poate fi vid!\n";
    if (numarRoti < 2 || numarRoti > 16 || numarRoti % 2 != 0) 
        erori += "Numarul de roti trebuie sa fie par, intre 2 si 16!\n";
    
    for (const auto& t : repo.get_all()) {
        if (t.getId() == id) {
            erori += "Exista deja un tractor cu acest ID!\n";
            break;
        }
    }
    
    if (!erori.empty()) throw std::invalid_argument(erori);

    repo.addTractor(Tractor(id, denumire, tip, numarRoti));
}

void Service::decrementWheels(int id) {
    Tractor t = cauta(id);
    if (t.getNumarRoti() >= 2) {
        t.setNumarRoti(t.getNumarRoti() - 2);
        repo.updateTractor(t);
    }
}