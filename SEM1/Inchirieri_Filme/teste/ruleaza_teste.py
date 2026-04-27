import unittest

from teste.teste_repo_fisier import TestRepoFisier
from teste.teste_domain import TesteComplete
from teste.teste_servicii_repo import TestServiciiComplete
from teste.teste_undo import TestUndo
from teste.teste_validari import TestValidators
from teste.testerandom import TestRandom


def ruleaza_toate_testele():
    """Ruleaza toate testele folosind TestSuite"""

    loader = unittest.TestLoader()
    suite = unittest.TestSuite()

    suite.addTests(loader.loadTestsFromTestCase(TestRepoFisier))
    suite.addTests(loader.loadTestsFromTestCase(TesteComplete))
    suite.addTests(loader.loadTestsFromTestCase(TestServiciiComplete))
    suite.addTests(loader.loadTestsFromTestCase(TestUndo))
    suite.addTests(loader.loadTestsFromTestCase(TestValidators))
    suite.addTests(loader.loadTestsFromTestCase(TestRandom))

    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(suite)