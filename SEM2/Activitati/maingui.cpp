#include <QApplication>
#include "repo/repository.h"
#include "service/service.h"
#include "ui/ActivitatiGUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    FileRepo r("activitati.txt");
    Service s(r);

    ActivitatiGUI gui(s);
    gui.show();

    return a.exec();
}