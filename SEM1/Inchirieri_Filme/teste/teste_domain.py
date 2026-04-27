import unittest

from domain.client import Client
from domain.data import Data
from domain.film import Film
from domain.inchiriere import Inchiriere


class TesteComplete(unittest.TestCase):

    def test_client_white_box(self):
        client = Client(1, "Popescu", "1960228123456")

        self.assertEqual(client.get_id_client(), 1)
        self.assertEqual(client.get_nume_client(), "Popescu")
        self.assertEqual(client.get_cnp_client(), "1960228123456")
        self.assertEqual(client.get_nr_inchiriate(), 0)

        client.set_id_client(2)
        client.set_nume_client("Ionescu")
        client.set_cnp_client("2960228123457")
        client.set_nr_inchiriate(5)

        self.assertEqual(client.get_id_client(), 2)
        self.assertEqual(client.get_nume_client(), "Ionescu")
        self.assertEqual(client.get_cnp_client(), "2960228123457")
        self.assertEqual(client.get_nr_inchiriate(), 5)

    def test_data_white_box(self):
        data = Data(2025, 11, 26)

        self.assertEqual(data.get_an(), 2025)
        self.assertEqual(data.get_luna(), 11)
        self.assertEqual(data.get_zi(), 26)

    def test_film_white_box(self):
        film = Film(1, "Matrix", "Un film fain", "actiune")

        self.assertEqual(film.get_id_film(), 1)
        self.assertEqual(film.get_titlu(), "Matrix")
        self.assertEqual(film.get_descriere(), "Un film fain")
        self.assertEqual(film.get_gen(), "actiune")
        self.assertEqual(film.get_inchiriat(), "NU")
        self.assertEqual(film.get_fost_inchiriat(), 0)

        film.set_id_film(2)
        film.set_titlu("Matrix Reloaded")
        film.set_descriere("Continuarea")
        film.set_gen("SF")
        film.set_inchiriat("DA")
        film.set_fost_inchiriat(3)

        self.assertEqual(film.get_id_film(), 2)
        self.assertEqual(film.get_titlu(), "Matrix Reloaded")
        self.assertEqual(film.get_descriere(), "Continuarea")
        self.assertEqual(film.get_gen(), "SF")
        self.assertEqual(film.get_inchiriat(), "DA")
        self.assertEqual(film.get_fost_inchiriat(), 3)

    def test_inchiriere_white_box(self):
        data_inchiriere = Data(2025, 11, 26)
        data_returnare = Data(2025, 12, 1)

        inchiriere = Inchiriere(1, 10, 2, data_inchiriere)
        self.assertEqual(inchiriere.get_id_inchiriere(), 1)
        self.assertEqual(inchiriere.get_id_film(), 10)
        self.assertEqual(inchiriere.get_id_client(), 2)
        self.assertEqual(inchiriere.get_data_inchirierii(), data_inchiriere)
        self.assertIsNone(inchiriere.get_data_returnarii())  # Verifică dacă e None

        inchiriere.set_data_returnarii(data_returnare)
        self.assertEqual(inchiriere.get_data_returnarii(), data_returnare)

        inchiriere2 = Inchiriere(2, 20, 3, data_inchiriere, data_returnare)
        self.assertEqual(inchiriere2.get_id_inchiriere(), 2)
        self.assertEqual(inchiriere2.get_id_film(), 20)
        self.assertEqual(inchiriere2.get_id_client(), 3)
        self.assertEqual(inchiriere2.get_data_inchirierii(), data_inchiriere)
        self.assertEqual(inchiriere2.get_data_returnarii(), data_returnare)