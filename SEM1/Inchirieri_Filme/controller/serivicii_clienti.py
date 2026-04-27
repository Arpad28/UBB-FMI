from domain.client import Client
from repository.repoclienti import RepoClienti
from repository.undo_manager import UndoManager


class ServiciiClient:

    def __init__(self,repo_clineti:RepoClienti,undo:UndoManager):
        """Initializeaza repo_clienti vid"""
        self.repo_clienti = repo_clineti
        self.undo=undo

    def adauga_client(self, id_client, nume_client, cnp_client):
        """Adauga in repo_clienti un obiect de tip client
        :param id_client: ID client de adaugat
        :param nume_client: Nume client de adaugat
        :param cnp_client: CNp client de adaugat
        """
        client = Client(id_client, nume_client, cnp_client)
        self.repo_clienti.adauga_client(client)
        def undo_adaugare():
            self.repo_clienti.sterge_client(id_client)
        self.undo.inregistreaza(undo_adaugare)

    def sterge_client(self, id_client):
        """Sterge din repo_clienti un obiect de tip client
        :param id_client: ID client de sters
        """
        client=self.repo_clienti.cauta_client(id_client)
        self.repo_clienti.sterge_client(id_client)
        def undo_stergere():
            self.repo_clienti.adauga_client(client)
        self.undo.inregistreaza(undo_stergere)

    def actualizare_client(self, id_client, nume_client, cnp_client):
        """Actualizeaza in repo_clienti un obiect de tip client
        :param id_client: ID client de actualizat
        :param nume_client: Nume client de actualizat
        :param cnp_client: CNp client de actualizat
        """
        client=self.repo_clienti.cauta_client(id_client)
        nume_vechi=client.get_nume_client()
        cnp_vechi=client.get_cnp_client()
        self.repo_clienti.actualizare_client(id_client, nume_client, cnp_client)
        def undo_actualizare():
            self.repo_clienti.actualizare_client(id_client, nume_vechi, cnp_vechi)
        self.undo.inregistreaza(undo_actualizare)

    def cauta_client(self,id_client):
        """Cauta client dupa ID client
        :param id_client:ID client de cautat
        """
        return self.repo_clienti.cauta_client(id_client)

    def lista_clienti(self):
        """Returneaza lista de obiecte din repo_clienti"""
        return self.repo_clienti.get_all_clienti()

    def clienti_sortati_dupa_nume(self):
        """Returneaza lista de obiecte din repo_clienti ordonate dupa nume"""
        lista=self.repo_clienti.get_all_clienti()
        lista_sortata=sorted(lista, key=lambda client:client.get_nume_client())
        return lista_sortata

    def clienti_sortati_dupa_nr_filme_inchiriate(self):
        """Returneaza lista de obiecte din repo_clienti care inchiriaza filme ordonate dupa nr"""
        return self.repo_clienti.clienti_sortati_dupa_nr_filme_inchiriate()

    def raport_clienti(self,procent):
        """Returneaza o lista de obiecte din repo_clienti cu primii procent% cei mai activi clienti care inchiriaza
        :param procent: procentul dupa care se calculeaza
        """
        lista=self.clienti_sortati_dupa_nr_filme_inchiriate()
        procent=max(1,len(lista)*procent//100)
        return lista[:procent]