from domain.client import Client
from datetime import datetime

class ValidatorClient:
    def __init__(self, client: Client):
        """Transmitem un obiect de tip client validatorului
        :param client: Obiect de tip client
        """
        self.__client = client

    def valideaza_client(self):
        """Valideaza clientul dupa ID,dupa nume si dupa CNP"""
        self._valideaza_id()
        self._valideaza_nume()
        self._valideaza_cnp()

    def _valideaza_id(self):
        try:
            id_client = int(self.__client.get_id_client())
            if id_client <= 0:
                raise ValueError
        except:
            raise ValueError("ID client trebuie să fie un număr pozitiv nenul")

    def _valideaza_nume(self):
        nume = self.__client.get_nume_client()
        if not nume:
            raise ValueError("Numele nu poate fi gol")
        if any(ch.isdigit() for ch in nume):
            raise ValueError("Numele nu poate conține cifre")

    def _valideaza_cnp(self):
        cnp = self.__client.get_cnp_client()
        if len(cnp) != 13 or not cnp.isdigit():
            raise ValueError("CNP-ul trebuie să conțină exact 13 cifre")
        coef = [2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9]
        suma = sum(int(cnp[i]) * coef[i] for i in range(12))
        cifra = suma % 11
        if cifra == 10:
            cifra = 1
        if cifra != int(cnp[12]):
            raise ValueError("CNP-ul este invalid (cifra de control greșită)")

        yy = int(cnp[1:3])
        mm = int(cnp[3:5])
        dd = int(cnp[5:7])

        try:
            datetime(yy, mm, dd)
        except ValueError:
            raise ValueError("Data din CNP nu este validă")
