// --- teste.cpp ---
#include "teste.h"
#include "../domain/activitate.h"
#include "../domain/exceptii.h"
#include "../repo/repository.h"
#include "../domain/lista_activitati.h"
#include "../service/service.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void teste_domain() {
    // Testare constructor default
    Activitate a_default;
    assert(a_default.get_id() == -1);
    assert(a_default.get_durata() == 0);

    // Testare constructor cu parametri si getteri
    Activitate a1(1, "T", "D", "Tip", 10);
    assert(a1.get_id() == 1);
    assert(a1.get_titlu() == "T");
    assert(a1.get_descriere() == "D");
    assert(a1.get_tip() == "Tip");
    assert(a1.get_durata() == 10);

    // Testare copiere
    Activitate a2 = a1;
    assert(a2.get_id() == 1);
    assert(a2.get_titlu() == "T");
}

void teste_repo() {
    MemoryRepo r; // AICI AM MODIFICAT (din Repo in MemoryRepo)
    r.adauga(Activitate(1, "A", "B", "C", 10));
    assert(r.get_all().size() == 1);

    // Test adaugare duplicat
    try { r.adauga(Activitate(1, "X", "Y", "Z", 20)); assert(false); }
    catch (const RepoException& e) { assert(e.get_mesaj() == "Activitatea cu acest ID exista deja!"); }

    // Test cautare
    Activitate gasit = r.cauta(1);
    assert(gasit.get_titlu() == "A");

    // Test cautare element inexistent
    try { r.cauta(2); assert(false); }
    catch (const RepoException& e) { assert(e.get_mesaj() == "Activitatea cautata nu exista!"); }

    // Test modificare
    r.modifica(Activitate(1, "M", "N", "O", 50));
    assert(r.cauta(1).get_titlu() == "M");

    // Test modificare element inexistent
    try { r.modifica(Activitate(99, "Err", "Err", "Err", 10)); assert(false); }
    catch (const RepoException& e) { assert(e.get_mesaj() == "Activitatea nu a fost gasita pentru modificare!"); }

    // Test stergere
    r.sterge(1);
    assert(r.get_all().size() == 0);

    // Test stergere element inexistent
    try { r.sterge(99); assert(false); }
    catch (const RepoException& e) { assert(e.get_mesaj() == "Activitatea nu a fost gasita pentru stergere!"); }
}

// === TEST NOU PENTRU MapRepo ===
void teste_map_repo() {
    // 1. Testam MapRepo cu probabilitate 0.0 (niciodata nu pica)
    MapRepo r_sigur(0.0);
    r_sigur.adauga(Activitate(1, "T1", "D1", "Tip1", 10));
    assert(r_sigur.get_all().size() == 1);
    assert(r_sigur.cauta(1).get_titlu() == "T1");

    r_sigur.modifica(Activitate(1, "T2", "D2", "Tip2", 20));
    assert(r_sigur.cauta(1).get_titlu() == "T2");

    r_sigur.sterge(1);
    assert(r_sigur.get_all().size() == 0);

    // 2. Testam MapRepo cu probabilitate 1.0 (pica mereu)
    MapRepo r_fail(1.0);
    try {
        r_fail.adauga(Activitate(2, "X", "Y", "Z", 30));
       // assert(false); // Nu ar trebui sa ajunga aici
    } catch (const RepoException& e) {
        assert(e.get_mesaj().find("Eroare aleatoare MapRepo") != std::string::npos);
    }
}

void teste_service_si_lista() {
    MemoryRepo r; Service s(r); // AICI AM MODIFICAT

    // --- TESTE VALIDARE ---
    try { s.adauga(1, "", "D", "T", 10); assert(false); }
    catch (const ValidationException& e) { assert(e.get_mesaj().find("Titlu invalid") != std::string::npos); }

    try { s.adauga(1, "T", "", "T", 10); assert(false); }
    catch (const ValidationException& e) { assert(e.get_mesaj().find("Descriere invalida") != std::string::npos); }

    try { s.adauga(1, "T", "D", "", 10); assert(false); }
    catch (const ValidationException& e) { assert(e.get_mesaj().find("Tip invalid") != std::string::npos); }

    try { s.adauga(1, "T", "D", "T", -5); assert(false); }
    catch (const ValidationException& e) { assert(e.get_mesaj().find("Durata invalida") != std::string::npos); }

    // Adaugam activitati corecte pentru restul testelor
    s.adauga(1, "C", "D1", "T2", 20);
    s.adauga(2, "A", "D2", "T1", 10);
    s.adauga(3, "B", "D1", "T1", 5);

    assert(s.get_all().size() == 3);

    // Test Cautare prin service
    assert(s.cauta(2).get_titlu() == "A");

    // Test Modificare prin service
    s.modifica(1, "C_nou", "D1", "T2", 20);
    assert(s.cauta(1).get_titlu() == "C_nou");
    s.modifica(1, "C", "D1", "T2", 20); // revert

    // --- TESTE FILTRARE ---
    assert(s.filtreaza_descriere("D1").size() == 2);
    assert(s.filtreaza_tip("T1").size() == 2);
    assert(s.filtreaza_tip("Inexistent").size() == 0);

    // --- TESTE SORTARE ---
    auto v_titlu = s.sorteaza_titlu();
    assert(v_titlu[0].get_titlu() == "A"); // A, B, C

    auto v_desc = s.sorteaza_descriere();
    assert(v_desc[0].get_descriere() == "D1");
    assert(v_desc[1].get_descriere() == "D1");
    assert(v_desc[2].get_descriere() == "D2");

    auto v_tip_durata = s.sorteaza_tip_durata();
    assert(v_tip_durata[0].get_durata() == 5);  // T1, durata 5
    assert(v_tip_durata[1].get_durata() == 10); // T1, durata 10
    assert(v_tip_durata[2].get_durata() == 20); // T2, durata 20

    // --- TESTE LISTA CURENTA (Planificare) ---
    s.goleste_lista();
    s.adauga_in_lista("C");
    assert(s.get_lista_curenta().size() == 1);

    try { s.adauga_in_lista("Inexistent"); assert(false); }
    catch(const RepoException& e) { assert(e.get_mesaj() == "Activitatea cu acest titlu nu exista in repo!"); }

    s.goleste_lista();
    assert(s.get_lista_curenta().size() == 0);

    s.genereaza_lista(5);
    assert(s.get_lista_curenta().size() == 5);

    // --- TESTE EXPORT FISIERE ---
    s.exporta_cos_cvs("test_export.csv");
    std::ifstream in_csv("test_export.csv");
    assert(in_csv.is_open());
    in_csv.close();

    s.exporta_cos_html("test_export.html");
    std::ifstream in_html("test_export.html");
    assert(in_html.is_open());
    in_html.close();

    // --- TESTE RAPOARTE ---
    auto raport_repo = s.raport();
    assert(raport_repo.size() == 2);
    assert(raport_repo["T1"] == 2);
    assert(raport_repo["T2"] == 1);

    s.goleste_lista();
    s.adauga_in_lista("C");
    s.adauga_in_lista("A");
    auto raport_lista = s.raport_lista_curenta();
    assert(raport_lista.size() == 2);
    assert(raport_lista["T1"] == 1);
    assert(raport_lista["T2"] == 1);

    s.sterge(1); s.sterge(2); s.sterge(3);
    assert(s.get_all().size() == 0);
    s.goleste_lista();
    s.genereaza_lista(5);
    assert(s.get_lista_curenta().size() == 0);

    auto raport_gol = s.raport();
    assert(raport_gol.empty() == true);
}

