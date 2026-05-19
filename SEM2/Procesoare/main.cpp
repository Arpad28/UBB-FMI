#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RepoProcesoare repoP("procesoare.txt");
    RepoPlaciDeBaza repoB("placi.txt");
    Service srv(repoP, repoB);
    MainGUI gui(srv);
    gui.show();
    return a.exec();
}