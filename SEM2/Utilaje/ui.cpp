#include "ui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>
#include <QGroupBox>

/*Constructor GUI avand referinta la service
 */
GUI::GUI(Service& srv) : srv(srv) {
    initGui();
    connectSignals();
    reloadList();
}

/*Initializam fereastra principala
 */
void GUI::initGui() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();

    table = new QTableView();
    model = new TableModel(this);
    table->setModel(model);           
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    topLayout->addWidget(table);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    QFormLayout* formLayout = new QFormLayout();
    
    dunumire = new QLineEdit();
    editTip = new QLineEdit();
    formLayout->addRow("Denumire:", dunumire);
    formLayout->addRow("Tip:", editTip);

    QGroupBox* grup = new QGroupBox("Numar Cilindri");
    QVBoxLayout* cilLayout = new QVBoxLayout();
    rb1 = new QRadioButton("1");
    rb2 = new QRadioButton("2");
    rb4 = new QRadioButton("4");
    rb8 = new QRadioButton("8");
    
    bgCilindri = new QButtonGroup(this);
    bgCilindri->addButton(rb1, 1);
    bgCilindri->addButton(rb2, 2);
    bgCilindri->addButton(rb4, 4);
    bgCilindri->addButton(rb8, 8);

    cilLayout->addWidget(rb1);
    cilLayout->addWidget(rb2);
    cilLayout->addWidget(rb4);
    cilLayout->addWidget(rb8);
    grup->setLayout(cilLayout);
    
    formLayout->addRow(grup);

    btnUpdate = new QPushButton("Actualizeaza");
    btnDelete = new QPushButton("Sterge");
    
    rightLayout->addLayout(formLayout);
    rightLayout->addWidget(btnUpdate);
    rightLayout->addWidget(btnDelete);

    topLayout->addLayout(rightLayout);
    mainLayout->addLayout(topLayout);

    drawWidget = new DrawWidget();
    mainLayout->addWidget(drawWidget);
}

/*Conectam semnalele pentru fiecare interactiune a utilizatorului
 */
void GUI::connectSignals() {
    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        QModelIndexList selected = table->selectionModel()->selectedRows();
        if (selected.isEmpty()) {
            selectedId = -1;
            dunumire->clear();
            editTip->clear();
            return;
        }
        int row = selected.first().row();
        selectedId = table->model()->index(row, 0).data().toInt();
        QString denumire = table->model()->index(row, 1).data().toString();
        QString tip = table->model()->index(row, 2).data().toString();
        int cilindri = table->model()->index(row, 3).data().toInt();
        dunumire->setText(denumire);
        editTip->setText(tip);
        if (cilindri == 1) rb1->setChecked(true);
        else if (cilindri == 2) rb2->setChecked(true);
        else if (cilindri == 4) rb4->setChecked(true);
        else if (cilindri == 8) rb8->setChecked(true);
    });

    QObject::connect(btnDelete, &QPushButton::clicked, [this]() {
        if (selectedId == -1) {
            QMessageBox::warning(this, "Eroare", "Nu ai selectat niciun utilaj");
            return;
        }
        try {
            srv.stergeUtilaj(selectedId);
            reloadList();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Eroare", e.what());
        }
    });

    QObject::connect(btnUpdate, &QPushButton::clicked, [this]() {
        if (selectedId == -1) {
            QMessageBox::warning(this, "Eroare", "Nu ai selectat niciun utilaj");
            return;
        }

        std::string denumire_noua = dunumire->text().toStdString();
        std::string tip_nou = editTip->text().toStdString();
        int noiCilindri = -1;
        if (bgCilindri->checkedId() != -1) {
            noiCilindri = bgCilindri->checkedId();
        }

        try {
            srv.updateUtilaj(selectedId, denumire_noua, tip_nou, noiCilindri);
            reloadList();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Eroare", e.what());
        }
    });
}

/*La fiecare modificare reincarcam atat tabelul cat si painterul
 */
void GUI::reloadList() {
    model->setDate(srv.get_all_sortat(), srv.get_nr_tip());
    drawWidget->setCounts(srv.get_nr_cilindrii());
}