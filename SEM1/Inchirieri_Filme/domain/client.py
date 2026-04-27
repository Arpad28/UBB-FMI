class Client:
    def __init__(self, id_client, nume_client, cnp_client,nr_inchiriate=0):
        """
        Initializam un obiect de tip client
        :param id_client: id ul clientului
        :param nume_client: numele clientului
        :param cnp_client: cnp ul clientului
        :param nr_inchiriate: nr filme inchiriate
        """
        self.__data={
            'id_client': id_client,
            'nume_client': nume_client,
            'cnp_client': cnp_client,
            'nr_inchiriate': nr_inchiriate
        }

    def get_id_client(self):
        """Returneaza id ul clientului"""
        return self.__data['id_client']

    def get_nume_client(self):
        """Returneaza numele clientului"""
        return self.__data['nume_client']

    def get_cnp_client(self):
        """Returneaza cnp ul clientului"""
        return self.__data['cnp_client']

    def get_nr_inchiriate(self):
        """Returneaza nr de filme inchiriate"""
        return self.__data['nr_inchiriate']

    def set_id_client(self, id_client):
        """Seteaza id ul clientului"""
        self.__data['id_client'] = id_client

    def set_nume_client(self, nume_client):
        """Seteaza numele clientului"""
        self.__data['nume_client'] = nume_client

    def set_cnp_client(self, cnp_client):
        """Seteaza cnp ul clientului"""
        self.__data['cnp_client'] = cnp_client

    def set_nr_inchiriate(self, nr_inchiriate):
        """Seteaza nr de filme inchiriate"""
        self.__data['nr_inchiriate'] = nr_inchiriate