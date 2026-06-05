#pragma once
#include <string>

using std::string;

class Activitate {
private:
    int id;
    string titlu, descriere, tip;
    int durata;

public:
    Activitate();
    Activitate(int id, const string& t, const string& d, const string& tip, int durata);
    Activitate(const Activitate& ot);
    Activitate& operator=(const Activitate& ot);

    int get_id() const;
    string get_titlu() const;
    string get_descriere() const;
    string get_tip() const;
    int get_durata() const;
};