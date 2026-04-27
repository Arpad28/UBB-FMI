import unittest
from teste.teste import Teste

def ruleaza_test():
    loader=unittest.TestLoader()
    suite=unittest.TestSuite()
    suite.addTest(loader.loadTestsFromTestCase(Teste))
    runner=unittest.TextTestRunner()
    runner.run(suite)