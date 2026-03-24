from Domain.TicTacToeStatus import TicTacToeStatus
from Repository.TicTacToeRepository import Repo_joc


class Service_joc:

    def __init__(self, repo_joc: Repo_joc):
        self.__repo_joc = repo_joc

    def vezi_castigator(self, tabla):
        castigat = [(0, 1, 2), (3, 4, 5), (6, 7, 8), (0, 3, 6), (1, 4, 7), (2, 5, 8), (0, 4, 8), (2, 4, 6)]
        for a, b, c in castigat:
            if tabla[a] and tabla[a] == tabla[b] == tabla[c]:
                return tabla[a]
        return ""

    def cauta_joc_neterminat(self):
        tot = self.__repo_joc.get_all()
        lista_neterminat = []
        for joc in tot:
            if not self.vezi_castigator(joc.get_table()) and not joc.gata():
                lista_neterminat.append(joc)
        return lista_neterminat

    def play(self, nr, linie, coloana):
        try:
            linie = int(linie)
            coloana = int(coloana)
        except:
            raise ValueError("Linia si coloana trebuie sa fie de tipul int")

        joc = self.__repo_joc.cauta_id(str(nr))
        tabla = list(joc.get_table())
        loc = linie * 3 + coloana

        if not 0 <= linie <= 2:
            raise ValueError("Linie inexistenta")
        if not 0 <= coloana <= 2:
            raise ValueError("Coloana inexistenta")
        if tabla[loc] != "":
            raise ValueError("Casuta ocupata")

        nr_x = tabla.count("X")
        nr_0 = tabla.count("O")

        simbol = "X"
        if nr_x <= nr_0:
            simbol = "X"
        else:
            simbol = "O"

        joc.set_poz(loc, simbol)
        self.__repo_joc.scrie()

        winner = self.vezi_castigator(joc.get_table())
        if winner or joc.gata():
            status = "Terminat"
        else:
            status = "Neterminat"
        return TicTacToeStatus(joc, status, winner)