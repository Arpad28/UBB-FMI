class Film:
    def __init__(self, id_film, titlu, descriere, gen,inchiriat="NU",fost_inchiriat=0):
        """Initializam un obiect de tip Film
        :param id_film: ID_filmului
        :param titlu: Titlu filmului
        :param descriere: Descrierea filmului
        :param gen: Genul filmului
        :param inchiriat: Filmul e inchiriat sau nu,la inceput nu
        """
        self.__data={
            'id_film': id_film,
            'titlu': titlu,
            'descriere': descriere,
            'gen': gen,
            'inchiriat': inchiriat,
            'fost_inchiriat': fost_inchiriat
        }
    def get_id_film(self):
        """Returnează ID film"""
        return self.__data['id_film']

    def get_titlu(self):
        """Retruneaza titlul filmului"""
        return self.__data['titlu']

    def get_descriere(self):
        """Returneaza descriere filmului"""
        return self.__data['descriere']

    def get_gen(self):
        """Returneaza genul filmului"""
        return self.__data['gen']

    def get_inchiriat(self):
        """Returneaza daca filmul e inchiriat sau nu"""
        return self.__data['inchiriat']

    def get_fost_inchiriat(self):
        """Returneaza daca filmul de cate ori a fost inchiriat"""
        return self.__data['fost_inchiriat']

    def set_id_film(self, id_film):
        """Seteaza ID filmului"""
        self.__data['id_film'] = id_film

    def set_titlu(self, titlu):
        """Seteaza titlu filmului"""
        self.__data['titlu'] = titlu

    def set_descriere(self, descriere):
        """Seteaza descrierea filmului"""
        self.__data['descriere'] = descriere

    def set_gen(self, gen):
        """Seteaza genul filmului"""
        self.__data['gen'] = gen

    def set_inchiriat(self, inchiriat):
        """Seteaza daca filmul devine inchiriat sau nu"""
        self.__data['inchiriat'] = inchiriat

    def set_fost_inchiriat(self, fost_inchiriat):
        """Seteaza de cate ori a fost filmul inchiriat"""
        self.__data['fost_inchiriat'] = fost_inchiriat
