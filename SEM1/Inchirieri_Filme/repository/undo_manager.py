class UndoManager:
    def __init__(self):
        self.__undo_list=[]

    def inregistreaza(self,functie_undo):
        self.__undo_list.append(functie_undo)

    def undo(self):
        if not self.__undo_list:
            raise ValueError("Nu mai ai la ce apela funcția undo")
        functie=self.__undo_list.pop()
        functie()