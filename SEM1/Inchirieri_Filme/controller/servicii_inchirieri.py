from domain.inchiriere import Inchiriere
from domain.data import Data
from validator.validatordata import ValidatorData
from validator.validatorinchiriere import ValidatorInchiriere

class ServiciiInchiriere:
    def __init__(self,repo_inchirieri,repo_filme,repo_clienti,undo):
        """Initializeaza repo_urile necesare"""
        self.repo_inchirieri = repo_inchirieri
        self.repo_filme = repo_filme
        self.repo_clienti = repo_clienti
        self.undo=undo

    def inchireaza_film(self,id_inchiriere,id_film,id_client,an_inchiriere,luna_inchiriere,zi_inchiriere,data_returnarii=None):
        """Adauga in repo_clienti un obiect de tip inchireaza_film
        :param id_inchiriere: ID_inchirere de adaugat
        :param id_film: ID_film de inchiriat
        :param id_client: ID_client care inchiriaza
        :param an_inchiriere: Anul in care se inchiriaza
        :param luna_inchiriere: Luna in care se inchiriaza
        :param zi_inchiriere: Ziua in care se inchiriaza
        :param data_returnarii: None,deoarece inca nu a returnat
        """
        film=self.repo_filme.cauta_film(id_film)
        client=self.repo_clienti.cauta_client(id_client)
        self.repo_clienti.cauta_client(id_client)
        data_inchirierii=Data(an_inchiriere,luna_inchiriere,zi_inchiriere)
        data_inchirierii=ValidatorData(data_inchirierii).valideaza_data()
        if film.get_inchiriat() == "DA":
            raise ValueError("Filmul deja este închiriat")
        else:
            self.repo_filme.actualizeaza(film,"DA")
        client.set_nr_inchiriate(client.get_nr_inchiriate() + 1)
        film.set_fost_inchiriat(film.get_fost_inchiriat() + 1)
        inchirieaza=Inchiriere(id_inchiriere,id_film,id_client,data_inchirierii,data_returnarii)
        self.repo_inchirieri.adauga_inchiriere(inchirieaza)
        def undo_inchirieri():
            self.repo_filme.actualizeaza(film,"NU")
            client.set_nr_inchiriate(client.get_nr_inchiriate() - 1)
            film.set_fost_inchiriat(film.get_fost_inchiriat() - 1)
            self.repo_inchirieri.sterge_inchiriere(id_inchiriere)
        self.undo.inregistreaza(undo_inchirieri)


    def retureaza_film(self,id_inchiriere,an_returnare,luna_returnare,zi_returnare):
        """Returneaza filmul cu ID film
        :param id_inchiriere: id_inchirere pe care il returnam
        :param an_returnare: an_returnare in care il returnam
        :param luna_returnare: luna_retunare in care il returnam
        :param zi_returnare: zi_returnare in care il returnam
        """
        inchiriere=self.repo_inchirieri.cauta_inchiriere(id_inchiriere)
        film=self.repo_filme.cauta_film(inchiriere.get_id_film())
        film.set_inchiriat("NU")
        self.repo_filme.actualizeaza(film,"NU")
        data=Data(an_returnare,luna_returnare,zi_returnare)
        data=ValidatorData(data).valideaza_data()
        self.repo_inchirieri.actualizeaza(inchiriere,data)
        def undo_returnare():
            self.repo_filme.actualizeaza(film,"DA")
            inchiriere.set_data_returnarii(None)
        self.undo.inregistreaza(undo_returnare)

    def sterge_inchiriere(self,id_inchiriere):
        """Sterge inchirierea cu ID inchiriere
         :param id_inchiriere: ID_inchirere de sters
        """
        inchiriere = self.repo_inchirieri.cauta_inchiriere(id_inchiriere)
        film = self.repo_filme.cauta_film(inchiriere.get_id_film())
        film.set_inchiriat("NU")
        client=self.repo_clienti.cauta_client(inchiriere.get_id_client())
        client.set_nr_inchiriate(client.get_nr_inchiriate() - 1)
        film.set_fost_inchiriat(film.get_fost_inchiriat() - 1)
        self.repo_inchirieri.sterge_inchiriere(id_inchiriere)
        def undo_stergere():
            film.set_inchiriat("DA")
            client.set_nr_inchiriate(client.get_nr_inchiriate() + 1)
            film.set_fost_inchiriat(film.get_fost_inchiriat() + 1)
            self.repo_inchirieri.adauga_inchiriere(inchiriere)
        self.undo.inregistreaza(undo_stergere)

    def cauta_inchirere(self,id_inchiriere):
        """Cauta un obiect de tip inchiriere_film cu id_ul dat
        :param id_inchiriere: ID_inchirere de cautat
        """
        return self.repo_inchirieri.cauta_inchiriere(id_inchiriere)

    def raport_legatura(self,numar):
        """Imi zice ca in top numar persoane active de cate ori a inchiriat top numar filme inchiriate
        :param numar: Numarul unde se opreste topul
        """
        raport=[]
        lista_client=self.repo_clienti.clienti_sortati_dupa_nr_filme_inchiriate()
        lista_filme=self.repo_filme.filme_sortati_nr_inchirate()
        if len(lista_filme)<numar or len(lista_client)<numar:
            raise ValueError("Nu sunt destule filme inchiriate/clienti")
        for _ in range(numar):
            for c in lista_client:
                linii=[]
                for _ in range(numar):
                    for f in lista_filme:
                        suma=self.repo_inchirieri.numar_inchirieri_client_film(c.get_id_client(),f.get_id_film())
                        linii.append((f.get_id_film(),f.get_titlu(),suma))
                raport.append((c,c.get_nr_inchiriate(),linii))
        return raport

    def lista_inchirieri(self):
        """Returneaza lista de inchirieri"""
        return self.repo_inchirieri.get_all_inchiriere()