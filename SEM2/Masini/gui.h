#pragma once
#include "service.h"
#include "domain.h"
#include <QWidget>
#include <QPushButton>
#include <QListWidget>

class GUI : public QWidget {
private:
    Service& srv;

    QListWidget* list;
    QPushButton* btnsortaremodel;
    QPushButton* btnsortarenrmatricol;
    QPushButton* btnnesortat;
    QLineEdit* txtDetalii;

    void initGUI();
    void connectsignals();
    void reloadlist(const std::vector<Masina>& masini);
public:
    GUI(Service& srv);
};