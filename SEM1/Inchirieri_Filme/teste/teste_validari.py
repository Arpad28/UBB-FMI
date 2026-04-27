import unittest
from domain.client import Client
from domain.data import Data
from domain.film import Film
from domain.inchiriere import Inchiriere
from validator.validatorclient import ValidatorClient
from validator.validatordata import ValidatorData
from validator.validatorfilm import ValidatorFilm
from validator.validatorinchiriere import ValidatorInchiriere


class TestValidators(unittest.TestCase):

    def test_validator_client(self):
        client_valid = Client(1, "Popescu", "1960228123457")
        validator = ValidatorClient(client_valid)
        with self.assertRaises(ValueError):
            validator.valideaza_client()

        client_id_invalid = Client(-1, "Popescu", "1960228123457")
        validator = ValidatorClient(client_id_invalid)
        with self.assertRaises(ValueError):
            validator.valideaza_client()

        client_nume_gol = Client(2, "", "1960228123457")
        validator = ValidatorClient(client_nume_gol)
        with self.assertRaises(ValueError):
            validator.valideaza_client()

        client_nume_cifre = Client(3, "Pop3scu", "1960228123457")
        validator = ValidatorClient(client_nume_cifre)
        with self.assertRaises(ValueError):
            validator.valideaza_client()

        client_cnp_invalid = Client(4, "Ionescu", "123")
        validator = ValidatorClient(client_cnp_invalid)
        with self.assertRaises(ValueError):
            validator.valideaza_client()

    def test_validator_data(self):
        data_valida = Data(2023, 5, 20)
        validator = ValidatorData(data_valida)
        d = validator.valideaza_data()
        self.assertEqual(d.year, 2023)
        self.assertEqual(d.month, 5)
        self.assertEqual(d.day, 20)

        data_viitor = Data(3000, 1, 1)
        validator = ValidatorData(data_viitor)
        with self.assertRaises(ValueError):
            validator.valideaza_data()

        data_invalida = Data(2023, 2, 30)
        validator = ValidatorData(data_invalida)
        with self.assertRaises(ValueError):
            validator.valideaza_data()

    def test_validator_film(self):
        film_valid = Film(1, "Matrix", "Film bun", "actiune")
        validator = ValidatorFilm(film_valid)
        validator.valideaza_film()

        film_id_invalid = Film(-1, "Matrix", "Film bun", "actiune")
        validator = ValidatorFilm(film_id_invalid)
        with self.assertRaises(ValueError):
            validator.valideaza_film()

        film_titlu_gol = Film(2, "", "Descriere", "drama")
        validator = ValidatorFilm(film_titlu_gol)
        with self.assertRaises(ValueError):
            validator.valideaza_film()

        film_descriere_gola = Film(3, "Titanic", "", "drama")
        validator = ValidatorFilm(film_descriere_gola)
        with self.assertRaises(ValueError):
            validator.valideaza_film()

        film_gen_invalid = Film(4, "Inception", "Film fain", "muzical")
        validator = ValidatorFilm(film_gen_invalid)
        with self.assertRaises(ValueError):
            validator.valideaza_film()

    def test_validator_inchiriere(self):
        data_inchiriere = Data(2023, 5, 20)
        data_returnare = Data(2023, 5, 25)

        inchiriere_valida = Inchiriere(1, 1, 1, data_inchiriere, data_returnare)
        validator = ValidatorInchiriere(inchiriere_valida)
        validator.valideaza_inchiriere()

        inchiriere_id_invalid = Inchiriere(-1, 1, 1, data_inchiriere, data_returnare)
        validator = ValidatorInchiriere(inchiriere_id_invalid)
        with self.assertRaises(ValueError):
            validator.valideaza_inchiriere()

        data_returnare_incorecta = Data(2023, 5, 19)
        inchiriere_data_gresita = Inchiriere(2, 1, 1, data_inchiriere, data_returnare_incorecta)
        validator = ValidatorInchiriere(inchiriere_data_gresita)
        with self.assertRaises(ValueError):
            validator.valideaza_inchiriere()

        inchiriere_fara_returnare = Inchiriere(3, 1, 1, data_inchiriere)
        validator = ValidatorInchiriere(inchiriere_fara_returnare)
        validator.valideaza_inchiriere()