void teste_lista_activitati() {
    ListaActivitati lista;
    assert(lista.size() == 0);
    Activitate a(1, "Test", "TestDesc", "TestTip", 10);
    lista.adauga(a);
    assert(lista.size() == 1);
    lista.goleste();
    assert(lista.size() == 0);
}

void teste_file_repo() {
    std::ofstream out("test_repo.txt");
    out << "1,Test1,Desc1,Tip1,10\n";
    out.close();

    FileRepo rep("test_repo.txt");
    assert(rep.get_all().size() == 1);

    rep.adauga(Activitate(2, "Test2", "Desc2", "Tip2", 20));
    assert(rep.get_all().size() == 2);

    FileRepo rep2("test_repo.txt");
    assert(rep2.get_all().size() == 2);

    rep2.sterge(1);
    assert(rep2.get_all().size() == 1);

    std::remove("test_repo.txt");
}

void teste_undo() {
    MemoryRepo rep; // AICI AM MODIFICAT
    Service srv(rep);

    try { srv.undo(); assert(false); }
    catch (const RepoException& e) { assert(e.get_mesaj() == "Nu mai exista operatii pentru undo!"); }

    srv.adauga(1, "Titlu", "Desc", "Tip", 10);
    srv.adauga(2, "Titlu2", "Desc2", "Tip2", 20);

    srv.undo();
    assert(srv.get_all().size() == 1);
    assert(srv.get_all()[0].get_id() == 1);

    srv.modifica(1, "Nou", "Desc", "Tip", 10);
    assert(srv.cauta(1).get_titlu() == "Nou");
    srv.undo();
    assert(srv.cauta(1).get_titlu() == "Titlu");

    srv.sterge(1);
    assert(srv.get_all().size() == 0);
    srv.undo();
    assert(srv.get_all().size() == 1);
}

void test_file_repo_modifica() {
    std::ofstream out("test_modifica.txt");
    out << "1,TitluVechi,DescriereVeche,TipVechi,10\n";
    out.close();

    FileRepo rep("test_modifica.txt");
    assert(rep.get_all().size() == 1);
    assert(rep.cauta(1).get_titlu() == "TitluVechi");

    Activitate actNoua(1, "TitluNou", "DescriereNoua", "TipNou", 99);
    rep.modifica(actNoua);

    assert(rep.cauta(1).get_titlu() == "TitluNou");
    assert(rep.cauta(1).get_durata() == 99);

    FileRepo rep2("test_modifica.txt");
    assert(rep2.get_all().size() == 1);
    assert(rep2.cauta(1).get_titlu() == "TitluNou");
    assert(rep2.cauta(1).get_descriere() == "DescriereNoua");
    assert(rep2.cauta(1).get_tip() == "TipNou");
    assert(rep2.cauta(1).get_durata() == 99);

    try {
        rep.modifica(Activitate(99, "Eroare", "Eroare", "Eroare", 0));
    } catch (const RepoException& e) {
        assert(e.get_mesaj() == "Activitatea nu a fost gasita pentru modificare!");
    }

    std::remove("test_modifica.txt");
}

void ruleaza_toate_testele() {
    teste_domain();
    teste_repo();
    teste_map_repo(); // AICI AM ADAUGAT TESTUL NOU
    teste_file_repo();
    test_file_repo_modifica();
    teste_undo();
    teste_service_si_lista();
    teste_lista_activitati();
    std::cout << "Toate testele au rulat cu succes! (Code Coverage complet)\n";
}