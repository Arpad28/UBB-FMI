import unittest
from busniess.service import Service
from repository.repo import Repo

class Teste(unittest.TestCase):
    def setUp(self):
        self.repo = Repo()
        self.service = Service(self.repo)

    def teste_repo(self):
        self.assertEqual(self.repo.get_complement("p"),"~p")
        self.assertEqual(self.repo.get_complement("~p"), "p")
        literali=self.repo.get_literali("pv~q")
        self.assertEqual(literali[0],"p")
        self.assertEqual(literali[1],"~q")
        literali = self.repo.get_literali("~pvqvr")
        self.assertEqual(literali[0], "~p")
        self.assertEqual(literali[1], "q")
        self.assertEqual(literali[2], "r")

    def teste_servici(self):
        self.assertEqual(self.service.get_literali("pv~q"),self.service.get_literali("~qvp"))
        self.assertEqual(self.service.get_literali("pvq"),self.service.get_literali("qvp"))
        self.assertTrue(self.service.este_subsumat("pvqvr","pvq"))
        self.assertFalse(self.service.este_subsumat("pvqvr", "pv~q"))
        self.assertTrue(self.service.este_subsumat("~pvqvr", "~p"))
        self.assertTrue(self.service.este_tautologie("pv~p"))
        self.assertTrue(self.service.este_tautologie("~pvp"))
        self.assertFalse(self.service.este_tautologie("pvp"))
        self.assertFalse(self.service.este_tautologie("~pv~p"))
        clauze="~pvpvq,~pvq,qvr,rv~pvq,~r"
        clauze=clauze.split(",")
        clauze=self.service.sterge_puri(clauze)
        self.assertEqual(clauze[0],"~r")
        self.assertEqual(len(clauze),1)
        clauze = "~pvpv~q,~pvq,qvr,rv~pvq,~r"
        clauze = clauze.split(",")
        clauze = self.service.sterge_puri(clauze)
        self.assertEqual(len(clauze), 5)
        self.assertEqual(clauze[0],"~pvpv~q")
        self.assertEqual(clauze[1], "~pvq")
        self.assertEqual(clauze[2], "qvr")
        self.assertEqual(clauze[3], "rv~pvq")
        self.assertEqual(clauze[4], "~r")
        self.assertEqual(self.service.rezolva("pvq","~pvq"),"q")
        self.assertEqual(self.service.rezolva("~pvq", "pv~q"), "Tautologie")
        self.assertEqual(self.service.rezolva("~p", "p"), "Clauza vida")
        self.assertFalse(self.service.rezolva("~p", "~p"))
        self.assertFalse(self.service.rezolva("~pvq", "~pvr"))

    def teste_metoda(self):

        def rezolva(clauze):
            i = 0
            clauza_vida = False
            while i < len(clauze):
                j = 0
                while j < i:
                    rezultat = self.service.rezolva(clauze[i], clauze[j])
                    if rezultat == "Clauza vida":
                        clauza_vida = True
                        clauze.append(rezultat)
                        return True
                    elif not rezultat:
                        j = j + 1
                        continue
                    elif rezultat == "Tautologie":
                        j = j + 1
                    else:
                        gasit = False
                        literali_rezultat = self.service.get_literali(rezultat)
                        for clauza in clauze:
                            if literali_rezultat == self.service.get_literali(clauza):
                                gasit = True
                        if not gasit:
                            clauze.append(rezultat)
                        j = j + 1
                if clauza_vida:
                    break
                i = i + 1
            return False

        clauze = "~pvpvq,~pvq,qvr,rv~pvq,~r"
        clauze = clauze.split(",")
        clauze = self.service.automatizare(clauze)
        self.assertFalse(rezolva(clauze))
        clauze = "pvq,~pvqv~r,~qvr"
        clauze = clauze.split(",")
        clauze = self.service.automatizare(clauze)
        self.assertFalse(rezolva(clauze))
        clauze = "pvq,~pvq,pv~q,~qv~p"
        clauze = clauze.split(",")
        clauze = self.service.automatizare(clauze)
        self.assertTrue(rezolva(clauze))
        clauze = "~pvq,~pvr,p,~qv~r"
        clauze = clauze.split(",")
        clauze = self.service.automatizare(clauze)
        self.assertTrue(rezolva(clauze))




