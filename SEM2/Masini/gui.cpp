#include "gui.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QVBoxLayout>

GUI::GUI(Service& srv):srv(srv) {
    initGUI();
    connectsignals();
    reloadlist(srv.get_all());
}

void GUI::initGUI() {
    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    list=new QListWidget();
    mainlayout->addWidget(list);
    QVBoxLayout *btnlayout = new QVBoxLayout();

    txtDetalii = new QLineEdit();
    txtDetalii->setPlaceholderText("Număr matricol mașină selectată");
    txtDetalii->setReadOnly(true);
    btnlayout->addWidget(txtDetalii);

    btnsortaremodel= new QPushButton("Sortare Model");
    btnsortarenrmatricol= new QPushButton("Sortare NrMatricol");
    btnnesortat= new QPushButton("Nesortat");
    btnlayout->addWidget(btnsortaremodel);
    btnlayout->addWidget(btnsortarenrmatricol);
    btnlayout->addWidget(btnnesortat);
    mainlayout->addLayout(btnlayout);

    this->setWindowTitle("Meniu Masini");
    this->resize(600,400);
}

void GUI::connectsignals() {
    QObject::connect(btnsortaremodel,&QPushButton::clicked,[this]() {
        reloadlist(srv.sorteaza_model());
    });
    QObject::connect(btnsortarenrmatricol,&QPushButton::clicked,[this]() {
        reloadlist(srv.sorteaza_nrmatricol());
    });
    QObject::connect(btnnesortat,&QPushButton::clicked,[this]() {
        reloadlist(srv.get_all());
    });

    QObject::connect(list, &QListWidget::itemSelectionChanged, [this]() {
        if (list->selectedItems().isEmpty()) {
            txtDetalii->clear();
            return;
        }
        auto item = list->selectedItems().first()->data(Qt::UserRole).toInt();
        txtDetalii->setText(QString::number(item));
    });
}

void GUI::reloadlist(const std::vector<Masina>& masini) {
    list->clear();
    for (auto m : masini) {
        QString text=QString::fromStdString(m.get_model())+" |Km:"+QString::number(m.get_kmrulati());
        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole,m.get_nrmatricol());
        if (m.get_culoare()=="galben")
            item->setBackground(Qt::yellow);
        else if (m.get_culoare()=="albastru")
            item->setBackground(Qt::blue);
        else if (m.get_culoare()=="rosu")
            item->setBackground(Qt::red);
        else if (m.get_culoare()=="negru")
            item->setBackground(Qt::black);
        list->addItem(item);
    }
}