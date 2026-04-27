from domain.sedinte import Sedinta
from repository.repo import Repo
from datetime import date

from validari.Validator import Validator


class Service:

    def __init__(self,repo:Repo):
        self.repo=repo

    def sedinte_maine(self):
        """Functia pune intr o lista toate sedintele care sunt maine
        :return: Returneaza o lista cu sedintele care sunt maine
        """
        data=date.today()
        rez=[]
        lista=self.repo.lista
        for sedinta in lista:
            if int(sedinta.get_luna())==data.month and int(sedinta.get_zi())-1==data.day:
                rez.append(sedinta)
        rez=sorted(rez,key=lambda sedinta:int(sedinta.get_ora()))
        return rez

    def adauga(self,zi,luna,ora,minute,subiect,tip):
        """Creaza un obiect de tip sedinta si le pune in fisier
        :param zi: Ziua sedintei
        :param luna: Luna sedintei
        :param ora: Ora sedintei
        :param minute: Minuta la care incepe sedinta
        :param subiect: Subiectul sedintei
        :param tip: Tipul sedintei
        :raises:Ridica ValueError daca datele sedintei sunt incorecte sau tipul sedintei e incorecta
        """
        if tip not in ["normal","extraordinara"]:
            raise ValueError("Nu exista sedinta de acest tip")
        valid = Validator(zi, luna, ora, minute)
        valid.valideaza()
        for sedinta in self.repo.get_all():
            if sedinta.get_tip()==tip and sedinta.get_subiect()==subiect:
                raise ValueError("Nu poate sa fie doua sedinte de acelasi fel cu aceleasi subiect")
        sedinta=Sedinta(zi,luna,ora,minute,subiect,tip)
        self.repo.adauga_sedinta(sedinta)

    def sedinte_setate(self,zi_setat,luna_setat):
        """Returneaza o lista cu toate sedintele care vor fi in urmatoarele trei zile de la data data
        :param zi_setat:Ziua de la care ma intereseaza sedintele
        :param luna_setat: Luna de la care ma intereseaza sedintele
        :return: Returneaza o lista cu sedintele in urmatoarele 3 zile sortate
        """
        rez = []
        lista = self.repo.lista
        for sedinta in lista:
            if int(sedinta.get_luna()) ==int(luna_setat) and int(zi_setat)<int(sedinta.get_zi())<=int(zi_setat)+3:
                rez.append(sedinta)
        rez = sorted(rez, key=lambda sedinta: int(sedinta.get_zi()))
        return rez

    def exporta_fisier(self,nume,sir):
        """Exporta intr un fisier cu numele 'nume' toate sedintele care contin in subiectul lui sirul de caractere 'sir'
        :param nume: Numele fisierului in care se exporta
        :param sir: Sirul de caractere ce trebuie sa fie in subiectul nostru
        """
        rez=[sedinta for sedinta in self.repo.get_all() if sir in str(sedinta.get_subiect())]
        rez = sorted(rez, key=lambda sedinta: int(sedinta.get_luna()) and int(sedinta.get_zi()) and int(sedinta.get_ora()) and int(sedinta.get_minute()))
        with open(f"{nume}", "w") as f:
            for sedinta in rez:
                f.write(
                    f"{sedinta.get_zi()}.{sedinta.get_luna()},{sedinta.get_ora()}:{sedinta.get_minute()},{sedinta.get_subiect()},{sedinta.get_tip()}\n")
