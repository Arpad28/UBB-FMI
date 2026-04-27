from domain.sedinte import Sedinta


class Repo:
    def __init__(self,cale_fisier):
        """Initializeaza clasa de Repo si citeste din fisier datele pe care le pune intr o lista
        :param cale_fisier: Calea catre fisierul din care citim
        """
        self.cale_fisier = cale_fisier
        self.lista=[]
        self.citeste_fisier()

    def citeste_fisier(self):
        """Functia citeste din fisier si pune valorile intr o lista"""
        with open(self.cale_fisier,"r") as f:
            linii=f.readlines()
            for linie in linii:
                linie=linie.strip()
                if linie!="":
                    arg=linie.split(",")
                    data=arg[0].split(".")
                    zi=data[0]
                    luna=data[1]
                    ora=arg[1].split(":")
                    ceas=ora[0]
                    minute=ora[1]
                    subiect=arg[2]
                    tip=arg[3]
                    sedinta=Sedinta(zi,luna,ceas,minute,subiect,tip)
                    self.lista.append(sedinta)

    def scrie_fisier(self):
        """Functia ia valorile din lista si le scrie in fisier"""
        with open(self.cale_fisier,"w") as f:
            for sedinta in self.lista:
                f.write(f"{sedinta.get_zi()}.{sedinta.get_luna()},{sedinta.get_ora()}:{sedinta.get_minute()},{sedinta.get_subiect()},{sedinta.get_tip()}\n")

    def adauga_sedinta(self,sedinta):
        """Functia adauga o clasa de tip sedinta in lista noastra
        :param sedinta: Clasa de tip sedinta
        """
        self.lista.append(sedinta)
        self.scrie_fisier()

    def get_all(self):
        """Returneaza intreaga lista de valori"""
        return self.lista