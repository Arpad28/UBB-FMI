#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "service.h"

class GUI:public QWidget {
private:
    Service& srv;
    QTableWidget* table;
    QLineEdit* specie;
    QTextEdit* text;

    QLineEdit* cod_input;
    QLineEdit* numar_input;
    QPushButton* btn_programeaza;
    QLabel* lbl_rezultat;

    void initGui();
    void connectsignals();
    void reloadlist(const std::vector<cabinet>&lista);
public:
    GUI(Service& srv);
};