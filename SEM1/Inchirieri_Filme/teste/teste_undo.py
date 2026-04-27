import unittest
from controller.serivicii_clienti import ServiciiClient
from controller.servicii_filme import ServiciiFilme
from controller.servicii_inchirieri import ServiciiInchiriere
from repository.repoclienti import RepoClienti
from repository.repofilme import RepoFilme
from repository.repoinchirieri import RepoInchirieri
from repository.undo_manager import UndoManager


class TestUndo(unittest.TestCase):
    def test_undo_complet(self):
        undo = UndoManager()

        repo_clienti = RepoClienti()
        srv_clienti = ServiciiClient(repo_clienti, undo)

        srv_clienti.adauga_client(1, "Popescu", "1890822411149")
        self.assertEqual(len(srv_clienti.lista_clienti()), 1)

        undo.undo()
        with self.assertRaises(ValueError):
            srv_clienti.lista_clienti()

        srv_clienti.adauga_client(2, "Ionescu", "1741004418925")
        srv_clienti.sterge_client(2)
        with self.assertRaises(ValueError):
            srv_clienti.lista_clienti()

        undo.undo()
        self.assertEqual(len(srv_clienti.lista_clienti()), 1)
        c = srv_clienti.lista_clienti()[0]
        self.assertEqual(c.get_nume_client(), "Ionescu")

        srv_clienti.actualizare_client(2, "Matei", "1951130413969")
        c = srv_clienti.cauta_client(2)
        self.assertEqual(c.get_nume_client(), "Matei")

        undo.undo()
        c = srv_clienti.cauta_client(2)
        self.assertEqual(c.get_nume_client(), "Ionescu")

        repo_filme = RepoFilme()
        srv_filme = ServiciiFilme(repo_filme, undo)

        srv_filme.adauga_film(10, "Matrix", "Fain", "sf")
        self.assertEqual(len(srv_filme.lista_filme()), 1)

        undo.undo()
        with self.assertRaises(ValueError):
            srv_filme.lista_filme()

        srv_filme.adauga_film(20, "Avatar", "Foarte Bun", "sf")
        srv_filme.actualizare_film(20, "Avatar 2", "Si mai bun", "sf")
        f = srv_filme.cauta_film(20)
        self.assertEqual(f.get_titlu(), "Avatar 2")

        undo.undo()
        f = srv_filme.cauta_film(20)
        self.assertEqual(f.get_titlu(), "Avatar")

        srv_filme.sterge_film(20)
        with self.assertRaises(ValueError):
            srv_filme.lista_filme()

        undo.undo()
        self.assertEqual(len(srv_filme.lista_filme()), 1)

        repo_inchirieri = RepoInchirieri()
        srv_inchirieri = ServiciiInchiriere(repo_inchirieri, repo_filme, repo_clienti, undo)

        srv_clienti.adauga_client(3, "Marin", "1950921419762")
        srv_filme.adauga_film(30, "Titanic", "Trist", "drama")

        srv_inchirieri.inchireaza_film(100, 30, 3, 2025, 11, 26)
        inch = srv_inchirieri.lista_inchirieri()[0]
        self.assertEqual(inch.get_id_client(), 3)
        self.assertEqual(inch.get_id_film(), 30)

        undo.undo()
        with self.assertRaises(ValueError):
            srv_inchirieri.lista_inchirieri()

        film = srv_filme.cauta_film(30)
        client = srv_clienti.cauta_client(3)
        self.assertEqual(film.get_inchiriat(), "NU")
        self.assertEqual(client.get_nr_inchiriate(), 0)

        srv_inchirieri.inchireaza_film(101, 30, 3, 2025, 11, 26)
        srv_inchirieri.retureaza_film(101, 2025, 11, 26)
        film = srv_filme.cauta_film(30)
        self.assertEqual(film.get_inchiriat(), "NU")

        undo.undo()
        inch = srv_inchirieri.lista_inchirieri()[0]
        film = srv_filme.cauta_film(30)
        self.assertEqual(film.get_inchiriat(), "DA")
        self.assertIsNone(inch.get_data_returnarii())

        undo.undo()
        with self.assertRaises(ValueError):
            srv_inchirieri.lista_inchirieri()

        self.assertEqual(film.get_inchiriat(), "NU")
        self.assertEqual(client.get_nr_inchiriate(), 0)

