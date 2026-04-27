from datetime import date
from domain.tractor import Tractor


class RepoTractoare:
    def __init__(self,cale_fisier):
        self.__cale_fisier = cale_fisier
        self.tractoare=[]
        self.citeste_fisier()

    def citeste_fisier(self):
        with open(self.__cale_fisier,'r') as f:
            linii=f.readlines()
            for linie in linii:
                linie=linie.strip()
                if linie!="":
                    valori=linie.split(",")
                    id=int(valori[0])
                    nume=valori[1]
                    pret=int(valori[2])
                    model=valori[3]
                    data=date(int(valori[6]),int(valori[5]),int(valori[4]))
                    tractor=Tractor(id,nume,pret,model,data)
                    self.tractoare.append(tractor)

    def scrie_fisier(self):
        with open(self.__cale_fisier,'w') as f:
            for tractor in self.tractoare:
                data=tractor.get_data()
                zi=data.day
                luna=data.month
                an=data.year
                f.write(f"{tractor.get_id()},{tractor.get_nume()},{tractor.get_pret()},{tractor.get_model()},{zi},{luna},{an}\n")

    def get_all(self):
        return self.tractoare


