#include "service.h"
#include "../domain/exceptii.h"
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <fstream>

Service::Service(Repo& r) : repo(r) {}

void Service::validare(const std::string& t, const std::string& d, const std::string& tip, int durata) const {
    std::string err = "";
    if (t.empty()) err += "Titlu invalid!\n";
    if (d.empty()) err += "Descriere invalida!\n";
    if (tip.empty()) err += "Tip invalid!\n";
    if (durata <= 0) err += "Durata invalida!\n";
    if (!err.empty()) throw ValidationException(err);
}

void Service::adauga(int id, const std::string& t, const std::string& d, const std::string& tip, int durata) {
    validare(t, d, tip, durata);
    Activitate act(id, t, d, tip, durata);
    repo.adauga(act);
    undoActions.push_back(std::make_unique<UndoAdauga>(repo, act));
}

void Service::sterge(int id) {
    Activitate actStearsa = repo.cauta(id);
    repo.sterge(id);
    undoActions.push_back(std::make_unique<UndoSterge>(repo, actStearsa));
}

void Service::modifica(int id, const std::string& t, const std::string& d, const std::string& tip, int durata) {
    validare(t, d, tip, durata);
    Activitate actVeche = repo.cauta(id);
    Activitate actNoua(id, t, d, tip, durata);
    repo.modifica(actNoua);
    undoActions.push_back(std::make_unique<UndoModifica>(repo, actVeche));
}

void Service::undo() {
    if (undoActions.empty()) {
        throw RepoException("Nu mai exista operatii pentru undo!");
    }
    undoActions.back()->doUndo();
    undoActions.pop_back();
}

const Activitate& Service::cauta(int id) const { return repo.cauta(id); }

std::vector<Activitate> Service::get_all() const {
    return repo.get_all();
}

std::vector<Activitate> Service::filtreaza_descriere(const std::string& d) const {
    std::vector<Activitate> rez;
    auto toate = repo.get_all();
    std::copy_if(toate.begin(), toate.end(), std::back_inserter(rez),
        [&d](const Activitate& act) { return act.get_descriere() == d; });
    return rez;
}

std::vector<Activitate> Service::filtreaza_tip(const std::string& t) const {
    std::vector<Activitate> rez;
    auto toate = repo.get_all();
    std::copy_if(toate.begin(), toate.end(), std::back_inserter(rez),
        [&t](const Activitate& act) { return act.get_tip() == t; });
    return rez;
}

std::vector<Activitate> Service::sorteaza_titlu() const {
    std::vector<Activitate> rez = repo.get_all();
    std::sort(rez.begin(), rez.end(), [](const Activitate& a, const Activitate& b) {
        return a.get_titlu() < b.get_titlu();
    });
    return rez;
}

std::vector<Activitate> Service::sorteaza_descriere() const {
    std::vector<Activitate> rez = repo.get_all();
    std::sort(rez.begin(), rez.end(), [](const Activitate& a, const Activitate& b) {
        return a.get_descriere() < b.get_descriere();
    });
    return rez;
}

std::vector<Activitate> Service::sorteaza_tip_durata() const {
    std::vector<Activitate> rez = repo.get_all();
    std::sort(rez.begin(), rez.end(), [](const Activitate& a, const Activitate& b) {
        if (a.get_tip() == b.get_tip()) return a.get_durata() < b.get_durata();
        return a.get_tip() < b.get_tip();
    });
    return rez;
}

// -------------------------------------------------------------------------
// Metodele pentru cos (unde implementam notificarea observer-ilor)
// -------------------------------------------------------------------------

void Service::goleste_lista() {
    lista_curenta.goleste();
    notifyObservers(); // Anuntam ferestrele ca s-a modificat cosul
}

void Service::adauga_in_lista(const std::string& titlu) {
    auto toate = repo.get_all();
    auto it = std::find_if(toate.begin(), toate.end(), [&titlu](const Activitate& act) {
        return act.get_titlu() == titlu;
    });

    if (it == toate.end()) throw RepoException("Activitatea cu acest titlu nu exista in repo!");
    lista_curenta.adauga(*it);

    notifyObservers(); // Anuntam ferestrele ca am adaugat un element nou
}

void Service::genereaza_lista(int numar) {
    lista_curenta.genereaza_aleator(numar, repo.get_all());

    notifyObservers(); // Anuntam ferestrele ca s-a generat o noua lista
}

const std::vector<Activitate>& Service::get_lista_curenta() const {
    return lista_curenta.get_toate();
}

std::unordered_map<std::string, int> Service::raport() const {
    std::unordered_map<std::string, int> raport;
    const auto& toate = repo.get_all();
    for (const auto& act : toate) {
        raport[act.get_tip()]++;
    }
    return raport;
}

void Service::exporta_cos_cvs(const std::string& nume_fisier) const {
    std::ofstream out(nume_fisier);
    for (const auto& act : lista_curenta.get_toate()) {
        out << act.get_id() << "," << act.get_titlu() << "," << act.get_descriere() << ","
            << act.get_tip() << "," << act.get_durata() << "\n";
    }
    out.close();
}

void Service::exporta_cos_html(const std::string& nume_fisier) const {
    std::ofstream out(nume_fisier);
    out << "<html><body>\n<table border=\"1\" style=\"width:100 % \">\n";
    out << "<tr><th>ID</th><th>Titlu</th><th>Descriere</th><th>Tip</th><th>Durata</th></tr>\n";
    for (const auto& act : lista_curenta.get_toate()) {
        out << "<tr><td>" << act.get_id() << "</td><td>" << act.get_titlu() << "</td><td>"
            << act.get_descriere() << "</td><td>" << act.get_tip() << "</td><td>" << act.get_durata() << "</td></tr>\n";
    }
    out << "</table>\n</body></html>\n";
    out.close();
}

std::unordered_map<std::string, int> Service::raport_lista_curenta() const {
    std::unordered_map<std::string, int> raport;
    const auto& toate = lista_curenta.get_toate();
    for (const auto& act : toate) { raport[act.get_tip()]++; }
    return raport;
}