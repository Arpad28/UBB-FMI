from busniess.servicii_experiment import Servicii_experiment
from repository.repo_experimente import repo_exp

def teste_repo_servicii():
    repo = repo_exp(r"C:\Users\Arpad Szilagyi\PycharmProjects\test\date_experimente")
    servicii = Servicii_experiment(repo)
    lista = repo.get_all()
    assert len(lista) == 10
    assert abs(servicii.get_medie_globala() - 0.5529411764705883) < 1e-9
    statistici = servicii.medie_ponderata()
    assert statistici["physical"]["repetari"] == 16
    assert statistici["physical"]["succese"] == 2
    assert statistici["social"]["repetari"] == 19
    assert statistici["social"]["succese"] == 16
    assert statistici["biological"]["repetari"] == 50
    assert statistici["biological"]["succese"] == 29
    ranking_social = servicii.ranking("social")
    assert ranking_social[0][1] == 1
    ranking_bio = servicii.ranking("biological")
    assert ranking_bio[0][0] == "Dr.Smith"
    assert ranking_bio[-1][0] == "Dr.Marius"
    assert abs(ranking_bio[-1][1] - 0.3333333333333333) < 1e-9
    ranking_phys = servicii.ranking("physical")
    assert ranking_phys[0][0] == "Dr.Q"
    assert abs(ranking_phys[0][1] - 0.3333333333333333) < 1e-9
    assert ranking_phys[1][0] == "Dr.X"
    assert ranking_phys[1][1] == 0.0