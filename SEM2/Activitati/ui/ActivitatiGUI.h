#pragma once
#include <QWidget>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QStringList>
#include "../service/service.h"
#include "../ui/PlanificareGUI.h"
#include "../ui/ActivitatiTableModel.h"

class ActivitatiGUI : public QWidget {
private:
    Service& srv;

    // Tabelul MVC inlocuieste vechiul QTableWidget
    QTableView* tableActivitati;
    ActivitatiTableModel* tableModel;

    QLineEdit* txtId;
    QLineEdit* txtTitlu;
    QLineEdit* txtDescriere;
    QLineEdit* txtTip;
    QLineEdit* txtDurata;

    // Butoane CRUD principale
    QPushButton* btnAdauga;
    QPushButton* btnModifica;
    QPushButton* btnSterge;
    QPushButton* btnCauta;
    QPushButton* btnUndo;
    QPushButton* btnReload;

    // Filtrare si Sortare
    QLineEdit* txtFiltru;
    QPushButton* btnFiltruDescriere;
    QPushButton* btnFiltruTip;
    QPushButton* btnSortTitlu;
    QPushButton* btnSortDescriere;
    QPushButton* btnSortTipDurata;

    QPushButton* btnRaport;
    
    // Fereastra veche de planificare
    QPushButton* btnFereastraPlanificare;
    PlanificareGUI* planificareFereastra;

    // Noile butoane pentru Observer (Cos)
    QPushButton* btnDeschideCosCRUD;
    QPushButton* btnDeschideCosReadOnly;

    void initGUI();
    void connectSignalsSlots();
    void reloadList(const std::vector<Activitate>& activitati);

public:
    ActivitatiGUI(Service& srv);
};