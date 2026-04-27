from controller.serivicii_clienti import ServiciiClient
from controller.servicii_filme import ServiciiFilme
from controller.servicii_inchirieri import ServiciiInchiriere
from repository.repoclienti import RepoClienti
from repository.repofilme import RepoFilme
from repository.repofisiereclienti import RepoFisierClienti
from repository.repofisierfilme import RepoFisierFilme
from repository.repofisierinchirieri import RepoFisierInchirieri
from repository.repoinchirieri import RepoInchirieri
from repository.undo_manager import UndoManager


class ApplicationCoordonator:

    def __init__(self,mod):
        """Initializam modul de stocrare
        :param mod:Modul de stocare introdus de utilizator
        """
        self.__mod=mod

    def initializeaza(self):
        undo=UndoManager()
        if self.__mod=="memorie":
            repo_clienti=RepoClienti()
            repo_filme=RepoFilme()
            repo_inchirieri=RepoInchirieri()
        elif self.__mod=="fisier":
            repo_clienti = RepoFisierClienti(r"C:\Users\Arpad Szilagyi\PycharmProjects\lab7_9\clienti.txt")
            repo_filme = RepoFisierFilme(r"C:\Users\Arpad Szilagyi\PycharmProjects\lab7_9\filme.txt")
            repo_inchirieri = RepoFisierInchirieri(r"C:\Users\Arpad Szilagyi\PycharmProjects\lab7_9\inchirieri.txt")
        else:
            raise ValueError("Mod de stocare inexistent")
        srv_clienti=ServiciiClient(repo_clienti,undo)
        srv_filme=ServiciiFilme(repo_filme,undo)
        srv_inchirieri=ServiciiInchiriere(repo_inchirieri,repo_filme,repo_clienti,undo)
        return srv_clienti,srv_filme,srv_inchirieri,undo