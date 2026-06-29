#include <QApplication>
#include <fstream>
#include "service.h"
#include "teste.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    ruleaza_teste();
    QApplication a(argc, argv);
    Repo repo("utilaje.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.resize(1000, 500);
    gui.show();
    return a.exec();
}