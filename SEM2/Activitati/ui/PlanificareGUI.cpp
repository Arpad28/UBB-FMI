#include "PlanificareGUI.h"
#include "../domain/exceptii.h"

PlanificareGUI::PlanificareGUI(Service& srv) : srv{srv} {
    initGUI();
    connectSignalsSlots();
    reloadCos();
}

void PlanificareGUI::initGUI() {
    this->setWindowTitle("Planificare Activitati Curente");
    this->resize(500, 350);
    QVBoxLayout* mainLayout = new QVBoxLayout{ this };

    tableCos = new QTableWidget{0, 3};
    QStringList headers = {"Titlu", "Tip", "Durata (min)"};
    tableCos->setHorizontalHeaderLabels(headers);
    tableCos->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableCos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(tableCos);

    lblTotal = new QLabel("Total activitati in lista: 0");
    mainLayout->addWidget(lblTotal);

    QHBoxLayout* topBtnsLayout = new QHBoxLayout;
    btnAdaugaTitlu = new QPushButton("Adauga dupa Titlu");
    btnGenereaza = new QPushButton("Genereaza Aleator");
    btnGoleste = new QPushButton("Goleste Lista");

    topBtnsLayout->addWidget(btnAdaugaTitlu);
    topBtnsLayout->addWidget(btnGenereaza);
    topBtnsLayout->addWidget(btnGoleste);
    mainLayout->addLayout(topBtnsLayout);

    QHBoxLayout* bottomBtnsLayout = new QHBoxLayout;
    btnExporta = new QPushButton("Exporta CSV / HTML");
    btnRaportCos = new QPushButton("Raport Tipuri (Lista)");

    bottomBtnsLayout->addWidget(btnExporta);
    bottomBtnsLayout->addWidget(btnRaportCos);
    mainLayout->addLayout(bottomBtnsLayout);
}

void PlanificareGUI::connectSignalsSlots() {
    QObject::connect(btnAdaugaTitlu, &QPushButton::clicked, [&]() {
        bool ok;
        QString titlu = QInputDialog::getText(this, "Adauga Activitate", "Titlul activitatii:", QLineEdit::Normal, "", &ok);
        if (ok && !titlu.isEmpty()) {
            try {
                srv.adauga_in_lista(titlu.toStdString());
                reloadCos();
            } catch (const RepoException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
        }
    });

    QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
        bool ok;
        int nr = QInputDialog::getInt(this, "Genereaza", "Numar activitati de generat:", 1, 1, 100, 1, &ok);
        if (ok) {
            srv.genereaza_lista(nr);
            reloadCos();
        }
    });

    QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
        srv.goleste_lista();
        reloadCos();
    });

    QObject::connect(btnExporta, &QPushButton::clicked, [&]() {
        bool ok;
        QString nume = QInputDialog::getText(this, "Exporta Lista", "Nume fisier (.csv sau .html):", QLineEdit::Normal, "lista.csv", &ok);
        if (ok && !nume.isEmpty()) {
            try {
                std::string filename = nume.toStdString();
                if (filename.find(".csv") != std::string::npos) {
                    srv.exporta_cos_cvs(filename);
                    QMessageBox::information(this, "Succes", "Export CSV realizat!");
                } else if (filename.find(".html") != std::string::npos) {
                    srv.exporta_cos_html(filename);
                    QMessageBox::information(this, "Succes", "Export HTML realizat!");
                } else {
                    QMessageBox::warning(this, "Eroare", "Extensie necunoscuta. Folositi .csv sau .html");
                }
            } catch (const RepoException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
        }
    });

    QObject::connect(btnRaportCos, &QPushButton::clicked, [&]() {
        auto raport = srv.raport_lista_curenta();
        if (raport.empty()) {
            QMessageBox::information(this, "Raport", "Lista curenta este goala!");
            return;
        }
        QString txt = "=== TIPURI IN LISTA CURENTA ===\n";
        for (const auto& p : raport) { txt += QString::fromStdString(p.first) + " -> " + QString::number(p.second) + "\n"; }
        QMessageBox::information(this, "Raport", txt);
    });
}

void PlanificareGUI::reloadCos() {
    tableCos->clearContents();
    const auto& lista = srv.get_lista_curenta();
    tableCos->setRowCount(lista.size());

    int row = 0;
    for (const auto& a : lista) {
        // Titlu
        QTableWidgetItem* itemTitlu = new QTableWidgetItem(QString::fromStdString(a.get_titlu()));
        itemTitlu->setFlags(itemTitlu->flags() ^ Qt::ItemIsEditable);
        tableCos->setItem(row, 0, itemTitlu);

        // Tip
        QTableWidgetItem* itemTip = new QTableWidgetItem(QString::fromStdString(a.get_tip()));
        itemTip->setFlags(itemTip->flags() ^ Qt::ItemIsEditable);
        tableCos->setItem(row, 1, itemTip);

        // Durata
        QTableWidgetItem* itemDurata = new QTableWidgetItem(QString::number(a.get_durata()));
        itemDurata->setFlags(itemDurata->flags() ^ Qt::ItemIsEditable);
        tableCos->setItem(row, 2, itemDurata);

        row++;
    }
    lblTotal->setText("Total activitati in lista: " + QString::number(lista.size()));
}