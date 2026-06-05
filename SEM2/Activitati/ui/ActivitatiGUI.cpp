#include "../ui/ActivitatiGUI.h"
#include "../ui/CosCRUDGUI.h"
#include "../ui/CosReadOnlyGUI.h"
#include "../domain/exceptii.h"
#include <map>
#include <string>

ActivitatiGUI::ActivitatiGUI(Service& srv) : srv{srv} {
    initGUI();
    connectSignalsSlots();
    reloadList(srv.get_all());
}

void ActivitatiGUI::initGUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout{ this };

    QVBoxLayout* leftLayout = new QVBoxLayout;

    // Initializare Model-View
    tableActivitati = new QTableView;
    tableModel = new ActivitatiTableModel;
    tableActivitati->setModel(tableModel);
    tableActivitati->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableActivitati->setSelectionMode(QAbstractItemView::SingleSelection);
    tableActivitati->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    leftLayout->addWidget(tableActivitati);
    QHBoxLayout* layoutLeftBtns = new QHBoxLayout;
    btnReload = new QPushButton("Afiseaza Toate");
    btnUndo = new QPushButton("Undo");
    layoutLeftBtns->addWidget(btnReload);
    layoutLeftBtns->addWidget(btnUndo);
    leftLayout->addLayout(layoutLeftBtns);

    mainLayout->addLayout(leftLayout);

    QVBoxLayout* rightLayout = new QVBoxLayout;

    QFormLayout* formLayout = new QFormLayout;
    txtId = new QLineEdit;
    txtTitlu = new QLineEdit;
    txtDescriere = new QLineEdit;
    txtTip = new QLineEdit;
    txtDurata = new QLineEdit;

    formLayout->addRow("ID:", txtId);
    formLayout->addRow("Titlu:", txtTitlu);
    formLayout->addRow("Descriere:", txtDescriere);
    formLayout->addRow("Tip:", txtTip);
    formLayout->addRow("Durata:", txtDurata);
    rightLayout->addLayout(formLayout);

    QHBoxLayout* btnCrudLayout = new QHBoxLayout;
    btnAdauga = new QPushButton("Adauga");
    btnModifica = new QPushButton("Modifica");
    btnSterge = new QPushButton("Sterge");
    btnCauta = new QPushButton("Cauta (dupa ID)");

    btnCrudLayout->addWidget(btnAdauga);
    btnCrudLayout->addWidget(btnModifica);
    btnCrudLayout->addWidget(btnSterge);
    btnCrudLayout->addWidget(btnCauta);
    rightLayout->addLayout(btnCrudLayout);

    QGroupBox* grpFiltre = new QGroupBox("Filtrare");
    QVBoxLayout* filtruLayout = new QVBoxLayout;
    txtFiltru = new QLineEdit;
    txtFiltru->setPlaceholderText("Introdu criteriul de filtrare...");
    QHBoxLayout* filtruBtnsLayout = new QHBoxLayout;
    btnFiltruDescriere = new QPushButton("Dupa Descriere");
    btnFiltruTip = new QPushButton("Dupa Tip");

    filtruBtnsLayout->addWidget(btnFiltruDescriere);
    filtruBtnsLayout->addWidget(btnFiltruTip);
    filtruLayout->addWidget(txtFiltru);
    filtruLayout->addLayout(filtruBtnsLayout);
    grpFiltre->setLayout(filtruLayout);
    rightLayout->addWidget(grpFiltre);

    QGroupBox* grpSort = new QGroupBox("Sortare");
    QHBoxLayout* sortLayout = new QHBoxLayout;
    btnSortTitlu = new QPushButton("Titlu");
    btnSortDescriere = new QPushButton("Descriere");
    btnSortTipDurata = new QPushButton("Tip+Durata");

    sortLayout->addWidget(btnSortTitlu);
    sortLayout->addWidget(btnSortDescriere);
    sortLayout->addWidget(btnSortTipDurata);
    grpSort->setLayout(sortLayout);
    rightLayout->addWidget(grpSort);

    btnRaport = new QPushButton("Raport Tipuri");
    btnFereastraPlanificare = new QPushButton("Meniu Vechi Planificare");

    // Butoanele noi pentru Observer
    btnDeschideCosCRUD = new QPushButton("Deschide Cos (Tabel + CRUD)");
    btnDeschideCosReadOnly = new QPushButton("Deschide Cos (Desene Read-Only)");

    rightLayout->addWidget(btnRaport);
    rightLayout->addWidget(btnFereastraPlanificare);

    // O linie separatoare vizuala pentru sectiunea Observer
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    rightLayout->addWidget(line);

    rightLayout->addWidget(btnDeschideCosCRUD);
    rightLayout->addWidget(btnDeschideCosReadOnly);

    mainLayout->addLayout(rightLayout);
}

