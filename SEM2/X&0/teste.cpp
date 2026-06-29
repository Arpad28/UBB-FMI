#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>

void test_domain() {
    Game g(1, 3, "---------", 'X', "Neinceput");
    assert(g.getId() == 1);
    assert(g.getDim() == 3);
    assert(g.getBoard() == "---------");
    assert(g.getNextPlayer() == 'X');
    assert(g.getStatus() == "Neinceput");
}

void test_repo_service() {
    std::ofstream out("teste.txt", std::ios::trunc);
    out << "1,3,---------,X,Neinceput\n";
    out.close();

    Repo repo("teste.txt");
    Service srv(repo);

    assert(srv.get_all_sorted().size() == 1);
    srv.createGame(3, 'O');
    assert(srv.get_all_sorted().size() == 2);

    srv.playMove(1, 0, 0); // Mutare randul 0, coloana 0
    Game g = srv.cauta(1);
    assert(g.getBoard()[0] == 'X');
    assert(g.getNextPlayer() == 'O');
    assert(g.getStatus() == "In derulare");
}

void ruleaza_teste() {
    test_domain();
    test_repo_service();
}