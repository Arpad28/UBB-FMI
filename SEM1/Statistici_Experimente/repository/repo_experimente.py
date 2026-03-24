from domain.experiment import Experiment


class repo_exp:

    def __init__(self,calea_fisier):
        """
        Initializam repo_exp ca o lista goala
        :param calea_fisier: Calea catre fisierul cu date
        """
        self.__calea_fisier = calea_fisier
        self.__lista=[]
        self.citeste_fisier()

    def  citeste_fisier(self):
        """Citeste datele din fisier"""
        with open(self.__calea_fisier,'r') as f:
            linii=f.readlines()
            for linie in linii:
                linie=linie.strip()
                if linie!="":
                    parti=linie.split(",")
                    id,titlu,tip,nume,rep,succes=parti
                    experiment=Experiment(id,titlu,tip,nume,rep,succes)
                    self.__lista.append(experiment)

    def scrie_fisier(self):
        """Scrie datele din fisier"""
        with open(self.__calea_fisier, 'w') as f:
            for experiment in self.__lista:
                f.write(experiment)

    def get_all(self):
        """Returneaza intreaga lista"""
        return self.__lista