from domain.film import Film

class ValidatorFilm:
    def __init__(self, film:Film):
        """Trasnmitem validatorului un obiect de tip film
        :param film: Obiectul de validat
        """
        self.__film = film

    def valideaza_film(self):
        """Valideaza filmul dupa ID,dupa titlu,dupa descriere,dupa gen"""
        try:
            id_film = int(self.__film.get_id_film())
        except:
            raise ValueError("ID film trebuie să fie un număr pozitiv nenul")
        if id_film <= 0:
            raise ValueError("ID film trebuie să fie un număr pozitiv nenul")

        titlu = self.__film.get_titlu()
        if titlu == "":
            raise ValueError("Titlul nu poate fi gol")
        n=len(titlu)
        if n==1 and titlu[0].isdigit():
            raise ValueError("Titlul nu poate conține cifre doar la final")
        for i in range(n-1):
            if titlu[i].isdigit():
                raise ValueError("Titlul nu poate conține cifre doar la final")
        descriere = self.__film.get_descriere()
        if descriere == "":
            raise ValueError("Descrierea nu poate fi goală")

        gen = self.__film.get_gen()
        if gen == "":
            raise ValueError("Genul nu poate fi gol")
        if gen not in ["actiune", "drama", "comedie", "horror", "sf", "animatie", "thriller"]:
            raise ValueError("Gen invalid")
