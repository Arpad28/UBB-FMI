#pragma once
#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPainter>
#include <QMap>
#include <vector>
#include "service.h"


/*Clasa pentru cercuri,tine minte frecventa fiecarei cilindru si deseanza un cerc pentru fiecare frecventa
 *pentru a putea face proportional vom inmulti diametrul cu numarul de elemente de aceas tip de cilindri
 */
class DrawWidget : public QWidget {
private:
    std::map<int, int> counts;
public:
    DrawWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumHeight(100);
    }

    void setCounts(const std::map<int, int>& noileCounts) {
        this->counts = noileCounts;
        update();
    }

protected:
    /*Painterul in sine,deseneaza cercuri pentru fiecare cilindru
     */
    void paintEvent(QPaintEvent* ev) override {
        QPainter p(this);
        int x = 0;
        std::vector<int> tipuri = {1, 2, 4, 8};
        
        for (int cil : tipuri) {
            int count = counts[cil];
            int diametru = count * 20;
            p.setBrush(Qt::red);
            p.drawEllipse(x, 20, diametru, diametru);
            x += 100;
        }
    }
};

/*Defineste clasa abstracta pentru Tabelul nostru avand 5 coloane
 */
class TableModel : public QAbstractTableModel {
private:
    std::vector<Utilaj> utilaje;
    std::map<std::string, int> nr_tip;
public:
    TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return utilaje.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= utilaje.size()) return QVariant();
        
        if (role == Qt::DisplayRole) {
            const auto& u = utilaje[index.row()];
            if (index.column() == 0) return QString::number(u.getId());
            if (index.column() == 1) return QString::fromStdString(u.getDenumire());
            if (index.column() == 2) return QString::fromStdString(u.getTip());
            if (index.column() == 3) return QString::number(u.getCilindrii());
            if (index.column() == 4) {
                auto it = nr_tip.find(u.getTip());
                return QString::number(it->second);
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Denumire";
            if (section == 2) return "Tip";
            if (section == 3) return "Cilindri";
            if (section == 4) return "Nr_aceeas_tip";
        }
        return QVariant();
    }

    void setDate(const std::vector<Utilaj>& data, const std::map<std::string, int>& counts) {
        beginResetModel();
        this->utilaje = data;
        this->nr_tip = counts;
        endResetModel();
    }
};

/*Clasa principala GUI care intializeaza fereastra
 */
class GUI : public QWidget {
private:
    Service& srv;
    
    QTableView* table;
    TableModel* model;

    QLineEdit* dunumire;
    QLineEdit* editTip;
    
    QRadioButton* rb1;
    QRadioButton* rb2;
    QRadioButton* rb4;
    QRadioButton* rb8;
    QButtonGroup* bgCilindri;

    QPushButton* btnUpdate;
    QPushButton* btnDelete;

    DrawWidget* drawWidget;
    int selectedId = -1;

    void initGui();
    void connectSignals();
    void reloadList();

public:
    GUI(Service& srv);
};