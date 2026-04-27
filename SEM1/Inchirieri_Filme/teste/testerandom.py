import unittest
import random
from controller.servicii_filme import ServiciiFilme
from repository.repofilme import RepoFilme
from repository.undo_manager import UndoManager

class TestRandom(unittest.TestCase):
    def test_random(self):
        repo_filme = RepoFilme()
        undo = UndoManager()
        ctrl_filme = ServiciiFilme(repo_filme, undo)

        random_seed = 123
        random.seed(random_seed)

        titlu_random = ctrl_filme.genereaza_titlu()
        self.assertEqual(titlu_random, "rfX")

        gen_random = ctrl_filme.genereaza_gen()
        self.assertEqual(gen_random, "horror")

        descriere_random = ctrl_filme.genereaza_descriere()
        self.assertEqual(descriere_random, "gcyIJvv")
