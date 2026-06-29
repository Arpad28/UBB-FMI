#pragma once
#include "repo.h"
#include <vector>
#include <map>
#include <set>

class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo) : repo(repo) {}
    
    std::vector<Tractor> get_all_sorted() const;
    std::map<std::string, int> get_tip_counts() const; // Pentru coloana a 5-a
    std::vector<std::string> get_distinct_types() const; // Pentru ComboBox
    
    Tractor cauta(int id) const;
    void addTractor(int id, const std::string& denumire, const std::string& tip, int numarRoti);
    void decrementWheels(int id);
};