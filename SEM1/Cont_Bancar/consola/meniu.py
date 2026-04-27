from adaugare.tranzactie import *
from servicii.functionalitati import*
from undo.undo import undo

def meniu_de_rulare():
    lista=[]
    lista_istoric=[]
    comenzi="""
    === MENIU CONT BANCAR ===
    1.Adaugă tranzacție
    2.Actualizează o tranzacție
    3.Caută tranzacții după un anumit criteriu(dupa tip/dupa interval/mai mari decat o suma)
    4.Șterge tranzacții după un anumit criteriu
    5.Cere rapoarte după un anumit criteriu
    6.Filtrează tranzacții după un anumit criteriu
    7.Efectuază undo la ultima operație
    8.Afișează toate tranzacțiile
    9.Ieșire
    ===============================
    """
    while True:
        print(comenzi)
        operatie=input("Alege o opțiune: ").strip()
        if operatie== "1":
           try:
               zi=input("Ziua: ").strip()
               suma=input("Suma: ").strip()
               tip=input("Tipul(intrare/iesire): ").strip()
               tranzactie=creaza_tranzactie(zi,suma,tip)
               adauga_tranzactie(lista_istoric,lista,tranzactie)
               print("Tranzacție adăugată cu succes")
           except ValueError as eroare:
               print("Tranzacție eșuată: ",eroare)
        elif operatie == "2":
            try:
                zi = input("Ziua de actualizat: ").strip()
                suma =input("Suma nouă: ").strip()
                tip = input("Tipul nou(iesire/intrare): ").strip()
                actualizare_tranzactie(lista_istoric,lista, zi, suma, tip)
                print("Tranzacția a fost actualizată cu succes")
            except ValueError as eroare:
                print("Eroare: ", eroare)
        elif operatie== "3":
            comenzi_afisari = """
    === MENIU CĂUTARE ===
    1.Afișează tranzacțiile cu suma mai mari decât o valoare
    2.Afișează tranzacțiile efectuate înainte de o zi și mai mari decât o sumă
    3.Afișează tranzacțiile de un anumit tip
    ===============================
    """
            print(comenzi_afisari)
            operatie_afisari=input("Alege o opțiune:")
            if operatie_afisari== "1":
                try:
                    suma_data = input("Introdu o sumă: ").strip()
                    suma_data=valideaza_suma(suma_data)
                    rezultat = tranzactii_mai_mari_decat_o_valoare(lista, suma_data)
                    afisare_tranzactii(rezultat)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            elif operatie_afisari== "2":
                try:
                    ziua_data=input("Introdu ziua: ").strip()
                    ziua_data=valideaza_zi(ziua_data)
                    suma_data=input("Introdu suma: ").strip()
                    suma_data=valideaza_suma(suma_data)
                    rezultat=tranzactii_efectuate_inainte_de_o_zi_si_mai_mari_de_o_suma(ziua_data, suma_data,lista)
                    afisare_tranzactii(rezultat)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            elif operatie_afisari== "3":
                try:
                    tipul_dat=input("Introdu un tip(intrare/iesire): ").strip()
                    valideaza_tip(tipul_dat)
                    rezultat = tranzactii_de_un_anumit_tip(lista, tipul_dat)
                    afisare_tranzactii(rezultat)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            else:
                print("Opțiune inexistentă")
        elif operatie=="4":
            comenzi_stergeri = """
    === MENIU ȘTERGERI ===
    1.Șterge tranzacțiile dintr-o zi
    2.Șterge tranzacțiile de la o perioadă dată
    3.Șterge toate tranzacțiile de un anumit tip
    ===============================
    """
            print(comenzi_stergeri)
            operatie_stergeri=input("Alege o opțiune: ")
            if operatie_stergeri== "1":
                try:
                    ziua_data=input("Introdu ziua: ").strip()
                    valideaza_zi(ziua_data)
                    lista=sterge_tranzactii_in_ziua_data(lista_istoric,ziua_data,lista)
                    print("Tranzacție ștearsă cu succes")
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            elif operatie_stergeri== "2":
                try:
                    ziua_initiala = input("Introdu ziua inițială: ").strip()
                    valideaza_zi(ziua_initiala)
                    ziua_finala= input("Introdu ziua finală ").strip()
                    valideaza_zi(ziua_finala)
                    lista=sterge_tranzactii_de_la_o_perioada(lista_istoric,ziua_initiala,ziua_finala,lista)
                    print("Tranzacție ștearsă cu succes")
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            elif operatie_stergeri== "3":
                try:
                    tipul_dat=input("Introdu un tip(intrare/iesire): ").strip()
                    valideaza_tip(tipul_dat)
                    lista = sterge_tranzactii_de_un_tip(lista_istoric,tipul_dat, lista)
                    print("Tranzacție ștearsă cu succes")
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            else:
                print("Opțiune inexistentă")
        elif operatie== "5":
            comenzi_rapoarte = """
    === MENIU RAPOARTE ===
    1.Cere suma totală a tranzacțiilor de un anumit tip
    2.Cere soldul contului la o dată specificată
    3.Cere toate tranzacțiile de un anumit tip ordonate după sumă
    ===============================
    """
            print(comenzi_rapoarte)
            operatie_rapoarte=input("Alege o opțiune: ")
            if operatie_rapoarte== "1":
                try:
                    tipul_dat=input("Introdu un tip(intrare/iesire): ").strip()
                    valideaza_tip(tipul_dat)
                    rez=calculeaza_suma_de_un_anumit_tip(lista,tipul_dat)
                    afiseaza_suma(rez)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            elif operatie_rapoarte== "2":
                try:
                    ziua_data=input("Introdu ziua: ").strip()
                    valideaza_zi(ziua_data)
                    rez=calculeaza_soldul_la_o_data(lista,ziua_data)
                    afiseaza_suma(rez)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            elif operatie_rapoarte== "3":
                try:
                    tipul_dat = input("Introdu un tip(intrare/iesire): ").strip()
                    valideaza_tip(tipul_dat)
                    lista_rez=tranzactii_de_un_anumit_tip_ordonate(lista,tipul_dat)
                    afisare_tranzactii(lista_rez)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            else:
                print("Opțiune inexistentă")
        elif operatie=="6":
            comenzi_filtrare= """
        === MENIU FILTRARE ===
        1.Filtrează tranzacțiile după un anumit tip
        2.Filtrează tranzacțiile mai mici decât o sumă și de un anumit tip
        ===============================
        """
            print(comenzi_filtrare)
            operatie_filtrare=input("Alege o opțiune: ")
            if operatie_filtrare== "1":
                try:
                    tipul_dat = input("Introdu un tip(intrare/iesire): ").strip()
                    valideaza_tip(tipul_dat)
                    lista_rez=filtreaza_tranzactii_de_un_anumit_tip(lista,tipul_dat)
                    afisare_tranzactii(lista_rez)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            elif operatie_filtrare== "2":
                try:
                    suma_data=input("Introdu o sumă: ").strip()
                    valideaza_zi(suma_data)
                    tipul_dat = input("Introdu un tip(intrare/iesire): ").strip()
                    valideaza_tip(tipul_dat)
                    lista_rez = (filtreaza_tranzactii_de_un_anumit_tip_si_mai_mici_decat_o_suma(lista,suma_data,tipul_dat))
                    afisare_tranzactii(lista_rez)
                except ValueError as eroare:
                    print("Eroare: ", eroare)
            else:
                print("Opțiune inexistentă")
        elif operatie=="7":
            try:
                undo(lista_istoric,lista)
                print("Operația undo a fost efectuată cu succes")
            except ValueError as eroare:
                print("Eroare: ", eroare)
        elif operatie=="8":
            afisare_tranzactii(lista)
        elif operatie== "9":
            print("La revedere")
            break
        else:
            print("Opțiune inexistentă")
