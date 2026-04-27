from busniess.serivce import ServiciiTractoare
from repo.repo_tractoare import RepoTractoare
from datetime import date


class UI:
    def __init__(self,repo:RepoTractoare,servicii:ServiciiTractoare):
        self.__repo=repo
        self.__servicii=servicii
        self.__comenzi="""
        adauga <id> <nume> <pret> <zi> <luna> <an>
        sterge <numar>
        filtru <text> <numar>
        afiseaza
        undo
        """

    def run(self):
        print("Scrie 'help' pentru lista de comenzi")
        while True:
            linie= input(">>>> ").strip()
            if not linie:
                continue
            parti=linie.split()
            comanda=parti[0]
            args=parti[1:]
            try:
                if comanda=="adauga":
                    id,nume,pret,model,zi,luna,an=args
                    data=date(int(an),int(luna),int(zi))
                    self.__servicii.aduaga_tractor(id,nume,pret,model,data)
                    print("Tractor adaugat cu succes")
                elif comanda=="sterge":
                    try:
                        numar=args[0]
                        numar=int(numar)
                        numere=self.__servicii.sterge_tractor(str(numar))
                        print(f"S-au sters {numere} tractoare cu succes")
                    except:
                        raise ValueError("Nu ai introdus un numar de tip int")
                elif comanda=="filtru":
                    if len(args)==1:
                            text=""
                            numar=args[0]
                            lista=self.__servicii.filtru(text,numar)
                            for t in lista:
                                print(t)
                    else:
                            text,numar=args
                            lista=self.__servicii.filtru(text,numar)
                            print(len(lista))
                            for t in lista:
                                print(t)
                elif comanda=="afiseaza":
                    lista=self.__repo.get_all()
                    for t in lista:
                        print(t)
                elif comanda=="undo":
                    self.__servicii.undo_manager()
                    print("S-a facut undo cu succes")
                elif comanda=="help":
                    print(self.__comenzi)
                else:
                    print("Comanda inexistenta")

            except ValueError as e:
                print("Eroare:",e)