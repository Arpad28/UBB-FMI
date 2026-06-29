#pragma once
#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QPainter>
#include <QMouseEvent>
#include <QBrush>
#include <functional>
#include <vector>
#include "service.h"

// ==========================================
// Widget Custom pentru desenat roti
// ==========================================
class DrawWidget : public QWidget {
public:
    int selectedId = -1;
    int numRoti = 0;
    std::function<void(int)> onWheelClicked;

    DrawWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumHeight(60);
    }

    void setTractor(int id, int roti) {
        selectedId = id;
        numRoti = roti;
        update(); // forteaza redesenarea
    }

protected:
    void paintEvent(QPaintEvent* ev) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(Qt::black);
        
        int startX = 20;
        int radius = 15;
        // Desenam 'numRoti' cercuri
        for (int i = 0; i < numRoti; i++) {
            p.drawEllipse(startX + i * (radius * 2 + 10), 15, radius * 2, radius * 2);
        }
    }

    void mousePressEvent(QMouseEvent* ev) override {
        if (selectedId == -1) return;
        
        int x = ev->pos().x();
        int y = ev->pos().y();
        int radius = 15;
        
        for (int i = 0; i < numRoti; i++) {
            int cx = 20 + i * (radius * 2 + 10) + radius;
            int cy = 15 + radius;
            // Distanta de la click la centrul cercului
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius) {
                if (onWheelClicked) {
                    onWheelClicked(selectedId);
                }
                break;
            }
        }
    }
};

// ==========================================
// DECLARARE SI IMPLEMENTARE TractorTableModel
// ==========================================
class TractorTableModel : public QAbstractTableModel {
private:
    std::vector<Tractor> tractoare;
    std::map<std::string, int> counts;
    std::string highlightedTip;
public:
    TractorTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return tractoare.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= tractoare.size()) return QVariant();
        
        const auto& t = tractoare[index.row()];
        
        // Colorare cu rosu daca tipul se potriveste cu combobox-ul
        if (role == Qt::BackgroundRole) {
            if (!highlightedTip.empty() && t.getTip() == highlightedTip) {
                return QBrush(Qt::red);
            }
        }

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return QString::number(t.getId());
            if (index.column() == 1) return QString::fromStdString(t.getDenumire());
            if (index.column() == 2) return QString::fromStdString(t.getTip());
            if (index.column() == 3) return QString::number(t.getNumarRoti());
            if (index.column() == 4) {
                auto it = counts.find(t.getTip());
                if (it != counts.end()) return QString::number(it->second);
                return "0";
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Denumire";
            if (section == 2) return "Tip";
            if (section == 3) return "Nr. Roti";
            if (section == 4) return "Total Acelasi Tip";
        }
        return QVariant();
    }

    void setDate(const std::vector<Tractor>& newTractoare, const std::map<std::string, int>& newCounts) {
        beginResetModel();
        this->tractoare = newTractoare;
        this->counts = newCounts;
        endResetModel();
    }

    void setHighlightedTip(const std::string& tip) {
        this->highlightedTip = tip;
        emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
    }
};

// ==========================================
// DECLARARE GUI
// ==========================================
class GUI : public QWidget {
private:
    Service& srv;
    
    QTableView* table;
    TractorTableModel* model;

    QLineEdit* editId;
    QLineEdit* editDenumire;
    QLineEdit* editTip;
    QLineEdit* editRoti;
    QPushButton* btnAdd;

    QComboBox* comboTip;
    DrawWidget* drawWidget;

    void initGui();
    void connectSignals();
    void reloadList();
    void populateCombo();

public:
    GUI(Service& srv);
};