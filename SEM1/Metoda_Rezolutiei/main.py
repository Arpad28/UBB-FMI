from UI.consola import Ui
from busniess.service import Service
from repository.repo import Repo
from teste.ruleaza_teste import ruleaza_test

if __name__ == '__main__':
    ruleaza_test()
    repo=Repo()
    servicii=Service(repo)
    ui=Ui(servicii)
    ui.ruleaza()