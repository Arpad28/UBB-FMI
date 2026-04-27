from repository.repo import Repo

class Service:
    def __init__(self,repo: Repo):
        self.repo = repo

    def get_literali(self,clauza):
        """Retuneaza literalii in forma de set,pentru a putea verifica
        mai usor daca sunt clauze identice"""
        return set(self.repo.get_literali(clauza))

    def este_tautologie(self, clauza):
        """Verifica daca clauza este tautologie sau nu"""
        literali=self.repo.get_literali(clauza)
        for literal in literali:
            if self.repo.get_complement(literal) in literali:
                 return True
        return False

    def este_subsumat(self, clauza_mare, clauza_mica):
        """Verifică dacă clauza_mare este subsumată față de clauza_mica"""
        literali_mare = self.repo.get_literali(clauza_mare)
        literali_mica = self.repo.get_literali(clauza_mica)
        for literal in literali_mica:
            if literal not in literali_mare:
                return False
        return True

    def sterge_puri(self,clauze):
        """Sterge toti literalii puri din multimea de clauze"""
        toti_literali=[]
        for clauza in clauze:
            for literal in self.repo.get_literali(clauza):
                toti_literali.append(literal)
        puri=[]
        for literal in toti_literali:
            if self.repo.get_complement(literal) not in toti_literali and literal not in puri:
                puri.append(literal)
        if not puri:
            return clauze
        rezultat=[]
        for clauza in clauze:
            literali=self.repo.get_literali(clauza)
            ok=False
            for literal in literali:
                if literal in puri:
                    ok=True
            if not ok:
                rezultat.append(clauza)
        return rezultat

    def automatizare(self,clauze):
        """Sterge clauzele care contin literali puri,sunt tautologice sau sunt subsumate
        si returneaza o multime de clauze noua care nu contin aceste clauze,pentru a evita
        obtinerea unor clauze irelevante pentru obtinerea clauzei vide"""
        clauze = self.sterge_puri(clauze)
        for clauza in clauze:
            if self.este_tautologie(clauza):
                clauze.remove(clauza)
        indici_de_sters = []
        n = len(clauze)
        for i in range(n):
            for j in range(n):
                if i != j:
                    if len(clauze[i]) > len(clauze[j]):
                        if self.este_subsumat(clauze[i], clauze[j]):
                            indici_de_sters.append(i)
        for x in indici_de_sters:
            clauze.remove(clauze[x])
        return clauze

    def rezolva(self,clauza1,clauza2):
        """Verifica daca clauza1 impreuna cu clauza2 rezolva
        si in caz pozitiv returneaza clauza noua"""
        literali1=self.repo.get_literali(clauza1)
        literali2=self.repo.get_literali(clauza2)
        literali_de_sters=[]
        for literal in literali1:
            if self.repo.get_complement(literal) in literali2:
                literali_de_sters.append(literal)
        if not literali_de_sters:
            return False
        if len(literali_de_sters) >1:
            return "Tautologie"
        rezultat=""
        for literal in literali1:
            if literal not in literali_de_sters and self.repo.get_complement(literal) not in literali_de_sters:
                if rezultat=="":
                    rezultat=str(literal)
                else:
                    rezultat+="v"+str(literal)
        literali_rezultat=self.repo.get_literali(rezultat)
        for literal in literali2:
            if literal not in literali_de_sters and self.repo.get_complement(literal) not in literali_de_sters and literal not in literali_rezultat:
                if rezultat == "":
                    rezultat = str(literal)
                else:
                    rezultat += "v" + str(literal)
        if rezultat == "":
            return "Clauza vida"
        return rezultat
