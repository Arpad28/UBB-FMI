class Experiment:
    def __init__(self,id,titlu,tip,nume,nr_repetari,nr_succese):
        """
        Initializam un obiect de tip experiment
        :param id: Id ul experimentului
        :param titlu: Titlul experimentului
        :param tip: Tipul experimentului
        :param nume: Numele experimentatorului
        :param nr_repetari: Numarul de incercari
        :param nr_succese: Numarul de succese
        """
        self.__id = id
        self.__titlu = titlu
        self.__tip = tip
        self.__nume = nume
        self.__nr_repetari = nr_repetari
        self.__nr_succese = nr_succese

    def get_id(self):
        """Returneaza id ul experimentului"""
        return self.__id

    def get_titlu(self):
        """Returneaza titlul experimentului"""
        return self.__titlu

    def get_tip(self):
        """Returneaza tipul experimentului"""
        return self.__tip

    def get_nume(self):
        """Returneaza numele experimentatorului"""
        return self.__nume

    def get_nr_repetari(self):
        """Returneaza numarul de repetari a experimentului"""
        return self.__nr_repetari

    def get_nr_succese(self):
        """Returneaza numarul de experimente cu succes"""
        return self.__nr_succese

    def __str__(self):
        print(f"{self.get_id},{self.get_titlu},{self.get_tip},{self.get_nume},{self.get_nr_repetari},{self.get_nr_succese()}\n")
