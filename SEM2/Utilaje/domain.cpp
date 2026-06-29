#include "domain.h"

/*Creeaza un obiect de tip utilaj
 *id: numar natural pozitiv
 *denumire:string nevid
 *tip:string nevid
 *cilindrii:numar natural ce ia valori intre 1,2,4,8
 */
Utilaj::Utilaj(int id, std::string denumire, std::string tip, int cilindrii) 
    : id(id), denumire(denumire), tip(tip), cilindrii(cilindrii) {
}
/*Returneaza id ul utilajului
 */
int Utilaj::getId() const {
    return id;
}
/*Returneaza denumirea utilajului
 */
std::string Utilaj::getDenumire() const {
    return denumire;
}
/*Returneaza tipul utilajului
 */
std::string Utilaj::getTip() const {
    return tip;
}
/*Returneaza numarul de cilindrii a utilajului
 */
int Utilaj::getCilindrii() const {
    return cilindrii;
}
/*Seteaza denumirea utilajul cu cel nou
 *d: denumire noua-string nevid
 */
void Utilaj::setDenumire(const std::string& d) {
    denumire = d;
}
/*Seteaza tipul utilajului
 *t-tipul nou-string nevid
 */
void Utilaj::setTip(const std::string& t) {
    tip = t;
}
/*Seteaza numarul de cilindrii a utilajului
 *c-cilindrii noi,valori intre {1,2,4,8}
 */
void Utilaj::setCilindrii(int c) {
    cilindrii = c;
}