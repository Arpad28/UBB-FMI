from domain.inchiriere import Inchiriere
from datetime import date
from validator.validatorinchiriere import ValidatorInchiriere

class RepoFisierInchirieri:
    def __init__(self,calea_catre_fisier):
        """Initializam o lista in care vom stoca inchirierile"""
        self.__inchirieri=[]
        self.__istoric=[]
        self.__calea_catre_fisier = calea_catre_fisier
        self.__citeste_fisier()

    def __citeste_fisier(self):
        with open(self.__calea_catre_fisier,'r') as f:
            self.__inchirieri=[]
            linii=f.readlines()
            for linie in linii:
                linie=linie.strip()
                if linie!="":
                    valori=linie.split(",")
                    id_inchiriere,id_film,id_client,an_inch,luna_inch,zi_inch,an_ret,luna_ret,zi_ret=valori
                    data_inch=date(int(an_inch),int(luna_inch),int(zi_inch))
                    if an_ret!="-":
                        data_ret=date(int(an_ret),int(luna_ret),int(zi_ret))
                    else:
                        data_ret=None
                    inchiriere=Inchiriere(id_inchiriere,id_film,id_client,data_inch,data_ret)
                    self.__inchirieri.append(inchiriere)
                    self.__istoric.append(inchiriere)

    def __salveaza_in_fisier(self):
        with open(self.__calea_catre_fisier, "w") as f:
            for inch in self.__inchirieri:
                data_i = inch.get_data_inchirierii()
                di = f"{data_i.year},{data_i.month},{data_i.day}"
                data_r = inch.get_data_returnarii()
                if data_r is None:
                    dr = "-,-,-"
                else:
                    dr = f"{data_r.year},{data_r.month},{data_r.day}"
                linie = f"{inch.get_id_inchiriere()},{inch.get_id_film()},{inch.get_id_client()},{di},{dr}\n"
                f.write(linie)

    def adauga_inchiriere(self,inchiriere:Inchiriere):
        """Adauga in lista un obiect de tip inchiriere
        :param inchiriere: Obiect de tip inchiriere
        """
        for x in self.__inchirieri:
            if x.get_id_inchiriere()==inchiriere.get_id_inchiriere() and x.get_data_returnarii() is None:
                raise ValueError("ID închiriere deja existent")
        ValidatorInchiriere(inchiriere).valideaza_inchiriere()
        self.__inchirieri.append(inchiriere)
        self.__istoric.append(inchiriere)
        self.__salveaza_in_fisier()

    def cauta_inchiriere(self,id_inchiriere):
        """Cauta o inchiriere dupa id ul dat
        :param id_inchiriere: Id inchiriere dupa care se cauta
        """
        for x in self.__inchirieri:
            if x.get_id_inchiriere()==id_inchiriere and x.get_data_returnarii() is None:
                return x
        raise ValueError("Nu există închiriere cu acest ID")

    def actualizeaza(self, inchiriere, data):
        """Actualizaza un obiect de tip inchiriere"""
        id_inchiriere = inchiriere.get_id_inchiriere()
        gasit = False
        for x in self.__inchirieri:
            if x.get_id_inchiriere() == id_inchiriere and x.get_data_returnarii() is None:
                x.set_data_returnarii(data)
                ValidatorInchiriere(inchiriere).valideaza_inchiriere()
                gasit = True
        if not gasit:
            raise ValueError("Nu există închiriere cu acest ID")
        self.__salveaza_in_fisier()

    def sterge_inchiriere(self, id_inchiriere):
        """Șterge închirierea cu ID dat"""
        lista_noua = []
        gasit = False
        for x in self.__inchirieri:
            if x.get_id_inchiriere() == id_inchiriere:
                gasit = True
            else:
                lista_noua.append(x)
        if not gasit:
            raise ValueError("Nu există închiriere cu acest ID")
        self.__inchirieri = lista_noua
        self.__salveaza_in_fisier()

    def get_all_inchiriere(self):
        """Returneaza lista de inchirieri"""
        if self.__inchirieri:
            return self.__inchirieri
        else:
            raise ValueError("Nu există închirieri făcute")

    def numar_inchirieri_client_film(self,id_client,id_film):
        suma=0
        for x in self.__istoric:
            if x.get_id_inchiriere() == id_client and x.get_id_film() == id_film:
                suma+=1
        return suma
