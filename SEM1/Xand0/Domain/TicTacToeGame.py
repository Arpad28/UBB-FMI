class TicTacToeGame:

    def __init__(self, nr, table):
        self.__nr = nr
        self.__table = table

    def get_nr(self):
        return self.__nr

    def get_table(self):
        return self.__table

    def set_poz(self, poz, symbol):
        self.__table[poz] = symbol

    def gata(self):
        return "" not in self.__table

    def __str__(self):
        t = [elem if elem != "" else " " for elem in self.__table]
        return (
            f"Joc #{self.__nr}\n"
            f" {t[0]} | {t[1]} | {t[2]} \n"
            f"---|---|---\n"
            f" {t[3]} | {t[4]} | {t[5]} \n"
            f"---|---|---\n"
            f" {t[6]} | {t[7]} | {t[8]} \n"
        )