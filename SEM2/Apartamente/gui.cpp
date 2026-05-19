#include "gui.h"
#include <QHBoxLayout>
#include <QString>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>

GUI::GUI(Service& srv) : srv(srv) {
    initGUI();
    connectsignals();
    reloadlist(srv.get_all());
}

void GUI::initGUI() {
    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    table = new QTableView();
    model = new TableModel(this);
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainlayout->addWidget(table);

    QVBoxLayout *btnlayout = new QVBoxLayout();

    btnfiltpret = new QPushButton("Filtrare Pret");
    QFormLayout* layout2 = new QFormLayout();
    pret1 = new QLineEdit();
    pret2 = new QLineEdit();
    layout2->addRow("Pret min", pret1);
    layout2->addRow("Pret max", pret2);

    btnfiltsupraf = new QPushButton("Filtrare Suprafata");
    QFormLayout* layout = new QFormLayout();
    supraf1 = new QLineEdit();
    supraf2 = new QLineEdit();
    layout->addRow("Supraf min", supraf1);
    layout->addRow("Supraf max", supraf2);

    btnnefiltrat = new QPushButton("Nefiltrat");
    btnsterge = new QPushButton("Sterge");

    btnlayout->addLayout(layout);
    btnlayout->addWidget(btnfiltsupraf);
    btnlayout->addLayout(layout2);
    btnlayout->addWidget(btnfiltpret);
    btnlayout->addWidget(btnnefiltrat);
    btnlayout->addWidget(btnsterge);

    mainlayout->addLayout(btnlayout);
    this->resize(650, 450);
}

void GUI::connectsignals() {
    QObject::connect(btnnefiltrat, &QPushButton::clicked, [this]() {
        reloadlist(srv.get_all());
        supraf1->clear(); supraf2->clear();
        pret1->clear(); pret2->clear();
    });

    QObject::connect(btnsterge, &QPushButton::clicked, [this]() {
        auto selectedRows = table->selectionModel()->selectedRows();
        if (selectedRows.isEmpty()) {
            QMessageBox::warning(this, "Eroare", "Nu ai selectat nimic!");
            return;
        }
        int currentRow = selectedRows.first().row();
        Apartament ap = model->getApartament(currentRow);
        srv.sterge(ap.get_strada(), ap.get_suprafata(), ap.get_pret());
        reloadlist(srv.get_all());
        supraf1->clear(); supraf2->clear();
        pret1->clear(); pret2->clear();
    });

    QObject::connect(btnfiltsupraf, &QPushButton::clicked, [this]() {
        if(supraf1->text().isEmpty() || supraf2->text().isEmpty()) {
            QMessageBox::warning(this, "Eroare", "Nu ai introdus in casute!");
            return;
        }
        double a = supraf1->text().toDouble();
        double b = supraf2->text().toDouble();
        reloadlist(srv.filtrare_suprafata(a, b));
    });

    QObject::connect(btnfiltpret, &QPushButton::clicked, [this]() {
        if(pret1->text().isEmpty() || pret2->text().isEmpty()){
            QMessageBox::warning(this, "Eroare", "Nu ai introdus in casute!");
            return;
        }
        int p1 = pret1->text().toInt();
        int p2 = pret2->text().toInt();

        auto rez_pret = srv.filtrare_pret(p1, p2);

        if (!supraf1->text().isEmpty() && !supraf2->text().isEmpty()) {
            double s1 = supraf1->text().toDouble();
            double s2 = supraf2->text().toDouble();
            std::vector<Apartament> rez_final;
            std::copy_if(rez_pret.begin(), rez_pret.end(), std::back_inserter(rez_final), [&s1, &s2](const Apartament& p) {
                return p.get_suprafata() >= s1 && p.get_suprafata() <= s2;
            });
            reloadlist(rez_final);
        } else {
            reloadlist(rez_pret);
        }
    });
}

void GUI::reloadlist(const std::vector<Apartament>& lista) {
    model->setApartamente(lista);
}