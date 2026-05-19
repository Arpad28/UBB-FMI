#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>

#include "service.h"

class GUI : public QWidget {
private:
    Service& srv;

    QTableWidget* table;
    QPushButton* btnInchiriaza;
    QPushButton* btnSortMarime;
    QPushButton* btnSortPret;
    QPushButton* btnNesortat;

    void initGUI();
    void connectSignals();
    void reloadList(const std::vector<Rochie>& rochii);

public:
    GUI(Service& srv);
};