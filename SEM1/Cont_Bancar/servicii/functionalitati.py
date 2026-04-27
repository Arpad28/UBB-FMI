from adaugare.tranzactie import creaza_tranzactie
from validare.get import *

def adauga_tranzactie(lista_istoric,lista,tranzactie):
    """
    Adaugă o tranzacție validă in listă
    :param lista_istoric: Istoricul de tranzactii
    :param lista:Lista de tranzacții
    :param tranzactie: Tranzacția validată
    """
    copie=[]
    for x in lista:
        copie.append(x.copy())
    lista_istoric.append(copie)
    lista.append(tranzactie)

def actualizare_tranzactie(lista_istoric,lista,zi,suma,tip):
    """
    Actualizează o tranzacție deja existentă
    :param lista_istoric: Istoricul de tranzactii
    :param lista: Lista de tranzacții deja făcute
    :param zi: Ziua de actualizat
    :param suma: Suma noua
    :param tip: Tipul nou
    """
    if len(lista)==0:
        raise ValueError ("Nu s-a facut nicio tranzacție momentan")
    tranzactie_noua=creaza_tranzactie(zi,suma,tip)
    gasit=False
    copie=[]
    n=len(lista)
    while not gasit:
        for i in range(n):
            if get_zi_tranzactie(lista[i]) == zi:
                for x in lista:
                    copie.append(x.copy())
                lista_istoric.append(copie)
                lista[i]=tranzactie_noua
                gasit=True
    if not gasit:
        raise ValueError (f"Nu există nicio tranzacție în ziua {zi} pentru a actualiza")

def tranzactii_mai_mari_decat_o_valoare(lista,suma_data):
    """
    Returnează tranzacțiile mai mari decât o sumă dată
    :param lista: Lista de tranzacții deja făcute
    :param suma_data: Suma dată
    :return: Returnează tranzacțiile într-o listă
    """
    rezultat=[x for x in lista if get_suma_tranzactie(x)>suma_data]
    return rezultat

def tranzactii_de_un_anumit_tip(lista,tipul_dat):
    """
    Returnează tranzacțiile de un anumit tip
    :param lista: Lista de tranzacții deja făcute
    :param tipul_dat: Tipul dat
    :return: Returnează tranzacțiile într-o listă
    """
    rezultat=[x for x in lista if get_tip_tranzactie(x)==tipul_dat]
    return rezultat

def calculeaza_suma_de_un_anumit_tip(lista,tipul_dat):
    """
    Calculează suma de tipul dat
    :param lista: lista de tranzacții
    :param tipul_dat: tipul dat
    :return: suma de tipul dat
    """
    suma_rezultat=0
    for x in lista:
        if get_tip_tranzactie(x)==tipul_dat:
            suma_rezultat=suma_rezultat+get_suma_tranzactie(x)
    return suma_rezultat

def tranzactii_efectuate_inainte_de_o_zi_si_mai_mari_de_o_suma(zi,suma,lista):
    """
    Returnează listă cu tranzacțiile mai mari decât o sumă și înainte de o zi
    :param lista: Lista de tranzacții
    :param zi:Ziua dată
    :param suma:Suma dată
    :return:O listă cu tranzacțiile mai mari decât o sumă și înainte de o zi
    """
    rezultat=[]
    for x in lista:
        if get_zi_tranzactie(x)<zi and get_suma_tranzactie(x)>suma:
            rezultat.append(x)
    return rezultat

def sterge_tranzactii_in_ziua_data(lista_istoric,ziua_data,lista):
    """
    Șterge tranzacțiile făcute în ziua dată
    :param lista_istoric: Istoricul de tranzactii
    :param ziua_data: Ziua dată
    :param lista: Lista de tranzacții
    :return: Returnează o listă nouă fâră tranzacțiile în ziua dată
    """
    copie = []
    for x in lista:
        copie.append(x.copy())
    lista_istoric.append(copie)
    lista_noua=[x for x in lista if get_zi_tranzactie(x)!=ziua_data]
    return lista_noua

def sterge_tranzactii_de_la_o_perioada(lista_istoric,ziua_initiala,ziua_finala,lista):
    """
    Șterge tranzacțiile într-o perioadă dată
    :param lista_istoric:Istoricul de tranzactii
    :param ziua_initiala: Ziua initială
    :param ziua_finala: Ziua finală
    :param lista: Lista de tranzacții
    :return: Returnează o listă nouă fâră tranzacțiile din acea perioadă
    """
    copie = []
    for x in lista:
        copie.append(x.copy())
    lista_istoric.append(copie)
    if ziua_initiala>ziua_finala:
        aux=ziua_initiala
        ziua_initiala=ziua_finala
        ziua_finala=aux
    lista_noua=[x for x in lista if not ziua_initiala<=get_zi_tranzactie(x)<=ziua_finala]
    return lista_noua

def sterge_tranzactii_de_un_tip(lista_istoric,tipul_dat, lista):
    """
    Șterge tranzacțiile de un anumit tip
    :param lista_istoric:Istoricul de tranzactii
    :param tipul_dat: Tipul dat
    :param lista: Lista de tranzacții
    :return: Returnează o listă nouă fâră tranzacțiile de tipul dat
    """
    copie = []
    for x in lista:
        copie.append(x.copy())
    lista_istoric.append(copie)
    lista_noua = [x for x in lista if get_tip_tranzactie(x)!= tipul_dat]
    return lista_noua

def calculeaza_soldul_la_o_data(lista,ziua_data):
    """
    Calculeaza soldul la o data specificata
    :param lista: Lista de tranzactii
    :param ziua_data: Data la care calculam
    :return: O suma ce reprezinta soldul la o data
    """
    rez=0
    for x in lista:
        if get_zi_tranzactie(x)<=ziua_data:
            if get_tip_tranzactie(x)=="intrare":
                rez=rez+get_suma_tranzactie(x)
            else:
                rez=rez-get_suma_tranzactie(x)
    return rez

def tranzactii_de_un_anumit_tip_ordonate(lista,tipul_dat):
    """
    Calculeaza tranzaciile de un anumit tip si le ordoneaza dupa suma
    :param lista: lista de tranzacții
    :param tipul_dat: tipul dat
    :return: lista ordonata dupa criteriu
    """
    lista_rez=[]
    for x in lista:
        if get_tip_tranzactie(x)==tipul_dat:
            lista_rez.append(x)
    lista_rez=sorted(lista_rez,key=lambda tranzactie: (get_suma_tranzactie(tranzactie),get_zi_tranzactie(tranzactie)))
    return lista_rez

def filtreaza_tranzactii_de_un_anumit_tip(lista,tipul_dat):
    """
    Filtreaza toate tranzactiile de un anumit tip
    :param lista: lista de tranzactii
    :param tipul_dat: tipul dat
    :return: O lista care contine tranzactille de un anumit tip
    """
    rez=[x for x in lista if(get_tip_tranzactie(x)==tipul_dat)]
    return rez

def filtreaza_tranzactii_de_un_anumit_tip_si_mai_mici_decat_o_suma(lista,suma_data,tipul_dat):
    """
    Filtreaza toate tranzactiile de un anumit tip si mai mici decat o suma
    :param lista: Lista de tranzactii
    :param suma_data: suma data
    :param tipul_dat: tipul dat
    :return: O lista are contine tranzactiile de un anumit tip si mai mici decat o suma
    """
    rez=[x for  x in lista if(get_tip_tranzactie(x)==tipul_dat and get_suma_tranzactie(x)<suma_data)]
    return rez