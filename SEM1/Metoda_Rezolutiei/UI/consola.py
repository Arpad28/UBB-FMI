from busniess.service import Service

class Ui:

    def __init__(self,servicii:Service):
        self.instructiuni = """============INSTRUCTIUNI============
        Fiecare clauza sa fie despartita de o virgula ','
        Daca se foloseste litera V literalii sa fie scris cu litere mari
        Notatii: ~ = not
                 v = sau
===================================="""
        self.servicii = servicii
    def ruleaza(self):
        print(self.instructiuni)
        while True:
            clauze = input(">>>Introdu o multime de clauze: ").strip()
            if not clauze:
                continue
            clauze = clauze.split(",")
            clauze=self.servicii.automatizare(clauze)
            print(f"Dupa aplicarea procesului rezolutiv multimea de clauze devine:\n{clauze}")
            i=0
            clauza_vida=False
            while i<len(clauze):
                j=0
                while j<i:
                    rezultat=self.servicii.rezolva(clauze[i],clauze[j])
                    if rezultat == "Clauza vida":
                        clauza_vida=True
                        clauze.append(rezultat)
                        print(f"Clauzele C{i + 1}={clauze[i]},C{j + 1}={clauze[j]} rezolva si se obtine clauza C{len(clauze) + 1}={rezultat}")
                        print(f"Prin aplicarea metodei de rezolutie s-a ajuns la multimea de clauze:\n{clauze}")
                        print("Din teorema de corectitudine si completitudine => Multimea este inconsistenta")
                        break
                    elif not rezultat:
                        j=j+1
                        continue
                    elif rezultat=="Tautologie":
                        print( f"Clauzele C{i + 1}={clauze[i]},C{j + 1}={clauze[j]} rezolva dar se obtine o Tautoligie ce nu ne ajuta")
                        j=j+1
                    else:
                        gasit=False
                        literali_rezultat=self.servicii.get_literali(rezultat)
                        for clauza in clauze:
                            if literali_rezultat == self.servicii.get_literali(clauza):
                                gasit=True
                        if not gasit:
                            print(f"Clauzele C{i+1}={clauze[i]},C{j+1}={clauze[j]} rezolva si se obtine clauza C{len(clauze)+1}={rezultat}")
                            clauze.append(rezultat)
                        else:
                            print(f"Clauzele C{i + 1}={clauze[i]},C{j + 1}={clauze[j]} rezolva dar se obtine o clauza ce este deja in multime ceee ce nu ne ajuta")
                        j=j+1
                if clauza_vida:
                    break
                i=i+1
            if not clauza_vida:
                print(f"Prin aplicarea metodei de rezolutie s-a ajuns la multimea de clauze:\n{clauze}")
                print("Nu s-a ajuns la clauza vida => Multimea este consistenta")
            break

