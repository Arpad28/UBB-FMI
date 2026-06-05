// --- ui.cpp ---
#include "ui.h"
#include "../domain/exceptii.h"
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

UI::UI(Service& s) : srv(s) {}

void UI::meniu() {
    cout << "\n========== MENIU ==========\n";
    cout << "1. Adauga activitate\n2. Afiseaza toate activitatile\n3. Sterge activitate\n";
    cout << "4. Actualizeaza activitate\n5. Cauta activitate\n6. Filtreaza activitati\n";
    cout << "7. Sorteaza activitati\n";
    cout << "8. Meniu planificare activitati curente\n";
    cout << "9. Raport tipuri activitati\n";
    cout << "10. UNDO ultima operatie\n";
    cout << "0. Iesire\n===========================\nAlege optiunea: ";
}

void UI::afiseaza(const std::vector<Activitate>& lista) {
    if (lista.empty()) { cout << "Nu exista activitati.\n"; return; }
    for (const auto& a : lista) {
        cout << "ID: " << a.get_id() << " | Titlu: " << a.get_titlu()
             << " | Desc: " << a.get_descriere() << " | Tip: " << a.get_tip()
             << " | Durata: " << a.get_durata() << "\n";
    }
}

void UI::adauga() {
    int id, durata; string t, d, tip;
    cout << "ID: "; cin >> id; cin.ignore();
    cout << "Titlu: "; getline(cin, t); cout << "Descriere: "; getline(cin, d);
    cout << "Tip: "; getline(cin, tip); cout << "Durata: "; cin >> durata;
    try { srv.adauga(id, t, d, tip, durata); cout << "Adaugare reusita!\n"; }
    catch (const RepoException& e) { cout << "Eroare Repo: " << e.get_mesaj() << "\n"; }
    catch (const ValidationException& e) { cout << "Eroare Validare: \n" << e.get_mesaj() << "\n"; }
}

void UI::sterge() {
    int id; cout << "ID de sters: "; cin >> id;
    try { srv.sterge(id); cout << "Sters cu succes!\n"; }
    catch (const RepoException& e) { cout << "Eroare Repo: " << e.get_mesaj() << "\n"; }
}

void UI::modifica() {
    int id, durata; string t, d, tip;
    cout << "ID activitate de modificat: "; cin >> id; cin.ignore();
    cout << "Titlu nou: "; getline(cin, t); cout << "Descriere noua: "; getline(cin, d);
    cout << "Tip nou: "; getline(cin, tip); cout << "Durata noua: "; cin >> durata;
    try { srv.modifica(id, t, d, tip, durata); cout << "Modificat cu succes!\n"; }
    catch (const RepoException& e) { cout << "Eroare Repo: " << e.get_mesaj() << "\n"; }
    catch (const ValidationException& e) { cout << "Eroare Validare: \n" << e.get_mesaj() << "\n"; }
}

void UI::undo() {
    try {
        srv.undo();
        cout << "Undo realizat cu succes!\n";
    } catch (const RepoException& e) { cout << "Eroare: " << e.get_mesaj() << "\n"; }
}

void UI::cauta() {
    int id; cout << "ID cautat: "; cin >> id;
    try {
        const Activitate& a = srv.cauta(id);
        cout << "Gasit: " << a.get_titlu() << " - " << a.get_descriere() << "\n";
    } catch (const RepoException& e) { cout << "Eroare Repo: " << e.get_mesaj() << "\n"; }
}

void UI::filtreaza() {
    int cmd; string filtru;
    cout << "1. Descriere | 2. Tip\nAlegere: "; cin >> cmd; cin.ignore();
    cout << "Criteriu: "; getline(cin, filtru);
    if (cmd == 1) afiseaza(srv.filtreaza_descriere(filtru));
    else if (cmd == 2) afiseaza(srv.filtreaza_tip(filtru));
    else cout << "Comanda invalida!\n";
}

