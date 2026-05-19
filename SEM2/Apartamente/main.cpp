#include <QApplication>
#include <QPushButton>
#include "repo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo r("apartamente.txt");
    Service srv(r);
    GUI gui(srv);
    gui.show();
    return a.exec();
}