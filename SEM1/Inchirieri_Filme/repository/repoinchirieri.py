from domain.inchiriere import Inchiriere

from validator.validatorinchiriere import ValidatorInchiriere

class RepoInchirieri:
    def __init__(self):
        """Initializam o lista in care vom stoca inchirierile"""
        self.__inchirieri=[]
        self.__istoric=[]

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

    def cauta_inchiriere(self,id_inchiriere):
        """Cauta o inchiriere dupa id ul dat
        :param id_inchiriere: Id inchiriere dupa care se cauta
        """
        for x in self.__inchirieri:
            if x.get_id_inchiriere()==id_inchiriere and x.get_data_returnarii() is None:
                return x
        raise ValueError("Nu există închiriere cu acest ID")

    def actualizeaza(self, inchiriere,data):
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
