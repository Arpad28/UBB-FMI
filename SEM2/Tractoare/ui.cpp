#include "ui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>

GUI::GUI(Service& srv) : srv(srv) {
    initGui();
    connectSignals();
    reloadList();
    populateCombo();
}

void GUI::initGui() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();

    // Stanga - Tabel
    table = new QTableView();
    model = new TractorTableModel(this); 
    table->setModel(model);           
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    topLayout->addWidget(table);

    // Dreapta - Formular adaugare + ComboBox
    QVBoxLayout* rightLayout = new QVBoxLayout();

    QFormLayout* formLayout = new QFormLayout();
    editId = new QLineEdit();
    editDenumire = new QLineEdit();
    editTip = new QLineEdit();
    editRoti = new QLineEdit();
    btnAdd = new QPushButton("Adauga Tractor");

    formLayout->addRow("ID:", editId);
    formLayout->addRow("Denumire:", editDenumire);
    formLayout->addRow("Tip:", editTip);
    formLayout->addRow("Nr. Roti (par, 2-16):", editRoti);
    formLayout->addWidget(btnAdd);
    rightLayout->addLayout(formLayout);

    rightLayout->addSpacing(20);
    rightLayout->addWidget(new QLabel("Evidentiere Tip:"));
    comboTip = new QComboBox();
    rightLayout->addWidget(comboTip);
    
    topLayout->addLayout(rightLayout);
    mainLayout->addLayout(topLayout);

    // Jos - Zona de desenare roti
    drawWidget = new DrawWidget();
    mainLayout->addWidget(new QLabel("Roti (click pe cerc pentru a sterge 2 roti):"));
    mainLayout->addWidget(drawWidget);
}

void GUI::connectSignals() {
    QObject::connect(btnAdd, &QPushButton::clicked, [this]() {
        try {
            int id = editId->text().toInt();
            std::string denumire = editDenumire->text().toStdString();
            std::string tip = editTip->text().toStdString();
            int roti = editRoti->text().toInt();
            
            srv.addTractor(id, denumire, tip, roti);
            
            // Dupa adaugare updatam lista si tipurile din combobox
            reloadList();
            populateCombo(); 
            
            // Golire campuri
            editId->clear(); editDenumire->clear(); editTip->clear(); editRoti->clear();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Erori Validare", e.what()); // Afiseaza toate problemele
        }
    });

    QObject::connect(comboTip, &QComboBox::currentTextChanged, [this](const QString& text) {
        model->setHighlightedTip(text.toStdString()); // Coloreaza randurile in rosu
    });

    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        QModelIndexList selected = table->selectionModel()->selectedRows();
        if (selected.isEmpty()) {
            drawWidget->setTractor(-1, 0);
            return;
        }
        int row = selected.first().row();
        int id = table->model()->index(row, 0).data().toInt();
        int roti = table->model()->index(row, 3).data().toInt();
        
        drawWidget->setTractor(id, roti);
    });

    // Callback pentru a intercepta click-urile de pe rotile desenate
    drawWidget->onWheelClicked = [this](int id) {
        srv.decrementWheels(id); // Reflecta in fisier
        reloadList();
        
        // Re-actualizam widget-ul cu numarul nou de roti
        Tractor t = srv.cauta(id);
        drawWidget->setTractor(id, t.getNumarRoti());
    };
}

void GUI::reloadList() {
    model->setDate(srv.get_all_sorted(), srv.get_tip_counts());
}

void GUI::populateCombo() {
    QString curent = comboTip->currentText(); // Pastram selectia curenta
    comboTip->clear();
    for (const auto& tip : srv.get_distinct_types()) {
        comboTip->addItem(QString::fromStdString(tip));
    }
    // Repunem selectia inapoi daca mai exista
    int idx = comboTip->findText(curent);
    if (idx != -1) comboTip->setCurrentIndex(idx);
}