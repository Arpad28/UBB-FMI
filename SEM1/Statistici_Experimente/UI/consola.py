from busniess.servicii_experiment import Servicii_experiment

class UI:

    def __init__(self,service:Servicii_experiment):
        self.__service=service

    def run(self):
        comenzi="""=============
medie_ponderata
ranking <tipul_experimentului>
exit
===============
                """
        print("Scrie 'help' pentru a afisa comenzile")
        while True:
            linie=input(">>>> ").strip()
            if not linie:
                continue
            linie=linie.split()
            comanda=linie[0]
            args=linie[1:]
            try:
                if comanda =="medie_ponderata":
                    medie_globala=self.__service.get_medie_globala()
                    statistici=self.__service.medie_ponderata()
                    for tip, valori in statistici.items():
                        if valori["repetari"] > 0:
                            medie_tip = valori["succese"] / valori["repetari"]
                        else:
                            medie_tip = 0
                        if medie_tip>=medie_globala:
                            rezultat="succes"
                        else:
                            rezultat=""
                        print(f"Tip: {tip}, Media ponderată: {medie_tip},{rezultat}")
                elif comanda=="help":
                    print(comenzi)
                elif comanda=="ranking":
                    if len(args)==1:
                        lista=self.__service.ranking(args[0])
                        for nume,rata in lista:
                            print(f"{nume} a avut o rata de succes la experimentul {args[0]} de {rata}")
                    else:
                        raise ValueError("Nu ai transmis tipul experimentului")
                elif comanda=="exit":
                    print("La revedere")
                    break
                else:
                    print("Comanda inexistenta")
            except ValueError as e:
                print("Eroare:",e)