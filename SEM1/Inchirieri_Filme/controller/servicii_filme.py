import random
import string
from domain.film import Film
from repository.repofilme import RepoFilme
from repository.undo_manager import UndoManager


class ServiciiFilme:

    def __init__(self,repo_filme:RepoFilme,undo:UndoManager):
        """Initializeaza repo_filme vid"""
        self.repo_filme=repo_filme
        self.undo=undo

    def adauga_film(self, id_film, titlu, descriere, gen):
        """
        Adauga in repo film un obiecti de tip film
        :param id_film: id film de adaugat
        :param titlu: titlu film
        :param descriere: descrire film
        :param gen: gen film
        """
        film = Film(id_film, titlu, descriere, gen)
        self.repo_filme.adauga_film(film)
        def undo_adaugare():
            self.repo_filme.sterge_film(id_film)
        self.undo.inregistreaza(undo_adaugare)


    def sterge_film(self, id_film):
        """
        Sterge din repo film un obiecti de tip film
        :param id_film: id ul filmului de sters
        """
        film=self.repo_filme.cauta_film(id_film)
        self.repo_filme.sterge_film(id_film)
        def undo_sterge():
            self.repo_filme.adauga_film(film)
        self.undo.inregistreaza(undo_sterge)

    def actualizare_film(self, id_film, titlu, descriere, gen):
        """
        Actualizeaza in repo film un obiecti de tip film
        :param id_film: id film de actualizat
        :param titlu: titlu film de actualizat
        :param descriere: descrire film de actualizat
        :param gen: gen film de actualizat
        """
        film=self.repo_filme.cauta_film(id_film)
        titlu_vechi=film.get_titlu()
        descriere_vechi=film.get_descriere()
        gen_vechi=film.get_gen()
        self.repo_filme.actualizare_film(id_film, titlu, descriere, gen)
        def undo_actualizare():
            self.repo_filme.actualizare_film(id_film,titlu_vechi, descriere_vechi, gen_vechi)
        self.undo.inregistreaza(undo_actualizare)

    def cauta_film(self,id_film):
        """Cauta film dupa ID film
        :param id_film: ID film de cautat
        """
        return self.repo_filme.cauta_film(id_film)

    def lista_filme(self):
        """Returneaza lista de obiecte din repo film"""
        return self.repo_filme.get_all_filme()

    def filme_sortati_nr_inchirate(self):
        """Returneaza lista de filme ordonate dupa nr de cate a  fost inchiriat"""
        return self.repo_filme.filme_sortati_nr_inchirate()

    def genereaza_titlu(self):
        lung = random.randint(3, 15)
        return ''.join(random.choice(string.ascii_letters) for _ in range(lung))

    def genereaza_descriere(self):
        lung = random.randint(3, 15)
        return ''.join(random.choice(string.ascii_letters + "_") for _ in range(lung))

    def genereaza_gen(self):
        return random.choice(["actiune", "drama", "comedie", "horror", "sf", "thriller"])

    def genereaza_filme(self,n):
        try:
            n=int(n)
        except:
            raise ValueError("Trebuie să fie un număr natural nenul")

        for i in range(n):
            id_film= str(random.randint(1,9999))
            titlu = self.genereaza_titlu()
            descriere = self.genereaza_descriere()
            gen = self.genereaza_gen()
            film=Film(id_film, titlu, descriere, gen)
            self.repo_filme.adauga_film(film)

