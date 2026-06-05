#pragma once
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include "../ui/Observer.h"
#include "../ui/ActivitatiTableModel.h"
#include "../service/service.h"

class CosCRUDGUI : public QWidget, public Observer {
private:
    Service& srv;
    QTableView* tableCos;
    ActivitatiTableModel* model;
    QPushButton* btnGoleste;
    QPushButton* btnGenereaza;

    void initGUI() {
        this->setWindowTitle("Cos CRUD - Tabel");
        QVBoxLayout* mainLayout = new QVBoxLayout{ this };

        tableCos = new QTableView;
        model = new ActivitatiTableModel;
        tableCos->setModel(model);
        tableCos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableCos->setSelectionBehavior(QAbstractItemView::SelectRows);
        mainLayout->addWidget(tableCos);

        QHBoxLayout* btnLayout = new QHBoxLayout;
        btnGoleste = new QPushButton("Goleste Cos");
        btnGenereaza = new QPushButton("Genereaza Random");
        btnLayout->addWidget(btnGoleste);
        btnLayout->addWidget(btnGenereaza);
        mainLayout->addLayout(btnLayout);
    }

    void connectSignalsSlots() {
        QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
            srv.goleste_lista();
        });
        QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
            srv.genereaza_lista(4); // exemplu de 4 activitati generate
        });
    }

public:
    CosCRUDGUI(Service& srv) : srv{srv} {
        initGUI();
        connectSignalsSlots();
        srv.addObserver(this); // Inregistram fereastra ca observer
        update(); // populam tabelul initial
    }

    ~CosCRUDGUI() {
        srv.removeObserver(this); // Curatam observerul la distrugere
    }

    void update() override {
        model->setActivitati(srv.get_lista_curenta());
    }
};