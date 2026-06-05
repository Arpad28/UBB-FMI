#pragma once
#include <QWidget>
#include <QPainter>
#include <random>
#include "Observer.h"
#include "../service/service.h"

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    Service& srv;
public:
    CosReadOnlyGUI(Service& srv) : srv{srv} {
        this->setWindowTitle("Cos ReadOnly - Desene");
        this->resize(400, 400);
        srv.addObserver(this);
    }

    ~CosReadOnlyGUI() {
        srv.removeObserver(this);
    }

    void update() override {
        repaint(); // declanseaza un nou paintEvent automat
    }

protected:
    // Am comentat /*ev*/ pentru a scapa de eroarea unused-parameter
    void paintEvent(QPaintEvent* /*ev*/) override {
        QPainter p{ this };

        int nrElemente = srv.get_lista_curenta().size();
        for (int i = 0; i < nrElemente; ++i) {
            int x = rand() % (this->width() - 50);
            int y = rand() % (this->height() - 50);

            p.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
            p.drawEllipse(x, y, 40, 40);
        }
    }
};