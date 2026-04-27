import unittest

from domain.sedinte import Sedinta
from repository.repo import Repo
from serivicii.serivce import Service
from validari.Validator import Validator


class TestCase(unittest.TestCase):
    def setUp(self):
        self.repo = Repo(r"C:\Users\Arpad Szilagyi\PycharmProjects\practicfp\fisier_teste")
        self.service=Service(self.repo)

    def tearDown(self):
        with open(r"C:\Users\Arpad Szilagyi\PycharmProjects\practicfp\fisier_teste",'w')as f:
            f.write("""22.02,08:00,mate,normal
5.02,12:00,info,normal
5.02,10:00,geogra,extraordinara
21.02,10:00,animale,normal
21.3,12:34,istorie,normal""")

    def test_repository(self):
        lista=self.repo.get_all()
        self.assertEqual(len(lista),5)
        self.assertEqual(lista[0].get_zi(),"22")
        self.assertEqual(lista[0].get_luna(),"02")
        self.assertEqual(lista[0].get_ora(),"08")
        self.assertEqual(lista[0].get_minute(),"00")
        sedinta=Sedinta("12","3","12","23","biologie","normal")
        self.repo.adauga_sedinta(sedinta)
        lista=self.repo.get_all()
        self.assertEqual(len(lista),6)
        self.assertEqual(lista[5].get_zi(),"12")
        self.assertEqual(lista[5].get_luna(),"3")

    def test_domain(self):
        sedinta = Sedinta("12", "3", "12", "23", "biologie", "normal")
        self.assertEqual(sedinta.get_zi(),"12")
        self.assertEqual(sedinta.get_luna(),"3")
        self.assertEqual(sedinta.get_ora(),"12")
        self.assertEqual(sedinta.get_minute(),"23")
        self.assertEqual(sedinta.get_subiect(),"biologie")
        self.assertEqual(sedinta.get_tip(),"normal")

    def test_service(self):
        lista=self.service.sedinte_maine()
        self.assertEqual(len(lista),2)
        self.assertEqual(lista[0].get_zi(),"5")
        self.assertEqual(lista[0].get_luna(),"02")
        self.assertEqual(lista[0].get_ora(),"10")
        self.assertEqual(lista[0].get_minute(),"00")
        self.assertEqual(lista[1].get_subiect(),"info")
        self.service.adauga("12","3","12","23","psihologie","normal")
        lista=self.repo.get_all()
        self.assertEqual(len(lista),6)
        self.assertEqual(lista[5].get_zi(),"12")
        self.assertEqual(lista[5].get_luna(),"3")
        self.assertEqual(lista[5].get_ora(),"12")
        self.assertEqual(lista[5].get_minute(),"23")
        self.assertEqual(lista[5].get_subiect(),"psihologie")
        self.assertEqual(lista[5].get_tip(),"normal")
        lista=self.service.sedinte_setate("19","2")
        self.assertEqual(len(lista),2)
        self.assertEqual(lista[0].get_zi(),"21")
        self.assertEqual(lista[0].get_luna(),"02")
        self.assertEqual(lista[0].get_ora(),"10")
        self.assertEqual(lista[0].get_minute(),"00")
        self.service.exporta_fisier("teste_exporta_teste","a")
        cnt=0
        valori=[]
        with open("teste_exporta_teste","r")as f:
            linii=f.readlines()
            for linie in linii:
                linie=linie.strip()
                if linie!="":
                    linie=linie.split(",")
                    valori.append(linie[0])
                cnt=cnt+1
        self.assertEqual(valori[0],"22.02")
        self.assertEqual(valori[1],"5.02")
        self.assertEqual(cnt,3)
        self.service.exporta_fisier("teste_exporta_teste", "z")
        cnt = 0
        with open("teste_exporta_teste", "r") as f:
            linii = f.readlines()
            for linie in linii:
                cnt = cnt + 1
        self.assertEqual(cnt, 0)

    def teste_validari(self):
        with self.assertRaises(ValueError):
            self.service.adauga("120","3","12","23","psihologie","normal")
            self.service.adauga("10", "30", "12", "23", "psihologie", "normal")
            self.service.adauga("12", "3", "100", "23", "psihologie", "normal")
            self.service.adauga("12", "3", "12", "203", "psihologie", "normal")
            self.service.adauga("asd", "3", "12", "23", "psihologie", "normal")
            self.service.adauga("12", "3", "asd", "23", "psihologie", "normal")
            self.service.adauga("12","3","1","1","mate","normal")

    def teste_Validator(self):
        validari=Validator("12","3","asd","23")
        with self.assertRaises(ValueError):
            validari.valideaza()
        validari = Validator("32", "3", "3", "23")
        with self.assertRaises(ValueError):
            validari.valideaza()
        validari = Validator("30", "15", "3", "23")
        with self.assertRaises(ValueError):
            validari.valideaza()
        validari = Validator("12", "3", "33", "23")
        with self.assertRaises(ValueError):
            validari.valideaza()
        validari = Validator("12", "3", "33", "60")
        with self.assertRaises(ValueError):
            validari.valideaza()


def ruleaza_teste():
    unittest.main(module=__name__,exit=False,argv=[''],verbosity=2)