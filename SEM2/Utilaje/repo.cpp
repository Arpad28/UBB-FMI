#include "repo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

/*Constructor repo,intializeaza vectorul nostru cu elemente din fisierul dat
 *nume_fisier:string nevid,fisier existent
 */
Repo::Repo(std::string nume_fisier) : nume_fisier(nume_fisier) {
    loadFromFile();
}

/*Citeste din fisier utilajele date,le extrage si dupa le pune in lista noastra
 */
void Repo::loadFromFile() {
    std::ifstream in(nume_fisier);
    std::string linie;
    lista.clear();
    while (std::getline(in, linie)) {
        std::stringstream ss(linie);
        std::string s_id, denumire, tip, s_cilindrii;
        std::getline(ss, s_id, ',');
        std::getline(ss, denumire, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, s_cilindrii, '\n');
        Utilaj u(std::stoi(s_id), denumire, tip, std::stoi(s_cilindrii));
        lista.push_back(u);
    }
    in.close();
}
/*Scrie in fisier lista noastra de utilaje actualizate
 */
void Repo::saveToFile() {
    std::ofstream out(nume_fisier);
    for (const auto& u : lista) {
        out << u.getId() << "," << u.getDenumire() << "," 
            << u.getTip() << "," << u.getCilindrii() << "\n";
    }
    out.close();
}
/*Returneaza lista de utilaje
 */
std::vector<Utilaj> Repo::get_all() const {
    return lista;
}
/*Cauta un utilaj dupa id ul sau
 *id- numar intreg
 *Exceptii: Daca ID nu exista se arunca o exceptie
 */
Utilaj Repo::cauta(int id) const {
    for (const auto& u : lista) {
        if (u.getId() == id) return u;
    }
    throw std::runtime_error("Utilajul nu a exista");}
/*Sterge utilajul cu id ul dat
 *id-numar intreg
 */
void Repo::sterge(int id) {
    auto it = lista.begin();
    while (it != lista.end()) {
        if (it->getId() == id) {
            lista.erase(it);
            saveToFile();
            return;
        }
        it++;}
}
/*Seteaza utilajul vechi cu utilajul nou,si dupa scrie in fisier
 *modified-utilaj nou,modificat avand aceas id  ca unul existent
 */
void Repo::update(const Utilaj& modified) {
    for (auto& u : lista) {
        if (u.getId() == modified.getId()) {
            u.setDenumire(modified.getDenumire());
            u.setTip(modified.getTip());
            u.setCilindrii(modified.getCilindrii());
            break;
        }
    }
    saveToFile();
}