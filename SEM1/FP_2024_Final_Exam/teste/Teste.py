import unittest
from datetime import date

from busniess.serivce import ServiciiTractoare
from repo.repo_tractoare import RepoTractoare


class TestCase(unittest.TestCase):
    def setUp(self):
        self.repo=RepoTractoare(r"C:\Users\Arpad Szilagyi\PycharmProjects\tractoare_practic_2024\fisier_teste")
        self.servicii=ServiciiTractoare(self.repo)

    def tearDown(self):
        with open(r"C:\Users\Arpad Szilagyi\PycharmProjects\tractoare_practic_2024\fisier_teste",'w') as f:
            f.write("""2,CaseIH,98000,MX,15,11,2026
4,Deutz,87000,DX,20,8,2022
1,JohnDeere,120000,JD-X,10,5,2023
3,NewHolland,105500,T7,1,3,2024
5,Fendt,150000,Vario,30,12,2027""")

    def test_repo(self):
        self.assertEqual(len(self.repo.get_all()),5)
        self.assertNotEqual(len(self.repo.get_all()),0)

    def test_servicii(self):
        self.servicii.aduaga_tractor(6,"Lamborghini",125000,2018,date(2006,2,28))
        self.assertEqual(len(self.repo.get_all()),6)
        self.servicii.undo_manager()
        self.assertEqual(len(self.repo.get_all()),5)
        self.servicii.sterge_tractor("1")
        self.assertEqual(len(self.repo.get_all()),2)
        self.servicii.undo_manager()
        self.assertEqual(len(self.repo.get_all()),5)
        lista=self.servicii.filtru("",-1)
        self.assertEqual(len(lista),5)
        lista=self.servicii.filtru("",125000)
        self.assertEqual(len(lista),4)
        lista=self.servicii.filtru("a",-1)
        self.assertEqual(len(lista),2)

    def test_undo_eroare(self):
        with self.assertRaises(ValueError):
            self.servicii.undo_manager()


def ruleaza_teste():
    unittest.main(module=__name__,exit=False,argv=[''],verbosity=2)
