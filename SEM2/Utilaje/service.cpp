#include "service.h"
#include <algorithm>
#include <stdexcept>

/*Sorteaza lista noastra de utilaje dupa tipul lor,iar la aceasi tip dupa denumirea lor
 */
std::vector<Utilaj> Service::get_all_sortat() const {
    std::vector<Utilaj> all = repo.get_all();
    std::sort(all.begin(), all.end(), [](const Utilaj& a, const Utilaj& b) {
        if (a.getTip() == b.getTip()) {
            return a.getDenumire() < b.getDenumire();
        }
        return a.getTip() < b.getTip();
    });
    return all;}
/*Calculeaza si returneaza numarul de aceasi tipuri din lista noastra de utilaje
 */
std::map<std::string, int> Service::get_nr_tip() const {
    std::map<std::string, int> counts;
    for (const auto& u : repo.get_all()) {
        if (counts[u.getTip()]<0)
            counts[u.getTip()]=0;
        counts[u.getTip()]++;
    }
    return counts;}
/*Calculeaza si returneaza numarul de cilindrii la fel din lista noastra de utilaje
 */
std::map<int, int> Service::get_nr_cilindrii() const {
    std::map<int, int> counts;
    for (const auto& u : repo.get_all()) {
        if (counts[u.getCilindrii()]<0)
            counts[u.getCilindrii()]=0;
        counts[u.getCilindrii()]++;
    }
    return counts;}

/*Cauta un utilaj dupa id
 *id-numar intreg,id cu aceas tip existent
 */
Utilaj Service::cauta(int id) const {
    return repo.cauta(id);
}
/*Sterge utilajul cu id ul dat,daca nu e ultimul cu numarul de cilindrii
 *id-numar intreg,id existent
 *Exceptii:Daca e ultimul cu numarul sau de cilindrii se arunca o exceptie
 */
void Service::stergeUtilaj(int id) {
    Utilaj u = cauta(id);
    auto counts = get_nr_cilindrii();

    if (counts[u.getCilindrii()] == 1) {
        throw std::runtime_error("Este ultimul avand numarul sau de cilindrii");
    }
    repo.sterge(id);
}
/*Actualizeaza utilajul nostru cu datele noi
 *Exceptii:Daca denuirea si/sau tipul este vid se arunca o exceptie
 *Daca numarul de cilindrii nu se conforma se arunca o exceptie
 */
void Service::updateUtilaj(int id, const std::string& denumire, const std::string& tip, int cilindrii) {
    if (denumire.empty() || tip.empty()) {
        throw std::invalid_argument("Denumirea si/sau tipul este vida");}
    if (cilindrii != 1 && cilindrii != 2 && cilindrii != 4 && cilindrii != 8) {
        throw std::invalid_argument("Numarul de cilindri trebuie sa fie 1, 2, 4 sau 8");}

    Utilaj modificat(id, denumire, tip, cilindrii);
    repo.update(modificat);
}