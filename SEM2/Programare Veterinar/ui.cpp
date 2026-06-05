#include "ui.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QFormLayout>
#include <QVBoxLayout>

GUI::GUI(Service& srv):srv(srv) {
    initGui();
    connectsignals();
    reloadlist(srv.get_all());
}

void GUI::initGui() {
    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    table=new QTableWidget();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Cod","Nume animal","Specie","Tip consultatie","Pret"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainlayout->addWidget(table);

    QVBoxLayout *btnlayout = new QVBoxLayout();
    QFormLayout* layout=new QFormLayout();
    specie=new QLineEdit();
    layout->addRow("Specie",specie);
    btnlayout->addLayout(layout);
    text = new QTextEdit();
    text->setReadOnly(true);
    btnlayout->addWidget(new QLabel("Detalii consultatie selectata"));
    btnlayout->addWidget(text);

    QFormLayout* programare_layout = new QFormLayout();
    cod_input = new QLineEdit();
    numar_input = new QLineEdit();
    programare_layout->addRow("Cod:", cod_input);
    programare_layout->addRow("Numar programari:", numar_input);
    btnlayout->addLayout(programare_layout);

    btn_programeaza = new QPushButton("Programeaza");
    lbl_rezultat = new QLabel("Cost total: -");
    btnlayout->addWidget(btn_programeaza);
    btnlayout->addWidget(lbl_rezultat);

    mainlayout->addLayout(btnlayout);
}

void GUI::connectsignals() {
    QObject::connect(specie, &QLineEdit::textChanged, [this]() {
        reloadlist(srv.filt_specie(specie->text().toStdString()));
    });

    QObject::connect(table, &QTableWidget::itemSelectionChanged, [this]() {
        if (table->selectedItems().isEmpty()) {
            text->clear();
            return;
        }
        auto linie=table->selectedItems().first()->row();
        QString cod = table->item(linie, 0)->text();
        QString nume = table->item(linie, 1)->text();
        QString specie = table->item(linie, 2)->text();
        QString tip = table->item(linie, 3)->text();
        QString pret = table->item(linie, 4)->text();
        QString detalii = "Cod: " + cod + "\nNume animal: " + nume + "\nSpecie: " + specie + "\nTip: " + tip + "\nPret: " + pret;
        text->setText(detalii);
    });

    QObject::connect(btn_programeaza, &QPushButton::clicked, [this]() {
            if (cod_input->text().isEmpty() || numar_input->text().isEmpty()) {
                lbl_rezultat->setText("Cost total: -");
                QMessageBox::warning(this, "Eroare", "Nu ai introdus destule date");
              return;
            }
            std::string cod = cod_input->text().toStdString();
            int numar = numar_input->text().toInt();
            if (numar <= 0) {
                QMessageBox::warning(this, "Eroare", "Numarul trebuie sa fie strict pozitiv!");
                return;
            }
            cabinet c = srv.cauta(cod);
            int total = c.get_pret() * numar;
            QString detalii = "Consultatie: " + QString::fromStdString(c.get_tip()) +
                              "\nCost total: " + QString::number(total);
            lbl_rezultat->setText(detalii);
    });
}

void GUI::reloadlist(const std::vector<cabinet>&lista) {
    table->clearContents();
    table->setRowCount(0);

    for (const auto& cab : lista) {
        int row = table->rowCount();
        table->insertRow(row);
        QTableWidgetItem* itemcod = new QTableWidgetItem(QString::fromStdString(cab.get_cod()));
        QTableWidgetItem* itemnume = new QTableWidgetItem(QString::fromStdString(cab.get_nume()));
        QTableWidgetItem* itemspecie = new QTableWidgetItem(QString::fromStdString(cab.get_specie()));
        QTableWidgetItem* itemconsultatie = new QTableWidgetItem(QString::fromStdString(cab.get_tip()));
        QTableWidgetItem* itempret = new QTableWidgetItem(QString::number(cab.get_pret()));

        table->setItem(row, 0, itemcod);
        table->setItem(row, 1, itemnume);
        table->setItem(row, 2, itemspecie);
        table->setItem(row,3, itemconsultatie);
        table->setItem(row, 4, itempret);
    }
}