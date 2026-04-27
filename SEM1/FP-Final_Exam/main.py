from repository.repo import Repo
from console.consola import Ui
from serivicii.serivce import Service
from teste.test import ruleaza_teste

if __name__ == "__main__":
    ruleaza_teste()
    repo=Repo(r"C:\Users\Arpad Szilagyi\PycharmProjects\practicfp\sedinte")
    service=Service(repo)
    ui=Ui(repo,service)
    ui.run()
