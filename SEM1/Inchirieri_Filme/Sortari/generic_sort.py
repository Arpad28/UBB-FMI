class GenericSort:
    def __init__(self, sort_class, key=lambda x: x, reverse=False):
        """
        Initializează sortarea generică.
        :param sort_class: Clasa de sortare (BingoSort sau MergeSort)
        :param key: Funcția pentru cheie
        :param reverse: Sortare descrescătoare dacă e True
        """
        self.sort_class = sort_class
        self.key = key
        self.reverse = reverse
        self.sorter = sort_class(key=self.key, reverse=self.reverse)

    def sort(self, lista):
        """Sortează lista folosind clasa selectată."""
        try:
            self.sorter.sort(lista, len(lista))#Bingo
        except TypeError:
            self.sorter.sort(lista, 0, len(lista) - 1)#Merge
        return lista
