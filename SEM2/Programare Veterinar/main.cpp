#include <QApplication>

#include "service.h"
#include "teste.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    ruleaza_teste();
    QApplication a(argc, argv);
    Repo repo("cabinet.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.show();
    return a.exec();
}
