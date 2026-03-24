from busniess.servicii_experiment import Servicii_experiment
from repository.repo_experimente import repo_exp
from UI.consola import UI
from teste.ruleaza_teste import ruleaza_toate_teste

if __name__=="__main__":
    ruleaza_toate_teste()
    fisier=r"C:\Users\Arpad Szilagyi\PycharmProjects\test\date_experimente"
    repo=repo_exp(fisier)
    service=Servicii_experiment(repo)
    consola=UI(service)
    consola.run()