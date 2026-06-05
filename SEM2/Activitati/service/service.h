#pragma once
#include "../repo/repository.h"
#include "../domain/lista_activitati.h"
#include "../ui/Observer.h" // Includem fisierul pentru sablonul Observer
#include "undo.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Clasa Service mosteneste acum public Observable
class Service : public Observable {
private:
    Repo& repo;
    ListaActivitati lista_curenta;
    std::vector<std::unique_ptr<ActiuneUndo>> undoActions; // Stiva pentru undo

    void validare(const std::string& t, const std::string& d, const std::string& tip, int durata) const;

public:
    Service(Repo& r);

    // CRUD clasic
    void adauga(int id, const std::string& t, const std::string& d, const std::string& tip, int durata);
    void sterge(int id);
    void modifica(int id, const std::string& t, const std::string& d, const std::string& tip, int durata);
    const Activitate& cauta(int id) const;
    std::vector<Activitate> get_all() const;

    void undo(); // Functia pentru anularea ultimei actiuni

    // Rapoarte
    std::unordered_map<std::string, int> raport() const;
    std::unordered_map<std::string, int> raport_lista_curenta() const;

    // Filtrare & Sortare
    std::vector<Activitate> filtreaza_descriere(const std::string& descriere) const;
    std::vector<Activitate> filtreaza_tip(const std::string& tip) const;
    std::vector<Activitate> sorteaza_titlu() const;
    std::vector<Activitate> sorteaza_descriere() const;
    std::vector<Activitate> sorteaza_tip_durata() const;

    // Planificarea activitatilor (Lista curenta)
    void goleste_lista();
    void adauga_in_lista(const std::string& titlu);
    void genereaza_lista(int numar);
    const std::vector<Activitate>& get_lista_curenta() const;
    void exporta_cos_cvs(const std::string& nume_fisier) const;
    void exporta_cos_html(const std::string& nume_fisier) const;
};