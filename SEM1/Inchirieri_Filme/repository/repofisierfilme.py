from domain.film import Film
from validator.validatorfilm import ValidatorFilm


class RepoFisierFilme:

    def __init__(self,calea_catre_fisier):
        """Initializeaza o lista in care vom stoca obiectele de tip film"""
        self.__filme=[]
        self.__calea_catre_fisier=calea_catre_fisier
        self.__citeste_fisier()

    def __citeste_fisier(self):
        with open(self.__calea_catre_fisier,'r') as f:
            self.__filme=[]
            linii=f.readlines()
            for linie in linii:
                linie=linie.strip()
                if linie!="":
                    valori=linie.split(",")
                    id_film,titlu,descriere,gen,inchiriat,fost_inchiriat=valori
                    film=Film(id_film,titlu,descriere,gen)
                    film.set_inchiriat(inchiriat)
                    film.set_fost_inchiriat(int(fost_inchiriat))
                    self.__filme.append(film)

    def __scrie_fisier(self):
        with open(self.__calea_catre_fisier,'w') as f:
            for film  in self.__filme:
                f.write(f"{film.get_id_film()},{film.get_titlu()},{film.get_descriere()},{film.get_gen()},{film.get_inchiriat()},{film.get_fost_inchiriat()}\n")

    def actualizeaza(self,film,mesaj):
        film.set_inchiriat(mesaj)
        self.__scrie_fisier()

    def adauga_film(self,film:Film):
        """Adauga un obiect de tip film
        :param film: Obiectul de adaugat
        """
        for x in self.__filme:
            if x.get_id_film()==film.get_id_film():
                raise ValueError("Film cu acest ID deja existent")
        ValidatorFilm(film).valideaza_film()
        self.__filme.append(film)
        self.__scrie_fisier()

    def actualizare_film(self,id_film,titlu,descriere,gen):
        """Actualizaza un obiect de tip film
        :param id_film: ID film de actualizat
        :param titlu: Noul titlu
        :param descriere: Noua descriere
        :param gen: Genul nou
        """
        gasit = False
        for x in self.__filme:
            if x.get_id_film() == id_film:
                x.set_titlu(titlu)
                x.set_descriere(descriere)
                x.set_gen(gen)
                ValidatorFilm(x).valideaza_film()
                gasit = True
        if not gasit:
            raise ValueError("Nu există film cu acest ID")
        self.__scrie_fisier()

    def cauta_film(self,id_film):
        """Cauta film dupa id ul dat
        :param id_film: Id film de cautat
        """
        for x in self.__filme:
            if x.get_id_film() == id_film:
                return x
        raise ValueError("Nu există film cu acest ID")

    def sterge_film(self, id_film):
        """Sterge film dupa id ul dat"""
        lista_noua = []
        gasit = False
        for x in self.__filme:
            if x.get_id_film() == id_film:
                gasit = True
                if x.get_inchiriat() == "DA":
                    raise ValueError("Nu poți șterge un film care se închiriază")
            else:
                lista_noua.append(x)
        if not gasit:
            raise ValueError("Nu există film cu acest ID")
        self.__filme = lista_noua
        self.__scrie_fisier()

    def filme_sortati_nr_inchirate(self):
        """Returneaza lista de filme ordonate dupa nr de cate a  fost inchiriat"""
        lista_filme = self.get_all_filme()
        lista_sortate = sorted(lista_filme, key=lambda filme: filme.get_fost_inchiriat(), reverse=True)
        return lista_sortate

    def get_all_filme(self):
        """Returneaza toate filmele"""
        if self.__filme:
            return self.__filme
        else:
            raise ValueError("Nu există filme adăugate")