class BingoSort:
    def __init__(self,key=lambda x:x,reverse=False):
        self.key = key
        self.reverse = reverse

    def sort(self,lista,lung):
        """Complexitate O(N*M),unde N=lung,iar M numarul de elemente distincte"""
        if not self.reverse:
            bingo=min(lista,key=self.key)
            largest=max(lista,key=self.key)
        else:
            bingo = max(lista, key=self.key)
            largest = min(lista, key=self.key)
        nextbingo=largest
        nextpos=0

        while self.key(bingo)!=self.key(nextbingo):
            startpos=nextpos
            for i in range(startpos,lung):
                if self.key(bingo)==self.key(lista[i]):
                    lista[i],lista[nextpos]=lista[nextpos],lista[i]
                    nextpos=nextpos+1
                else:
                    if not self.reverse:
                        if self.key(lista[i]) < self.key(nextbingo):
                            nextbingo = lista[i]
                    else:
                        if self.key(lista[i]) > self.key(nextbingo):
                            nextbingo = lista[i]
            bingo=nextbingo
            nextbingo=largest