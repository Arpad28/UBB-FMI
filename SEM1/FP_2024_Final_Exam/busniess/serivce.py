from domain.tractor import Tractor
from repo.repo_tractoare import RepoTractoare
from datetime import date


class ServiciiTractoare():

    def __init__(self,repo:RepoTractoare):
        self.repo=repo
        self.undo=[]

    def aduaga_tractor(self,id,nume,pret,model,data:date):
        tractor=Tractor(id,nume,pret,model,data)
        self.repo.tractoare.append(tractor)
        self.repo.scrie_fisier()
        self.undo.append(("adauga",tractor))

    def sterge_tractor(self,numar):
        sterse=[t for t in self.repo.tractoare if numar in str(t.get_pret())]
        self.repo.tractoare = [t for t in self.repo.tractoare if t not in sterse]
        self.repo.scrie_fisier()
        self.undo.append(("sterge",sterse))
        return len(sterse)

    def filtru(self,text,pret):
        rezultat=self.repo.get_all()
        if text!="":
            rezultat=[t for t in rezultat if text in str(t.get_nume())]
        if int(pret)!=-1:
            rezultat = [t for t in rezultat if int(pret)>t.get_pret()]
        return rezultat

    def undo_manager(self):
        if not self.undo:
            raise ValueError("Nu mai exista comenzi la care se poate da undo")
        comanda,lista=self.undo.pop()
        if comanda =="adauga":
            self.repo.tractoare.remove(lista)
        if comanda == "sterge":
            self.repo.tractoare.extend(lista)
        self.repo.scrie_fisier()

