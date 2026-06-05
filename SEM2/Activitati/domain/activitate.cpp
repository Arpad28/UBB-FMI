#include "activitate.h"
#include <iostream>

Activitate::Activitate() : id(-1), durata(0) {}

Activitate::Activitate(int id, const string& t, const string& d, const string& tip, int durata)
    : id(id), titlu(t), descriere(d), tip(tip), durata(durata) {}

Activitate::Activitate(const Activitate& ot)
    : id(ot.id), titlu(ot.titlu), descriere(ot.descriere), tip(ot.tip), durata(ot.durata) {}

Activitate& Activitate::operator=(const Activitate& ot) {
    id = ot.id;
    titlu = ot.titlu;
    descriere = ot.descriere;
    tip = ot.tip;
    durata = ot.durata;
    return *this;
}

int Activitate::get_id() const { return id; }
string Activitate::get_titlu() const { return titlu; }
string Activitate::get_descriere() const { return descriere; }
string Activitate::get_tip() const { return tip; }
int Activitate::get_durata() const { return durata; }