void UI::sorteaza() {
    int cmd;
    cout << "1. Titlu | 2. Descriere | 3. Tip+Durata\nAlegere: "; cin >> cmd;
    if (cmd == 1) afiseaza(srv.sorteaza_titlu());
    else if (cmd == 2) afiseaza(srv.sorteaza_descriere());
    else if (cmd == 3) afiseaza(srv.sorteaza_tip_durata());
    else cout << "Comanda invalida!\n";
}

void UI::submeniu_lista() {
    int cmd;
    while (true) {
        cout << "\n--- MENIU LISTA ACTIVITATI (Planificare) ---\n";
        cout << "1. Goleste lista\n2. Adauga activitate (dupa titlu)\n3. Genereaza lista aleator\n";
        cout << "4. Afiseaza lista curenta\n5. Exporta lista in fisier\n";
        cout << "6. Raport tipuri in lista curenta\n";
        cout << "0. Inapoi\nAlegere: ";
        cin >> cmd; cin.ignore();

        if (cmd == 1) { srv.goleste_lista(); }
        else if (cmd == 2) {
            string titlu; cout << "Titlu de adaugat: "; getline(cin, titlu);
            try { srv.adauga_in_lista(titlu); }
            catch (const RepoException& e) { cout << "Eroare: " << e.get_mesaj() << "\n"; }
        } else if (cmd == 3) {
            int nr; cout << "Numar de activitati de generat: "; cin >> nr;
            srv.genereaza_lista(nr);
        } else if (cmd == 4) { afiseaza(srv.get_lista_curenta()); }
        else if (cmd == 5) {
            cout << "Introdu numele fisierului (ex: lista.csv sau lista.html): ";
            string nume_fisier; getline(cin, nume_fisier);
            try {
                if (nume_fisier.find(".csv") != string::npos) {
                    srv.exporta_cos_cvs(nume_fisier);
                    cout << "Export CSV realizat cu succes!\n";
                } else if (nume_fisier.find(".html") != string::npos) {
                    srv.exporta_cos_html(nume_fisier);
                    cout << "Export HTML realizat cu succes!\n";
                } else cout << "Eroare: Extensie necunoscuta. Folositi .csv sau .html\n";
            } catch (const RepoException& e) { cout << "Eroare: " << e.get_mesaj() << "\n"; }
        } else if (cmd == 6) {
            cout << "\n=== RAPORT TIPURI IN LISTA CURENTA ===\n";
            auto raport_sublista = srv.raport_lista_curenta();
            if (raport_sublista.empty()) cout << "Lista curenta este goala!\n";
            else {
                for (const auto& pereche : raport_sublista) {
                    cout << "Tipul: [" << pereche.first << "] -> " << pereche.second << " activitati\n";
                }
            }
            cout << "======================================\n";
        } else if (cmd == 0) { break; }
        else cout << "Comanda invalida!\n";

        if(cmd >= 1 && cmd <= 3) cout << "=> Numar total activitati in lista curenta: " << srv.get_lista_curenta().size() << "\n";
    }
}

void UI::raport_tipuri_ui() {
    std::cout << "\n=== RAPORT TIPURI ACTIVITATI ===\n";
    auto raport = srv.raport();
    if (raport.empty()) {
        std::cout << "Nu exista nicio activitate adaugata!\n"; return;
    }
    for (const auto& pereche : raport) {
        std::cout << "Tipul: [" << pereche.first << "] -> " << pereche.second << " activitati\n";
    }
    std::cout << "================================\n";
}

void UI::run() {
    int cmd;
    while (true) {
        meniu(); cin >> cmd;
        if (cmd == 1) adauga();
        else if (cmd == 2) afiseaza(srv.get_all());
        else if (cmd == 3) sterge();
        else if (cmd == 4) modifica();
        else if (cmd == 5) cauta();
        else if (cmd == 6) filtreaza();
        else if (cmd == 7) sorteaza();
        else if (cmd == 8) submeniu_lista();
        else if (cmd == 9) raport_tipuri_ui();
        else if (cmd == 10) undo(); // Apeleaza logica de Undo
        else if (cmd == 0) break;
        else cout << "Comanda invalida!\n";
    }
}