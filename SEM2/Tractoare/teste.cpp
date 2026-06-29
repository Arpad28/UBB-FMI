#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>
#include <stdexcept>

void test_domain() {
    Tractor t(1, "JohnDeere", "Agricol", 4);
    assert(t.getId() == 1);
    assert(t.getDenumire() == "JohnDeere");
    assert(t.getTip() == "Agricol");
    assert(t.getNumarRoti() == 4);
    t.setNumarRoti(2);
    assert(t.getNumarRoti() == 2);
}

void test_repo_service() {
    std::ofstream out("teste_tractoare.txt", std::ios::trunc);
    out << "1,Zimbrul,Industrial,4\n";
    out.close();

    Repo repo("teste_tractoare.txt");
    Service srv(repo);

    assert(srv.get_all_sorted().size() == 1);
    
    // Adaugare cu validare OK
    srv.addTractor(2, "Alpha", "Industrial", 6);
    assert(srv.get_all_sorted().size() == 2);
    // Sunt sortate: "Alpha" (2) inainte de "Zimbrul" (1)
    assert(srv.get_all_sorted()[0].getDenumire() == "Alpha");

    // Test tip count
    auto counts = srv.get_tip_counts();
    assert(counts["Industrial"] == 2);

    // Test exceptii
    try {
        srv.addTractor(2, "", "", 1); // ID duplicat, nume/tip vid, roti impare
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::string erori = e.what();
        assert(erori.find("vida") != std::string::npos);
        assert(erori.find("ID") != std::string::npos);
        assert(erori.find("par") != std::string::npos);
    }

    // Test decrementare roti
    srv.decrementWheels(2);
    assert(srv.cauta(2).getNumarRoti() == 4);
}

void ruleaza_teste() {
    test_domain();
    test_repo_service();
}