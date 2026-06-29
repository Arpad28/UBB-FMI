#include "ui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>

GUI::GUI(Service& srv) : srv(srv) {
    initGui();
    connectSignals();
    reloadList(srv.get_all_sorted());
}

void GUI::initGui() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    table = new QTableView();
    model = new GameTableModel(this);
    table->setModel(model);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(table);

    QVBoxLayout* rightLayout = new QVBoxLayout();

    QFormLayout* createLayout = new QFormLayout();
    createDim = new QLineEdit();
    createPlayer = new QLineEdit();
    btnCreate = new QPushButton("Creare Joc");
    createLayout->addRow("Dimensiune:", createDim);
    createLayout->addRow("Jucator (X/O):", createPlayer);
    createLayout->addWidget(btnCreate);
    rightLayout->addLayout(createLayout);

    QFormLayout* modLayout = new QFormLayout();
    modId = new QLineEdit(); modId->setReadOnly(true);
    modDim = new QLineEdit();
    modBoard = new QLineEdit();
    modPlayer = new QLineEdit();
    modStatus = new QLineEdit();
    btnModify = new QPushButton("Modifica Joc");

    modLayout->addRow("ID Selectat:", modId);
    modLayout->addRow("Dimensiune:", modDim);
    modLayout->addRow("Tabla:", modBoard);
    modLayout->addRow("Jucator:", modPlayer);
    modLayout->addRow("Stare:", modStatus);
    modLayout->addWidget(btnModify);
    rightLayout->addLayout(modLayout);

    // Tabla de joc
    boardWidget = new QWidget();
    boardLayout = new QGridLayout(boardWidget);
    rightLayout->addWidget(boardWidget);

    mainLayout->addLayout(rightLayout);
}

void GUI::connectSignals() {
    QObject::connect(btnCreate, &QPushButton::clicked, [this]() {
        try {
            int dim = createDim->text().toInt();
            char p = createPlayer->text().toStdString()[0];
            srv.createGame(dim, p);
            reloadList(srv.get_all_sorted());
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Eroare", e.what());
        }
    });

    QObject::connect(btnModify, &QPushButton::clicked, [this]() {
        try {
            int id = modId->text().toInt();
            int dim = modDim->text().toInt();
            std::string board = modBoard->text().toStdString();
            char p = modPlayer->text().toStdString()[0];
            std::string status = modStatus->text().toStdString();

            srv.updateGame(id, dim, board, p, status);
            reloadList(srv.get_all_sorted());
            setupBoard(srv.cauta(id));
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Eroare", e.what());
        }
    });

    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        QModelIndexList selected = table->selectionModel()->selectedRows();
        if (selected.isEmpty()) return;

        int row = selected.first().row();
        int id = table->model()->index(row, 0).data().toInt();
        selectedGameId = id;

        Game g = srv.cauta(id);
        modId->setText(QString::number(g.getId()));
        modDim->setText(QString::number(g.getDim()));
        modBoard->setText(QString::fromStdString(g.getBoard()));
        modPlayer->setText(QString(g.getNextPlayer()));
        modStatus->setText(QString::fromStdString(g.getStatus()));

        setupBoard(g);
    });
}

void GUI::setupBoard(const Game& g) {
    QLayoutItem* item;
    while ((item = boardLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    int dim = g.getDim();
    std::string board = g.getBoard();

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            char val = board[i * dim + j];
            QPushButton* btn = new QPushButton(QString(val == '-' ? ' ' : val));
            btn->setFixedSize(50, 50);

            QObject::connect(btn, &QPushButton::clicked, [this, i, j]() {
                if (selectedGameId != -1) {
                    srv.playMove(selectedGameId, i, j);
                    reloadList(srv.get_all_sorted());
                    setupBoard(srv.cauta(selectedGameId));
                }
            });

            boardLayout->addWidget(btn, i, j);
        }
    }
}

void GUI::reloadList(const std::vector<Game>& lista) {
    model->setGames(lista);
}