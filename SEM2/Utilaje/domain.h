#pragma once
#include <string>

/*Defineste clasa utilaj avand it,denumire,tip,cilindrii si functiile sale
 */
class Utilaj {
private:
    int id;
    std::string denumire;
    std::string tip;
    int cilindrii;
public:
    Utilaj(int id, std::string denumire, std::string tip, int cilindrii);

    int getId() const;
    std::string getDenumire() const;
    std::string getTip() const;
    int getCilindrii() const;

    void setDenumire(const std::string& d);
    void setTip(const std::string& t);
    void setCilindrii(int c);
};