from serivicii.serivce import Service
from repository.repo import Repo

class Ui:

    def __init__(self, repo:Repo,serivce:Service):
        """Initializeaza clasa de tip UI in care vom lucra
        :param repo: Repository ul de la sedinta
        :param serivce: Service ul de la sedinta
        """
        self.repo=repo
        self.service=serivce
        self.comenzi="""
        adauga <zi> <luna> <ora> <minute> <subiect> <tip> 
        seteaza_data <zi> <luna>
        exporta_date <nume_fisier> <sir>
        exit
        """

    def run(self):
        """Functia run ne ajuta sa putem lucra in consola si in fisiere"""
        print("Sedintele pentru ziua de maine sunt:")
        lista=self.service.sedinte_maine()
        for sedinta in lista:
            print(sedinta)
        print("Scrie 'help' pentru lista de comenzi")
        zi_setat,luna_setat=0,0
        while True:
            if zi_setat != 0:
                print("Sedintele pentru urmatoarele trei zile de la data selectata sunt:\n")
                sedinte = self.service.sedinte_setate(zi_setat, luna_setat)
                for sedinta in sedinte:
                    print(sedinta)
            linie = input(">>>> ").strip()
            if not linie:
                continue
            parti = linie.split()
            comanda = parti[0]
            args = parti[1:]
            try:
                if comanda=="adauga":
                    zi,luna,ora,minute,subiect,tip=args
                    self.service.adauga(zi,luna,ora,minute,subiect,tip)
                elif comanda=="seteaza_data":
                    zi_setat,luna_setat=args
                elif comanda=="exporta_date":
                    nume_fisier,text=args
                    self.service.exporta_fisier(nume_fisier,text)
                elif comanda=="help":
                    print(self.comenzi)
                elif comanda=="exit":
                    print("La revedere")
                    break
                else:
                    print("Comanda necunoscuta")
            except ValueError as e:
                print("Eroare",e)

