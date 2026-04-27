from domain.client import Client
from validator.validatorclient import ValidatorClient


class RepoFisierClienti:

    def __init__(self,calea_catre_fisier):
        """Initializeaza o lista in care vom stoca obiectele de tip client"""
        self.__clienti=[]
        self.__calea_catre_fisier=calea_catre_fisier
        self.__citeste_fisier()

    def __citeste_fisier(self):
        with open(self.__calea_catre_fisier,'r') as f:
            self.__clienti=[]
            linii=f.readlines()
            for linie in linii:
                linie=linie.strip()
                if linie!="":
                    valori=linie.split(",")
                    id_client,nume_client,cnp_client,nr_inchiriat=valori
                    client=Client(id_client,nume_client,cnp_client)
                    client.set_nr_inchiriate(int(nr_inchiriat))
                    self.__clienti.append(client)

    def __scrie_fisier(self):
        with open(self.__calea_catre_fisier,'w') as f:
            for c in self.__clienti:
                f.write(f"{c.get_id_client()},{c.get_nume_client()},{c.get_cnp_client()},{c.get_nr_inchiriate()}\n")

    def adauga_client(self,client:Client):
        """Adauga un client validat in lista
        :param client: Obiect de tip client
        """
        for x in self.__clienti:
            if x.get_id_client()==client.get_id_client():
                raise ValueError("Client cu acest ID deja existent")
            if x.get_cnp_client()==client.get_cnp_client():
                raise ValueError("Client cu acest CNP deja existent")
        ValidatorClient(client).valideaza_client()
        self.__clienti.append(client)
        self.__scrie_fisier()

    def sterge_client(self,id_client):
        """Sterge un client existent din lista
        :param id_client: Id client de sters
        """
        lista_noua=[]
        gasit = False
        for x in self.__clienti:
            if x.get_id_client() == id_client:
                gasit = True
                if x.get_nr_inchiriate()>0:
                    raise ValueError("Nu se poate șterge un client care închiriază filme")
            else:
                lista_noua.append(x)
        if not gasit:
            raise ValueError("Nu există client cu acest ID")
        self.__clienti=lista_noua
        self.__scrie_fisier()

    def actualizare_client(self,id_client,nume_client,cnp_client):
        """Actualizaza un client din lista
        :param id_client:Id client de actualizat
        :param nume_client:Numele nou
        :param cnp_client:Cnp client nou
        """
        gasit=False
        for x in self.__clienti:
            if x.get_id_client()==id_client:
                x.set_nume_client(nume_client)
                x.set_cnp_client(cnp_client)
                ValidatorClient(x).valideaza_client()
                gasit=True
        if not gasit:
            raise ValueError("Nu există client cu acest ID")
        self.__scrie_fisier()

    def cauta_client(self,id_client):
        """Cauta client dupa id
        :param id_client: ID client de cautatat
        """
        for x in self.__clienti:
            if x.get_id_client()==id_client:
                return x
        raise ValueError("Nu există client cu acest ID")

    def get_all_clienti(self):
        """Returneaza lista de clienti"""
        if self.__clienti:
            return self.__clienti
        else:
            raise ValueError("Nu există clienți adăugați")

    def clienti_sortati_dupa_nr_filme_inchiriate(self):
        """Returneaza lista de obiecte din repo_clienti care inchiriaza filme ordonate dupa nr"""
        lista =self.get_all_clienti()
        lista_sortata = sorted(lista, key=lambda client: client.get_nr_inchiriate(), reverse=True)
        return lista_sortata