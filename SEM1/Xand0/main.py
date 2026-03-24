from Controller.ServiceTicTacToe import Service_joc
from Repository.TicTacToeRepository import Repo_joc
from UI.Console import UI

if __name__=="__main__":
    repo=Repo_joc(r"C:\Users\Arpad Szilagyi\PycharmProjects\Xand0\jocuri")
    service=Service_joc(repo)
    Ui=UI(service,repo)
    Ui.run()