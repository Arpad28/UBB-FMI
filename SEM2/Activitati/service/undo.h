#pragma once
#include "../domain/activitate.h"
#include "../repo/repository.h"

// Clasa abstracta pentru Actiune Undo
class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    // Destructorul virtual este obligatoriu pentru polimorfism
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    Repo& rep;              // Am mutat Repo sus
    Activitate actAdaugata; // Am mutat Activitate jos
public:
    UndoAdauga(Repo& rep, const Activitate& act) : rep{ rep }, actAdaugata{ act } {}
    void doUndo() override {
        rep.sterge(actAdaugata.get_id());
    }
};

class UndoSterge : public ActiuneUndo {
private:
    Repo& rep;
    Activitate actStearsa;
public:
    UndoSterge(Repo& rep, const Activitate& act) : rep{ rep }, actStearsa{ act } {}
    void doUndo() override {
        rep.adauga(actStearsa);
    }
};

class UndoModifica : public ActiuneUndo {
private:
    Repo& rep;
    Activitate actVeche;
public:
    UndoModifica(Repo& rep, const Activitate& act) : rep{ rep }, actVeche{ act } {}
    void doUndo() override {
        rep.modifica(actVeche);
    }
};