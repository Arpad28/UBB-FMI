from datetime import date

class Data:
    def __init__(self, an, luna, zi):
        self.__an = an
        self.__luna = luna
        self.__zi = zi

    def get_an(self):
        return self.__an

    def get_luna(self):
        return self.__luna

    def get_zi(self):
        return self.__zi

    def to_date(self):
        return date(self.__an, self.__luna, self.__zi)

    def __lt__(self, other):
        return self.to_date() < other.to_date()

    def __le__(self, other):
        return self.to_date() <= other.to_date()

    def __gt__(self, other):
        return self.to_date() > other.to_date()

    def __ge__(self, other):
        return self.to_date() >= other.to_date()

    def __eq__(self, other):
        return self.to_date() == other.to_date()
