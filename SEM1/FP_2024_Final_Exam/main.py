from busniess.serivce import ServiciiTractoare
from repo.repo_tractoare import RepoTractoare
from UI.consola import UI
from teste.Teste import ruleaza_teste

if __name__=='__main__':
    ruleaza_teste()
    repo=RepoTractoare(r"C:\Users\Arpad Szilagyi\PycharmProjects\tractoare_practic_2024\fisier")
    servicii=ServiciiTractoare(repo)
    ui=UI(repo,servicii)
    ui.run()
