#pragma once
#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "service.h"


class GameTableModel : public QAbstractTableModel {
private:
    std::vector<Game> games;
public:
    GameTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return games.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const auto& g = games[index.row()];
            if (index.column() == 0) return QString::number(g.getId());
            if (index.column() == 1) return QString::number(g.getDim());
            if (index.column() == 2) return QString::fromStdString(g.getBoard());
            if (index.column() == 3) return QString(g.getNextPlayer());
            if (index.column() == 4) return QString::fromStdString(g.getStatus());
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Dimensiune";
            if (section == 2) return "Tabla";
            if (section == 3) return "Jucator Urm.";
            if (section == 4) return "Stare";
        }
        return QVariant();
    }

    void setGames(const std::vector<Game>& newGames) {
        beginResetModel();
        this->games = newGames;
        endResetModel();
    }
};

class GUI : public QWidget {
private:
    Service& srv;

    QTableView* table;
    GameTableModel* model;

    // Controale Creare
    QLineEdit* createDim;
    QLineEdit* createPlayer;
    QPushButton* btnCreate;

    // Controale Modificare
    QLineEdit* modId;
    QLineEdit* modDim;
    QLineEdit* modBoard;
    QLineEdit* modPlayer;
    QLineEdit* modStatus;
    QPushButton* btnModify;

    // Zona Tablei de joc
    QWidget* boardWidget;
    QGridLayout* boardLayout;
    int selectedGameId = -1;

    void initGui();
    void connectSignals();
    void reloadList(const std::vector<Game>& lista);
    void setupBoard(const Game& g);

public:
    GUI(Service& srv);
};