from Sortari.generic_sort import GenericSort
from Sortari.merge_sort import MergeSort
from Sortari.bingo_sort import BingoSort
from domain.film import Film
from validator.validatorfilm import ValidatorFilm


class RepoFilme:
    def __init__(self):
        """Initializeaza o lista in care vom stoca obiectele de tip film"""
        self.__filme=[]

    def adauga_film(self,film:Film):
        """Adauga un obiect de tip film
        :param film: Obiectul de adaugat
        """
        for x in self.__filme:
            if x.get_id_film()==film.get_id_film():
                raise ValueError("Film cu acest ID deja existent")
        ValidatorFilm(film).valideaza_film()
        self.__filme.append(film)

    def adauga_film_recursiv(self,film:Film,index=0):
        """Adauga un obiect de tip film
        :param film: Obiectul de adaugat
        :param index: Index ul de la care se verifica"""
        if index==len(self.__filme):
            ValidatorFilm(film).valideaza_film()
            self.__filme.append(film)
            return
        if self.__filme[index].get_id_film()==film.get_id_film():
            raise ValueError("Film cu acest ID deja existent")
        return self.adauga_film_recursiv(film,index+1)

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

    def actualizeaza(self,film,mesaj):
        film.set_inchiriat(mesaj)

    def cauta_film(self,id_film):
        """Cauta film dupa id ul dat,complexitate O(n),
        cel mai bun caz teta(1)-primul din lista,cel mai rau caz-ultimul din lista
        :param id_film: Id film de cautat
        """
        for x in self.__filme:
            if x.get_id_film() == id_film:
                return x
        raise ValueError("Nu există film cu acest ID")

    def cauta_film_recursiv(self, id_film,index=0):
        """Cauta film dupa id ul dat(recursiv)
        :param index: Indexul de unde sortam
        :param id_film: Id film de cautat
        """
        if index==len(self.__filme):
            raise ValueError("Nu exista film cu acest ID")
        if self.__filme[index].get_id_film() == id_film:
            return self.__filme[index]
        return self.cauta_film_recursiv(id_film,index+1)

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

    def filme_sortati_nr_inchirate_basic(self):
        """Returneaza lista de filme ordonate dupa nr de cate a  fost inchiriat"""
        lista_filme = self.get_all_filme()
        lista_sortate = sorted(lista_filme, key=lambda filme: filme.get_fost_inchiriat(), reverse=True)
        return lista_sortate

    def filme_sortati_nr_inchirate(self):
        lista=self.get_all_filme()
        sorter=GenericSort(MergeSort,key=lambda filme: filme.get_fost_inchiriat(),reverse=True)
        sorter.sort(lista)
        return lista

    def get_all_filme(self):
        """Returneaza toate filmele"""
        if self.__filme:
            return self.__filme
        else:
            raise ValueError("Nu există filme adăugate")