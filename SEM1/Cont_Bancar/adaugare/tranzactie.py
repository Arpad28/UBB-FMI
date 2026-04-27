from validare.get import *

def creaza_tranzactie(zi,suma,tip):
    """
    Creează o tranzacție validă
    :param zi: Ziua când se face tranzacția
    :param suma: Suma tranzacționată
    :param tip: Tipul operației
    :return: Returnează într-un dicționar ziua,suma si tipul tranzacției
    """
    valideaza_suma(suma)
    valideaza_zi(zi)
    valideaza_tip(tip)
    tranzactie=[zi,suma,tip]
    return tranzactie

def afisare_tranzactii(lista):
    """
    Afișează tranzicțiile dorite
    :param lista: Lista de tranzicții făcute
    """
    if len(lista)==0:
        print("Nu există tranzacții cu acest criteriu")
    for x in lista:
        print(f"Ziua:{get_zi_tranzactie(x)}|Suma:{get_suma_tranzactie(x)}|Tip:{get_tip_tranzactie(x)}")