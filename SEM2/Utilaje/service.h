#pragma once
#include "repo.h"
#include <vector>
#include <map>

/*Defineste clasa Service care are acces la repo si functiile sale
 */
class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo) : repo(repo) {}
    
    std::vector<Utilaj> get_all_sortat() const;
    std::map<std::string, int> get_nr_tip() const;
    std::map<int, int> get_nr_cilindrii() const;
    
    Utilaj cauta(int id) const;
    void stergeUtilaj(int id);
    void updateUtilaj(int id, const std::string& denumire, const std::string& tip, int cilindrii);
};