void ActivitatiGUI::connectSignalsSlots() {
    // Selectia din tabel
    QObject::connect(tableActivitati->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        if (tableActivitati->selectionModel()->selectedIndexes().isEmpty()) {
            txtId->setText(""); txtTitlu->setText(""); txtDescriere->setText("");
            txtTip->setText(""); txtDurata->setText("");
            return;
        }
        int row = tableActivitati->selectionModel()->selectedIndexes().at(0).row();

        // Luam ID-ul direct din modelul nostru
        auto index = tableModel->index(row, 0);
        int id = tableModel->data(index, Qt::DisplayRole).toInt();

        try {
            Activitate a = srv.cauta(id);
            txtId->setText(QString::number(a.get_id()));
            txtTitlu->setText(QString::fromStdString(a.get_titlu()));
            txtDescriere->setText(QString::fromStdString(a.get_descriere()));
            txtTip->setText(QString::fromStdString(a.get_tip()));
            txtDurata->setText(QString::number(a.get_durata()));
        } catch (...) {}
    });

    // Buton Adauga
    QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
        try {
            srv.adauga(txtId->text().toInt(), txtTitlu->text().toStdString(),
                       txtDescriere->text().toStdString(), txtTip->text().toStdString(),
                       txtDurata->text().toInt());
            reloadList(srv.get_all());
            QMessageBox::information(this, "Succes", "Activitate adaugata!");
        } catch (const RepoException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
          catch (const ValidationException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
    });

    // Buton Modifica
    QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
        try {
            srv.modifica(txtId->text().toInt(), txtTitlu->text().toStdString(),
                         txtDescriere->text().toStdString(), txtTip->text().toStdString(),
                         txtDurata->text().toInt());
            reloadList(srv.get_all());
            QMessageBox::information(this, "Succes", "Activitate modificata!");
        } catch (const RepoException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
          catch (const ValidationException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
    });

    // Buton Sterge
    QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
        try {
            srv.sterge(txtId->text().toInt());
            reloadList(srv.get_all());
            QMessageBox::information(this, "Succes", "Activitate stearsa!");
        } catch (const RepoException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
    });

    // Buton Cauta
    QObject::connect(btnCauta, &QPushButton::clicked, [&]() {
        try {
            int id = txtId->text().toInt();
            Activitate a = srv.cauta(id);
            QMessageBox::information(this, "Gasit", "Titlu: " + QString::fromStdString(a.get_titlu()) +
                                     "\nDescriere: " + QString::fromStdString(a.get_descriere()));
        } catch (const RepoException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
    });

    // Undo
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            srv.undo();
            reloadList(srv.get_all());
            QMessageBox::information(this, "Succes", "Undo realizat!");
        } catch (const RepoException& e) { QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_mesaj())); }
    });

    // Reload list
    QObject::connect(btnReload, &QPushButton::clicked, [&]() { reloadList(srv.get_all()); });

    // Filtre
    QObject::connect(btnFiltruDescriere, &QPushButton::clicked, [&]() {
        reloadList(srv.filtreaza_descriere(txtFiltru->text().toStdString()));
    });
    QObject::connect(btnFiltruTip, &QPushButton::clicked, [&]() {
        reloadList(srv.filtreaza_tip(txtFiltru->text().toStdString()));
    });

    // Sortari
    QObject::connect(btnSortTitlu, &QPushButton::clicked, [&]() { reloadList(srv.sorteaza_titlu()); });
    QObject::connect(btnSortDescriere, &QPushButton::clicked, [&]() { reloadList(srv.sorteaza_descriere()); });
    QObject::connect(btnSortTipDurata, &QPushButton::clicked, [&]() { reloadList(srv.sorteaza_tip_durata()); });

    // Raport
    QObject::connect(btnRaport, &QPushButton::clicked, [&]() {
        auto raport = srv.raport();
        if (raport.empty()) {
            QMessageBox::information(this, "Raport", "Nu exista activitati.");
            return;
        }
        QString txt = "=== RAPORT TIPURI ===\n";
        for (const auto& p : raport) { txt += QString::fromStdString(p.first) + " -> " + QString::number(p.second) + "\n"; }
        QMessageBox::information(this, "Raport Tipuri", txt);
    });

    // Fereastra Veche Planificare
    QObject::connect(btnFereastraPlanificare, &QPushButton::clicked, [&]() {
        planificareFereastra = new PlanificareGUI(srv);
        planificareFereastra->show();
    });

    // Noile ferestre Observer
    QObject::connect(btnDeschideCosCRUD, &QPushButton::clicked, [&]() {
        auto fereastraCRUD = new CosCRUDGUI(srv);
        fereastraCRUD->setAttribute(Qt::WA_DeleteOnClose);
        fereastraCRUD->show();
    });

    QObject::connect(btnDeschideCosReadOnly, &QPushButton::clicked, [&]() {
        auto fereastraReadOnly = new CosReadOnlyGUI(srv);
        fereastraReadOnly->setAttribute(Qt::WA_DeleteOnClose);
        fereastraReadOnly->show();
    });
}

void ActivitatiGUI::reloadList(const std::vector<Activitate>& activitati) {
    // Delegam modelului sarcina de a notifica view-ul
    tableModel->setActivitati(activitati);
}