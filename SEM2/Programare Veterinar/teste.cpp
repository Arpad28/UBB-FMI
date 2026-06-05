#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>

void test_domain() {
    cabinet c("C101", "Rex", "caine", "vaccinare", 120);
    assert(c.get_cod() == "C101");
    assert(c.get_nume() == "Rex");
    assert(c.get_specie() == "caine");
    assert(c.get_tip() == "vaccinare");
    assert(c.get_pret() == 120);
}

void test_repo() {
    std::ofstream out("teste.txt",std::ios::trunc);
    out << "C101,Rex,caine,vaccinare,120\n";
    out << "C102,Miti,pisica,control,50\n";
    out.close();
    Repo repo("teste.txt");
    assert(repo.get_all().size() == 2);
}
void test_service() {
    std::ofstream out("teste.txt",std::ios::trunc);
    out << "C101,Rex,caine,vaccinare,120\n";
    out << "C102,Miti,pisica,control,50\n";
    out << "C103,Max,caine,operatie,500\n";
    out.close();
    Repo repo("teste.txt");
    Service srv(repo);
    assert(srv.get_all().size() == 3);
    auto filtru1 = srv.filt_specie("caine");
    assert(filtru1.size() == 2);
    auto filtru2 = srv.filt_specie("pisica");
    assert(filtru2.size() == 1);
    auto filtru3 = srv.filt_specie("papagal");
    assert(filtru3.size() == 0);
    cabinet gasit = srv.cauta("C102");
    assert(gasit.get_nume() == "Miti");
}

void ruleaza_teste() {
    test_domain();
    test_repo();
    test_service();
}