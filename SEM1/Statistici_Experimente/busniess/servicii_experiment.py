from repository.repo_experimente import repo_exp

class Servicii_experiment:
    def __init__(self, repo: repo_exp):
        """Initializam service ul cu datele din repo"""
        self.__repo = repo

    def medie_ponderata(self):
        """Calculam numarul de repetari si de succese la fiecare tip si returnam intr un dictionar"""
        lista = self.__repo.get_all()
        statistici = {}
        for experiment in lista:
            tip = experiment.get_tip()
            if tip not in statistici:
                statistici[tip] = {"repetari": 0, "succese": 0}
            statistici[tip]["repetari"] += int(experiment.get_nr_repetari())
            statistici[tip]["succese"] += int(experiment.get_nr_succese())
        return statistici

    def get_medie_globala(self):
        """Calculam media globala a experimentelor"""
        lista = self.__repo.get_all()
        nr_total_repetari = 0
        nr_total_succese = 0
        for experiment in lista:
            nr_total_repetari += int(experiment.get_nr_repetari())
            nr_total_succese += int(experiment.get_nr_succese())
        if nr_total_repetari > 0:
            media_globala = nr_total_succese / nr_total_repetari
        else:
            media_globala = 0
        return media_globala

    def ranking(self, tipul_dat):
        """
        Filtram experimentele de tipul dat,iar dupa numaram numarul de repetari
        si de succese a fiecarui exeperimentator,returnam lista deja sortata cu rankingul facut
        :param tipul_dat: Tipul experimentului cautat
        :return:
        """
        lista = self.__repo.get_all()
        experimente_tip = [exp for exp in lista if exp.get_tip() == tipul_dat]
        if not experimente_tip:
            raise ValueError("Nu exista tipul dat")
        conducatori = {}
        for exp in experimente_tip:
            nume = exp.get_nume()
            if nume not in conducatori:
                conducatori[nume] = {"repetari": 0, "succese": 0}
            conducatori[nume]["repetari"] += int(exp.get_nr_repetari())
            conducatori[nume]["succese"] += int(exp.get_nr_succese())
        rezultate = []
        for nume, valori in conducatori.items():
            if valori["repetari"] > 0:
                rata = valori["succese"] / valori["repetari"]
            else:
                rata = 0
            rezultate.append((nume, rata))
        rezultate.sort(key=lambda x: x[1], reverse=True)
        return rezultate