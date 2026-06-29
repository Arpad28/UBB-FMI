#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

/*Functia testeaza domainul
 */
void test_domeniu() {
    Utilaj u(1, "Claas", "Combina", 8);
    assert(u.getId() == 1);
    assert(u.getDenumire() == "Claas");
    assert(u.getTip() == "Combina");
    assert(u.getCilindrii() == 8);
    u.setDenumire("Clas");
    assert(u.getDenumire() == "Clas");
    u.setTip("Combinaa");
    assert(u.getTip() == "Combinaa");
    u.setCilindrii(4);
    assert(u.getCilindrii() == 4);
}

/*Functie care testeaza serivce ul,implicit si repo
 */
void test_service() {
    std::ofstream out("test_utilaje.txt", std::ios::trunc);
    out << "1,Claas,Combina,8\n";
    out << "2,TractorX,Tractor,4\n";
    out.close();
    Repo repo("test_utilaje.txt");
    Service srv(repo);

    assert(srv.get_all_sortat().size() == 2);
    assert(srv.get_all_sortat()[0].getTip() == "Combina");
    srv.updateUtilaj(1, "ClaasNou", "Combina", 4);
    try {
        srv.updateUtilaj(1, "", "Combina", 4);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    try {
        srv.updateUtilaj(1, "Class", "Combina", 6);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    assert(srv.cauta(1).getDenumire() == "ClaasNou");
    assert(srv.cauta(1).getCilindrii() == 4);
    srv.stergeUtilaj(1);
    try {
        srv.stergeUtilaj(2);
        assert(false);
    } catch (std::exception& e) {
        assert(true);
    }
}
/*Testeaza functiile ajutatoare pentru UI
 */
void teste_functii_pentru_ui() {
    std::ofstream out("test_utilaje.txt", std::ios::trunc);
    out << "1,Claas,Combina,8\n";
    out << "2,TractorX,Tractor,4\n";
    out<< "3,John Deere,Combina,8\n";
    out<<"4,JCB,Motosapa,2\n";
    out.close();
    Repo repo("test_utilaje.txt");
    Service srv(repo);

    auto rez=srv.get_nr_cilindrii();
    assert(rez.size() == 3);
    assert(rez[8]==2);
    assert(rez[4]==1);
    assert(rez[2]==1);
}
/*Apelam toate functiile pentru test*/
void ruleaza_teste() {
    teste_functii_pentru_ui();
    test_domeniu();
    test_service();
    std::cout<<"Toate testele au trecut cu succes";
}