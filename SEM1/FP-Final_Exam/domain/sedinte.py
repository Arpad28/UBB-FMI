class Sedinta:
    def __init__(self,zi,luna,ora,minute,subiect,tip):
        """Initializeaza o clasa de tip Sedinta
        :param zi: ziua sedintei
        :param luna: luna sedintei
        :param ora: ora sedintei
        :param minute:minuta la care incepe sedinta
        :param subiect:Subiectul sedintei
        :param tip:Tipul sedintei
        """
        self.__zi = zi
        self.__luna = luna
        self.__ora = ora
        self.__minute = minute
        self.__subiect = subiect
        self.__tip = tip

    def get_zi(self):
        """Returneaza ziua sedintei"""
        return self.__zi
    def get_luna(self):
        """Returneaza luna sedintei"""
        return self.__luna
    def get_ora(self):
        """Returneaza ora sedintei"""
        return self.__ora
    def get_minute(self):
        """Returneaza minuta sedintei"""
        return self.__minute
    def get_subiect(self):
        """Returneaza subiectul sedintei"""
        return self.__subiect
    def get_tip(self):
        """Returneaza tipul sedintei"""
        return self.__tip

    def __str__(self):
        """Returneaza formatul cum vreau sa apara pe ecran/fisier
        :return: returneaza_formatul
        """
        return f"{self.get_zi()}.{self.get_luna()},{self.get_ora()}:{self.get_minute()},{self.get_subiect()},{self.get_tip()}"