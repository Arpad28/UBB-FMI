class Validator():
    def __init__(self,zi,luna,ora,minute):
        """Initializeaza o clasa de tip Validator care va valida datele de intrare
        :param zi: ziua de validat
        :param luna: luna de validat
        :param ora: ora de validat
        :param minute: minuta de validat
        """
        self.zi=zi
        self.luna=luna
        self.ora=ora
        self.minute=minute

    def valideaza(self):
        """Functia valideaza datele de intrare si ridica o lista cu erori
        :raises:Da raise la toate erorile pe care le intampinam in timpul validarii
        """
        try:
            zi = int(self.zi)
            erori = ""
            if zi < 0 or zi > 31:
                erori += "Ziua trebuie sa fie intre 0 si 31\n"
            luna = int(self.luna)
            if luna < 0 or luna > 12:
                erori += "Luna trebuie sa fie intre 0 si 12\n"
            ora = int(self.ora)
            if ora < 0 or ora > 24:
                erori += "Ora trebuie sa fie intre 0 si 24\n"
            minute = int(self.minute)
            if minute < 0 or minute > 59:
                erori += "Minutele trebuie sa fie intre 0 si 59\n"
        except:
                raise ValueError("Datele nu sunt de tip int")
        if erori != "":
            raise ValueError(erori)