#include "gui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

MainGUI::MainGUI(Service& srv) : srv(srv) {
    initGUI();
    connectSignals();
    populeazaProcesoare();
    populeazaPlaci(srv.getPlaciDeBaza());
}

void MainGUI::initGUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    listProcesoare = new QListWidget();
    listPlaci = new QListWidget();
    mainLayout->addWidget(listProcesoare);
    mainLayout->addWidget(listPlaci);

    QVBoxLayout* rightLayout = new QVBoxLayout();

    QFormLayout* formLayout = new QFormLayout();
     txtNume = new QLineEdit();
     txtSoclu = new QLineEdit();
     txtPret = new QLineEdit();
     formLayout->addRow("Nume Placă:", txtNume);
     formLayout->addRow("Soclu Placă:", txtSoclu);
     formLayout->addRow("Preț Placă:", txtPret);
     rightLayout->addLayout(formLayout);

    btnAdauga = new QPushButton("Adaugă Placă de Bază");
    rightLayout->addWidget(btnAdauga);

    lblPretTotal = new QLabel("Preț Total selectat: 0 RON");
    rightLayout->addWidget(lblPretTotal);

    mainLayout->addLayout(rightLayout);
    this->setWindowTitle("Configurator Componente PC");
    this->resize(600, 400);
}

void MainGUI::connectSignals() {
    QObject::connect(listProcesoare, &QListWidget::itemSelectionChanged, this, &MainGUI::handlerFiltrareSiPret);
    QObject::connect(listPlaci, &QListWidget::itemSelectionChanged, this, &MainGUI::handlerFiltrareSiPret);
    QObject::connect(btnAdauga, &QPushButton::clicked, this, &MainGUI::handlerAdaugare);
}

void MainGUI::populeazaProcesoare() {
    listProcesoare->clear();
    for (const auto& p : srv.getProcesoare()) {
        QString itemText = QString::fromStdString(p.getNume() + " - " + std::to_string(p.getNumarThreaduri()));
        listProcesoare->addItem(itemText);
    }
}

void MainGUI::populeazaPlaci(const std::vector<PlacaDeBaza>& placi) {
    listPlaci->clear();
    for (const auto& p : placi) {
        QString itemText = QString::fromStdString(p.getNume());
        listPlaci->addItem(itemText);
    }
}

void MainGUI::handlerFiltrareSiPret() {
    int idxProc = listProcesoare->currentRow();

    if (idxProc >= 0 && !listPlaci->hasFocus()) {
        auto procSelectat = srv.getProcesoare()[idxProc];
        auto placiFiltrate = srv.filtreazaPlaciDupaSoclu(procSelectat.getSocluProcesor());
        populeazaPlaci(placiFiltrate);
    }
    double pretTotal = 0;
    int currentProcIdx = listProcesoare->currentRow();
    if (currentProcIdx >= 0) {
        pretTotal += srv.getProcesoare()[currentProcIdx].getPret();
    }

    int currentPlacaIdx = listPlaci->currentRow();
    if (currentPlacaIdx >= 0) {
        // Atenție: dacă lista e filtrată, indexul din listă corespunde listei filtrate!
        if (currentProcIdx >= 0) {
            auto proc = srv.getProcesoare()[currentProcIdx];
            auto placiFiltrate = srv.filtreazaPlaciDupaSoclu(proc.getSocluProcesor());
            pretTotal += placiFiltrate[currentPlacaIdx].getPret();
        } else {
            pretTotal += srv.getPlaciDeBaza()[currentPlacaIdx].getPret();
        }
    }

    lblPretTotal->setText(QString("Preț Total selectat: %1 RON").arg(pretTotal));
}

void MainGUI::handlerAdaugare() {
    std::string nume = txtNume->text().toStdString();
    std::string soclu = txtSoclu->text().toStdString();
    double pret = txtPret->text().toDouble();

    try {
        srv.adaugaPlacaDeBaza(nume, soclu, pret);
        populeazaPlaci(srv.getPlaciDeBaza());
        txtNume->clear(); txtSoclu->clear(); txtPret->clear();
        QMessageBox::information(this, "Succes", "Placa de baza a fost adăugată!");
    } catch (std::runtime_error& e) {
        QMessageBox::critical(this, "Eroare", e.what());
    }
}