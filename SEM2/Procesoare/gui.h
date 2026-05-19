#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "service.h"

class MainGUI : public QWidget {
private:
    Service& srv;

    QListWidget* listProcesoare;
    QListWidget* listPlaci;

    QLineEdit* txtNume;
    QLineEdit* txtSoclu;
    QLineEdit* txtPret;
    QPushButton* btnAdauga;

    QLabel* lblPretTotal;

    void initGUI();
    void connectSignals();
    void populeazaProcesoare();
    void populeazaPlaci(const std::vector<PlacaDeBaza>& placi);

    void handlerFiltrareSiPret();
    void handlerAdaugare();

public:
    MainGUI(Service& srv);
};