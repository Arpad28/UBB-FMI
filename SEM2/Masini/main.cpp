#include <QApplication>
#include <QPushButton>
#include "repo.h"
#include "gui.h"
#include "service.h"
#include "domain.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo("masini.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.show();
    return a.exec();
}