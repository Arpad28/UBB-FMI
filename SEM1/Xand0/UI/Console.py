from Controller.ServiceTicTacToe import Service_joc
from Repository.TicTacToeRepository import Repo_joc

class UI:

    def __init__(self, service: Service_joc, repo: Repo_joc):
        self.__service = service
        self.__repo = repo

    def run(self):
        print("Scrie 'help' pentru lista de comenzi")
        while True:
            lista_comenzi = """
            lista
            joc <nr_joc> <nr_linie> <nr_coloana>
            exit
            """
            linie = input(">>>> ").strip()
            if linie != "":
                linie_split = linie.split()
                comanda = linie_split[0]
                args = linie_split[1:]
                try:
                    if comanda == "lista":
                        lista = self.__service.cauta_joc_neterminat()
                        for joc in lista:
                            print(joc)
                    elif comanda == "joc":
                        nr, linie, coloana = args
                        stare_joc = self.__service.play(nr, linie, coloana)
                        print("Mutare efectuata")
                        print(stare_joc.getGame())
                        if stare_joc.getWinner() != "":
                            print(f"FELICITARI! Castigatorul este: {stare_joc.getWinner()}")
                        elif stare_joc.getStatus() == "Terminat":
                            print("Jocul s-a terminat cu REMIZA.")
                        else:
                            print("Jocul continua...")
                    elif comanda == "help":
                        print(lista_comenzi)
                    elif comanda == "exit":
                        self.__repo.scrie_exit()
                        break
                    else:
                        print("Comanda inexistenta")
                except ValueError as eroare:
                    print("Eroare", eroare)