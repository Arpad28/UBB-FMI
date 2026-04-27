from ui.AppCoord import ApplicationCoordonator
from ui.consola import UI
from teste.ruleaza_teste import ruleaza_toate_testele

if __name__ == "__main__":
    ruleaza_toate_testele()
    while True:
        mod = input("Cum vrei să salvezi datele (memorie/fisier): ")
        try:
            coord = ApplicationCoordonator(mod)
            srv_clienti, srv_filme, srv_inchirieri, undo = coord.initializeaza()
            ui = UI(srv_clienti, srv_filme, srv_inchirieri, undo)
            ui.ruleaza()
            break
        except ValueError as e:
            print("Eroare:", e)

