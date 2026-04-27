from datetime import date


class Tractor:
    def __init__(self,id,nume,pret,model,data:date):
        self.__id=id
        self.__nume=nume
        self.__pret=pret
        self.__model=model
        self.__data=data

    def get_expirat(self):
        return self.__data<date.today()

    def get_id(self):
        return self.__id
    def get_nume(self):
        return self.__nume
    def get_pret(self):
        return self.__pret
    def get_model(self):
        return self.__model
    def get_data(self):
        return self.__data

    def __str__(self):
        zi=self.__data.day
        luna=self.__data.month
        an=self.__data.year
        prefix="*" if self.get_expirat() else ""
        return f"{self.get_id()},{prefix}{self.get_nume()},{self.get_pret()},{self.get_model()},{zi},{luna},{an}"