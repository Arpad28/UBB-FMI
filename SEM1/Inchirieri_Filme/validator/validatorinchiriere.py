from domain.inchiriere import Inchiriere

class ValidatorInchiriere:
    def __init__(self, inchiriere:Inchiriere):
        """Transmitem validatorului un obiect de tip inchiriere
        :param inchiriere: obiectul de validat
        """
        self.__inchiriere = inchiriere

    def valideaza_inchiriere(self):
        """Valideaza inchirere dupa id si dupa data inchirierii/returnarii"""
        try:
            id_inchiriere = int(self.__inchiriere.get_id_inchiriere())
        except:
            raise ValueError("ID închiriere trebuie să fie un număr pozitiv nenul")
        if id_inchiriere <= 0:
            raise ValueError("ID închiriere trebuie să fie un număr pozitiv nenul")
        if self.__inchiriere.get_data_returnarii() is not None:
                if self.__inchiriere.get_data_inchirierii()> self.__inchiriere.get_data_returnarii():
                    raise ValueError("Nu poți returna filmul înainte să-l închiriezi")
