import unittest

from controller.serivicii_clienti import ServiciiClient
from controller.servicii_filme import ServiciiFilme
from controller.servicii_inchirieri import ServiciiInchiriere
from repository.repoclienti import RepoClienti
from repository.repofilme import RepoFilme
from repository.repoinchirieri import RepoInchirieri
from repository.undo_manager import UndoManager


class TestServiciiComplete(unittest.TestCase):

    def setUp(self):
        self.undo_manager = UndoManager()
        self.repo_clienti = RepoClienti()
        self.srv_clienti = ServiciiClient(self.repo_clienti, self.undo_manager)
        self.repo_filme = RepoFilme()
        self.srv_filme = ServiciiFilme(self.repo_filme, self.undo_manager)
        self.repo_inchirieri = RepoInchirieri()
        self.srv_inchirieri = ServiciiInchiriere(self.repo_inchirieri, self.repo_filme, self.repo_clienti,
                                                 self.undo_manager)

    def tearDown(self):
        self.repo_filme = RepoFilme()
        self.repo_clienti = RepoClienti()
        self.repo_inchirieri = RepoInchirieri()

    def test_gestionare_clienti_white_box(self):
        """Testează adăugarea, căutarea și actualizarea clienților (White-Box)"""
        self.srv_clienti.adauga_client(1, "Popescu", "1890822411149")
        self.srv_clienti.adauga_client(2, "Ionescu", "1741004418925")
        self.srv_clienti.adauga_client(3, "Marin", "1950921419762")

        clienti = self.srv_clienti.lista_clienti()
        self.assertEqual(len(clienti), 3)

        c = self.srv_clienti.cauta_client(2)
        self.assertEqual(c.get_nume_client(), "Ionescu")

        self.srv_clienti.actualizare_client(3, "Matei", "1951130413969")
        c = self.srv_clienti.cauta_client(3)
        self.assertEqual(c.get_nume_client(), "Matei")

    def test_rapoarte_clienti_white_box(self):
        """Testează sortările și topul clienților (White-Box)"""
        self.srv_clienti.adauga_client(1, "Popescu", "1890822411149")
        self.srv_clienti.adauga_client(2, "Ionescu", "1741004418925")
        self.srv_clienti.adauga_client(3, "Matei", "1951130413969")  # Numele deja actualizat pentru test

        sort_nume = self.srv_clienti.clienti_sortati_dupa_nume()
        lista_nume = [c.get_nume_client() for c in sort_nume]
        self.assertEqual(lista_nume, ["Ionescu", "Matei", "Popescu"])

        self.srv_clienti.cauta_client(1).set_nr_inchiriate(2)
        self.srv_clienti.cauta_client(2).set_nr_inchiriate(5)
        self.srv_clienti.cauta_client(3).set_nr_inchiriate(3)

        sort_inchirieri = self.srv_clienti.clienti_sortati_dupa_nr_filme_inchiriate()
        lista_id = [c.get_id_client() for c in sort_inchirieri]
        self.assertEqual(lista_id, [2, 3, 1])

        top_clienti = self.srv_clienti.raport_clienti(30)
        self.assertEqual(len(top_clienti), 1)
        self.assertEqual(top_clienti[0].get_id_client(), 2)

    def test_gestionare_filme_white_box(self):
        """Testează funcționalitățile pentru filme (White-Box)"""
        self.srv_filme.adauga_film(10, "Matrix", "Fain", "sf")
        self.srv_filme.adauga_film(20, "Avatar", "Foarte Bun", "sf")
        self.srv_filme.adauga_film(30, "Titanic", "Trist", "drama")

        filme = self.srv_filme.lista_filme()
        self.assertEqual(len(filme), 3)

        f = self.srv_filme.cauta_film(20)
        self.assertEqual(f.get_titlu(), "Avatar")

        self.srv_filme.actualizare_film(30, "Titanic 2", "Mai Trist", "drama")
        f = self.srv_filme.cauta_film(30)
        self.assertEqual(f.get_titlu(), "Titanic 2")

        self.srv_filme.cauta_film(10).set_fost_inchiriat(5)
        self.srv_filme.cauta_film(20).set_fost_inchiriat(10)
        self.srv_filme.cauta_film(30).set_fost_inchiriat(2)

        filme_sortate = self.srv_filme.filme_sortati_nr_inchirate()
        lista_id_filme = [f.get_id_film() for f in filme_sortate]
        self.assertEqual(lista_id_filme, [20, 10, 30])


    def test_inchiriere_returnare_white_box(self):
        """Testează fluxul de închiriere și returnare (White-Box)"""
        self.srv_clienti.adauga_client(4, "Adrian", "1700515410624")
        self.srv_filme.adauga_film(40, "Inception", "Bun", "sf")

        self.srv_inchirieri.inchireaza_film(100, 40, 4, 2025, 11, 26)
        inchirieri = self.srv_inchirieri.lista_inchirieri()
        self.assertEqual(len(inchirieri), 1)

        self.srv_inchirieri.retureaza_film(100, 2025, 11, 26)

        film = self.srv_filme.cauta_film(40)
        self.assertEqual(film.get_inchiriat(), "NU")

        self.srv_inchirieri.inchireaza_film(101, 40, 4, 2025, 11, 26)
        self.srv_inchirieri.retureaza_film(101, 2025, 11, 26)

    def test_stergere_cu_validare_white_box(self):
        """Testează ștergerea și excepțiile (White-Box)"""
        self.srv_clienti.adauga_client(4, "Adrian", "1700515410624")
        self.srv_clienti.sterge_client(4)
        self.srv_filme.adauga_film(40, "Inception", "Bun", "sf")
        self.assertEqual(len(self.srv_filme.lista_filme()), 1)
        self.srv_filme.sterge_film(40)
        with self.assertRaises(Exception):
                self.srv_filme.lista_filme()

    def test_adauga_client_black_box(self):
        """BLACK-BOX TESTING pentru metoda adauga_client"""
        with self.assertRaises(ValueError):
            self.srv_clienti.adauga_client(99, "Black Box User", "1990000000000")
        self.srv_filme.adauga_film(40, "Inception", "Bun", "sf")

