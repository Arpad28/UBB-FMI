class Repo:
    def __init__(self):
        pass

    def get_literali(self,clauza):
        """Returneaza o lista care contine literalii clauzei"""
        clauza=clauza.split("v")
        return clauza

    def get_complement(self,literal):
        """Retruneaza negatia literalului"""
        if len(literal)==1:
            return '~'+literal
        else:
            return literal[1]

