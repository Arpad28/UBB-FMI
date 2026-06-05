#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringList>
#include "../service/service.h"

class PlanificareGUI : public QWidget {
private:
    Service& srv;

    QTableWidget* tableCos;
    QLabel* lblTotal;

    QPushButton* btnAdaugaTitlu;
    QPushButton* btnGoleste;
    QPushButton* btnGenereaza;
    QPushButton* btnExporta;
    QPushButton* btnRaportCos;

    void initGUI();
    void connectSignalsSlots();
    void reloadCos();

public:
    PlanificareGUI(Service& srv);
};