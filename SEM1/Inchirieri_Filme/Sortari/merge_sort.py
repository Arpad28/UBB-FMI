class MergeSort:
    def __init__(self, key=lambda x: x, reverse=False):
        self.key = key
        self.reverse = reverse

    def merge(self, lista, st, mij, dr):
        n1 = mij - st + 1
        n2 = dr - mij

        left = [0] * n1
        right = [0] * n2

        for i in range(n1):
            left[i] = lista[st + i]
        for i in range(n2):
            right[i] = lista[mij + i + 1]

        i = j = 0
        k = st

        while i < n1 and j < n2:
            if (self.key(left[i]) <= self.key(right[j])) ^ self.reverse:
                lista[k] = left[i]
                i += 1
            else:
                lista[k] = right[j]
                j += 1
            k += 1

        while i < n1:
            lista[k] = left[i]
            i += 1
            k += 1

        while j < n2:
            lista[k] = right[j]
            j += 1
            k += 1

    def sort(self, lista, st, dr):
        """Complexitate Teta(nlogn)"""
        if st < dr:
            mij = (st + dr) // 2
            self.sort(lista, st, mij)
            self.sort(lista, mij + 1, dr)
            self.merge(lista, st, mij, dr)
