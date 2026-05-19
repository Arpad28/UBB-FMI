#include "gui.h"
#include <QMessageBox>
#include <QString>
#include <QHeaderView>
#include <QTableWidget>
#include "exceptii.h"

GUI::GUI(Service& srv) : srv(srv) {
    initGUI();
    connectSignals();
    reloadList(srv.get_all());
}

void GUI::initGUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    table = new QTableWidget();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Denumire", "Mărime", "Preț"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(table);

    QVBoxLayout* btnLayout = new QVBoxLayout();
    btnInchiriaza = new QPushButton("Inchirieri rochie");
    btnSortMarime = new QPushButton("Sortare marime");
    btnSortPret = new QPushButton("Sortare pret");
    btnNesortat = new QPushButton("Nesortat");

    btnLayout->addWidget(btnInchiriaza);
    btnLayout->addStretch();
    btnLayout->addWidget(btnSortMarime);
    btnLayout->addWidget(btnSortPret);
    btnLayout->addWidget(btnNesortat);

    mainLayout->addLayout(btnLayout);
    this->setWindowTitle("Magazin Inchirieri Rochii");
    this->resize(600, 400);
}

void GUI::connectSignals() {
    QObject::connect(btnInchiriaza, &QPushButton::clicked, [this]() {
        int selectedRow = table->currentRow();
        if (selectedRow < 0) {
            QMessageBox::warning(this, "Atentie", "Nu ai selectat nicio rochie!");
            return;
        }

        QTableWidgetItem* firstItem = table->item(selectedRow, 0);
        int cod_rochie = firstItem->data(Qt::UserRole).toInt();

        try {
            srv.inchiriaza(cod_rochie);
            reloadList(srv.get_all());
            QMessageBox::information(this, "Succes", "Rochia a fost inchiriata cu succes!");
        } catch (const RepoException& ex) {
            QMessageBox::critical(this, "Eroare Inchiriere", QString::fromStdString(ex.get_mesaj()));
        }
    });

    QObject::connect(btnSortMarime, &QPushButton::clicked, [this]() {
        reloadList(srv.sortare_marime());
    });

    QObject::connect(btnSortPret, &QPushButton::clicked, [this]() {
        reloadList(srv.sortare_pret());
    });

    QObject::connect(btnNesortat, &QPushButton::clicked, [this]() {
        reloadList(srv.get_all());
    });
}

void GUI::reloadList(const std::vector<Rochie>& rochii) {
    table->clearContents();
    table->setRowCount(0);

    for (const auto& r : rochii) {
        int row = table->rowCount();
        table->insertRow(row);
        QTableWidgetItem* itemDenumire = new QTableWidgetItem(QString::fromStdString(r.get_denumire()));
        QTableWidgetItem* itemMarime = new QTableWidgetItem(QString::fromStdString(r.get_marime()));
        QTableWidgetItem* itemPret = new QTableWidgetItem(QString::number(r.get_pret()));

        itemDenumire->setData(Qt::UserRole, r.get_cod());

        QColor color = (r.get_disponibiliate() == "True") ? Qt::green : Qt::red;
        itemDenumire->setBackground(color);
        itemMarime->setBackground(color);
        itemPret->setBackground(color);

        table->setItem(row, 0, itemDenumire);
        table->setItem(row, 1, itemMarime);
        table->setItem(row, 2, itemPret);
    }
}