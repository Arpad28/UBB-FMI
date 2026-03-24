from Domain.TicTacToeGame import TicTacToeGame

class Repo_joc:

    def __init__(self, cale_fisier):
        self.__cale_fisier = cale_fisier
        self.__lista = []
        self.__copie = []
        self.__citeste()

    def __citeste(self):
        try:
            with open(self.__cale_fisier, 'r') as f:
                linii = f.readlines()
                for linie in linii:
                    linie = linie.strip()
                    if linie != "":
                        valori = linie.split(",")
                        if len(valori) >= 10:
                            joc = valori[1:10]
                            self.__lista.append(TicTacToeGame(valori[0], joc))
                            self.__copie.append(TicTacToeGame(valori[0], list(joc)))
        except FileNotFoundError:
            pass

    def scrie(self):
        with open(self.__cale_fisier, 'w') as f:
            for joc in self.__lista:
                f.write(f"{joc.get_nr()},{','.join(joc.get_table())}\n")

    def scrie_exit(self):
        with open(self.__cale_fisier, 'w') as f:
            for joc in self.__copie:
                f.write(f"{joc.get_nr()},{','.join(joc.get_table())}\n")

    def cauta_id(self, id):
        for joc in self.__lista:
            if joc.get_nr() == id:
                return joc
        raise ValueError("Nu exista joc cu acest ID")

    def actualizare_joc(self, id, joc: TicTacToeGame):
        for game in self.__copie:
            if game.get_nr() == id:
                game.set_poz(joc.get_table())
                self.scrie()
                return
        raise ValueError("Nu exista joc cu acest ID")

    def get_all(self):
        return self.__lista