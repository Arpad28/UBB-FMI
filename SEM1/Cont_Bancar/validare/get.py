def valideaza_suma(suma_data):
    """
    Validează dacă am citit o sumă validă
    :param suma_data: Șir de caractere ce trebuie verificat dacă e o sumă
    :return: Returnează suma validă(daca este)
    """
    try:
        suma=float(suma_data)
    except ValueError:
        raise ValueError("Șirul introdus nu este un număr")
    if suma<=0:
        raise ValueError("Suma trebuie să fie pozitivă nenulă")
    return suma

def get_zi_tranzactie(tranzactie):
    """
    Returnează ziua în care a fost făcută tranzactia
    :param tranzactie: Tranzactia mea
    :return: returnează ziua
    """
    return tranzactie[0]

def get_suma_tranzactie(tranzactie):
    """
    Returnează suma tranzacției
    :param tranzactie: Tranzactia mea
    :return: returnează suma
    """
    return float(tranzactie[1])

def get_tip_tranzactie(tranzactie):
    """
     Returnează tipul tranzacției
     :param tranzactie: Tranzactia mea
     :return: returnează tipul
     """
    return tranzactie[2]

def valideaza_zi(ziua_data):
    """
    Validează dacă am citit o zi validă
    :param ziua_data: Șir de caractere ce trebuie verificat dacă e o zi validă
    :return: Returnează ziua valid dacă e valid
    """
    try:
        zi=int(ziua_data)
    except ValueError:
        raise ValueError("Șirul introdus nu este un număr natural")
    if not (1 <= zi <= 31):
        raise ValueError("Ziua trebuie să fie între 1 și 31")
    return zi

def valideaza_tip(tipul_dat):
    """
    Validează tipul dat
    :param tipul_dat:Tipul dat
    :return: Returnează tipul dat dacă e valid
    """
    if tipul_dat not in ["intrare", "iesire"]:
        raise ValueError("Tipul trebuie să fie de 'intrare' sau de 'ieșire'")
    return tipul_dat

def afiseaza_suma(suma_data):
    """
    Afișează suma/soldul
    :param suma_data: suma dată
    :return: returnează o sumă
    """
    print(f"Soldul total este: {suma_data}")
