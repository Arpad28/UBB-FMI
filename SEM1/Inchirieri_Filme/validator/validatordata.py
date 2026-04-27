from datetime import date
from domain.data import Data

class ValidatorData:
    def __init__(self,data:Data):
        """Transmitem validatorului obiectul de tip Data"""
        self.__data=data

    def valideaza_data(self):
        """Valideaza data valida si returneaza in format data
        :return: Returneaza data in format data
        """
        try:
            data_valida = date(int(self.__data.get_an()), int(self.__data.get_luna()), int(self.__data.get_zi()))
            if data_valida > date.today():
                raise ValueError("Închirierea nu poate fi făcută în viitor")
            return data_valida
        except:
            raise ValueError("Dată invalidă")