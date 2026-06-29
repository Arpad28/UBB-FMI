#include <QApplication>
#include <fstream>
#include "service.h"
#include "teste.h"
#include "ui.h"


int main(int argc, char *argv[]) {
    ruleaza_teste();

    QApplication a(argc, argv);
    Repo repo("tractoare.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.resize(800, 500);
    gui.show();

    return a.exec();
}