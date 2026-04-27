import unittest
from datetime import date

from repository.repofisiereclienti import RepoFisierClienti
from repository.repofisierfilme import RepoFisierFilme
from repository.repofisierinchirieri import RepoFisierInchirieri
from domain.client import Client
from domain.film import Film
from domain.inchiriere import Inchiriere


class TestRepoFisier(unittest.TestCase):

    def setUp(self):
        self.date_clienti = """1,Ionescu,1820510413426,2
2,Andrei,1750218410518,3
3,Maria,2800812153853,5
4,Andreea,2800812151710,2
5,Matei,1800812154378,1
6,Ioan,1800812150565,10
7,Petru,1920216411803,7
8,Mihai,1991228413099,6
9,George,1701101419807,1
10,Ianis,1750707416850,3"""

        self.date_filme = """1,Matrix,fain,sf,NU,10
2,Matrix2,ok,sf,DA,7
3,StrangerThings,super,sf,DA,3
4,Transporter,fain,actiune,DA,4
5,Mario,ok,animatie,DA,5
6,IronMan,top,actiune,NU,3
7,JohnWick,legendar,thriller,NU,1
8,JohnWick2,legendar,thriller,NU,0
9,JohnWick3,ok,thriller,NU,0
10,HTTD,bun,animatie,NU,4"""

        self.date_inchirieri = """1,1,1,2025,8,22,2025,8,23
2,2,2,2024,4,24,-,-,-
3,3,3,2023,1,15,-,-,-
4,4,4,2022,4,11,-,-,-
5,5,5,2017,12,16,-,-,-"""


        self.path_clienti = "clienti_teste.txt"
        self.path_filme = "filme_teste.txt"
        self.path_inchirieri = "inchirieri_teste.txt"
        with open(self.path_clienti, "w") as f:
            f.write(self.date_clienti)


        with open(self.path_filme, "w") as f:
            f.write(self.date_filme)

        with open(self.path_inchirieri, "w") as f:
            f.write(self.date_inchirieri)

        self.repo_clienti = RepoFisierClienti(self.path_clienti)
        self.repo_filme = RepoFisierFilme(self.path_filme)
        self.repo_inchirieri = RepoFisierInchirieri(self.path_inchirieri)

    def tearDown(self):
        with open(self.path_clienti, "w") as f:
            f.write("")
        with open(self.path_filme, "w") as f:
            f.write("")
        with open(self.path_inchirieri, "w") as f:
            f.write("")


    def test_adauga_si_salvare_client(self):
        c = Client(11, "Client Nou", "1800725415438")
        self.repo_clienti.adauga_client(c)
        self.assertEqual(len(self.repo_clienti.get_all_clienti()), 11)

    def test_sterge_si_salvare_client(self):
        with self.assertRaises(ValueError):
            self.repo_clienti.sterge_client("9")

        c_nou = Client(99, "Temp", "1751114414351")
        self.repo_clienti.adauga_client(c_nou)
        self.repo_clienti.sterge_client(99)

        with self.assertRaises(ValueError):
            self.repo_clienti.cauta_client(99)


    def test_incarcare_initiala_filme(self):
        self.assertEqual(len(self.repo_filme.get_all_filme()), 10)

        f = self.repo_filme.cauta_film("2")
        self.assertEqual(f.get_titlu(), "Matrix2")
        self.assertEqual(f.get_inchiriat(), "DA")

        f1 = self.repo_filme.cauta_film("1")
        self.assertEqual(f1.get_inchiriat(), "NU")

    def test_adauga_si_salvare_film(self):
        f = Film(11, "Film Nou", "Desc", "sf")
        self.repo_filme.adauga_film(f)
        self.assertEqual(len(self.repo_filme.get_all_filme()), 11)

    def test_sterge_film_inchiriat(self):
        with self.assertRaises(ValueError):
            self.repo_filme.sterge_film("2")

        self.repo_filme.sterge_film("1")
        with self.assertRaises(ValueError):
            self.repo_filme.cauta_film("1")


    def test_incarcare_initiala_inchirieri(self):
        self.assertEqual(len(self.repo_inchirieri.get_all_inchiriere()), 5)

        i2 = self.repo_inchirieri.cauta_inchiriere("2")
        self.assertEqual(i2.get_id_inchiriere(), "2")
        self.assertIsNone(i2.get_data_returnarii())

        with self.assertRaises(ValueError):
            self.repo_inchirieri.cauta_inchiriere("7")

    def test_adauga_si_salvare_inchiriere(self):
        d_inch = date(2025, 12, 1)
        inchiriere = Inchiriere(6, 10, 10, d_inch, None)
        self.repo_inchirieri.adauga_inchiriere(inchiriere)
        self.assertEqual(len(self.repo_inchirieri.get_all_inchiriere()), 6)