#pragma once
#include "service.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QAbstractTableModel>
#include <QWidget>
#include <vector>

class TableModel : public QAbstractTableModel {
private:
    std::vector<Apartament> apartamente;
public:
    TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setApartamente(const std::vector<Apartament>& ap) {
        beginResetModel();
        apartamente = ap;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return apartamente.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 3;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const auto& ap = apartamente[index.row()];
            if (index.column() == 0) return QString::fromStdString(ap.get_strada());
            if (index.column() == 1) return QString::number(ap.get_suprafata());
            if (index.column() == 2) return QString::number(ap.get_pret());
        }
        if (role == Qt::BackgroundRole) {
            const auto& ap = apartamente[index.row()];

            if (ap.get_suprafata() < 25) {
                return QBrush(Qt::red);
            } else {
                return QBrush(Qt::green);
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "Stradă";
            if (section == 1) return "Suprafață (m^2)";
            if (section == 2) return "Preț (Euro)";
        }
        return QVariant();
    }

    Apartament getApartament(int row) {
        return apartamente[row];
    }
};

class GUI : public QWidget {
private:
    Service& srv;
    QTableView* table;
    TableModel* model;

    QPushButton* btnfiltsupraf;
    QPushButton* btnfiltpret;
    QPushButton* btnnefiltrat;
    QPushButton* btnsterge;
    QLineEdit* supraf1;
    QLineEdit* supraf2;
    QLineEdit* pret1;
    QLineEdit* pret2;

    void initGUI();
    void connectsignals();
    void reloadlist(const std::vector<Apartament>& lista);

public:
    GUI(Service& srv);
};