#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "../domain/activitate.h"

class ActivitatiTableModel : public QAbstractTableModel {
private:
    std::vector<Activitate> activitati;
public:
    ActivitatiTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setActivitati(const std::vector<Activitate>& noiActivitati) {
        beginResetModel();
        activitati = noiActivitati;
        endResetModel();
    }

    int rowCount(const QModelIndex& /*parent*/ = QModelIndex()) const override {
        return activitati.size();
    }

    int columnCount(const QModelIndex& /*parent*/ = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const auto& a = activitati[index.row()];
            switch (index.column()) {
                case 0: return QString::number(a.get_id());
                case 1: return QString::fromStdString(a.get_titlu());
                case 2: return QString::fromStdString(a.get_descriere());
                case 3: return QString::fromStdString(a.get_tip());
                case 4: return QString::number(a.get_durata());
            }
        }
        return QVariant{};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "ID";
                case 1: return "Titlu";
                case 2: return "Descriere";
                case 3: return "Tip";
                case 4: return "Durata";
            }
        }
        return QVariant{};
    }
};