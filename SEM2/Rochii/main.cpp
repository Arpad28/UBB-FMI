#include <QApplication>
#include "repo.h"
#include "service.h"
#include "gui.h"
#include "exceptii.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo("fisier.txt");
    Service srv(repo);
    GUI gui(srv);

    gui.show();
    return a.exec();
}