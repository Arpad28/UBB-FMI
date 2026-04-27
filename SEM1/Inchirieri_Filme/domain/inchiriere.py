class Inchiriere:

    def __init__(self,id_inchiriere,id_film,id_client,data_inchirierii,data_returnarii=None):
        """Initializam un obiect de tip inchiriere
        :param id_inchiriere: ID inchiriere
        :param id_film: ID filmului de inchiriat
        :param id_client: ID clientului care inchiriaza
        :param data_inchirierii: Data in care s-a inchiriat un film
        :param data_returnarii: Data in care se returneaza filmul,initial None
        """
        self.__id_inchiriere = id_inchiriere
        self.__id_film = id_film
        self.__id_client = id_client
        self.__data_inchirierii = data_inchirierii
        self.__data_returnarii = data_returnarii

    def get_id_inchiriere(self):
        """Returneaza ID inchiriere"""
        return self.__id_inchiriere
    def get_id_film(self):
        """Returneaza ID filmul"""
        return self.__id_film
    def get_id_client(self):
        """Returneaza ID client"""
        return self.__id_client
    def get_data_inchirierii(self):
        """Returneaza data inchirierii"""
        return self.__data_inchirierii
    def get_data_returnarii(self):
        """Returneaza data returnarii"""
        return self.__data_returnarii

    def set_data_returnarii(self,data):
        """Seteaza data returnarii"""
        self.__data_returnarii = data
        